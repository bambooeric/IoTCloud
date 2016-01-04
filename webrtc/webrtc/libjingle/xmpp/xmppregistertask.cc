/*
 *  Copyright 2004 The WebRTC Project Authors. All rights reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include "webrtc/libjingle/xmpp/xmppregistertask.h"

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
const ConstantLabel XmppRegisterTask::REGITERTASK_STATES[] = {
  KLABEL(REGITERSTATE_INIT),
  KLABEL(REGITERSTATE_STREAMSTART_SENT),
  KLABEL(REGITERSTATE_STARTED_XMPP),
  KLABEL(REGITERSTATE_TLS_INIT),
  KLABEL(REGITERSTATE_AUTH_INIT),
  KLABEL(REGITERSTATE_BIND_INIT),
  KLABEL(REGITERSTATE_TLS_REQUESTED),
  KLABEL(REGITERSTATE_SASL_RUNNING),
  KLABEL(REGITERSTATE_BIND_REQUESTED),
  KLABEL(REGITERSTATE_SESSION_REQUESTED),
  KLABEL(REGITERSTATE_DONE),
  LASTLABEL
};
#endif  // _DEBUG
XmppRegisterTask::XmppRegisterTask(XmppEngineImpl * pctx) :
  pctx_(pctx),
  authNeeded_(true),
  allowNonGoogleLogin_(true),
  state_(REGISTERSTATE_INIT),
  pelStanza_(NULL),
  isStart_(false),
  iqId_(STR_EMPTY),
  pelFeatures_(),
  fullJid_(STR_EMPTY),
  streamId_(STR_EMPTY),
  pvecQueuedStanzas_(new std::vector<XmlElement *>()),
  sasl_mech_() {
}

XmppRegisterTask::~XmppRegisterTask() {
  for (size_t i = 0; i < pvecQueuedStanzas_->size(); i += 1)
    delete (*pvecQueuedStanzas_)[i];
}

void
XmppRegisterTask::IncomingStanza(const XmlElement *element, bool isStart) {
  pelStanza_ = element;
  isStart_ = isStart;
  Advance();
  pelStanza_ = NULL;
  isStart_ = false;
}

const XmlElement *
XmppRegisterTask::NextStanza() {
  const XmlElement * result = pelStanza_;
  pelStanza_ = NULL;
  return result;
}

bool
XmppRegisterTask::Advance() {

  for (;;) {

    const XmlElement * element = NULL;

#if _DEBUG
    LOG(LS_VERBOSE) << "XmppRegisterTask::Advance - "
      << rtc::ErrorName(state_, REGITERTASK_STATES);
#endif  // _DEBUG
    printf("XmppRegisterTask::Advance - %d\n", state_);

    switch (state_) {

      case REGISTERSTATE_INIT: {
        pctx_->RaiseReset();
        pelFeatures_.reset(NULL);

        // The proper domain to verify against is the real underlying
        // domain - i.e., the domain that owns the JID.  Our XmppEngineImpl
        // also allows matching against a proxy domain instead, if it is told
        // to do so - see the implementation of XmppEngineImpl::StartTls and
        // XmppEngine::SetTlsServerDomain to see how you can use that feature
        pctx_->InternalSendStart(pctx_->user_jid_.domain());
        state_ = REGISTERSTATE_STREAMSTART_SENT;
        break;
      }

      case REGISTERSTATE_STREAMSTART_SENT: {
	  	printf("REGISTERSTATE_STREAMSTART_SENT 000\n");
		
        if (NULL == (element = NextStanza()))
          return true;
		
		printf("REGISTERSTATE_STREAMSTART_SENT 111\n");

        if (!isStart_ || !HandleStartStream(element))
          return Failure(XmppEngine::ERROR_VERSION);
		
		printf("REGISTERSTATE_STREAMSTART_SENT 222\n");

        state_ = REGISTERSTATE_STARTED_XMPP;
        return true;
      }

      case REGISTERSTATE_STARTED_XMPP: {
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
          state_ = REGISTERSTATE_TLS_INIT;
          continue;
        }

        state_ = REGISTERSTATE_REG_INIT;
        continue;
      }

      case REGISTERSTATE_TLS_INIT: {
        const XmlElement * pelTls = GetFeature(QN_TLS_STARTTLS);
        if (!pelTls)
          return Failure(XmppEngine::ERROR_TLS);

        XmlElement el(QN_TLS_STARTTLS, true);
        pctx_->InternalSendStanza(&el);
        state_ = REGISTERSTATE_TLS_REQUESTED;
        continue;
      }

      case REGISTERSTATE_TLS_REQUESTED: {
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
        state_ = REGISTERSTATE_INIT;
        continue;
      }

	  case REGISTERSTATE_REG_INIT: {
  	    // OK, let's start it.
  	    XmlElement reg_query(QN_IQ);
		
		iqId_ = pctx_->NextId();

		reg_query.AddAttr(QN_TYPE, "get");
		reg_query.AddAttr(QN_ID, iqId_);
		reg_query.AddAttr(QN_ID, pctx_->GetUser().domain());
		
		reg_query.AddElement(new XmlElement(QN_REGISTER_QUERY, true));

  	    pctx_->InternalSendStanza(&reg_query);
  	    state_ = REGISTERSTATE_REG_RUNNING;
		
		continue;
	  }

	  case REGISTERSTATE_REG_RUNNING: {
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
  	    XmlElement reg_query(QN_IQ);
		
		iqId_ = pctx_->NextId();

		reg_query.AddAttr(QN_TYPE, "set");
		reg_query.AddAttr(QN_ID, iqId_);
		reg_query.AddAttr(QN_ID, pctx_->GetUser().domain());
		
		reg_query.AddElement(new XmlElement(QN_REGISTER_QUERY, true));

		continue;
	  }
	  
      case REGISTERSTATE_DONE:
        return false;
    }
  }
}

bool
XmppRegisterTask::HandleStartStream(const XmlElement *element) {

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
XmppRegisterTask::HandleFeatures(const XmlElement *element) {
  if (element->Name() != QN_STREAM_FEATURES)
    return false;

  pelFeatures_.reset(new XmlElement(*element));
  return true;
}

const XmlElement *
XmppRegisterTask::GetFeature(const QName & name) {
  return pelFeatures_->FirstNamed(name);
}

bool
XmppRegisterTask::Failure(XmppEngine::Error reason) {
  state_ = REGISTERSTATE_DONE;
  pctx_->SignalError(reason, 0);
  return false;
}

void
XmppRegisterTask::OutgoingStanza(const XmlElement * element) {
  XmlElement * pelCopy = new XmlElement(*element);
  pvecQueuedStanzas_->push_back(pelCopy);
}

void
XmppRegisterTask::FlushQueuedStanzas() {
  for (size_t i = 0; i < pvecQueuedStanzas_->size(); i += 1) {
    pctx_->InternalSendStanza((*pvecQueuedStanzas_)[i]);
    delete (*pvecQueuedStanzas_)[i];
  }
  pvecQueuedStanzas_->clear();
}

}
