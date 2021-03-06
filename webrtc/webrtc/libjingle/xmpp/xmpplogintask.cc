/*
 *  Copyright 2004 The WebRTC Project Authors. All rights reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include "webrtc/libjingle/xmpp/xmpplogintask.h"

#include <string>
#include <vector>

#include "webrtc/libjingle/xmllite/xmlelement.h"
#include "webrtc/libjingle/xmpp/constants.h"
#include "webrtc/libjingle/xmpp/jid.h"
#include "webrtc/libjingle/xmpp/saslmechanism.h"
#include "webrtc/libjingle/xmpp/xmppengineimpl.h"
#include "webrtc/base/base64.h"
#include "webrtc/base/common.h"

using rtc::ConstantLabel;

namespace buzz {

#ifdef _DEBUG
const ConstantLabel XmppLoginTask::LOGINTASK_STATES[] = {
  KLABEL(LOGINSTATE_INIT),
  KLABEL(LOGINSTATE_STREAMSTART_SENT),
  KLABEL(LOGINSTATE_STARTED_XMPP),
  KLABEL(LOGINSTATE_TLS_INIT),
  KLABEL(LOGINSTATE_AUTH_INIT),
  KLABEL(LOGINSTATE_BIND_INIT),
  KLABEL(LOGINSTATE_TLS_REQUESTED),
  KLABEL(LOGINSTATE_SASL_RUNNING),
  KLABEL(LOGINSTATE_BIND_REQUESTED),
  KLABEL(LOGINSTATE_SESSION_REQUESTED),
  KLABEL(LOGINSTATE_DONE),
  LASTLABEL
};
#endif  // _DEBUG
XmppLoginTask::XmppLoginTask(XmppEngineImpl * pctx) :
  pctx_(pctx),
  authNeeded_(true),
  allowNonGoogleLogin_(true),
  state_(LOGINSTATE_INIT),
  pelStanza_(NULL),
  isStart_(false),
  iqId_(STR_EMPTY),
  pelFeatures_(),
  fullJid_(STR_EMPTY),
  streamId_(STR_EMPTY),
  pvecQueuedStanzas_(new std::vector<XmlElement *>()),
  sasl_mech_() {
}

XmppLoginTask::~XmppLoginTask() {
  for (size_t i = 0; i < pvecQueuedStanzas_->size(); i += 1)
    delete (*pvecQueuedStanzas_)[i];
}

void
XmppLoginTask::IncomingStanza(const XmlElement *element, bool isStart) {
  pelStanza_ = element;
  isStart_ = isStart;
  Advance();
  pelStanza_ = NULL;
  isStart_ = false;
}

const XmlElement *
XmppLoginTask::NextStanza() {
  const XmlElement * result = pelStanza_;
  pelStanza_ = NULL;
  return result;
}

bool
XmppLoginTask::Advance() {

  for (;;) {

    const XmlElement * element = NULL;

#if _DEBUG
    LOG(LS_VERBOSE) << "XmppLoginTask::Advance - "
      << rtc::ErrorName(state_, LOGINTASK_STATES);
#endif  // _DEBUG
    printf("XmppLoginTask::Advance - %d\n", state_);

    switch (state_) {

      case LOGINSTATE_INIT: {
        pctx_->RaiseReset();
        pelFeatures_.reset(NULL);

        // The proper domain to verify against is the real underlying
        // domain - i.e., the domain that owns the JID.  Our XmppEngineImpl
        // also allows matching against a proxy domain instead, if it is told
        // to do so - see the implementation of XmppEngineImpl::StartTls and
        // XmppEngine::SetTlsServerDomain to see how you can use that feature
        pctx_->InternalSendStart(pctx_->user_jid_.domain());
        state_ = LOGINSTATE_STREAMSTART_SENT;
        break;
      }

      case LOGINSTATE_STREAMSTART_SENT: {
        if (NULL == (element = NextStanza()))
          return true;

        if (!isStart_ || !HandleStartStream(element))
          return Failure(XmppEngine::ERROR_VERSION);

        state_ = LOGINSTATE_STARTED_XMPP;
        return true;
      }

      case LOGINSTATE_STARTED_XMPP: {
        if (NULL == (element = NextStanza()))
          return true;

        if (!HandleFeatures(element))
          return Failure(XmppEngine::ERROR_VERSION);

        bool tls_present = (GetFeature(QN_TLS_STARTTLS) != NULL);
        // Error if TLS required but not present.
        if (pctx_->tls_option_ == buzz::TLS_REQUIRED && !tls_present) {
          return Failure(XmppEngine::ERROR_TLS);
        }
        // Use TLS if required or enabled, and also available
        if ((pctx_->tls_option_ == buzz::TLS_REQUIRED ||
            pctx_->tls_option_ == buzz::TLS_ENABLED) && tls_present) {
          state_ = LOGINSTATE_TLS_INIT;
          continue;
        }

		printf("register flag value: %d\n", pctx_->GetRegister());
		if (pctx_->GetRegister()) {
          state_ = LOGINSTATE_REG_INIT;
    	  continue;
		}

        if (authNeeded_) {
          state_ = LOGINSTATE_AUTH_INIT;
          continue;
        }

        state_ = LOGINSTATE_BIND_INIT;
        continue;
      }

      case LOGINSTATE_TLS_INIT: {
        const XmlElement * pelTls = GetFeature(QN_TLS_STARTTLS);
        if (!pelTls)
          return Failure(XmppEngine::ERROR_TLS);

        XmlElement el(QN_TLS_STARTTLS, true);
        pctx_->InternalSendStanza(&el);
        state_ = LOGINSTATE_TLS_REQUESTED;
        continue;
      }

      case LOGINSTATE_TLS_REQUESTED: {
        if (NULL == (element = NextStanza()))
          return true;
        if (element->Name() != QN_TLS_PROCEED)
          return Failure(XmppEngine::ERROR_TLS);

        // The proper domain to verify against is the real underlying
        // domain - i.e., the domain that owns the JID.  Our XmppEngineImpl
        // also allows matching against a proxy domain instead, if it is told
        // to do so - see the implementation of XmppEngineImpl::StartTls and
        // XmppEngine::SetTlsServerDomain to see how you can use that feature
        pctx_->StartTls(pctx_->user_jid_.domain());
        pctx_->tls_option_ = buzz::TLS_ENABLED;
        state_ = LOGINSTATE_INIT;
        continue;
      }

	  case LOGINSTATE_REG_INIT: {
  	    // OK, let's start it.
  	    XmlElement reg_query(QN_IQ);
		
		iqId_ = pctx_->NextId();

		reg_query.AddAttr(QN_TYPE, "get");
		reg_query.AddAttr(QN_ID, iqId_);
		reg_query.AddAttr(QN_TO, pctx_->GetUser().domain());
		
		reg_query.AddElement(new XmlElement(QN_REGISTER_QUERY, true));

  	    pctx_->InternalSendStanza(&reg_query);
  	    state_ = LOGINSTATE_REG_RUNNING;
		
		continue;
	  }

	  case LOGINSTATE_REG_RUNNING: {
		if (NULL == (element = NextStanza()))
		  return true;

		if (element->Name() != QN_IQ || element->Attr(QN_ID) != iqId_ ||
			element->Attr(QN_TYPE) == "get" || element->Attr(QN_TYPE) == "set") {
		  return true;
		}

		if (element->Attr(QN_TYPE) != "result" || element->FirstElement() == NULL ||
			element->FirstElement()->Name() != QN_REGISTER_QUERY) {
		  return Failure(XmppEngine::ERROR_REG);
		}

  	    // OK, let's start it.
  	    XmlElement iq(QN_IQ);
		
		iqId_ = pctx_->NextId();

		iq.AddAttr(QN_TYPE, "set");
		iq.AddAttr(QN_ID, iqId_);
		iq.AddAttr(QN_TO, pctx_->GetUser().domain());
		
		XmlElement* query = new XmlElement(QN_REGISTER_QUERY, true);

		XmlElement* username = new XmlElement(QN_USERNAME, false);
		username->AddText(pctx_->GetUser().node());

		XmlElement* passwd = new XmlElement(QN_PASSWRD, false);
		passwd->AddText("11111111");

		query->AddElement(username);
        query->AddElement(passwd);
		iq.AddElement(query);

		pctx_->InternalSendStanza(&iq);
		state_ = LOGINSTATE_REG_REQUESTED;

		printf("start requested....\n");
		
		continue;
	  }
	  
      case LOGINSTATE_REG_REQUESTED: {
	  	printf("starting requested....\n");
		
        if (NULL == (element = NextStanza()))
          return true;
        
        if (element->Name() != QN_IQ || element->Attr(QN_ID) != iqId_ ||
          element->Attr(QN_TYPE) == "get" || element->Attr(QN_TYPE) == "set") {
          printf("requested err1, %s\n", iqId_.c_str());
          return false;
        }
        
        if (element->Attr(QN_TYPE) != "result") {
		  printf("requested err2!\n");
          return Failure(XmppEngine::ERROR_REG);
        }

		pctx_->SetRegister(false);

		if (authNeeded_) {
		  state_ = LOGINSTATE_AUTH_INIT;
		} else {
		  state_ = LOGINSTATE_BIND_INIT;
		}

		printf("requested ok!\n");

		continue;
	  }
	  
      case LOGINSTATE_AUTH_INIT: {
        const XmlElement * pelSaslAuth = GetFeature(QN_SASL_MECHANISMS);
        if (!pelSaslAuth) {
          return Failure(XmppEngine::ERROR_AUTH);
        }

        // Collect together the SASL auth mechanisms presented by the server
        std::vector<std::string> mechanisms;
        for (const XmlElement * pelMech =
             pelSaslAuth->FirstNamed(QN_SASL_MECHANISM);
             pelMech;
             pelMech = pelMech->NextNamed(QN_SASL_MECHANISM)) {

          mechanisms.push_back(pelMech->BodyText());
        }

        // Given all the mechanisms, choose the best
        std::string choice(pctx_->ChooseBestSaslMechanism(mechanisms, pctx_->IsEncrypted()));
        if (choice.empty()) {
          return Failure(XmppEngine::ERROR_AUTH);
        }

        // No recognized auth mechanism - that's an error
        sasl_mech_.reset(pctx_->GetSaslMechanism(choice));
        if (!sasl_mech_) {
          return Failure(XmppEngine::ERROR_AUTH);
        }

        // OK, let's start it.
        XmlElement * auth = sasl_mech_->StartSaslAuth();
        if (auth == NULL) {
          return Failure(XmppEngine::ERROR_AUTH);
        }
        if (allowNonGoogleLogin_) {
          // Setting the following two attributes is required to support
          // non-google ids.

          // Allow login with non-google id accounts.
          auth->SetAttr(QN_GOOGLE_ALLOW_NON_GOOGLE_ID_XMPP_LOGIN, "true");

          // Allow login with either the non-google id or the friendly email.
          auth->SetAttr(QN_GOOGLE_AUTH_CLIENT_USES_FULL_BIND_RESULT, "true");
        }

        pctx_->InternalSendStanza(auth);
        delete auth;
        state_ = LOGINSTATE_SASL_RUNNING;
        continue;
      }

      case LOGINSTATE_SASL_RUNNING: {
        if (NULL == (element = NextStanza()))
          return true;
        if (element->Name().Namespace() != NS_SASL)
          return Failure(XmppEngine::ERROR_AUTH);
        if (element->Name() == QN_SASL_CHALLENGE) {
          XmlElement * response = sasl_mech_->HandleSaslChallenge(element);
          if (response == NULL) {
            return Failure(XmppEngine::ERROR_AUTH);
          }
          pctx_->InternalSendStanza(response);
          delete response;
          state_ = LOGINSTATE_SASL_RUNNING;
          continue;
        }
        if (element->Name() != QN_SASL_SUCCESS) {
          return Failure(XmppEngine::ERROR_UNAUTHORIZED);
        }

        // Authenticated!
        authNeeded_ = false;
        state_ = LOGINSTATE_INIT;
        continue;
      }

      case LOGINSTATE_BIND_INIT: {
        const XmlElement * pelBindFeature = GetFeature(QN_BIND_BIND);
        const XmlElement * pelSessionFeature = GetFeature(QN_SESSION_SESSION);
        if (!pelBindFeature || !pelSessionFeature)
          return Failure(XmppEngine::ERROR_BIND);

        XmlElement iq(QN_IQ);
        iq.AddAttr(QN_TYPE, "set");

        iqId_ = pctx_->NextId();
        iq.AddAttr(QN_ID, iqId_);
        iq.AddElement(new XmlElement(QN_BIND_BIND, true));

        if (pctx_->requested_resource_ != STR_EMPTY) {
          iq.AddElement(new XmlElement(QN_BIND_RESOURCE), 1);
          iq.AddText(pctx_->requested_resource_, 2);
        }
        pctx_->InternalSendStanza(&iq);
        state_ = LOGINSTATE_BIND_REQUESTED;
        continue;
      }

      case LOGINSTATE_BIND_REQUESTED: {
        if (NULL == (element = NextStanza()))
          return true;

        if (element->Name() != QN_IQ || element->Attr(QN_ID) != iqId_ ||
            element->Attr(QN_TYPE) == "get" || element->Attr(QN_TYPE) == "set")
          return true;

        if (element->Attr(QN_TYPE) != "result" || element->FirstElement() == NULL ||
            element->FirstElement()->Name() != QN_BIND_BIND)
          return Failure(XmppEngine::ERROR_BIND);

        fullJid_ = Jid(element->FirstElement()->TextNamed(QN_BIND_JID));
        if (!fullJid_.IsFull()) {
          return Failure(XmppEngine::ERROR_BIND);
        }

        // now request session
        XmlElement iq(QN_IQ);
        iq.AddAttr(QN_TYPE, "set");

        iqId_ = pctx_->NextId();
        iq.AddAttr(QN_ID, iqId_);
        iq.AddElement(new XmlElement(QN_SESSION_SESSION, true));
        pctx_->InternalSendStanza(&iq);

        state_ = LOGINSTATE_SESSION_REQUESTED;
        continue;
      }

      case LOGINSTATE_SESSION_REQUESTED: {
        if (NULL == (element = NextStanza()))
          return true;
        if (element->Name() != QN_IQ || element->Attr(QN_ID) != iqId_ ||
            element->Attr(QN_TYPE) == "get" || element->Attr(QN_TYPE) == "set")
          return false;

        if (element->Attr(QN_TYPE) != "result")
          return Failure(XmppEngine::ERROR_BIND);

        pctx_->SignalBound(fullJid_);
        FlushQueuedStanzas();
        state_ = LOGINSTATE_DONE;
        return true;
      }

      case LOGINSTATE_DONE:
        return false;
    }
  }
}

bool
XmppLoginTask::HandleStartStream(const XmlElement *element) {

  if (element->Name() != QN_STREAM_STREAM)
    return false;

  if (element->Attr(QN_XMLNS) != "jabber:client")
    return false;

  if (element->Attr(QN_VERSION) != "1.0")
    return false;

  if (!element->HasAttr(QN_ID))
    return false;

  streamId_ = element->Attr(QN_ID);

  return true;
}

bool
XmppLoginTask::HandleFeatures(const XmlElement *element) {
  if (element->Name() != QN_STREAM_FEATURES)
    return false;

  pelFeatures_.reset(new XmlElement(*element));
  return true;
}

const XmlElement *
XmppLoginTask::GetFeature(const QName & name) {
  return pelFeatures_->FirstNamed(name);
}

bool
XmppLoginTask::Failure(XmppEngine::Error reason) {
  state_ = LOGINSTATE_DONE;
  pctx_->SignalError(reason, 0);
  return false;
}

void
XmppLoginTask::OutgoingStanza(const XmlElement * element) {
  XmlElement * pelCopy = new XmlElement(*element);
  pvecQueuedStanzas_->push_back(pelCopy);
}

void
XmppLoginTask::FlushQueuedStanzas() {
  for (size_t i = 0; i < pvecQueuedStanzas_->size(); i += 1) {
    pctx_->InternalSendStanza((*pvecQueuedStanzas_)[i]);
    delete (*pvecQueuedStanzas_)[i];
  }
  pvecQueuedStanzas_->clear();
}

}
