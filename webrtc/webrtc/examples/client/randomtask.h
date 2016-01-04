/*
 *  Copyright 2011 The WebRTC Project Authors. All rights reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef WEBRTC_CLIENT_RANDOMTASK_H_
#define WEBRTC_CLIENT_RANDOMTASK_H_

#include "webrtc/base/task.h"
#include "webrtc/base/taskparent.h"
#include "webrtc/base/messagehandler.h"
#include "webrtc/base/messagequeue.h"
#include "webrtc/base/buffer.h"

#include <sys/socket.h>  
#include <arpa/inet.h>  

class RandomTask : public rtc::Task, private rtc::MessageHandler {
 public:
  explicit RandomTask(rtc::TaskParent *parent,
  	  rtc::MessageQueue* message_queue, 
  	  uint32 random_period_millis_,
      uint32 random_timeout_millis);

  bool CheckRandom(const rtc::Buffer &random);
  
  virtual int ProcessStart();

  void SetDeviceID(const std::string &device_id) { 
  	device_id_ = device_id; 
  }
  
 protected:
  ~RandomTask();
	
 private:
  // Implementation of MessageHandler.
  virtual void OnMessage(rtc::Message* msg);

  rtc::Buffer pre_random_;
  rtc::Buffer curr_random_;

  std::string device_id_;

  rtc::MessageQueue* message_queue_;
  int32 random_socket_;
  
  uint32 random_period_millis_;
  uint32 random_timeout_millis_;

  uint32 next_random_time_;

  struct sockaddr_in broadcast_addr_;
};

#endif  //  WEBRTC_CLIENT_RANDOMTASK_H_