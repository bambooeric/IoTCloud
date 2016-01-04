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

#include <stdio.h>

#include <iostream>

#include "webrtc/libjingle/xmpp/constants.h"
#include "webrtc/libjingle/xmpp/xmppclientsettings.h"
#include "webrtc/libjingle/xmpp/xmppengine.h"
#include "webrtc/libjingle/xmpp/xmppthread.h"
#include "webrtc/libjingle/xmpp/xmppauth.h"

#include "webrtc/base/ssladapter.h"
#include "webrtc/base/thread.h"

static bool SSLVerificationCallback(void* cert) {
	return true;
}

void CallClient::OnStateChange(buzz::XmppEngine::State state) {
  switch (state) {
    case buzz::XmppEngine::STATE_START:
      console_->PrintLine("connecting...");
      break;
    case buzz::XmppEngine::STATE_OPENING:
      console_->PrintLine("logging in...");
      break;
    case buzz::XmppEngine::STATE_OPEN:
      console_->PrintLine("logged in...");
      InitMedia();
      InitPresence();
      break;
    case buzz::XmppEngine::STATE_CLOSED:
      {
        buzz::XmppEngine::Error error = xmpp_client_->GetError(NULL);
        console_->PrintLine("logged out... %s", strerror(error).c_str());
        Quit();
      }
      break;
    default:
      break;
  }
}

int main(int argc, char **argv) {
  std::cout << "OAuth Access Token: ";
  std::string auth_token;
  std::getline(std::cin, auth_token);

  std::cout << "User Name: ";
  std::string username;
  std::getline(std::cin, username);
  
  rtc::InsecureCryptStringImpl pass;
  pass.password() = auth_token;
  
  rtc::Thread* main_thread = rtc::Thread::Current();

  if (!rtc::InitializeSSL(SSLVerificationCallback)) {
    LOG(LS_ERROR) << "initialize ssl failed!";
  }
  if (!rtc::InitializeSSLThread()) {
    LOG(LS_ERROR) << "initialize ssl thread failed!";
  }
  
  //Login task
  buzz::XmppClientSettings xcs;
  xcs.set_user(username.c_str());
  xcs.set_pass(rtc::CryptString(pass));
  xcs.set_host("dev.hiberry");
  xcs.set_allow_plain(true);
  xcs.set_use_tls(buzz::TLS_REQUIRED);
  xcs.set_server(rtc::SocketAddress("192.168.1.60", 5222));

  buzz::XmppPump pump;

  pump.DoLogin(xcs, new buzz::XmppSocket(buzz::TLS_REQUIRED), new XmppAuth());
  main_thread->Run();
  pump.DoDisconnect();

  // Use main thread for console input
  std::string line;
  while (std::getline(std::cin, line)) {
    if (line == "quit")
      break;
  }
  return 0;
}
