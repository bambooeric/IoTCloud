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

#include "webrtc/examples/client/callclient.h"
#include "webrtc/examples/client/conductor.h"

#include "webrtc/examples/client/console.h"
#include "webrtc/base/base64.h"
#include "webrtc/base/helpers.h"
#include "webrtc/base/logging.h"
#include "webrtc/base/network.h"
#include "webrtc/base/socketaddress.h"
#include "webrtc/base/stringencode.h"
#include "webrtc/base/stringutils.h"
#include "webrtc/base/thread.h"
#include "webrtc/base/taskrunner.h"
#ifdef HAVE_SCTP
#include "talk/media/sctp/sctpdataengine.h"
#endif
#include "webrtc/p2p/client/basicportallocator.h"
#include "webrtc/libjingle/xmpp/constants.h"
#include "webrtc/libjingle/xmpp/presenceouttask.h"

#include "webrtc/system_wrappers/interface/sleep.h"

using rtc::Base64;

// Must be period >= timeout.
const uint32 kPingPeriodMillis = 10000;
const uint32 kPingTimeoutMillis = 10000;
const uint32 kRandomPeriodMillis = 5000;
const uint32 kRandomTimeoutMillis = 500;

const std::string msgSdpSubject = "session-description";

const std::string modeClient = "client";
const std::string modeServer = "server";

const char* DescribeStatus(buzz::PresenceStatus::Show show,
                           const std::string& desc) {
  switch (show) {
  case buzz::PresenceStatus::SHOW_XA:      return desc.c_str();
  case buzz::PresenceStatus::SHOW_ONLINE:  return "online";
  case buzz::PresenceStatus::SHOW_AWAY:    return "away";
  case buzz::PresenceStatus::SHOW_DND:     return "do not disturb";
  case buzz::PresenceStatus::SHOW_CHAT:    return "ready to chat";
  default:                                 return "offline";
  }
}

CallClient::CallClient(buzz::XmppClient* xmpp_client,
                       const std::string& caps_node, const std::string& version)
    : xmpp_client_(xmpp_client),
      worker_thread_(NULL),
      data_engine_(NULL),
      data_channel_type_(cricket::DCT_NONE),
      portallocator_flags_(0),
      allow_local_ips_(false),
      transport_protocol_(cricket::ICEPROTO_HYBRID),
      sdes_policy_(cricket::SEC_DISABLED),
      dtls_policy_(cricket::SEC_DISABLED),
      ssl_identity_(),
      ping_task_(NULL),
      ice_disco_task_(NULL) {
  xmpp_client_->SignalStateChange.connect(this, &CallClient::OnStateChange);
  my_status_.set_caps_node(caps_node);
  my_status_.set_version(version);
}

CallClient::~CallClient() {
  delete worker_thread_;
}

void CallClient::RegisterObserver(CallClientObserver* callback) {
  ASSERT(!callback);
  Peer peer;
  peer.jid = buzz::Jid();
  peer.callback = callback;
  printf("register observer:%p\n", callback);
  peers_.push_back(peer);
}

const std::string CallClient::strerror(buzz::XmppEngine::Error err) {
  switch (err) {
    case buzz::XmppEngine::ERROR_NONE:
      return "";
    case buzz::XmppEngine::ERROR_XML:
      return "Malformed XML or encoding error";
    case buzz::XmppEngine::ERROR_STREAM:
      return "XMPP stream error";
    case buzz::XmppEngine::ERROR_VERSION:
      return "XMPP version error";
    case buzz::XmppEngine::ERROR_UNAUTHORIZED:
      return "User is not authorized (Check your username and password)";
    case buzz::XmppEngine::ERROR_TLS:
      return "TLS could not be negotiated";
    case buzz::XmppEngine::ERROR_AUTH:
      return "Authentication could not be negotiated";
    case buzz::XmppEngine::ERROR_BIND:
      return "Resource or session binding could not be negotiated";
    case buzz::XmppEngine::ERROR_CONNECTION_CLOSED:
      return "Connection closed by output handler.";
    case buzz::XmppEngine::ERROR_DOCUMENT_CLOSED:
      return "Closed by </stream:stream>";
    case buzz::XmppEngine::ERROR_SOCKET:
      return "Socket error";
    default:
      return "Unknown error";
  }
}


static const std::string jid = "iot01584573227021@dev.hinest";

void CallClient::OnStateChange(buzz::XmppEngine::State state) {
  switch (state) {
    case buzz::XmppEngine::STATE_START:
      console_->PrintLine("connecting...");
      break;
    case buzz::XmppEngine::STATE_OPENING:
      console_->PrintLine("logging in...");
      break;
    case buzz::XmppEngine::STATE_OPEN:
	  {
        console_->PrintLine("logged in...");
        InitPresence();
        if (true) {
          StartBindRandom();
        }

		webrtc::SleepMs(1000);

        InitMessage();

		StartExtdiscoIce();

        StartXmppPing();

		if (mode_ == modeClient) {
       	  Conductor *conductor = new Conductor(this);
       	  conductor->ConnectToPeer(buzz::Jid(jid));
		}
  	  }
      break;
    case buzz::XmppEngine::STATE_CLOSED:
      {
        buzz::XmppEngine::Error error = xmpp_client_->GetError(NULL);
        console_->PrintLine("logged out... %s", strerror(error).c_str());
      }
      break;
    default:
      break;
  }
}

void CallClient::InitDataChannel() {
#if 0
  worker_thread_ = new rtc::Thread();
  // The worker thread must be started here since initialization of
  // the ChannelManager will generate messages that need to be
  // dispatched by it.
  worker_thread_->Start();

  // TODO: It looks like we are leaking many objects. E.g.
  // |network_manager_| is never deleted.
  network_manager_ = new rtc::BasicNetworkManager();

  // TODO: Decide if the relay address should be specified here.
  rtc::SocketAddress stun_addr("stun.l.google.com", 19302);
  cricket::ServerAddresses stun_servers;
  stun_servers.insert(stun_addr);
  port_allocator_ =  new cricket::BasicPortAllocator(
      network_manager_, stun_servers, rtc::SocketAddress(),
      rtc::SocketAddress(), rtc::SocketAddress());

  if (portallocator_flags_ != 0) {
    port_allocator_->set_flags(portallocator_flags_);
  }

  if (!data_engine_) {
    if (data_channel_type_ == cricket::DCT_SCTP) {
#ifdef HAVE_SCTP
      data_engine_ = new cricket::SctpDataEngine();
#else
      LOG(LS_WARNING) << "SCTP Data Engine not supported.";
#endif
    } else {
      // Even if we have DCT_NONE, we still have a data engine, just
      // to make sure it isn't NULL.
      data_engine_ = new cricket::RtpDataEngine();
    }
  }
#endif
}

void SetAvailable(const buzz::Jid& jid, buzz::PresenceStatus* status) {
  status->set_jid(jid);
  status->set_available(true);
  status->set_show(buzz::PresenceStatus::SHOW_ONLINE);
}

void CallClient::InitPresence() {
  presence_out_ = new buzz::PresenceOutTask(xmpp_client_);
  SetAvailable(xmpp_client_->jid(), &my_status_);
  SendStatus(my_status_);
  presence_out_->Start();

  presence_recv_ = new buzz::PresenceReceiveTask(xmpp_client_);
  presence_recv_->PresenceUpdate.connect(this,
      &CallClient::OnPresenceUpdate);
  presence_recv_->Start();
}

void CallClient::InitMessage() {
  message_recv_ = new buzz::MessageReceiveTask(xmpp_client_);
  
  message_recv_->MessageUpdate.connect(this,
      &CallClient::OnMessageUpdate);
  message_recv_->Start();
}

void CallClient::StartXmppPing() {
  ping_task_ = new buzz::PingTask(
      xmpp_client_, rtc::Thread::Current(),
      kPingPeriodMillis, kPingTimeoutMillis);
  ping_task_->SignalTimeout.connect(this, &CallClient::OnPingTimeout);
  ping_task_->Start();
}

void CallClient::OnPingTimeout() {
  LOG(LS_WARNING) << "XMPP Ping timeout. Will keep trying...";
  StartXmppPing();

  // Or should we do this instead?
  // Quit();
}

//
// Ext Disco  implementation.
//
void CallClient::OnExtDiscoServices(std::vector<buzz::ExtDiscoService> items) {
  //printf("ice extern disco task running!\n");
  //printf("OnExtDiscoServices thread id:%p\n", rtc::ThreadManager::Instance()->CurrentThread());

  servers_.clear();
  // Read the intended destination from the wire.
  for (int i = 0; i < items.size(); i++) {
    webrtc::PeerConnectionInterface::IceServer server;
    server.uri = items[i].type + ":" + items[i].host + ":" + items[i].port;
	server.username = items[i].username;
	server.password = items[i].password;
    servers_.push_back(server);

	//printf("extdisco services uri:%s, username:%s, password:%s\n", 
	     //server.uri.c_str(), server.username.c_str(), server.password.c_str());
  }

  rtc::Thread::Current()->PostDelayed(12000, this, EXTDISCO_MSG_ID, NULL);  
}

void CallClient::StartExtdiscoIce() {
  buzz::Jid host_jid("dev.hinest");
  ice_disco_task_ = new buzz::ExtDiscoServicesTask(xmpp_client_, host_jid); 
  ice_disco_task_->SignalResult.connect(this, &CallClient::OnExtDiscoServices);
  ice_disco_task_->Start();
}

// Implementation of MessageHandler.
void CallClient::OnMessage(rtc::Message* msg) {
  switch(msg->message_id) {
	case EXTDISCO_MSG_ID:
	  StartExtdiscoIce();
	  break;
	case BYE_MSG_ID:
	  {
		rtc::TypedMessageData<std::string> *data =
          static_cast<rtc::TypedMessageData<std::string>*>(msg->pdata);
		
		buzz::Jid peer_jid(data->data()); 
	    int id = -1;
    	for (int i = 0; i < peers_.size(); i++) {
          if (!peers_[i].jid.IsEmpty() && peers_[i].jid == peer_jid) {
    	    id = i;
    		break;
    	  }
    	}

		if (id != -1) {
		  delete peers_[id].conductor;
          peers_.erase(peers_.begin() + id);
		}
	  }
	  break;
    default:
	  break;
  }
}

void CallClient::StartBindRandom() {
  console_->PrintLine("Start Bind Random Task!");
  runner_ = new rtc::FakeTaskRunner();
  random_task_ = new RandomTask(
  	  runner_,
  	  rtc::Thread::Current(), 
  	  kRandomPeriodMillis, kRandomTimeoutMillis);
  random_task_->SetDeviceID(device_id_);
  random_task_->Start();
}

void CallClient::StopBindRandom() {
  console_->PrintLine("Stop Bind Random Task!");
  delete runner_;
}

void CallClient::SendStatus(const buzz::PresenceStatus& status) {
  presence_out_->Send(status);
}

void CallClient::OnPresenceUpdate(const buzz::PresenceStatus& status) {
  RosterItem item;
  item.jid = status.jid();
  item.show = status.show();
  item.status = status.status();
  
  std::string key = item.jid.Str();

  printf("decode status, %s\n", status.type().c_str());
  
  if (status.available()) {
	if (0 == status.type().compare(buzz::STR_SUBSCRIBE)) {
	  console_->PrintLine("Adding to roster: %s, state: %s", 
	  	key.c_str(), status.status().c_str());
	  
	  if (!bind_flag_) {

		std::vector<char> random;
		Base64::DecodeFromArray(status.status().data(), status.status().length(), 
			                 Base64::DO_LAX, &random, NULL);
		rtc::Buffer buffer(&(*random.begin()), random.size());
	  	if (random_task_->CheckRandom(buffer)) {
		  bind_flag_ = true;
		  bind_jid_.CopyFrom(item.jid);
		  StopBindRandom();

		  //write config
		} else {
		  console_->PrintLine("no random add!\n");
		  
		  bind_flag_ = true;
		  bind_jid_.CopyFrom(item.jid);
		  StopBindRandom();

		  const std::string s_type(buzz::STR_SUBSCRIBED);
		  buzz::PresenceStatus s_status;
		  s_status.set_available(true);
		  s_status.set_jid(xmpp_client_->jid());
		  s_status.set_type(s_type);
		  presence_out_->SendDirected(item.jid, s_status);

		}
	  } else {
        const std::string s_type(buzz::STR_SUBSCRIBED);
        buzz::PresenceStatus s_status;
        s_status.set_available(true);
        s_status.set_jid(xmpp_client_->jid());
        s_status.set_type(s_type);
        presence_out_->SendDirected(item.jid, s_status);
	  }
	} 

	if (0 == status.type().compare(buzz::STR_UNSUBSCRIBE)) {
	  console_->PrintLine("Removing from roster: %s, state: %s", 
	  	key.c_str(), status.status().c_str());

	  if (0 == bind_jid_.Compare(item.jid)) {
	  	console_->PrintLine("del no random!\n");
		
	  	bind_flag_ = false;
	    StartBindRandom();
		//write config
	  }

	  const std::string s_type(buzz::STR_UNSUBSCRIBED);
	  buzz::PresenceStatus s_status;
      s_status.set_available(true);
      s_status.set_jid(xmpp_client_->jid());
      s_status.set_type(s_type);
      presence_out_->SendDirected(item.jid, s_status);
	}
  } 
}

void CallClient::OnMessageUpdate(const buzz::MessageStatus& status) {
   if (status.subject() == msgSdpSubject) {
	 //printf("receive sdp subject message!\n");

	 buzz::Jid peer_jid = status.peer_jid();
	 std::string msg_body = status.body();
#if 0	 
	 printf("peer jid:%s\n", peer_jid.c_str());
	 printf("subject:%s\n", status.subject().c_str());
	 printf("body:%s\n", status.body().c_str());
#endif

	 int id = -1;
	 for (int i = 0; i < peers_.size(); i++) {
       if (!peers_[i].jid.IsEmpty() && peers_[i].jid == peer_jid) {
	     id = i;
		 break;
	   }
	 }

	 if (-1 == id) {
  	   for (int i = 0; i < peers_.size(); i++) {
  	     if (peers_[i].jid.IsEmpty()) {
  		   peers_[i].jid.CopyFrom(peer_jid);
  		   id = i;
  		   break;
  	     }
  	   }
	 }

	 if (-1 == id) {
	   Conductor *data_conductor = new Conductor(this);
       for (int i = 0; i < peers_.size(); i++) {
	     if (peers_[i].jid.IsEmpty()) {
		   peers_[i].jid.CopyFrom(peer_jid);
		   peers_[i].conductor = data_conductor;
		   id = i;
		   break;
		 }
       }
	 }

	 printf("message update:%d, peer_jid:%s\n", id, peer_jid.Str().c_str());
	 
	 peers_[id].callback->OnMessageFromPeer(peer_jid, msg_body);
   } 
}

bool CallClient::SendChat(const std::string& to, const std::string sub_msg, const std::string body_msg) {
  bool stanza_ret;
  buzz::XmlElement* stanza = new buzz::XmlElement(buzz::QN_MESSAGE);
  stanza->AddAttr(buzz::QN_TO, to);
  stanza->AddAttr(buzz::QN_ID, rtc::CreateRandomString(16));
  stanza->AddAttr(buzz::QN_TYPE, "chat");
  buzz::XmlElement* subject = new buzz::XmlElement(buzz::QN_SUBJECT);
  subject->SetBodyText(sub_msg);
  stanza->AddElement(subject);
  buzz::XmlElement* body = new buzz::XmlElement(buzz::QN_BODY);
  body->SetBodyText(body_msg);
  stanza->AddElement(body);

  if (buzz::XMPP_RETURN_OK == xmpp_client_->SendStanza(stanza)) {
  	stanza_ret = true;
  } else {
    stanza_ret = false;
  }
  delete stanza;

  return stanza_ret;
}

void CallClient::SendData(const std::string& streamid,
                          const std::string& text) {
#if 0
  // TODO(mylesj): Support sending data over sessions other than the first.
  cricket::Session* session = GetFirstSession();
  if (!call_ || !session) {
    console_->PrintLine("Must be in a call to send data.");
    return;
  }
  if (!call_->has_data()) {
    console_->PrintLine("This call doesn't have a data channel.");
    return;
  }

  const cricket::DataContentDescription* data =
      cricket::GetFirstDataContentDescription(session->local_description());
  if (!data) {
    console_->PrintLine("This call doesn't have a data content.");
    return;
  }

  cricket::StreamParams stream;
  if (!cricket::GetStreamByIds(
          data->streams(), "", streamid, &stream)) {
    LOG(LS_WARNING) << "Could not send data: no such stream: "
                    << streamid << ".";
    return;
  }

  cricket::SendDataParams params;
  params.ssrc = stream.first_ssrc();
  rtc::Buffer payload(text.data(), text.length());
  cricket::SendDataResult result;
  bool sent = call_->SendData(session, params, payload, &result);
  if (!sent) {
    if (result == cricket::SDR_BLOCK) {
      LOG(LS_WARNING) << "Could not send data because it would block.";
    } else {
      LOG(LS_WARNING) << "Could not send data for unknown reason.";
    }
  }
#endif
}

void CallClient::OnPresenterStateChange(
    const std::string& nick, bool was_presenting, bool is_presenting) {
  if (!was_presenting && is_presenting) {
    console_->PrintLine("%s now presenting.", nick.c_str());
  } else if (was_presenting && !is_presenting) {
    console_->PrintLine("%s no longer presenting.", nick.c_str());
  } else if (was_presenting && is_presenting) {
    console_->PrintLine("%s still presenting.", nick.c_str());
  } else if (!was_presenting && !is_presenting) {
    console_->PrintLine("%s still not presenting.", nick.c_str());
  }
}

