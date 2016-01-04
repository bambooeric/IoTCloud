#=================================================================================
# export variable
#=================================================================================
ifeq ($(CFG_EXPORT_FLAG),)
include ../../config.mak
endif

#=================================================================================
# local variable
#=================================================================================
LIBS :=librtc_voice_engine
WEBRTC_PATH = ../../webrtc


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
RC_ALL += include/voe_audio_processing.h
SRC_ALL += include/voe_base.h
SRC_ALL += include/voe_codec.h
SRC_ALL += include/voe_dtmf.h
SRC_ALL += include/voe_errors.h
SRC_ALL += include/voe_external_media.h
SRC_ALL += include/voe_file.h
SRC_ALL += include/voe_hardware.h
SRC_ALL += include/voe_neteq_stats.h
SRC_ALL += include/voe_network.h
SRC_ALL += include/voe_rtp_rtcp.h
SRC_ALL += include/voe_video_sync.h
SRC_ALL += include/voe_volume_control.h
SRC_ALL += channel.cc
SRC_ALL += channel.h
SRC_ALL += channel_manager.cc
SRC_ALL += channel_manager.h
SRC_ALL += dtmf_inband.cc
SRC_ALL += dtmf_inband.h
SRC_ALL += dtmf_inband_queue.cc
SRC_ALL += dtmf_inband_queue.h
SRC_ALL += level_indicator.cc
SRC_ALL += level_indicator.h
SRC_ALL += monitor_module.cc
SRC_ALL += monitor_module.h
SRC_ALL += network_predictor.cc
SRC_ALL += network_predictor.h
SRC_ALL += output_mixer.cc
SRC_ALL += output_mixer.h
SRC_ALL += shared_data.cc
SRC_ALL += shared_data.h
SRC_ALL += statistics.cc
SRC_ALL += statistics.h
SRC_ALL += transmit_mixer.cc
SRC_ALL += transmit_mixer.h
SRC_ALL += utility.cc
SRC_ALL += utility.h
SRC_ALL += voe_audio_processing_impl.cc
SRC_ALL += voe_audio_processing_impl.h
SRC_ALL += voe_base_impl.cc
SRC_ALL += voe_base_impl.h
SRC_ALL += voe_codec_impl.cc
SRC_ALL += voe_codec_impl.h
SRC_ALL += voe_dtmf_impl.cc
SRC_ALL += voe_dtmf_impl.h
SRC_ALL += voe_external_media_impl.cc
SRC_ALL += voe_external_media_impl.h
SRC_ALL += voe_file_impl.cc
SRC_ALL += voe_file_impl.h
SRC_ALL += voe_hardware_impl.cc
SRC_ALL += voe_hardware_impl.h
SRC_ALL += voe_neteq_stats_impl.cc
SRC_ALL += voe_neteq_stats_impl.h
SRC_ALL += voe_network_impl.cc
SRC_ALL += voe_network_impl.h
SRC_ALL += voe_rtp_rtcp_impl.cc
SRC_ALL += voe_rtp_rtcp_impl.h
SRC_ALL += voe_video_sync_impl.cc
SRC_ALL += voe_video_sync_impl.h
SRC_ALL += voe_volume_control_impl.cc
SRC_ALL += voe_volume_control_impl.h
SRC_ALL += voice_engine_defines.h
SRC_ALL += voice_engine_impl.cc
SRC_ALL += voice_engine_impl.h
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



