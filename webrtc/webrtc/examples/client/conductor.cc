/*
 *  Copyright 2012 The WebRTC Project Authors. All rights reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include "webrtc/examples/client/conductor.h"
#include "webrtc/examples/client/callclient.h"

#include <utility>
#include <vector>

#include "talk/app/webrtc/videosourceinterface.h"
#include "webrtc/examples/peerconnection/client/defaults.h"
#include "talk/media/devices/devicemanager.h"
#include "talk/app/webrtc/datachannelinterface.h"

#include "talk/app/webrtc/test/fakeconstraints.h"
#include "talk/app/webrtc/test/fakeaudiocapturemodule.h"
#include "talk/app/webrtc/test/fakeperiodicvideocapturer.h"

#include "webrtc/base/common.h"
#include "webrtc/base/json.h"
#include "webrtc/base/logging.h"
#include "webrtc/base/socketaddress.h"

//#include "talk/app/webrtc/test/fakeaudiocapturemodule.h"
//#include "talk/media/webrtc/fakewebrtcvideoengine.h"

// Names used for a IceCandidate JSON object.
const char kCandidateSdpMidName[] = "sdpMid";
const char kCandidateSdpMlineIndexName[] = "sdpMLineIndex";
const char kCandidateSdpName[] = "candidate";

// Names used for a SessionDescription JSON object.
const char kSessionDescriptionTypeName[] = "type";
const char kSessionDescriptionSdpName[] = "sdp";

const std::string msgOfferType = "offer";
const std::string msgAnswerType = "answer";
const std::string msgIceType = "candidate";

const std::string msgSdpSubject = "session-description";

#define DTLS_ON  true
#define DTLS_OFF false

extern std::string client_ip;
extern std::string proxy_ip;
extern int proxy_port;

class DummySetSessionDescriptionObserver
    : public webrtc::SetSessionDescriptionObserver {
 public:
  static DummySetSessionDescriptionObserver* Create() {
    return
        new rtc::RefCountedObject<DummySetSessionDescriptionObserver>();
  }
  virtual void OnSuccess() {
    LOG(INFO) << __FUNCTION__;
	printf("SetSessionDescriptionObserver OnSuccess!\n");
  }
  virtual void OnFailure(const std::string& error) {
    LOG(INFO) << __FUNCTION__ << " " << error;
	printf("SetSessionDescriptionObserver On failure:%s\n", error.c_str());
  }

 protected:
  DummySetSessionDescriptionObserver() {}
  ~DummySetSessionDescriptionObserver() {}
};

rtc::AsyncSocket* CreateClientSocket(int family) {
  rtc::Thread* thread = rtc::Thread::Current();
  ASSERT(thread != NULL);
  return thread->socketserver()->CreateAsyncSocket(family, SOCK_DGRAM);
}

Conductor::Conductor(CallClient *client)
  : peer_jid_(buzz::Jid()),
    loopback_(false),
    client_(client),
    datachannel_(NULL),
    proxy_socket_(NULL) {
    client_->RegisterObserver(this);
}

Conductor::~Conductor() {
  ASSERT(peer_connection_.get() == NULL);
}

bool Conductor::connection_active() const {
  return peer_connection_.get() != NULL;
}

void Conductor::Close() {
  DeletePeerConnection();
}

bool Conductor::InitializePeerConnection() {
  ASSERT(peer_connection_factory_.get() == NULL);
  ASSERT(peer_connection_.get() == NULL);

  peer_connection_factory_ = webrtc::CreatePeerConnectionFactory(
	                      rtc::Thread::Current(), rtc::Thread::Current(),
	                      FakeAudioCaptureModule::Create(), 
	                      NULL, NULL);

  if (!peer_connection_factory_.get()) {
    LOG(LS_ERROR) << "Failed to initialize PeerConnectionFactory";
    DeletePeerConnection();
    return false;
  }

  if (!CreatePeerConnection(DTLS_ON)) {
	LOG(LS_ERROR) << "CreatePeerConnection failed";
    DeletePeerConnection();
  }

  // add streams
  //AddStreams();

  //add data channel
  AddDataChannel();
  
  return peer_connection_.get() != NULL;
}

bool Conductor::CreatePeerConnection(bool dtls) {
  ASSERT(peer_connection_factory_.get() != NULL);
  ASSERT(peer_connection_.get() == NULL);

#if 0
  webrtc::PeerConnectionInterface::IceServers servers;
  webrtc::PeerConnectionInterface::IceServer server;
  server.uri = GetPeerConnectionString();
  servers.push_back(server);
#endif

  webrtc::FakeConstraints constraints;
  if (dtls) {
    constraints.AddOptional(webrtc::MediaConstraintsInterface::kEnableDtlsSrtp,
                            "true");
  }
  else
  {
    constraints.AddOptional(webrtc::MediaConstraintsInterface::kEnableDtlsSrtp,
                            "false");
  }

  constraints.SetAllowDtlsSctpDataChannels();

  peer_connection_ =
      peer_connection_factory_->CreatePeerConnection(client_->IceServers(),
                                                     &constraints,
                                                     NULL,
                                                     NULL,
                                                     this);
  peer_connection_->SetIceConnectionReceivingTimeout(3000);
  
  return peer_connection_.get() != NULL;
}

void Conductor::DeletePeerConnection() {
  peer_connection_ = NULL;
  active_streams_.clear();
  peer_connection_factory_ = NULL;
  peer_jid_ = buzz::Jid();
  loopback_ = false;
}

bool Conductor::InitializeProxyConnection() {
  rtc::SocketAddress client_addr;
  rtc::AsyncSocket* socket;

  client_addr.SetIP(client_ip);
  client_addr.SetPort(0);
  proxy_addr_.SetIP(proxy_ip);
  proxy_addr_.SetPort(proxy_port);

  socket = CreateClientSocket(client_addr.ipaddr().family());
  proxy_socket_ = rtc::AsyncUDPSocket::Create(socket, client_addr);
  if (NULL == proxy_socket_) {
	printf("create proxy socket failed!\n");
	return false;
  }     
  proxy_socket_->SignalReadPacket.connect(this, &Conductor::OnProxyUDPPacket);
  //printf("create proxy socket success!\n");

  return true;
}

void Conductor::DeleteProxyConnection() {
  if (NULL != proxy_socket_) {
  	proxy_socket_->Close();
	proxy_socket_ = NULL;
  }
}

void Conductor::SendDataToProxy(const unsigned char *buffer, size_t size) {
  rtc::PacketOptions options;
  //printf("start on proxy send udp packet start!\n");
  if (NULL != proxy_socket_) {
    int ret = proxy_socket_->SendTo(buffer, size, proxy_addr_, options);
	//printf("start on proxy send udp packet ret:%d!\n", ret);
  }
}

//
// AsyncUDPSocket  implementation.
//
void Conductor::OnProxyUDPPacket(
    rtc::AsyncPacketSocket* socket, const char* buf, size_t size,
    const rtc::SocketAddress& addr, const rtc::PacketTime& packet_time) {
  // Read the intended destination from the wire.

  // printf("start on proxy udp packet start!\n");
  if (proxy_addr_ != addr) {
  	return;
  }

  //printf("start on proxy udp packet start data!\n");
  webrtc::DataBuffer buffer(rtc::Buffer(buf, size), false);
  if (NULL != datachannel_) {
  	bool ret = datachannel_->Send(buffer);
	//printf("datachannel send return:%d\n", ret);
  }
}

//
// PeerConnectionObserver implementation.
//

// Called when a remote stream is added
void Conductor::OnAddStream(webrtc::MediaStreamInterface* stream) {
  LOG(INFO) << __FUNCTION__ << " " << stream->label();

  stream->AddRef();

  ThreadCallback(NEW_STREAM_ADDED, stream);
}

void Conductor::OnRemoveStream(webrtc::MediaStreamInterface* stream) {
  LOG(INFO) << __FUNCTION__ << " " << stream->label();
  
  stream->AddRef();
  
  ThreadCallback(STREAM_REMOVED, stream);
}

void Conductor::OnDataChannel(webrtc::DataChannelInterface* channel) {
  datachannel_ = channel;
  datachannel_->RegisterObserver(this);

  printf("DataChannel is OK, %p!\n", channel);
}


void Conductor::OnIceConnectionChange(
      webrtc::PeerConnectionInterface::IceConnectionState new_state) {
  printf("OnIceConnectionChange, %d\n", new_state);
  switch(new_state) {
  case webrtc::PeerConnectionInterface::kIceConnectionFailed:
  case webrtc::PeerConnectionInterface::kIceConnectionDisconnected:
  case webrtc::PeerConnectionInterface::kIceConnectionClosed:
  	{
	  std::string peer_id_str = peer_jid_.Str();
	  if (NULL != datachannel_) {
		datachannel_->Close();
	  }

	  DeleteProxyConnection();

	  DeletePeerConnection();
	  
	  rtc::Thread::Current()->Post(client_, CallClient::BYE_MSG_ID, 
	  	                   new rtc::TypedMessageData<std::string>(peer_id_str));
  	}
	break;
  default:
	break;
  }
}

void Conductor::OnIceCandidate(const webrtc::IceCandidateInterface* candidate) {
  LOG(INFO) << __FUNCTION__ << " " << candidate->sdp_mline_index();
  
  Json::StyledWriter writer;
  Json::Value jmessage;

  jmessage[kSessionDescriptionTypeName] = msgIceType;
  jmessage[kCandidateSdpMidName] = candidate->sdp_mid();
  jmessage[kCandidateSdpMlineIndexName] = candidate->sdp_mline_index();
  std::string sdp;
  if (!candidate->ToString(&sdp)) {
    LOG(LS_ERROR) << "Failed to serialize candidate";
    return;
  }

  //printf("OnIceCandidate:%s\n", sdp.c_str());
	
  jmessage[kCandidateSdpName] = sdp;
  SendMessage(writer.write(jmessage));
}

void Conductor::OnIceConnectionReceivingChange(bool receiving) {
  printf("OnIceConnectionReceivingChange:%d\n", receiving);
}


//
// DataChannelObserver implementation.
//
void Conductor::OnStateChange() {
  //
  printf("data channel changed, state:%s!\n",
         webrtc::DataChannelInterface::DataStateString(datachannel_->state()));
}

void Conductor::OnMessage(const webrtc::DataBuffer& buffer) {
#if DEBUG
  printf("recieve message size:%d!\n", buffer.size());

  int k = 0;
  printf("key: ");
  for (k = 0; k < buffer.size(); k++) {
  	if (k % 8 == 0) {
  		printf("\n");
  	}
  	printf("0x%x ", *(buffer.data.data() + k));
  }
  printf("\n");
#endif

  SendDataToProxy(buffer.data.data(), buffer.size());
}

//
// CallClientObserver implementation.
//

void Conductor::OnSignedIn() {
  LOG(INFO) << __FUNCTION__;
}

void Conductor::OnDisconnected() {
  LOG(INFO) << __FUNCTION__;

  DeletePeerConnection();
}

void Conductor::OnPeerConnected(const buzz::Jid& jid, const std::string& name) {
  LOG(INFO) << __FUNCTION__;
}

void Conductor::OnPeerDisconnected(const buzz::Jid& jid) {
  LOG(INFO) << __FUNCTION__;
  if (jid== peer_jid_) {
    LOG(INFO) << "Our peer disconnected";
  } else {
  	;
  }
}

void Conductor::OnMessageFromPeer(const buzz::Jid& peer_jid, const std::string& message) {
  ASSERT(!message.empty());

  //printf("OnMessageFromPeer thread id:%p\n", rtc::ThreadManager::Instance()->CurrentThread());
  
  if (!peer_connection_.get()) {
    ASSERT(peer_id_.Isempty());

	//printf("PeerId:%s, message:%s\n", peer_jid.Str().c_str(), message.c_str());
	
	peer_jid_.CopyFrom(peer_jid);

	if (!InitializePeerConnection()) {
      LOG(LS_ERROR) << "Failed to initialize our PeerConnection instance";
      //client_->SignOut();
      return;
    }

	if (!InitializeProxyConnection()) {
      LOG(LS_ERROR) << "Failed to initialize our ProxyConnection instance";
	  //client_->SignOut();
	  return;
    }
  } else if (peer_jid == peer_jid_) {
  	ASSERT(peer_id_.Isempty());
  } else if (peer_jid.BareJid() == peer_jid_.BareJid() && 
  			 peer_jid_.resource().empty()) {
  	peer_jid_.CopyFrom(peer_jid);
  } else {
    ASSERT(!peer_id_.empty());
    LOG(WARNING) << "Received a message from unknown peer while already in a "
  				  "conversation with a different peer.";
    return;
  }

  Json::Reader reader;
  Json::Value jmessage;
  if (!reader.parse(message, jmessage)) {
    LOG(WARNING) << "Received unknown message. " << message;
    return;
  }
  std::string type;
  std::string json_object;

  rtc::GetStringFromJsonObject(jmessage, kSessionDescriptionTypeName, &type);
  if (msgOfferType == type || msgAnswerType == type) {
    std::string sdp;
    if (!rtc::GetStringFromJsonObject(jmessage, kSessionDescriptionSdpName,
                                      &sdp)) {
      LOG(WARNING) << "Can't parse received session description message.";
      return;
    }
    webrtc::SdpParseError error;
    webrtc::SessionDescriptionInterface* session_description(
        webrtc::CreateSessionDescription(type, sdp, &error));
    if (!session_description) {
      LOG(WARNING) << "Can't parse received session description message. "
          << "SdpParseError was: " << error.description;
      return;
    }
    LOG(INFO) << " Received session description :" << message;
    peer_connection_->SetRemoteDescription(
        DummySetSessionDescriptionObserver::Create(), session_description);
    if (session_description->type() ==
        webrtc::SessionDescriptionInterface::kOffer) {
      peer_connection_->CreateAnswer(this, NULL);
    }
	
    return;
  } else if (msgIceType == type) {
    std::string sdp_mid;
    int sdp_mlineindex = 0;
    std::string sdp;
    if (!rtc::GetStringFromJsonObject(jmessage, kCandidateSdpMidName,
                                      &sdp_mid) ||
        !rtc::GetIntFromJsonObject(jmessage, kCandidateSdpMlineIndexName,
                                   &sdp_mlineindex) ||
        !rtc::GetStringFromJsonObject(jmessage, kCandidateSdpName, &sdp)) {
      LOG(WARNING) << "Can't parse received message.";
      return;
    }

	printf("recive candidate!\n");
    webrtc::SdpParseError error;
    rtc::scoped_ptr<webrtc::IceCandidateInterface> candidate(
        webrtc::CreateIceCandidate(sdp_mid, sdp_mlineindex, sdp, &error));
    if (!candidate.get()) {
      LOG(WARNING) << "Can't parse received candidate message. "
          << "SdpParseError was: " << error.description;
      return;
    }
	
    if (!peer_connection_->AddIceCandidate(candidate.get())) {
      LOG(WARNING) << "Failed to apply the received candidate";
      return;
    }
	
    LOG(INFO) << " Received candidate :" << message;
	printf("recive candidate, set OK!\n");
	return;
  }else {
	LOG(INFO) << " Received unknowed message :" << message;
	printf("recieve unknowned message!\n");
	return;
  }
}

void Conductor::OnMessageSent(int err) {
  // Process the next pending message if any.
  ThreadCallback(SEND_MESSAGE_TO_PEER, NULL);
}

void Conductor::OnServerConnectionFailure() {
	LOG(INFO) << "Failed to connect to "; 
}

//
// MainWndCallback implementation.
//
void Conductor::ConnectToPeer(const buzz::Jid& peer_jid) {
  ASSERT(peer_jid_.IsEmpty());
  ASSERT(!peer_jid.IsEmpty());

  //printf("ConnectToPeer thread id:%p\n", rtc::ThreadManager::Instance()->CurrentThread());

  if (peer_connection_.get()) {
    LOG(LS_ERROR) << "We only support connecting to one peer at a time";
    return;
  }

  if (InitializePeerConnection()) {
    peer_jid_.CopyFrom(peer_jid);
    peer_connection_->CreateOffer(this, NULL);
  } else {
    LOG(LS_ERROR) << "Failed to initialize PeerConnection";
  }
}

void Conductor::DisconnectFromPeer() {
  LOG(INFO) << __FUNCTION__;
  if (peer_connection_.get()) {
    //client_->SendHangUp(peer_id_);
    DeletePeerConnection();
  }

  if (NULL != proxy_socket_) {
	DeleteProxyConnection();
  }
}

cricket::VideoCapturer* Conductor::OpenVideoCaptureDevice() {
  rtc::scoped_ptr<cricket::DeviceManagerInterface> dev_manager(
      cricket::DeviceManagerFactory::Create());
  if (!dev_manager->Init()) {
    LOG(LS_ERROR) << "Can't create device manager";
    return NULL;
  }
  std::vector<cricket::Device> devs;
  if (!dev_manager->GetVideoCaptureDevices(&devs)) {
    LOG(LS_ERROR) << "Can't enumerate video devices";
    return NULL;
  }
  std::vector<cricket::Device>::iterator dev_it = devs.begin();
  cricket::VideoCapturer* capturer = NULL;
  for (; dev_it != devs.end(); ++dev_it) {
    capturer = dev_manager->CreateVideoCapturer(*dev_it);
    if (capturer != NULL)
      break;
  }
  return capturer;
}

void Conductor::AddStreams() {
  if (active_streams_.find(kStreamLabel) != active_streams_.end())
    return;  // Already added.

  rtc::scoped_refptr<webrtc::AudioTrackInterface> audio_track(
      peer_connection_factory_->CreateAudioTrack(
          kAudioLabel, peer_connection_factory_->CreateAudioSource(NULL)));

  rtc::scoped_refptr<webrtc::VideoTrackInterface> video_track(
      peer_connection_factory_->CreateVideoTrack(
          kVideoLabel,
          peer_connection_factory_->CreateVideoSource(OpenVideoCaptureDevice(),
                                                      NULL)));

  rtc::scoped_refptr<webrtc::MediaStreamInterface> stream =
      peer_connection_factory_->CreateLocalMediaStream(kStreamLabel);

  stream->AddTrack(audio_track);
  stream->AddTrack(video_track);
  if (!peer_connection_->AddStream(stream)) {
    LOG(LS_ERROR) << "Adding stream to PeerConnection failed";
  }
  typedef std::pair<std::string,
                    rtc::scoped_refptr<webrtc::MediaStreamInterface> >
      MediaStreamPair;
  active_streams_.insert(MediaStreamPair(stream->label(), stream));
}

void Conductor::AddDataChannel()  {
  webrtc::DataChannelInit config;
  
  config.ordered = true;
  config.maxRetransmits = 3;
  datachannel_ = peer_connection_->CreateDataChannel("control", &config);
  datachannel_->RegisterObserver(this);
}

void Conductor::StartLogin(const std::string& server, int port) {
  return;
}

void Conductor::DisconnectFromServer() {
  return;
}
void Conductor::ThreadCallback(int msg_id, void* data) {
  switch (msg_id) {
    case PEER_CONNECTION_CLOSED:
      LOG(INFO) << "PEER_CONNECTION_CLOSED";
      DeletePeerConnection();

      ASSERT(active_streams_.empty());

#if NO_KNOW
      if (main_wnd_->IsWindow()) {
        if (client_->is_connected()) {
          main_wnd_->SwitchToPeerList(client_->peers());
        } else {
          main_wnd_->SwitchToConnectUI();
        }
      } else {
        DisconnectFromServer();
      }
#endif
      break;

    case SEND_MESSAGE_TO_PEER: {
      LOG(INFO) << "SEND_MESSAGE_TO_PEER";
      std::string* msg = reinterpret_cast<std::string*>(data);
      if (msg) {
        // For convenience, we always run the message through the queue.
        // This way we can be sure that messages are sent to the server
        // in the same order they were signaled without much hassle.
        pending_messages_.push_back(msg);
      }

      if (!pending_messages_.empty()) {
        msg = pending_messages_.front();
        pending_messages_.pop_front();

        if (!client_->SendChat(peer_jid_.Str(), msgSdpSubject, *msg) && !peer_jid_.IsEmpty()) {
          LOG(LS_ERROR) << "SendToPeer failed";
          DisconnectFromServer();
        }
        delete msg;
      }

      if (!peer_connection_.get())
        peer_jid_ = buzz::Jid("");

      break;
    }
    case NEW_STREAM_ADDED: {
      webrtc::MediaStreamInterface* stream =
          reinterpret_cast<webrtc::MediaStreamInterface*>(
          data);
      webrtc::VideoTrackVector tracks = stream->GetVideoTracks();
      // Only render the first track.
      if (!tracks.empty()) {
        webrtc::VideoTrackInterface* track = tracks[0];
      }
      stream->Release();
      break;
    }

    case STREAM_REMOVED: {
      // Remote peer stopped sending a stream.
      webrtc::MediaStreamInterface* stream =
          reinterpret_cast<webrtc::MediaStreamInterface*>(
          data);
      stream->Release();
      break;
    }

    default:
      ASSERT(false);
      break;
  }
}

void Conductor::OnSuccess(webrtc::SessionDescriptionInterface* desc) {
  peer_connection_->SetLocalDescription(
      DummySetSessionDescriptionObserver::Create(), desc);
  
  std::string sdp;
  desc->ToString(&sdp);

  printf("OnSuccess.....:type=%s, content:\n%s\n", desc->type().c_str(), sdp.c_str());

  Json::StyledWriter writer;
  Json::Value jmessage;
  jmessage[kSessionDescriptionTypeName] = desc->type();
  jmessage[kSessionDescriptionSdpName] = sdp;
  SendMessage(writer.write(jmessage));
}

void Conductor::OnFailure(const std::string& error) {
    LOG(LERROR) << error;
}

void Conductor::SendMessage(const std::string& json_object) {
  std::string* msg = new std::string(json_object);
  ThreadCallback(SEND_MESSAGE_TO_PEER, msg);
}

