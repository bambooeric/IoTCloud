#=================================================================================
# export variable
#=================================================================================
ifeq ($(CFG_EXPORT_FLAG),)
include ../../../config.mak
endif

#=================================================================================
# local variable
#=================================================================================
WEBRTC_PATH = ../../../webrtc

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
SRC_ALL += include/audio_device.h
SRC_ALL += include/audio_device_defines.h
SRC_ALL += audio_device_buffer.cc
SRC_ALL += audio_device_buffer.h
SRC_ALL += audio_device_generic.cc
SRC_ALL += audio_device_generic.h
SRC_ALL += audio_device_config.h
SRC_ALL += dummy/audio_device_dummy.cc
SRC_ALL += dummy/audio_device_dummy.h
SRC_ALL += dummy/file_audio_device.cc
SRC_ALL += dummy/file_audio_device.h
SRC_ALL += dummy/file_audio_device_factory.cc
SRC_ALL += dummy/file_audio_device_factory.h
#SRC_ALL += fine_audio_buffer.cc
#SRC_ALL += fine_audio_buffer.h
#SRC_ALL += linux/alsasymboltable_linux.cc
#SRC_ALL += linux/alsasymboltable_linux.h
#SRC_ALL += linux/audio_device_alsa_linux.cc
#SRC_ALL += linux/audio_device_alsa_linux.h
#SRC_ALL += linux/audio_mixer_manager_alsa_linux.cc
#SRC_ALL += linux/audio_mixer_manager_alsa_linux.h
#SRC_ALL += linux/latebindingsymboltable_linux.cc
#SRC_ALL += linux/latebindingsymboltable_linux.h
#SRC_ALL += linux/audio_device_pulse_linux.cc
#SRC_ALL += linux/audio_device_pulse_linux.h
#SRC_ALL += linux/audio_mixer_manager_pulse_linux.cc
#SRC_ALL += linux/audio_mixer_manager_pulse_linux.h
#SRC_ALL += linux/pulseaudiosymboltable_linux.cc
#SRC_ALL += linux/pulseaudiosymboltable_linux.h

SRC_C := $(filter %.c,$(SRC_ALL))
SRC_CC := $(filter %.cc,$(SRC_ALL))

OBJ_C = $(patsubst %.c,%.o,$(sort $(SRC_C)))
OBJ_CC = $(patsubst %.cc,%.o,$(sort $(SRC_CC)))

.PHONY : all lib clean

all:$(OBJ_C) $(OBJ_CC) 

clean:
	$(AT)-rm -rf $(OBJ_C)
	$(AT)-rm -rf $(OBJ_CC)
	$(AT)-rm -rf $(LIBS).a

$(OBJ_C):%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_CC):%.o: %.cc
	$(CXX) $(CFLAGS) -c $< -o $@

	


