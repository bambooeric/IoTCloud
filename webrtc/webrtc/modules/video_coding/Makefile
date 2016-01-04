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
CFLAGS += -I$(WEBRTC_PATH)/../third_party/libvpx/source/libvpx
CFLAGS += -I$(WEBRTC_PATH)/../third_party/libyuv/include

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

CXXFLAGS += $(CFLAGS)
CXXFLAGS += -std=c++11 -fpermissive

#################################################################################
#################### main ##################### 
SRC_ALL += main/interface/video_coding.h
SRC_ALL += main/interface/video_coding_defines.h
SRC_ALL += main/source/codec_database.h
SRC_ALL += main/source/codec_timer.h
SRC_ALL += main/source/content_metrics_processing.h
SRC_ALL += main/source/decoding_state.h
SRC_ALL += main/source/encoded_frame.h
SRC_ALL += main/source/fec_tables_xor.h
SRC_ALL += main/source/frame_buffer.h
SRC_ALL += main/source/generic_decoder.h
SRC_ALL += main/source/generic_encoder.h
SRC_ALL += main/source/inter_frame_delay.h
SRC_ALL += main/source/internal_defines.h
SRC_ALL += main/source/jitter_buffer.h
SRC_ALL += main/source/jitter_buffer_common.h
SRC_ALL += main/source/jitter_estimator.h
SRC_ALL += main/source/media_opt_util.h
SRC_ALL += main/source/media_optimization.h
SRC_ALL += main/source/nack_fec_tables.h
SRC_ALL += main/source/packet.h
SRC_ALL += main/source/qm_select_data.h
SRC_ALL += main/source/qm_select.h
SRC_ALL += main/source/receiver.h
SRC_ALL += main/source/rtt_filter.h
SRC_ALL += main/source/session_info.h
SRC_ALL += main/source/timestamp_map.h
SRC_ALL += main/source/timing.h
SRC_ALL += main/source/video_coding_impl.h
SRC_ALL += main/source/codec_database.cc
SRC_ALL += main/source/codec_timer.cc
SRC_ALL += main/source/content_metrics_processing.cc
SRC_ALL += main/source/decoding_state.cc
SRC_ALL += main/source/encoded_frame.cc
SRC_ALL += main/source/frame_buffer.cc
SRC_ALL += main/source/generic_decoder.cc
SRC_ALL += main/source/generic_encoder.cc
SRC_ALL += main/source/inter_frame_delay.cc
SRC_ALL += main/source/jitter_buffer.cc
SRC_ALL += main/source/jitter_estimator.cc
SRC_ALL += main/source/media_opt_util.cc
SRC_ALL += main/source/media_optimization.cc
SRC_ALL += main/source/packet.cc
SRC_ALL += main/source/qm_select.cc
SRC_ALL += main/source/receiver.cc
SRC_ALL += main/source/rtt_filter.cc
SRC_ALL += main/source/session_info.cc
SRC_ALL += main/source/timestamp_map.cc
SRC_ALL += main/source/timing.cc
SRC_ALL += main/source/video_coding_impl.cc
SRC_ALL += main/source/video_sender.cc
SRC_ALL += main/source/video_receiver.cc
###################### utility #######################
SRC_ALL += utility/frame_dropper.cc
SRC_ALL += utility/include/frame_dropper.h
SRC_ALL += utility/include/moving_average.h
SRC_ALL += utility/include/quality_scaler.h
SRC_ALL += utility/include/vp8_header_parser.h
SRC_ALL += utility/quality_scaler.cc
SRC_ALL += utility/vp8_header_parser.cc
###################### h264 codecs #######################
SRC_ALL += codecs/h264/h264.cc
SRC_ALL += codecs/h264/include/h264.h
###################### i420 codecs #######################
SRC_ALL += codecs/i420/main/source/i420.cc
SRC_ALL += codecs/i420/main/interface/i420.h
###################### vp8 codecs #######################
#SRC_ALL += codecs/vp8/default_temporal_layers.cc
#SRC_ALL += codecs/vp8/default_temporal_layers.h
#SRC_ALL += codecs/vp8/include/vp8.h
#SRC_ALL += codecs/vp8/include/vp8_common_types.h
#SRC_ALL += codecs/vp8/realtime_temporal_layers.cc
#SRC_ALL += codecs/vp8/reference_picture_selection.cc
#SRC_ALL += codecs/vp8/reference_picture_selection.h
#SRC_ALL += codecs/vp8/screenshare_layers.cc
#SRC_ALL += codecs/vp8/screenshare_layers.h
#SRC_ALL += codecs/vp8/simulcast_encoder_adapter.cc
#SRC_ALL += codecs/vp8/simulcast_encoder_adapter.h
#SRC_ALL += codecs/vp8/temporal_layers.h
#SRC_ALL += codecs/vp8/vp8_factory.cc
#SRC_ALL += codecs/vp8/vp8_factory.h
#SRC_ALL += codecs/vp8/vp8_impl.cc
#SRC_ALL += codecs/vp8/vp8_impl.h
SRC_ALL += codecs/vp8/vp8_dummy_impl.cc
###################### vp9 codecs #######################
SRC_ALL += codecs/vp9/vp9_dummy_impl.cc

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
	$(CXX) $(CXXFLAGS) -c $< -o $@

	


