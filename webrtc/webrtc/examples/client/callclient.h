/*
 * libjingle
 * Copyright 2004--2005, Google Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *  3. The name of the author may not be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef WEBRTC_EXAMPLES_CLIENT_CALLCLIENT_H_
#define WEBRTC_EXAMPLES_CLIENT_CALLCLIENT_H_

#include <map>
#include <string>
#include <vector>

#include "webrtc/examples/client/console.h"

#include "webrtc/examples/client/randomtask.h"

#include "webrtc/p2p/base/session.h"
#include "webrtc/p2p/base/transportdescription.h"
#include "webrtc/libjingle/xmpp/hangoutpubsubclient.h"
#include "webrtc/libjingle/xmpp/presencereceivetask.h"
#include "webrtc/libjingle/xmpp/presencestatus.h"
#include "webrtc/libjingle/xmpp/messagereceivetask.h"
#include "webrtc/libjingle/xmpp/xmppclient.h"
#include "webrtc/libjingle/xmpp/jid.h"
#include "webrtc/libjingle/xmpp/pingtask.h"
#include "webrtc/libjingle/xmpp/extdiscoservicestask.h"
#include "webrtc/base/scoped_ptr.h"
#include "webrtc/base/sslidentity.h"
#include "webrtc/base/faketaskrunner.h"
#include "talk/media/base/mediaengine.h"
#include "talk/app/webrtc/peerconnectioninterface.h"

namespace buzz {
class PresenceOutTask;
class DiscoItemsQueryTask;
class PresenceStatus;
class IqTask;
class XmlElement;
class HangoutPubSubClient;
}  // namespace buzz

namespace rtc {
class Thread;
class NetworkManager;
class FakeTaskRunner;
}  // namespace rtc

namespace cricket {
class PortAllocator;
}  // namespace cricket

struct RosterItem {
  buzz::Jid jid;
  buzz::PresenceStatus::Show show;
  std::string status;
};

class Conductor;

class CallClientObserver {
 public:
  virtual void OnSignedIn() = 0;  // Called when we're logged on.
  virtual void OnDisconnected() = 0;
  virtual void OnPeerConnected(const buzz::Jid& jid, const std::string& name) = 0;
  virtual void OnPeerDisconnected(const buzz::Jid& jid) = 0;
  virtual void OnMessageFromPeer(const buzz::Jid& peer_id, const std::string& message) = 0;
  virtual void OnMessageSent(int err) = 0;
  virtual void OnServerConnectionFailure() = 0;

 protected:
  virtual ~CallClientObserver() {}
};

struct Peer {
  buzz::Jid jid;
  Conductor *conductor;
  CallClientObserver* callback;
};

class CallClient: public sigslot::has_slots<>, public rtc::MessageHandler {
 public:
  CallClient(buzz::XmppClient* xmpp_client,
             const std::string& caps_node,
             const std::string& version);
  ~CallClient();

  enum MessageID {
    EXTDISCO_MSG_ID = 1,
    BYE_MSG_ID
  };

  void RegisterObserver(CallClientObserver* callback);

  buzz::XmppClient* XmppClient() { return xmpp_client_; }
  
  void SetDataChannelType(cricket::DataChannelType data_channel_type) {
    data_channel_type_ = data_channel_type;
  }
  void SetConsole(Console *console) {
    console_ = console;
  }
  void SetPriority(int priority) {
    my_status_.set_priority(priority);
  }
  void SetMode(const std::string& mode) {
	mode_ = mode;
  }
  void SendStatus() {
    SendStatus(my_status_);
  }
  void SendStatus(const buzz::PresenceStatus& status);

  bool SendChat(const std::string& to, const std::string subject, const std::string msg);
  void SendData(const std::string& stream_name,
                const std::string& text);
  void SetPortAllocatorFlags(uint32 flags) { portallocator_flags_ = flags; }
  void SetAllowLocalIps(bool allow_local_ips) {
    allow_local_ips_ = allow_local_ips;
  }
  void SetTransportProtocol(cricket::TransportProtocol protocol) {
    transport_protocol_ = protocol;
  }
  void SetSecurePolicy(cricket::SecurePolicy sdes_policy,
                       cricket::SecurePolicy dtls_policy) {
    sdes_policy_ = sdes_policy;
    dtls_policy_ = dtls_policy;
  }
  void SetSslIdentity(rtc::SSLIdentity* identity) {
    ssl_identity_.reset(identity);
  }

  void SetDeviceId(const std::string &device_id) {
  	device_id_ = device_id;
  }

  webrtc::PeerConnectionInterface::IceServers& IceServers() {
	return servers_;
  }
  
 private:
  void OnStateChange(buzz::XmppEngine::State state);

  void InitPresence();
  void InitMessage();
  void StartXmppPing();
  void OnPingTimeout();

  void StartExtdiscoIce();
  void OnExtDiscoServices(std::vector<buzz::ExtDiscoService> items);
  void OnMessage(rtc::Message* msg);

  void StartBindRandom();
  void StopBindRandom();
  void OnPresenterStateChange(const std::string& nick, 
  							bool was_presenting, bool is_presenting) ;

  void OnPresenceUpdate(const buzz::PresenceStatus& status);
  void OnMessageUpdate(const buzz::MessageStatus& status);

  void InitDataChannel();

  const std::string strerror(buzz::XmppEngine::Error err);

  Console *console_;
  buzz::XmppClient* xmpp_client_;
  rtc::Thread* worker_thread_;
  rtc::NetworkManager* network_manager_;
  cricket::PortAllocator* port_allocator_;
  cricket::DataEngineInterface* data_engine_;

  CallClientObserver* callback_;

  buzz::HangoutPubSubClient* hangout_pubsub_client_;
  bool incoming_call_;
  bool auto_accept_;
  cricket::DataChannelType data_channel_type_;
  bool multisession_enabled_;

  buzz::PresenceStatus my_status_;
  buzz::PresenceOutTask* presence_out_;
  buzz::PresenceReceiveTask* presence_recv_;
  uint32 portallocator_flags_;

  buzz::MessageReceiveTask* message_recv_;

  bool allow_local_ips_;
  cricket::TransportProtocol transport_protocol_;
  cricket::SecurePolicy sdes_policy_;
  cricket::SecurePolicy dtls_policy_;
  rtc::scoped_ptr<rtc::SSLIdentity> ssl_identity_;
  std::string last_sent_to_;

  bool show_roster_messages_;

  bool bind_flag_;
  buzz::Jid bind_jid_;
  RandomTask* random_task_;
 
  rtc::FakeTaskRunner* runner_;

  std::string device_id_;

  std::vector<Peer> peers_;

  std::string mode_;

  buzz::PingTask* ping_task_;

  buzz::ExtDiscoServicesTask* ice_disco_task_;
  webrtc::PeerConnectionInterface::IceServers servers_;
};

#endif  // TALK_EXAMPLES_CALL_CALLCLIENT_H_
