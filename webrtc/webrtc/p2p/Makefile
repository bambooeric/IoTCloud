#=================================================================================
# export variable
#=================================================================================
ifeq ($(CFG_EXPORT_FLAG),)
include ../../config.mak
endif

#=================================================================================
# local variable
#=================================================================================
LIBS :=librtc_p2p
WEBRTC_PATH = ../../webrtc
INSTALL_DIR := ../../out/lib

##################################################################################
CFLAGS += -I./
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

#################################################################################
SRC_ALL += base/asyncstuntcpsocket.cc
SRC_ALL += base/asyncstuntcpsocket.h
SRC_ALL += base/basicpacketsocketfactory.cc
SRC_ALL += base/basicpacketsocketfactory.h
SRC_ALL += base/candidate.h
SRC_ALL += base/common.h
SRC_ALL += base/constants.cc
SRC_ALL += base/constants.h
SRC_ALL += base/dtlstransportchannel.cc
SRC_ALL += base/dtlstransportchannel.h
SRC_ALL += base/p2ptransport.cc
SRC_ALL += base/p2ptransport.h
SRC_ALL += base/p2ptransportchannel.cc
SRC_ALL += base/p2ptransportchannel.h
SRC_ALL += base/packetsocketfactory.h
SRC_ALL += base/port.cc
SRC_ALL += base/port.h
SRC_ALL += base/portallocator.cc
SRC_ALL += base/portallocator.h
SRC_ALL += base/portinterface.h
SRC_ALL += base/pseudotcp.cc
SRC_ALL += base/pseudotcp.h
SRC_ALL += base/rawtransport.cc
SRC_ALL += base/rawtransport.h
SRC_ALL += base/rawtransportchannel.cc
SRC_ALL += base/rawtransportchannel.h
SRC_ALL += base/relayport.cc
SRC_ALL += base/relayport.h
SRC_ALL += base/relayserver.cc
SRC_ALL += base/relayserver.h
SRC_ALL += base/session.cc
SRC_ALL += base/session.h
SRC_ALL += base/sessiondescription.cc
SRC_ALL += base/sessiondescription.h
SRC_ALL += base/sessionid.h
SRC_ALL += base/stun.cc
SRC_ALL += base/stun.h
SRC_ALL += base/stunport.cc
SRC_ALL += base/stunport.h
SRC_ALL += base/stunrequest.cc
SRC_ALL += base/stunrequest.h
SRC_ALL += base/stunserver.cc
SRC_ALL += base/stunserver.h
SRC_ALL += base/tcpport.cc
SRC_ALL += base/tcpport.h
SRC_ALL += base/transport.cc
SRC_ALL += base/transport.h
SRC_ALL += base/transportchannel.cc
SRC_ALL += base/transportchannel.h
SRC_ALL += base/transportchannelimpl.h
SRC_ALL += base/transportchannelproxy.cc
SRC_ALL += base/transportchannelproxy.h
SRC_ALL += base/transportdescription.cc
SRC_ALL += base/transportdescription.h
SRC_ALL += base/transportdescriptionfactory.cc
SRC_ALL += base/transportdescriptionfactory.h
SRC_ALL += base/transportinfo.h
SRC_ALL += base/turnport.cc
SRC_ALL += base/turnport.h
SRC_ALL += base/turnserver.cc
SRC_ALL += base/turnserver.h
SRC_ALL += base/udpport.h
SRC_ALL += client/basicportallocator.cc
SRC_ALL += client/basicportallocator.h
SRC_ALL += client/httpportallocator.cc
SRC_ALL += client/httpportallocator.h
SRC_ALL += client/socketmonitor.cc
SRC_ALL += client/socketmonitor.h

SRC_C := $(filter %.c,$(SRC_ALL))
SRC_CC := $(filter %.cc,$(SRC_ALL))

OBJ_C = $(patsubst %.c,%.o,$(sort $(SRC_C)))
OBJ_CC = $(patsubst %.cc,%.o,$(sort $(SRC_CC)))

.PHONY : all lib clean install

all:$(OBJ_C) $(OBJ_CC) 

lib: $(OBJ_C) $(OBJ_CC)
	$(AR) -rc $(LIBS).a $(OBJ_C) $(OBJ_CC)

install:
	cp -af $(LIBS).a $(INSTALL_DIR)


clean:
	$(AT)-rm -rf $(OBJ_C)
	$(AT)-rm -rf $(OBJ_CC)
	$(AT)-rm -rf $(LIBS).a

$(OBJ_C):%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_CC):%.o: %.cc
	$(CXX) $(CFLAGS) -c $< -o $@



