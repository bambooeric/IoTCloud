/*
 *  Copyright 2011 The WebRTC Project Authors. All rights reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef WEBRTC_LIBJINGLE_XMPP_MESSAGERECEIVETASK_H_
#define WEBRTC_LIBJINGLE_XMPP_MESSAGERECEIVETASK_H_

#include "webrtc/base/sigslot.h"
#include "webrtc/libjingle/xmpp/receivetask.h"

namespace buzz {

class MessageStatus {
public:
  MessageStatus();
  ~MessageStatus() {}

  const buzz::Jid& peer_jid() const { return peer_jid_; }
  const std::string body() const { return body_; }
  const std::string subject() const { return subject_; }
  const std::string& msg_id() const { return msg_id_; }

  void set_peer_jid(const std::string peer_jid) { peer_jid_ = buzz::Jid(peer_jid); }
  void set_body(const std::string body) { body_ = body; }
  void set_subject(const std::string subject) { subject_ = subject; }
  void set_msg_id(const std::string msg_id) { msg_id_ = msg_id; }
  
private:
  buzz::Jid peer_jid_;
  std::string body_;
  std::string subject_;
  std::string msg_id_;
};

// A base class for receiving stanzas.  Override WantsStanza to
// indicate that a stanza should be received and ReceiveStanza to
// process it.  Once started, ReceiveStanza will be called for all
// stanzas that return true when passed to WantsStanza. This saves
// you from having to remember how to setup the queueing and the task
// states, etc.
class MessageReceiveTask : public ReceiveTask {
 public:
  explicit MessageReceiveTask(XmppTaskParentInterface* parent);
  virtual ~MessageReceiveTask() {};

    // Slot for message callbacks
  sigslot::signal1<const MessageStatus&> MessageUpdate;
	
 protected:
  // Return true if the stanza should be received.
  bool WantsStanza(const XmlElement* stanza);
  // Process the received stanza.
  void ReceiveStanza(const XmlElement* stanza);
};

}  // namespace buzz

#endif  // WEBRTC_LIBJINGLE_XMPP_RECEIVETASK_H_
