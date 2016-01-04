/*
 *  Copyright 2004 The WebRTC Project Authors. All rights reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */


#ifndef WEBRTC_LIBJINGLE_XMPP_EXTDISCOSERVICESTASK_H_
#define WEBRTC_LIBJINGLE_XMPP_EXTDISCOSERVICESTASK_H_

#include <string>
#include <vector>

#include "webrtc/libjingle/xmpp/iqtask.h"

namespace buzz {

struct ExtDiscoService {
  std::string type;
  std::string host;
  std::string port;
  std::string transport;
  std::string username;
  std::string password;
};

class ExtDiscoServicesTask : public IqTask {
 public:
  ExtDiscoServicesTask(XmppTaskParentInterface* parent, const Jid& to);
  
  ~ExtDiscoServicesTask() {}
  sigslot::signal1<std::vector<ExtDiscoService> > SignalResult;

 private:
  static XmlElement* MakeRequest();
  virtual void HandleResult(const XmlElement* result);
  static bool ParseItem(const XmlElement* element, ExtDiscoService* item);
};

}  // namespace buzz

#endif  // WEBRTC_LIBJINGLE_XMPP_EXTDISCOITEMSSERVERSTASK_H_