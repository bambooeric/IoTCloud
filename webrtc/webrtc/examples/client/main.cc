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
#include <string.h>
#include <time.h>

#include <iomanip>
#include <iostream>
#include <vector>

#include "webrtc/examples/client/callclient.h"
#include "webrtc/examples/client/console.h"
#include "webrtc/examples/client/config.h"

#include "webrtc/p2p/base/transportdescription.h"
#include "webrtc/base/flags.h"
#include "webrtc/base/logging.h"
#include "webrtc/p2p/base/constants.h"
#include "webrtc/libjingle/xmpp/xmppauth.h"
#include "webrtc/libjingle/xmpp/xmppclientsettings.h"
#include "webrtc/libjingle/xmpp/xmpppump.h"
#include "webrtc/libjingle/xmpp/xmppsocket.h"
#include "webrtc/base/pathutils.h"
#include "webrtc/base/ssladapter.h"
#include "webrtc/base/sslidentity.h"
#include "webrtc/base/stream.h"
#include "webrtc/base/thread.h"


static bool SSLVerificationCallback(void* cert) {
	return true;
}

#define CONF_FILE_PATH  "./config.ini"  
#define MAX_CONFIG_PATH 256

static char g_szConfigPath[MAX_CONFIG_PATH];

static char *wan_gateway_key = "wan_gateway";
static char *device_id_key = "device_id";
static char *device_passwd_key = "device_passwd";
static char *server_ip_key = "server_ip";
static char *service_mode_key = "service_mode";
static char *client_ip_key = "client_ip";
static char *proxy_ip_key = "proxy_ip";
static char *proxy_port_key = "proxy_port";

std::string client_ip;
std::string proxy_ip;
int proxy_port;

void IniConfigInit() 
{
	char buf[MAX_CONFIG_PATH];  
	 
	//memset(buf,0,sizeof(buf));  
	//GetCurrentPath(buf, CONF_FILE_PATH);  
	strcpy(g_szConfigPath, CONF_FILE_PATH);  
}

int main(int argc, char **argv) {
  cricket::TransportProtocol transport_protocol = cricket::ICEPROTO_RFC5245;
  cricket::DataChannelType data_channel_type = cricket::DCT_SCTP;
  cricket::SecurePolicy sdes_policy =  cricket::SEC_DISABLED;
  cricket::SecurePolicy dtls_policy = cricket::SEC_REQUIRED;
  rtc::SSLIdentity* ssl_identity = NULL;

  std::string auth_token;
  std::string username;
  std::string mode;
  std::string address;
  char *ini_config_val;
  int ini_cofig_int_val;

  IniConfigInit();

  ini_config_val = GetIniKeyString(wan_gateway_key, device_passwd_key, g_szConfigPath);
  if (NULL != ini_config_val) {
  	  auth_token = std::string(ini_config_val);
  }

  printf("password:%s\n", auth_token.c_str());

  ini_config_val = GetIniKeyString(wan_gateway_key, device_id_key, g_szConfigPath);
  if (NULL != ini_config_val) {
  	  username = std::string(ini_config_val);
  }

  printf("username:%s\n", username.c_str());

  ini_config_val = GetIniKeyString(wan_gateway_key, service_mode_key, g_szConfigPath);
  if (NULL != ini_config_val) {
  	  mode = std::string(ini_config_val);
  }

  printf("service_mode:%s\n", mode.c_str());

  ini_config_val = GetIniKeyString(wan_gateway_key, server_ip_key, g_szConfigPath);
  if (NULL != ini_config_val) {
  	  address = std::string(ini_config_val);
  }

  printf("server_ip:%s\n", address.c_str());

  ini_config_val = GetIniKeyString(wan_gateway_key, client_ip_key, g_szConfigPath);
  if (NULL != ini_config_val) {
  	  client_ip = std::string(ini_config_val);
  }

  printf("client_ip:%s\n", client_ip.c_str());

  ini_config_val = GetIniKeyString(wan_gateway_key, proxy_ip_key, g_szConfigPath);
  if (NULL != ini_config_val) {
  	  proxy_ip = std::string(ini_config_val);
  }

  printf("proxy_ip:%s\n", proxy_ip.c_str());

  ini_cofig_int_val = GetIniKeyInt(wan_gateway_key, proxy_port_key, g_szConfigPath);
  if (0 != ini_cofig_int_val) {
  	  proxy_port = ini_cofig_int_val;
  }

  printf("proxy_port:%d\n", proxy_port);

  rtc::InsecureCryptStringImpl pass;
  pass.password() = auth_token;
  
  rtc::Thread* main_thread = rtc::Thread::Current();

  std::string caps_node = "Caps node: A URI identifying the app.";
  std::string caps_ver = "1.0";

  buzz::XmppPump pump;
  CallClient *client = new CallClient(pump.client(), caps_node, caps_ver);

  if (!rtc::InitializeSSL(SSLVerificationCallback)) {
    LOG(LS_ERROR) << "initialize ssl failed!";
  }
  if (!rtc::InitializeSSLThread()) {
    LOG(LS_ERROR) << "initialize ssl thread failed!";
  }

  buzz::Jid jid;
  jid = buzz::Jid(username);
  if (dtls_policy != cricket::SEC_DISABLED) {
    ssl_identity = rtc::SSLIdentity::Generate(jid.Str(), rtc::KT_RSA);
    if (!ssl_identity) {
      LOG(LS_ERROR) << "Failed to generate identity for DTLS!";
      return 1;
    }
  }
  
  //Login task
  buzz::XmppClientSettings xcs;
  xcs.set_user(username.c_str());
  xcs.set_pass(rtc::CryptString(pass));
  xcs.set_host("dev.hinest");
  xcs.set_allow_plain(true);
  xcs.set_use_tls(buzz::TLS_DISABLED);
  xcs.set_server(rtc::SocketAddress(address, 5222));

  Console *console = new Console(main_thread, client);
  client->SetConsole(console);
  client->SetDeviceId(username);
  client->SetAllowLocalIps(true);
  client->SetTransportProtocol(transport_protocol);
  client->SetSecurePolicy(sdes_policy, dtls_policy);
  client->SetSslIdentity(ssl_identity);
  client->SetMode(mode);
  client->SetDataChannelType(data_channel_type);
  console->Start();

  pump.DoLogin(xcs, new buzz::XmppSocket(buzz::TLS_DISABLED), new XmppAuth());
  main_thread->Run();
  pump.DoDisconnect();

  console->Stop();
  delete console;
  delete client;

  return 0;
}
