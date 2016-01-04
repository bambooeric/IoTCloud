/*
 *  Copyright 2004 The WebRTC Project Authors. All rights reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef WEBRTC_LIBJINGLE_XMPP_REGITERTASK_H_
#define WEBRTC_LIBJINGLE_XMPP_REGITERTASK_H_

#include <string>
#include <vector>

#include "webrtc/libjingle/xmpp/jid.h"
#include "webrtc/libjingle/xmpp/xmppengine.h"
#include "webrtc/base/logging.h"
#include "webrtc/base/scoped_ptr.h"

namespace buzz {

class XmlElement;
class XmppEngineImpl;
class SaslMechanism;


// TODO: Rename to RegisterTask.
class XmppRegisterTask {

public:
  XmppRegisterTask(XmppEngineImpl *pctx);
  ~XmppRegisterTask();

  bool IsDone()
    { return state_ == REGISTERSTATE_DONE; }
  void IncomingStanza(const XmlElement * element, bool isStart);
  void OutgoingStanza(const XmlElement *element);
  void set_allow_non_google_login(bool b)
    { allowNonGoogleLogin_ = b; }

private:
  enum RegisterTaskState {
    REGISTERSTATE_INIT = 0,
    REGISTERSTATE_STREAMSTART_SENT,
    REGISTERSTATE_STARTED_XMPP,
    REGISTERSTATE_TLS_INIT,
    REGISTERSTATE_REG_INIT,
    REGISTERSTATE_TLS_REQUESTED,
    REGISTERSTATE_REG_RUNNING,
    REGISTERSTATE_DONE,
  };

  const XmlElement * NextStanza();
  bool Advance();
  bool HandleStartStream(const XmlElement * element);
  bool HandleFeatures(const XmlElement * element);
  const XmlElement * GetFeature(const QName & name);
  bool Failure(XmppEngine::Error reason);
  void FlushQueuedStanzas();

  XmppEngineImpl * pctx_;
  bool authNeeded_;
  bool allowNonGoogleLogin_;
  RegisterTaskState state_;
  const XmlElement * pelStanza_;
  bool isStart_;
  std::string iqId_;
  rtc::scoped_ptr<XmlElement> pelFeatures_;
  Jid fullJid_;
  std::string streamId_;
  rtc::scoped_ptr<std::vector<XmlElement *> > pvecQueuedStanzas_;

  rtc::scoped_ptr<SaslMechanism> sasl_mech_;

#ifdef _DEBUG
  static const rtc::ConstantLabel REGISTERTASK_STATES[];
#endif  // _DEBUG
};

}

#endif  //  WEBRTC_LIBJINGLE_XMPP_LOGINTASK_H_
