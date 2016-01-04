#=================================================================================
# export variable
#=================================================================================
ifeq ($(CFG_EXPORT_FLAG),)
include ../config.mak
endif

#=================================================================================
# local variable
#=================================================================================
LIBS :=libtalk
TALK_PATH = ../talk
WEBRTC_PATH = ../webrtc
THIRD_PARTY_PATH = ../third_party

##################################################################################
CFLAGS += -I./
CFLAGS += -I$(TALK_PATH)/../
CFLAGS += -I$(TALK_PATH)
CFLAGS += -I$(WEBRTC_PATH)/../
CFLAGS += -I$(WEBRTC_PATH)
CFLAGS += -I$(WEBRTC_PATH)/common_audio/resampler/include
CFLAGS += -I$(WEBRTC_PATH)/common_audio/signal_processing/include
CFLAGS += -I$(WEBRTC_PATH)/common_audio/vad/include
CFLAGS += -I$(WEBRTC_PATH)/common_video/interface
CFLAGS += -I$(WEBRTC_PATH)/modules/audio_coding/codecs/cnq/include
CFLAGS += -I$(WEBRTC_PATH)/modules/audio_coding/neteq
CFLAGS += -I$(WEBRTC_PATH)/modules/audio_coding/codecs/g711/include
CFLAGS += -I$(WEBRTC_PATH)/modules/audio_coding/dummy
CFLAGS += -I$(WEBRTC_PATH)/modules/audio_coding/linux

CFLAGS += -I$(THIRD_PARTY_PATH)/libyuv/include
CFLAGS += -I$(THIRD_PARTY_PATH)/libsrtp/srtp/include
CFLAGS += -I$(THIRD_PARTY_PATH)/libsrtp/srtp/crypto/include
CFALGS += -I$(THIRD_PARTY_PATH)/openssl/include/
CFLAGS += -I$(THIRD_PARTY_PATH)/usrsctp
CFLAGS += -I$(THIRD_PARTY_PATH)/libudev


##################################################################################

CFLAGS += -std=c++11 -fpermissive
CFLAGS += -D_REENTRANT
CFLAGS += -DDISABLE_DYNAMIC_CAST
CFALGS += -DHASH_NAMESPACE=__gnu_cxx
CFALGS += -DLINUX
CFLAGS += -DPOSIX
CFLAGS += -DWEBRTC_LINUX
CFLAGS += -DWEBRTC_POSIX
CFLAGS += -DLOGGING=1
CFLAGS += -DWEBRTC_THREAD_RR
CFLAGS += -DHAVE_SCTP
CFLAGS += -DHAVE_SRTP
CFLAGS += -DHAVE_OPENSSL_SSL_H
CFLAGS += -DHAVE_WEBRTC_VIDEO
CFLAGS += -DHAVE_WEBRTC_VOICE
CFLAGS += -DWEBRTC_NS_FLOAT
CFLAGS += -DSSL_USE_OPENSSL
CFLAGS += -DFEATURE_ENABLE_SSL
CFLAGS += -DSRTP_RELATIVE_PATH
CFLAGS += -DEXPAT_RELATIVE_PATH
CFLAGS += -DJSONCPP_RELATIVE_PATH
CFLAGS += -DUSE_WEBRTC_DEV_BRANCH
CFLAGS += -DLIBPEERCONNECTION_LIB=1
CFLAGS += -DWEBRTC_DUMMY_AUDIO_BUILD
CFLAGS += -DWEBRTC_DUMMY_FILE_DEVICES

################################# libjingle_media ###########################################
SRC_ALL += media/base/audioframe.h
SRC_ALL += media/base/audiorenderer.h
SRC_ALL += media/base/capturemanager.cc
SRC_ALL += media/base/capturemanager.h
SRC_ALL += media/base/capturerenderadapter.cc
SRC_ALL += media/base/capturerenderadapter.h
SRC_ALL += media/base/codec.cc
SRC_ALL += media/base/codec.h
SRC_ALL += media/base/constants.cc
SRC_ALL += media/base/constants.h
SRC_ALL += media/base/cpuid.cc
SRC_ALL += media/base/cpuid.h
SRC_ALL += media/base/cryptoparams.h
SRC_ALL += media/base/device.h
SRC_ALL += media/base/fakescreencapturerfactory.h
SRC_ALL += media/base/hybriddataengine.h
SRC_ALL += media/base/mediachannel.h
SRC_ALL += media/base/mediacommon.h
SRC_ALL += media/base/mediaengine.cc
SRC_ALL += media/base/mediaengine.h
SRC_ALL += media/base/rtpdataengine.cc
SRC_ALL += media/base/rtpdataengine.h
SRC_ALL += media/base/rtpdump.cc
SRC_ALL += media/base/rtpdump.h
SRC_ALL += media/base/rtputils.cc
SRC_ALL += media/base/rtputils.h
SRC_ALL += media/base/screencastid.h
SRC_ALL += media/base/streamparams.cc
SRC_ALL += media/base/streamparams.h
SRC_ALL += media/base/videoadapter.cc
SRC_ALL += media/base/videoadapter.h
SRC_ALL += media/base/videocapturer.cc
SRC_ALL += media/base/videocapturer.h
SRC_ALL += media/base/videocapturerfactory.h
SRC_ALL += media/base/videocommon.cc
SRC_ALL += media/base/videocommon.h
SRC_ALL += media/base/videoframe.cc
SRC_ALL += media/base/videoframe.h
SRC_ALL += media/base/videoframefactory.cc
SRC_ALL += media/base/videoframefactory.h
SRC_ALL += media/base/videorenderer.h
SRC_ALL += media/base/voiceprocessor.h
SRC_ALL += media/base/yuvframegenerator.cc
SRC_ALL += media/base/yuvframegenerator.h
SRC_ALL += media/devices/deviceinfo.h
#SRC_ALL += media/devices/devicemanager.cc
SRC_ALL += media/devices/devicemanager.h
SRC_ALL += media/devices/dummydevicemanager.cc
SRC_ALL += media/devices/dummydevicemanager.h
SRC_ALL += media/devices/filevideocapturer.cc
SRC_ALL += media/devices/filevideocapturer.h
SRC_ALL += media/devices/videorendererfactory.h
SRC_ALL += media/devices/yuvframescapturer.cc
SRC_ALL += media/devices/yuvframescapturer.h
SRC_ALL += media/sctp/sctpdataengine.cc
SRC_ALL += media/sctp/sctpdataengine.h
SRC_ALL += media/webrtc/simulcast.cc
SRC_ALL += media/webrtc/simulcast.h
SRC_ALL += media/webrtc/webrtccommon.h
SRC_ALL += media/webrtc/webrtcmediaengine.cc
SRC_ALL += media/webrtc/webrtcmediaengine.h
SRC_ALL += media/webrtc/webrtcmediaengine.cc
SRC_ALL += media/webrtc/webrtcpassthroughrender.cc
SRC_ALL += media/webrtc/webrtcpassthroughrender.h
SRC_ALL += media/webrtc/webrtcvideocapturer.cc
SRC_ALL += media/webrtc/webrtcvideocapturer.h
SRC_ALL += media/webrtc/webrtcvideocapturerfactory.h
SRC_ALL += media/webrtc/webrtcvideocapturerfactory.cc
SRC_ALL += media/webrtc/webrtcvideodecoderfactory.h
SRC_ALL += media/webrtc/webrtcvideoencoderfactory.h
SRC_ALL += media/webrtc/webrtcvideoengine2.cc
SRC_ALL += media/webrtc/webrtcvideoengine2.h
SRC_ALL += media/webrtc/webrtcvideoframe.cc
SRC_ALL += media/webrtc/webrtcvideoframe.h
SRC_ALL += media/webrtc/webrtcvideoframefactory.cc
SRC_ALL += media/webrtc/webrtcvideoframefactory.h
SRC_ALL += media/webrtc/webrtcvoe.h
SRC_ALL += media/webrtc/webrtcvoiceengine.cc
SRC_ALL += media/webrtc/webrtcvoiceengine.h

#SRC_ALL += media/devices/libudevsymboltable.cc
#SRC_ALL += media/devices/libudevsymboltable.h
#SRC_ALL += media/devices/linuxdeviceinfo.cc
#SRC_ALL += media/devices/linuxdevicemanager.cc
#SRC_ALL += media/devices/linuxdevicemanager.h
#SRC_ALL += media/devices/v4llookup.cc
#SRC_ALL += media/devices/v4llookup.h

################################# libjingle p2p ##########################
SRC_ALL += session/media/audiomonitor.cc
SRC_ALL += session/media/audiomonitor.h
SRC_ALL += session/media/bundlefilter.cc
SRC_ALL += session/media/bundlefilter.h
SRC_ALL += session/media/channel.cc
SRC_ALL += session/media/channel.h
SRC_ALL += session/media/channelmanager.cc
SRC_ALL += session/media/channelmanager.h
SRC_ALL += session/media/currentspeakermonitor.cc
SRC_ALL += session/media/currentspeakermonitor.h
SRC_ALL += session/media/mediamonitor.cc
SRC_ALL += session/media/mediamonitor.h
SRC_ALL += session/media/mediasession.cc
SRC_ALL += session/media/mediasession.h
SRC_ALL += session/media/mediasink.h
SRC_ALL += session/media/rtcpmuxfilter.cc
SRC_ALL += session/media/rtcpmuxfilter.h
SRC_ALL += session/media/srtpfilter.cc
SRC_ALL += session/media/srtpfilter.h
SRC_ALL += session/media/typingmonitor.cc
SRC_ALL += session/media/voicechannel.h

################################# libjingle peerconnect ##########################
SRC_ALL += app/webrtc/audiotrack.cc
SRC_ALL += app/webrtc/audiotrack.h
SRC_ALL += app/webrtc/audiotrackrenderer.cc
SRC_ALL += app/webrtc/audiotrackrenderer.h
SRC_ALL += app/webrtc/datachannel.cc
SRC_ALL += app/webrtc/datachannel.h
SRC_ALL += app/webrtc/datachannelinterface.h
SRC_ALL += app/webrtc/dtlsidentitystore.cc
SRC_ALL += app/webrtc/dtlsidentitystore.h
SRC_ALL += app/webrtc/dtmfsender.cc
SRC_ALL += app/webrtc/dtmfsender.h
SRC_ALL += app/webrtc/dtmfsenderinterface.h
SRC_ALL += app/webrtc/fakeportallocatorfactory.h
SRC_ALL += app/webrtc/jsep.h
SRC_ALL += app/webrtc/jsepicecandidate.cc
SRC_ALL += app/webrtc/jsepicecandidate.h
SRC_ALL += app/webrtc/jsepsessiondescription.cc
SRC_ALL += app/webrtc/jsepsessiondescription.h
SRC_ALL += app/webrtc/localaudiosource.cc
SRC_ALL += app/webrtc/localaudiosource.h
SRC_ALL += app/webrtc/mediaconstraintsinterface.cc
SRC_ALL += app/webrtc/mediaconstraintsinterface.h
SRC_ALL += app/webrtc/mediastream.cc
SRC_ALL += app/webrtc/mediastream.h
SRC_ALL += app/webrtc/mediastreamhandler.cc
SRC_ALL += app/webrtc/mediastreamhandler.h
SRC_ALL += app/webrtc/mediastreaminterface.h
SRC_ALL += app/webrtc/mediastreamprovider.h
SRC_ALL += app/webrtc/mediastreamproxy.h
SRC_ALL += app/webrtc/mediastreamsignaling.cc
SRC_ALL += app/webrtc/mediastreamsignaling.h
SRC_ALL += app/webrtc/mediastreamtrack.h
SRC_ALL += app/webrtc/mediastreamtrackproxy.h
SRC_ALL += app/webrtc/notifier.h
SRC_ALL += app/webrtc/peerconnection.cc
SRC_ALL += app/webrtc/peerconnection.h
SRC_ALL += app/webrtc/peerconnectionfactory.cc
SRC_ALL += app/webrtc/peerconnectionfactory.h
SRC_ALL += app/webrtc/peerconnectionfactoryproxy.h
SRC_ALL += app/webrtc/peerconnectioninterface.h
SRC_ALL += app/webrtc/peerconnectionproxy.h
SRC_ALL += app/webrtc/portallocatorfactory.cc
SRC_ALL += app/webrtc/portallocatorfactory.h
SRC_ALL += app/webrtc/proxy.h
SRC_ALL += app/webrtc/remoteaudiosource.cc
SRC_ALL += app/webrtc/remoteaudiosource.h
SRC_ALL += app/webrtc/remotevideocapturer.cc
SRC_ALL += app/webrtc/remotevideocapturer.h
SRC_ALL += app/webrtc/sctputils.cc
SRC_ALL += app/webrtc/sctputils.h
SRC_ALL += app/webrtc/statscollector.cc
SRC_ALL += app/webrtc/statscollector.h
SRC_ALL += app/webrtc/statstypes.cc
SRC_ALL += app/webrtc/statstypes.h
SRC_ALL += app/webrtc/streamcollection.h
SRC_ALL += app/webrtc/videosource.cc
SRC_ALL += app/webrtc/videosource.h
SRC_ALL += app/webrtc/videosourceinterface.h
SRC_ALL += app/webrtc/videosourceproxy.h
SRC_ALL += app/webrtc/videotrack.cc
SRC_ALL += app/webrtc/videotrack.h
SRC_ALL += app/webrtc/videotrackrenderers.cc
SRC_ALL += app/webrtc/videotrackrenderers.h
SRC_ALL += app/webrtc/webrtcsdp.cc
SRC_ALL += app/webrtc/webrtcsdp.h
SRC_ALL += app/webrtc/webrtcsession.cc
SRC_ALL += app/webrtc/webrtcsession.h
SRC_ALL += app/webrtc/webrtcsessiondescriptionfactory.cc
SRC_ALL += app/webrtc/webrtcsessiondescriptionfactory.h
SRC_ALL += app/webrtc/test/fakeaudiocapturemodule.cc
SRC_ALL += app/webrtc/test/fakeaudiocapturemodule.h

SRC_C := $(filter %.c,$(SRC_ALL))
SRC_CC := $(filter %.cc,$(SRC_ALL))

OBJ_C = $(patsubst %.c,%.o,$(sort $(SRC_C)))
OBJ_CC = $(patsubst %.cc,%.o,$(sort $(SRC_CC)))

.PHONY : all lib clean

all:$(OBJ_C) $(OBJ_CC) 

lib: $(OBJ_C) $(OBJ_CC)
	$(AR) -rc $(LIBS).a $(OBJ_C) $(OBJ_CC)

	
clean:
	$(AT)-rm -rf $(OBJ_C)
	$(AT)-rm -rf $(OBJ_CC)
	$(AT)-rm -rf $(LIBS).a

$(OBJ_C):%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_CC):%.o: %.cc
	$(CXX) $(CFLAGS) -c $< -o $@

