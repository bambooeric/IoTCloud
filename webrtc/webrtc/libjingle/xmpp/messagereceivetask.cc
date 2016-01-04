/*
 *  Copyright 2011 The WebRTC Project Authors. All rights reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include "webrtc/libjingle/xmpp/constants.h"
#include "webrtc/libjingle/xmpp/messagereceivetask.h"

namespace buzz {

MessageStatus::MessageStatus() {
  return;
}

MessageReceiveTask::MessageReceiveTask(XmppTaskParentInterface* parent)
  : ReceiveTask(parent) {
  return;
}

bool MessageReceiveTask::WantsStanza(const XmlElement * stanza) {
  if (QN_MESSAGE == stanza->Name()) {
	return true;
  }

  return false;
}

// Process the received stanza.
void MessageReceiveTask::ReceiveStanza(const XmlElement* stanza) {
  MessageStatus status;

  if (stanza->HasAttr(QN_FROM)) {
	status.set_peer_jid(stanza->Attr(QN_FROM));
  }

  const XmlElement* body_stanza;
  const XmlElement* subject_stanza;

  body_stanza = stanza->FirstNamed(QN_BODY);
  subject_stanza = stanza->FirstNamed(QN_SUBJECT);

  if (NULL != body_stanza) {
  	status.set_body(body_stanza->BodyText());
  }

  if (NULL != subject_stanza) {
	status.set_subject(subject_stanza->BodyText());
  }

  printf("receive message:%s\n", stanza->Str().c_str());

  MessageUpdate(status);

  return;
}

}  // namespace buzz
