#=================================================================================
# export variable
#=================================================================================
ifeq ($(CFG_EXPORT_FLAG),)
include ../../../config.mak
endif

#=================================================================================
# local variable
#=================================================================================
TARGET = client
WEBRTC_PATH = ../../../webrtc

##################################################################################
CFLAGS += -I$(WEBRTC_PATH)/../third_party/expat/files/lib
CFLAGS += -I$(WEBRTC_PATH)/../third_party/jsoncpp/source/include
CFLAGS += -I$(WEBRTC_PATH)/../third_party/openssl/include

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

LDFLAGS += -L$(WEBRTC_PATH)/../out/lib -ltalk -lrtc -lexpat -ljsoncpp -lsrtp -lusrsctp -lyuv -ljpeg -L. -lstdc++ -lssl -lcrypto
LDFLAGS += -lm -ldl -lrt -lpthread
#LDFLAGS += --static 

#################################################################################
SRC_ALL += callclient.cc
SRC_ALL += callclient.h
SRC_ALL += console.cc
SRC_ALL += console.h
SRC_ALL += main.cc
SRC_ALL += randomtask.h
SRC_ALL += randomtask.cc
SRC_ALL += conductor.h
SRC_ALL += conductor.cc
SRC_ALL += defaults.h
SRC_ALL += defaults.cc
SRC_ALL += config.h
SRC_ALL += config.cc


SRC_C := $(filter %.c,$(SRC_ALL))
SRC_CC := $(filter %.cc,$(SRC_ALL))

OBJ_C = $(patsubst %.c,%.o,$(sort $(SRC_C)))
OBJ_CC = $(patsubst %.cc,%.o,$(sort $(SRC_CC)))

.PHONY : all lib clean install

all:$(OBJ_C) $(OBJ_CC) target

target: $(OBJ_C) $(OBJ_CC)
	$(CXX) -o $(TARGET) $(OBJ_C) $(OBJ_CC) $(LDFLAGS)
	
clean:
	$(AT)-rm -rf $(OBJ_C)
	$(AT)-rm -rf $(OBJ_CC)
	$(AT)-rm -rf $(LIB).a

install:
	sudo cp -af lib* /home/ykx/shared
	sudo cp -af $(TARGET) /home/ykx/shared 

$(OBJ_C):%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_CC):%.o: %.cc
	$(CXX) $(CFLAGS) -c $< -o $@



