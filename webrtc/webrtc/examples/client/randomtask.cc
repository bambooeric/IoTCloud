/*
 *  Copyright 2011 The WebRTC Project Authors. All rights reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include "webrtc/examples/client/randomtask.h"

#include <unistd.h>  
#include <stdbool.h>  

#include <openssl/rand.h>
#include <openssl/sha.h>   
#include <openssl/crypto.h>
#include <openssl/hmac.h>

#include "webrtc/base/logging.h"
#include "webrtc/base/scoped_ptr.h"
#include "webrtc/base/base64.h"

#define PORT 7773
#define MAXDATASIZE 512
#define RANDOM_SIZE 32

#define MAGIC_VAL "Hi_IoT"
#define MAGIC_LEN 6

using rtc::Base64;

//send broastcast add route
//route add -net 255.255.255.255 netmask 255.255.255.255 dev eth0 metric 1
//or
//route add -host 255.255.255.255 dev eth0

RandomTask::RandomTask(rtc::TaskParent *parent,
                   rtc::MessageQueue* message_queue,
                   uint32 random_period_millis,
                   uint32 random_timeout_millis)
    : Task(parent),
      message_queue_(message_queue),
      random_period_millis_(random_period_millis),
      random_timeout_millis_(random_timeout_millis) {
  next_random_time_ = rtc::Time();
  broadcast_addr_.sin_family = AF_INET;
  broadcast_addr_.sin_port = htons(PORT);
  broadcast_addr_.sin_addr.s_addr = inet_addr("255.255.255.255");
  bzero(&(broadcast_addr_.sin_zero), 8);

  printf("random task start!\n");

  random_socket_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);	
  if(random_socket_ < 0) {
  	printf("create udp socket failed!\n");
  	LOG(LS_WARNING) << "Failed to create a UDP socket" << std::endl;
  }
  
  int so_broadcast = 1;	  
  if(setsockopt(random_socket_, SOL_SOCKET, SO_BROADCAST, 
     &so_broadcast, sizeof(so_broadcast)) < 0 ) {
    printf("set sockopt failed!\n");
  	LOG(LS_WARNING)  << "setsockopt() failed!";  
  }

  struct sockaddr_in user_addr;
  user_addr.sin_family=AF_INET;
  user_addr.sin_port=htons(PORT);
  user_addr.sin_addr.s_addr=htonl(INADDR_ANY);
  bzero(&(user_addr.sin_zero), 8);
  if(0 > (bind(random_socket_, (struct sockaddr *)&user_addr,
                      sizeof(struct sockaddr)))) {
      printf("socket bing failed!\n");
	  LOG(LS_WARNING)  << "socket bing failed!"; 
  }

  uint8 rnd[RANDOM_SIZE];
  RAND_bytes((uint8 *)rnd, RANDOM_SIZE);
  curr_random_.SetData((const char *)rnd, RANDOM_SIZE);
  pre_random_ = curr_random_;
}

RandomTask::~RandomTask() {
  printf("~RandomTask!\n");
  if (random_socket_ >= 0) {
  	close(random_socket_);
  }
  message_queue_->Clear(this);
}

bool RandomTask::CheckRandom(const rtc::Buffer &random) {
  if (random == pre_random_ || random == curr_random_ ) {
  	return true;
  }

  return false;
}

// This task runs indefinitely and remains in either the start or blocked
// states.
int RandomTask::ProcessStart() {
  uint32 now = rtc::Time();

  //printf("random task process start!\n");

  // calc random
  if (now >= next_random_time_) {
  	uint8_t rnd[RANDOM_SIZE];

	next_random_time_ = now + random_period_millis_;

	// Update random
	pre_random_ = curr_random_;
	
	RAND_bytes((uint8_t *)rnd, RANDOM_SIZE);
	curr_random_.SetData((const char *)rnd, RANDOM_SIZE);

#if 0
	int k;
	printf("device_id:%s, random:", device_id_.c_str());
	for (k = 0; k < 32; k++) {
		if (k % 8 == 0) {
			printf("\n");
		}
		printf("0x%x ", rnd[k]);
	}
	printf("\n");


	std::string pre_encode;
	std::string curr_encode;

    Base64::EncodeFromArray(pre_random_.data(), pre_random_.size(), &pre_encode);
    Base64::EncodeFromArray(curr_random_.data(), curr_random_.size(), &curr_encode);
    printf("pre_random_base64:%s, random_base64:%s\n", 
  		pre_encode.c_str(),
  	    curr_encode.c_str());

	std::vector<char> random;
	Base64::DecodeFromArray(curr_encode.data(), curr_encode.length(), 
						 Base64::DO_LAX, &random, NULL);
	rtc::Buffer buffer(&(*random.begin()), random.size());

	char *tmp = (char *)buffer.data();
	printf("decode random, size:%d", curr_random_.size());
	for (k = 0; k < 32; k++) {
		if (k % 8 == 0) {
			printf("\n");
		}
		printf("0x%x ", tmp[k]);
	}
	printf("\n");

	if (CheckRandom(buffer)) {
	  printf("random check OK!\n");
	}
#endif
  }

  //printf("random task process start1!\n");

  // Send a random broadcast
  {
    uint8_t buf[MAXDATASIZE];
	uint32_t blen;
    socklen_t size;
	uint32_t output_length;
	int32_t rlen;

	blen = 0;
	memcpy(buf+blen, MAGIC_VAL, MAGIC_LEN);
	blen += MAGIC_LEN;
	*(uint16_t *)(buf+blen) = htons(RANDOM_SIZE);
	blen += sizeof(uint16_t);
	memcpy(buf+blen, curr_random_.data(), RANDOM_SIZE);
	blen += RANDOM_SIZE;

    // calc key 
    SHA256_CTX c;  
    uint8_t md[SHA256_DIGEST_LENGTH];  
 
    SHA256_Init(&c);  
    SHA256_Update(&c, device_id_.data(), device_id_.length());  
    SHA256_Final(md, &c);  
    OPENSSL_cleanse(&c, sizeof(c)); 

#if 0
	int k = 0;
	printf("key: ");
	for (k = 0; k < 32; k++) {
		if (k % 8 == 0) {
			printf("\n");
		}
		printf("0x%X ", md[k]);
	}
	printf("\n");
#endif

	// calc hmac 
  	const EVP_MD *engine = EVP_sha256();   
    HMAC_CTX ctx;  
    HMAC_CTX_init(&ctx);  
    HMAC_Init_ex(&ctx, md, sizeof(md), engine, NULL);  
    HMAC_Update(&ctx, (uint8_t *)buf, blen);        // input is OK; &input is WRONG !!!  

    HMAC_Final(&ctx, buf+blen, &output_length);  
    HMAC_CTX_cleanup(&ctx);  

#if 0
    printf("blen:%d\n", blen);
	printf("tag: ");
	for (k = 0; k < 32; k++) {
		if (k % 8 == 0) {
			printf("\n");
		}
		printf("0x%X ", buf[blen+k]);
	}
	printf("\n");
#endif

	blen += output_length;

	//printf("sendto buflen :%d\n", blen);

	rlen = sendto(random_socket_, buf, blen, 0, 
		(struct sockaddr *)&broadcast_addr_, sizeof(broadcast_addr_));
    if (0 > rlen) {
      LOG(LS_WARNING) << "send random broadcast packet failed!";  
	  printf("sendto failed, %d!\n", rlen);
	}
  }
  
  // Wake ourselves up when it's time to send another ping or when the ping
  // times out (so we can fire a signal).
  message_queue_->PostDelayed(random_timeout_millis_, this);

  return STATE_BLOCKED;
}

void RandomTask::OnMessage(rtc::Message* msg) {
  //printf("random task on message!\n");
  // Get the task manager to run this task so we can send a random packet
  // process a random send.
  Wake();
}

