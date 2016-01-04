/*
 *  Copyright 2012 The WebRTC Project Authors. All rights reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef TALK_EXAMPLES_CLIENT_CONDUCTOR_H_
#define TALK_EXAMPLES_CLIENT_CONDUCTOR_H_
#pragma once

#include <deque>
#include <map>
#include <set>
#include <string>

#include "webrtc/examples/client/callclient.h"

#include "talk/app/webrtc/mediastreaminterface.h"
#include "talk/app/webrtc/peerconnectioninterface.h"
#include "talk/app/webrtc/datachannelinterface.h"
#include "webrtc/base/scoped_ptr.h"
#include "webrtc/base/sigslot.h"
#include "webrtc/base/asyncudpsocket.h"
#include "webrtc/libjingle/xmpp/jid.h"

#include "talk/app/webrtc/jsep.h"

class CallClient;
class CallClientObserver;

namespace webrtc {
class VideoCaptureModule;
}  // namespace webrtc

namespace cricket {
class VideoRenderer;
}  // namespace cricket

#if 0
class PeerConnectionObserverImpl
  : public webrtc::PeerConnectionObserver {
 public:
  virtual void OnStateChange(
      webrtc::PeerConnectionObserver::StateType state_changed) {}
  virtual void OnAddStream(webrtc::MediaStreamInterface* stream);
  virtual void OnRemoveStream(webrtc::MediaStreamInterface* stream);
  virtual void OnDataChannel(webrtc::DataChannelInterface* channel);
  virtual void OnRenegotiationNeeded() {}
  virtual void OnIceChange() {}
  virtual void OnIceCandidate(const webrtc::IceCandidateInterface* candidate); 
}

class DataChannelObserverImpl
  : public webrtc::DataChannelObserver {
 public:
  virtual void OnStateChange() {}
  virtual void OnMessage(const DataBuffer& buffer);  
}

class CreateSessionDescriptionObserverImpl
  : public webrtc::CreateSessionDescriptionObserver {
 public:
  virtual void OnSuccess(webrtc::SessionDescriptionInterface* desc) {}
  virtual void OnFailure(const std::string& error);
}
#endif

class Conductor
  : public webrtc::PeerConnectionObserver,
    public webrtc::DataChannelObserver, 
    public webrtc::CreateSessionDescriptionObserver,
    public CallClientObserver, 
    public sigslot::has_slots<> {
 public:
  enum CallbackID {
    MEDIA_CHANNELS_INITIALIZED = 1,
    PEER_CONNECTION_CLOSED,
    SEND_MESSAGE_TO_PEER,
    NEW_STREAM_ADDED,
    STREAM_REMOVED,
  };

  Conductor(CallClient *client);

  ~Conductor();

  bool connection_active() const;

  virtual void Close();

 protected:
  bool InitializePeerConnection();
  bool ReinitializePeerConnectionForLoopback();
  bool CreatePeerConnection(bool dtls);
  void DeletePeerConnection();
  bool InitializeProxyConnection();
  void DeleteProxyConnection();
  void SendDataToProxy(const unsigned char *buffer, size_t size);
  
  void AddStreams();
  void AddDataChannel();
  cricket::VideoCapturer* OpenVideoCaptureDevice();
  
  //
  // AsyncUDPSocket  implementation.
  //
  void OnProxyUDPPacket(
      rtc::AsyncPacketSocket* socket, const char* buf, size_t size,
      const rtc::SocketAddress& addr, const rtc::PacketTime& packet_time);

  //
  // PeerConnectionObserver implementation.
  //
  virtual void OnStateChange(
      webrtc::PeerConnectionObserver::StateType state_changed) {}
  virtual void OnAddStream(webrtc::MediaStreamInterface* stream);
  virtual void OnRemoveStream(webrtc::MediaStreamInterface* stream);
  virtual void OnDataChannel(webrtc::DataChannelInterface* channel);
  virtual void OnRenegotiationNeeded() {}
  virtual void OnIceChange() { printf("IceChange\n"); }
  virtual void OnIceCandidate(const webrtc::IceCandidateInterface* candidate);
  virtual void OnIceConnectionChange(webrtc::PeerConnectionInterface::IceConnectionState new_state);
  virtual void OnIceConnectionReceivingChange(bool receiving);

  //
  // DataChannelObserver implementation.
  //
  virtual void OnStateChange();
  virtual void OnMessage(const webrtc::DataBuffer& buffer);  

  //
  // PeerConnectionClientObserver implementation.
  //

  virtual void OnSignedIn();

  virtual void OnDisconnected();

  virtual void OnPeerConnected(const buzz::Jid& jid, const std::string& name);

  virtual void OnPeerDisconnected(const buzz::Jid& jid);

  virtual void OnMessageFromPeer(const buzz::Jid& peer_jid, const std::string& message);

  virtual void OnMessageSent(int err);

  virtual void OnServerConnectionFailure();

  // CreateSessionDescriptionObserver implementation.
  virtual void OnSuccess(webrtc::SessionDescriptionInterface* desc);
  
  virtual void OnFailure(const std::string& error);

  virtual int AddRef() {};

  virtual int Release() {};

  //
  // MainWndCallback implementation.
  //
 public:
  virtual void StartLogin(const std::string& server, int port);

  virtual void DisconnectFromServer();

  virtual void ConnectToPeer(const buzz::Jid& peer_id);

  virtual void DisconnectFromPeer();

  virtual void ThreadCallback(int msg_id, void* data);

 protected:
  // Send a message to the remote peer.
  void SendMessage(const std::string& json_object);

  buzz::Jid peer_jid_;
  bool loopback_;
  rtc::scoped_refptr<webrtc::PeerConnectionInterface> peer_connection_;
  rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface>
      peer_connection_factory_;
  rtc::scoped_refptr<webrtc::DataChannelInterface> datachannel_;
  CallClient* client_;
  std::deque<std::string*> pending_messages_;
  std::map<std::string, rtc::scoped_refptr<webrtc::MediaStreamInterface> >
      active_streams_;
  std::string server_;

  rtc::AsyncUDPSocket* proxy_socket_;
  rtc::SocketAddress proxy_addr_;
};

#endif  // TALK_EXAMPLES_PEERCONNECTION_CLIENT_CONDUCTOR_H_
