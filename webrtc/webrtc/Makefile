#=================================================================================
# export variable
#=================================================================================
ifeq ($(CFG_EXPORT_FLAG),)
include ../config.mak
endif

#=================================================================================
# local variable
#=================================================================================
LIBS :=librtc
WEBRTC_PATH = ../webrtc
INSTALL_DIR = ../out/lib
##################################################################################
CFLAGS += -I./
CFLAGS += -I$(WEBRTC_PATH)
CFLAGS += -I$(WEBRTC_PATH)/../
CFLAGS += -I$(WEBRTC_PATH)/common_audio/resampler/include
CFLAGS += -I$(WEBRTC_PATH)/common_audio/signal_processing/include
CFLAGS += -I$(WEBRTC_PATH)/common_audio/vad/include
CFLAGS += -I$(WEBRTC_PATH)/common_video/interface
CFLAGS += -I$(WEBRTC_PATH)/modules/audio_coding/codecs/cng/include
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
OBJ_ALL +=$(WEBRTC_PATH)/base/*.o
OBJ_ALL +=$(WEBRTC_PATH)/system_wrappers/source/*.o
OBJ_ALL +=$(WEBRTC_PATH)/common_audio/resampler/*.o
OBJ_ALL +=$(WEBRTC_PATH)/common_audio/signal_processing/*.o
OBJ_ALL +=$(WEBRTC_PATH)/common_audio/vad/*.o
OBJ_ALL +=$(WEBRTC_PATH)/common_audio/*.o
OBJ_ALL +=$(WEBRTC_PATH)/common_video/*.o
OBJ_ALL +=$(WEBRTC_PATH)/common_video/libyuv/*.o
OBJ_ALL +=$(WEBRTC_PATH)/p2p/base/*.o
OBJ_ALL +=$(WEBRTC_PATH)/p2p/client/*.o
OBJ_ALL +=$(WEBRTC_PATH)/modules/audio_coding/neteq/*.o
OBJ_ALL +=$(WEBRTC_PATH)/modules/audio_coding/main/acm2/*.o
OBJ_ALL +=$(WEBRTC_PATH)/modules/audio_coding/codecs/*.o
OBJ_ALL +=$(WEBRTC_PATH)/modules/audio_coding/codecs/cng/*.o
OBJ_ALL +=$(WEBRTC_PATH)/modules/audio_coding/codecs/g711/*.o
OBJ_ALL +=$(WEBRTC_PATH)/modules/audio_coding/codecs/red/*.o
OBJ_ALL +=$(WEBRTC_PATH)/modules/audio_coding/codecs/isac/main/source/*.o
OBJ_ALL +=$(WEBRTC_PATH)/modules/audio_conference_mixer/source/*.o
OBJ_ALL +=$(WEBRTC_PATH)/modules/audio_device/dummy/*.o
OBJ_ALL +=$(WEBRTC_PATH)/modules/audio_device/*.o
OBJ_ALL +=$(WEBRTC_PATH)/modules/audio_processing/*.o
OBJ_ALL +=$(WEBRTC_PATH)/modules/audio_processing/aec/*.o
OBJ_ALL +=$(WEBRTC_PATH)/modules/audio_processing/aecm/*.o
OBJ_ALL +=$(WEBRTC_PATH)/modules/audio_processing/agc/*.o
OBJ_ALL +=$(WEBRTC_PATH)/modules/audio_processing/agc/legacy/*.o
OBJ_ALL +=$(WEBRTC_PATH)/modules/audio_processing/beamformer/*.o
OBJ_ALL +=$(WEBRTC_PATH)/modules/audio_processing/intelligibility/*.o
OBJ_ALL +=$(WEBRTC_PATH)/modules/audio_processing/ns/*.o
OBJ_ALL +=$(WEBRTC_PATH)/modules/audio_processing/transient/*.o
OBJ_ALL +=$(WEBRTC_PATH)/modules/audio_processing/utility/*.o
OBJ_ALL +=$(WEBRTC_PATH)/modules/audio_processing/vad/*.o
OBJ_ALL +=$(WEBRTC_PATH)/modules/bitrate_controller/*.o
OBJ_ALL +=$(WEBRTC_PATH)/modules/media_file/source/*.o
OBJ_ALL +=$(WEBRTC_PATH)/modules/pacing/*.o
OBJ_ALL +=$(WEBRTC_PATH)/modules/remote_bitrate_estimator/*.o
OBJ_ALL +=$(WEBRTC_PATH)/modules/rtp_rtcp/source/*.o
OBJ_ALL +=$(WEBRTC_PATH)/modules/utility/source/*.o
OBJ_ALL +=$(WEBRTC_PATH)/modules/video_capture/external/*.o
OBJ_ALL +=$(WEBRTC_PATH)/modules/video_capture/*.o
OBJ_ALL +=$(WEBRTC_PATH)/modules/video_coding/codecs/i420/main/source/*.o
OBJ_ALL +=$(WEBRTC_PATH)/modules/video_coding/codecs/h264/*.o
OBJ_ALL +=$(WEBRTC_PATH)/modules/video_coding/codecs/vp8/*.o
OBJ_ALL +=$(WEBRTC_PATH)/modules/video_coding/codecs/vp9/*.o
OBJ_ALL +=$(WEBRTC_PATH)/modules/video_coding/main/source/*.o
OBJ_ALL +=$(WEBRTC_PATH)/modules/video_coding/utility/*.o
OBJ_ALL +=$(WEBRTC_PATH)/modules/video_processing/main/source/*.o
OBJ_ALL +=$(WEBRTC_PATH)/modules/video_render/external/*.o
OBJ_ALL +=$(WEBRTC_PATH)/modules/video_render/*.o
OBJ_ALL +=$(WEBRTC_PATH)/voice_engine/*.o
OBJ_ALL +=$(WEBRTC_PATH)/video_engine/*.o
OBJ_ALL +=$(WEBRTC_PATH)/video/*.o
OBJ_ALL +=$(WEBRTC_PATH)/libjingle/xmpp/*.o
OBJ_ALL +=$(WEBRTC_PATH)/libjingle/xmllite/*.o

#####################################################################
SRC_ALL +=$(WEBRTC_PATH)/common_types.cc
SRC_ALL +=$(WEBRTC_PATH)/common_types.h
SRC_ALL +=$(WEBRTC_PATH)/config.cc
SRC_ALL +=$(WEBRTC_PATH)/config.h
SRC_ALL +=$(WEBRTC_PATH)/engine_configurations.h
SRC_ALL +=$(WEBRTC_PATH)/typedefs.h

SRC_C := $(filter %.c,$(SRC_ALL))
SRC_CC := $(filter %.cc,$(SRC_ALL))

OBJ_C = $(patsubst %.c,%.o,$(sort $(SRC_C)))
OBJ_CC = $(patsubst %.cc,%.o,$(sort $(SRC_CC)))

OBJ_ALL += $(OBJ_C)
OBJ_ALL += $(OBJ_CC)

######################################################################
.PHONY : all clean install depend

all: depend $(OBJ_C) $(OBJ_CC) $(LIBS)

install:
	cp -af $(LIBS).a $(INSTALL_DIR)

clean:
	$(AT)-rm -rf $(OBJ_ALL)
	$(AT)-rm -rf $(LIBS).a

$(OBJ_C):%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_CC):%.o: %.cc
	$(CXX) $(CFLAGS) -c $< -o $@

$(LIBS): $(OBJ_ALL)
	$(AR) -rc $(LIBS).a $(OBJ_ALL)

######################################################################
.PHONY : depend depend_clean
depend:
	make -j 2 -C $(WEBRTC_PATH)/base all
	make -j 2 -C $(WEBRTC_PATH)/system_wrappers all
	make -j 2 -C $(WEBRTC_PATH)/common_audio all
	make -j 2 -C $(WEBRTC_PATH)/common_video all
	make -j 2 -C $(WEBRTC_PATH)/p2p all
	make -j 2 -C $(WEBRTC_PATH)/libjingle all
	make -j 2 -C $(WEBRTC_PATH)/modules/audio_coding all
	make -j 2 -C $(WEBRTC_PATH)/modules/audio_conference_mixer all
	make -j 2 -C $(WEBRTC_PATH)/modules/audio_device all
	make -j 2 -C $(WEBRTC_PATH)/modules/audio_processing all
	make -j 2 -C $(WEBRTC_PATH)/modules/bitrate_controller all
	make -j 2 -C $(WEBRTC_PATH)/modules/media_file all
	make -j 2 -C $(WEBRTC_PATH)/modules/pacing all
	make -j 2 -C $(WEBRTC_PATH)/modules/remote_bitrate_estimator all
	make -j 2 -C $(WEBRTC_PATH)/modules/rtp_rtcp all
	make -j 2 -C $(WEBRTC_PATH)/modules/utility all
	make -j 2 -C $(WEBRTC_PATH)/modules/video_capture all
	make -j 2 -C $(WEBRTC_PATH)/modules/video_coding all
	make -j 2 -C $(WEBRTC_PATH)/modules/video_processing all
	make -j 2 -C $(WEBRTC_PATH)/modules/video_render all
	make -j 2 -C $(WEBRTC_PATH)/voice_engine all
	make -j 2 -C $(WEBRTC_PATH)/video_engine all
	make -j 2 -C $(WEBRTC_PATH)/video all


	

