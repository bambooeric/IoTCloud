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
############################ Common ##############################
SRC_ALL += interface/fec_receiver.h
SRC_ALL += interface/receive_statistics.h
SRC_ALL += interface/remote_ntp_time_estimator.h
SRC_ALL += interface/rtp_header_parser.h
SRC_ALL += interface/rtp_payload_registry.h
SRC_ALL += interface/rtp_receiver.h
SRC_ALL += interface/rtp_rtcp.h
SRC_ALL += interface/rtp_rtcp_defines.h
SRC_ALL += source/bitrate.cc
SRC_ALL += source/bitrate.h
SRC_ALL += source/byte_io.h
SRC_ALL += source/fec_receiver_impl.cc
SRC_ALL += source/fec_receiver_impl.h
SRC_ALL += source/packet_loss_stats.cc
SRC_ALL += source/packet_loss_stats.h
SRC_ALL += source/receive_statistics_impl.cc
SRC_ALL += source/receive_statistics_impl.h
SRC_ALL += source/remote_ntp_time_estimator.cc
SRC_ALL += source/rtp_header_parser.cc
SRC_ALL += source/rtp_rtcp_config.h
SRC_ALL += source/rtp_rtcp_impl.cc
SRC_ALL += source/rtp_rtcp_impl.h
SRC_ALL += source/rtcp_packet.cc
SRC_ALL += source/rtcp_packet.h
SRC_ALL += source/rtcp_packet/transport_feedback.cc
SRC_ALL += source/rtcp_packet/transport_feedback.h
SRC_ALL += source/rtcp_receiver.cc
SRC_ALL += source/rtcp_receiver.h
SRC_ALL += source/rtcp_receiver_help.cc
SRC_ALL += source/rtcp_receiver_help.h
SRC_ALL += source/rtcp_sender.cc
SRC_ALL += source/rtcp_sender.h
SRC_ALL += source/rtcp_utility.cc
SRC_ALL += source/rtcp_utility.h
SRC_ALL += source/rtp_header_extension.cc
SRC_ALL += source/rtp_header_extension.h
SRC_ALL += source/rtp_receiver_impl.cc
SRC_ALL += source/rtp_receiver_impl.h
SRC_ALL += source/rtp_sender.cc
SRC_ALL += source/rtp_sender.h
SRC_ALL += source/rtp_utility.cc
SRC_ALL += source/rtp_utility.h
SRC_ALL += source/ssrc_database.cc
SRC_ALL += source/ssrc_database.h
SRC_ALL += source/tmmbr_help.cc
SRC_ALL += source/tmmbr_help.h
#################### Audio Files #######################
SRC_ALL += source/dtmf_queue.cc
SRC_ALL += source/dtmf_queue.h
SRC_ALL += source/rtp_receiver_audio.cc
SRC_ALL += source/rtp_receiver_audio.h
SRC_ALL += source/rtp_sender_audio.cc
SRC_ALL += source/rtp_sender_audio.h
#################### Video Files #######################
SRC_ALL += source/fec_private_tables_random.h
SRC_ALL += source/fec_private_tables_bursty.h
SRC_ALL += source/forward_error_correction.cc
SRC_ALL += source/forward_error_correction.h
SRC_ALL += source/forward_error_correction_internal.cc
SRC_ALL += source/forward_error_correction_internal.h
SRC_ALL += source/h264_sps_parser.cc
SRC_ALL += source/h264_sps_parser.h
SRC_ALL += source/producer_fec.cc
SRC_ALL += source/producer_fec.h
SRC_ALL += source/rtp_packet_history.cc
SRC_ALL += source/rtp_packet_history.h
SRC_ALL += source/rtp_payload_registry.cc
SRC_ALL += source/rtp_receiver_strategy.cc
SRC_ALL += source/rtp_receiver_strategy.h
SRC_ALL += source/rtp_receiver_video.cc
SRC_ALL += source/rtp_receiver_video.h
SRC_ALL += source/rtp_sender_video.cc
SRC_ALL += source/rtp_sender_video.h
SRC_ALL += source/video_codec_information.h
SRC_ALL += source/rtp_format.cc
SRC_ALL += source/rtp_format.h
SRC_ALL += source/rtp_format_h264.cc
SRC_ALL += source/rtp_format_h264.h
SRC_ALL += source/rtp_format_vp8.cc
SRC_ALL += source/rtp_format_vp8.h
SRC_ALL += source/rtp_format_vp9.cc
SRC_ALL += source/rtp_format_vp9.h
SRC_ALL += source/rtp_format_video_generic.cc
SRC_ALL += source/rtp_format_video_generic.h
SRC_ALL += source/vp8_partition_aggregator.cc
SRC_ALL += source/vp8_partition_aggregator.h
###################### Mocks ##########################
SRC_ALL += mocks/mock_rtp_rtcp.h
SRC_ALL += source/mock/mock_rtp_payload_strategy.h

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

	


