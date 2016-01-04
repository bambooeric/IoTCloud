/*
 *  Copyright 2004 The WebRTC Project Authors. All rights reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include "webrtc/libjingle/xmpp/constants.h"
#include "webrtc/libjingle/xmpp/extdiscoservicestask.h"
#include "webrtc/libjingle/xmpp/xmpptask.h"
#include "webrtc/base/scoped_ptr.h"

namespace buzz {

ExtDiscoServicesTask::ExtDiscoServicesTask(XmppTaskParentInterface* parent,
                                         const Jid& to)
    : IqTask(parent, STR_GET, to, MakeRequest()) {
}

XmlElement* ExtDiscoServicesTask::MakeRequest() {
  XmlElement* element = new XmlElement(QN_EXTDISCO_SERVICES, true);
  return element;
}

void ExtDiscoServicesTask::HandleResult(const XmlElement* stanza) {
  const XmlElement* query = stanza->FirstNamed(QN_EXTDISCO_SERVICES);
  if (query) {
    std::vector<ExtDiscoService> items;
    for (const buzz::XmlChild* child = query->FirstChild(); child;
         child = child->NextChild()) {
      ExtDiscoService item;
      const buzz::XmlElement* child_element = child->AsElement();
	  
      if (ParseItem(child_element, &item)) {
        items.push_back(item);
      }
    }
    SignalResult(items);
  } else {
    SignalError(this, NULL);
  }
}

bool ExtDiscoServicesTask::ParseItem(const XmlElement* element,
                                    ExtDiscoService* item) {
  if (!element->HasAttr(QN_EXTDISCO_TYPE)) {
    return false;
  }

  //parse stun and turn
  item->type = element->Attr(QN_EXTDISCO_TYPE);
  if (0 == item->type.compare("stun")) {
    item->type = element->Attr(QN_EXTDISCO_TYPE);
    item->host = element->Attr(QN_EXTDISCO_HOST);
    item->port = element->Attr(QN_EXTDISCO_PORT);
    item->transport = element->Attr(QN_EXTDISCO_TRANSPORT);
  } else if (0 == item->type.compare("turn")) {
    item->type = element->Attr(QN_EXTDISCO_TYPE);
    item->host = element->Attr(QN_EXTDISCO_HOST);
    item->port = element->Attr(QN_EXTDISCO_PORT);
    item->transport = element->Attr(QN_EXTDISCO_TRANSPORT);
    item->username = element->Attr(QN_EXTDISCO_USERNAME);
    item->password = element->Attr(QN_EXTDISCO_PASSWORD);
  } else {
	return false;
  }
  
  return true;
}

}  // namespace buzz
