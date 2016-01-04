/*
 *  Copyright 2011 The WebRTC Project Authors. All rights reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef WEBRTC_EXAMPLES_CLIENT_CONFIG_H_
#define WEBRTC_EXAMPLES_CLIENT_CONFIG_H_
#pragma once

int GetCurrentPath(char buf[],char *pFileName);

char *GetIniKeyString(char *title,char *key,char *filename);

int GetIniKeyInt(char *title,char *key,char *filename);

#endif  // PEERCONNECTION_SAMPLES_CLIENT_DEFAULTS_H_
