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
CFLAGS += -I$(WEBRTC_PATH)/modules/audio_coding/codecs/cng/include
CFLAGS += -I$(WEBRTC_PATH)/modules/audio_coding/neteq
CFLAGS += -I$(WEBRTC_PATH)/modules/audio_coding/codecs/g711/include
CFLAGS += -I$(WEBRTC_PATH)/modules/audio_coding/codecs/isac/main/interface
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
SRC_ALL += main/acm2/acm_codec_database.cc
SRC_ALL += main/acm2/acm_codec_database.h
SRC_ALL += main/acm2/acm_common_defs.h
SRC_ALL += main/acm2/acm_receiver.cc
SRC_ALL += main/acm2/acm_receiver.h
SRC_ALL += main/acm2/acm_resampler.cc
SRC_ALL += main/acm2/acm_resampler.h
SRC_ALL += main/acm2/audio_coding_module.cc
SRC_ALL += main/acm2/audio_coding_module_impl.cc
SRC_ALL += main/acm2/audio_coding_module_impl.h
SRC_ALL += main/acm2/call_statistics.cc
SRC_ALL += main/acm2/call_statistics.h
SRC_ALL += main/acm2/codec_manager.cc
SRC_ALL += main/acm2/codec_manager.h
SRC_ALL += main/acm2/codec_owner.cc
SRC_ALL += main/acm2/codec_owner.h
SRC_ALL += main/acm2/initial_delay_manager.cc
SRC_ALL += main/acm2/initial_delay_manager.h
SRC_ALL += main/acm2/nack.cc
SRC_ALL += main/acm2/nack.h
SRC_ALL += main/interface/audio_coding_module.h
SRC_ALL += main/interface/audio_coding_module_typedefs.h

#################################### neteq #####################################
SRC_ALL += neteq/interface/neteq.h
SRC_ALL += neteq/accelerate.cc
SRC_ALL += neteq/accelerate.h
#SRC_ALL += neteq/audio_classifier.cc
#SRC_ALL += neteq/audio_classifier.h
SRC_ALL += neteq/audio_decoder_impl.cc
SRC_ALL += neteq/audio_decoder_impl.h
SRC_ALL += neteq/audio_multi_vector.cc
SRC_ALL += neteq/audio_multi_vector.h
SRC_ALL += neteq/audio_vector.cc
SRC_ALL += neteq/audio_vector.h
SRC_ALL += neteq/background_noise.cc
SRC_ALL += neteq/background_noise.h
SRC_ALL += neteq/buffer_level_filter.cc
SRC_ALL += neteq/buffer_level_filter.h
SRC_ALL += neteq/comfort_noise.cc
SRC_ALL += neteq/comfort_noise.h
SRC_ALL += neteq/decision_logic.cc
SRC_ALL += neteq/decision_logic.h
SRC_ALL += neteq/decision_logic_fax.cc
SRC_ALL += neteq/decision_logic_fax.h
SRC_ALL += neteq/decision_logic_normal.cc
SRC_ALL += neteq/decision_logic_normal.h
SRC_ALL += neteq/decoder_database.cc
SRC_ALL += neteq/decoder_database.h
SRC_ALL += neteq/defines.h
SRC_ALL += neteq/delay_manager.cc
SRC_ALL += neteq/delay_manager.h
SRC_ALL += neteq/delay_peak_detector.cc
SRC_ALL += neteq/delay_peak_detector.h
SRC_ALL += neteq/dsp_helper.cc
SRC_ALL += neteq/dsp_helper.h
SRC_ALL += neteq/dtmf_buffer.cc
SRC_ALL += neteq/dtmf_buffer.h
SRC_ALL += neteq/dtmf_tone_generator.cc
SRC_ALL += neteq/dtmf_tone_generator.h
SRC_ALL += neteq/expand.cc
SRC_ALL += neteq/expand.h
SRC_ALL += neteq/merge.cc
SRC_ALL += neteq/merge.h
SRC_ALL += neteq/neteq_impl.cc
SRC_ALL += neteq/neteq_impl.h
SRC_ALL += neteq/neteq.cc
SRC_ALL += neteq/statistics_calculator.cc
SRC_ALL += neteq/statistics_calculator.h
SRC_ALL += neteq/normal.cc
SRC_ALL += neteq/normal.h
SRC_ALL += neteq/packet_buffer.cc
SRC_ALL += neteq/packet_buffer.h
SRC_ALL += neteq/payload_splitter.cc
SRC_ALL += neteq/payload_splitter.h
SRC_ALL += neteq/post_decode_vad.cc
SRC_ALL += neteq/post_decode_vad.h
SRC_ALL += neteq/preemptive_expand.cc
SRC_ALL += neteq/preemptive_expand.h
SRC_ALL += neteq/random_vector.cc
SRC_ALL += neteq/random_vector.h
SRC_ALL += neteq/rtcp.cc
SRC_ALL += neteq/rtcp.h
SRC_ALL += neteq/sync_buffer.cc
SRC_ALL += neteq/sync_buffer.h
SRC_ALL += neteq/timestamp_scaler.cc
SRC_ALL += neteq/timestamp_scaler.h
SRC_ALL += neteq/time_stretch.cc
SRC_ALL += neteq/time_stretch.h

#################################### codec ################################
SRC_ALL += codecs/audio_decoder.cc
SRC_ALL += codecs/audio_decoder.h
SRC_ALL += codecs/audio_encoder.cc
SRC_ALL += codecs/audio_encoder.h

SRC_ALL += codecs/cng/include/audio_encoder_cng.h
SRC_ALL += codecs/cng/include/webrtc_cng.h
SRC_ALL += codecs/cng/audio_encoder_cng.cc
SRC_ALL += codecs/cng/webrtc_cng.c
SRC_ALL += codecs/cng/cng_helpfuns.c
SRC_ALL += codecs/cng/cng_helpfuns.h

SRC_ALL += codecs/g711/include/g711_interface.h
SRC_ALL += codecs/g711/include/audio_encoder_pcm.h
SRC_ALL += codecs/g711/g711_interface.c
SRC_ALL += codecs/g711/g711.c
SRC_ALL += codecs/g711/g711.h
SRC_ALL += codecs/g711/audio_encoder_pcm.cc

SRC_ALL += codecs/red/audio_encoder_copy_red.h
SRC_ALL += codecs/red/audio_encoder_copy_red.cc

SRC_ALL += codecs/isac/audio_encoder_isac_t.h
SRC_ALL += codecs/isac/audio_encoder_isac_t_impl.h
SRC_ALL += codecs/isac/main/interface/audio_encoder_isac.h
SRC_ALL += codecs/isac/main/interface/isac.h
SRC_ALL += codecs/isac/main/source/arith_routines.c
SRC_ALL += codecs/isac/main/source/arith_routines_hist.c
SRC_ALL += codecs/isac/main/source/arith_routines_logist.c
SRC_ALL += codecs/isac/main/source/audio_encoder_isac.cc
SRC_ALL += codecs/isac/main/source/bandwidth_estimator.c
SRC_ALL += codecs/isac/main/source/crc.c
SRC_ALL += codecs/isac/main/source/decode.c
SRC_ALL += codecs/isac/main/source/decode_bwe.c
SRC_ALL += codecs/isac/main/source/encode.c
SRC_ALL += codecs/isac/main/source/encode_lpc_swb.c
SRC_ALL += codecs/isac/main/source/entropy_coding.c
SRC_ALL += codecs/isac/main/source/fft.c
SRC_ALL += codecs/isac/main/source/filter_functions.c
SRC_ALL += codecs/isac/main/source/filterbank_tables.c
SRC_ALL += codecs/isac/main/source/intialize.c
SRC_ALL += codecs/isac/main/source/isac.c
SRC_ALL += codecs/isac/main/source/filterbanks.c
SRC_ALL += codecs/isac/main/source/pitch_lag_tables.c
SRC_ALL += codecs/isac/main/source/lattice.c
SRC_ALL += codecs/isac/main/source/lpc_gain_swb_tables.c
SRC_ALL += codecs/isac/main/source/lpc_analysis.c
SRC_ALL += codecs/isac/main/source/lpc_shape_swb12_tables.c
SRC_ALL += codecs/isac/main/source/lpc_shape_swb16_tables.c
SRC_ALL += codecs/isac/main/source/lpc_tables.c
SRC_ALL += codecs/isac/main/source/pitch_estimator.c
SRC_ALL += codecs/isac/main/source/pitch_filter.c
SRC_ALL += codecs/isac/main/source/pitch_gain_tables.c
SRC_ALL += codecs/isac/main/source/spectrum_ar_model_tables.c
SRC_ALL += codecs/isac/main/source/transform.c
SRC_ALL += codecs/isac/main/source/arith_routines.h
SRC_ALL += codecs/isac/main/source/bandwidth_estimator.h
SRC_ALL += codecs/isac/main/source/codec.h
SRC_ALL += codecs/isac/main/source/crc.h
SRC_ALL += codecs/isac/main/source/encode_lpc_swb.h
SRC_ALL += codecs/isac/main/source/entropy_coding.h
SRC_ALL += codecs/isac/main/source/fft.h
SRC_ALL += codecs/isac/main/source/filterbank_tables.h
SRC_ALL += codecs/isac/main/source/lpc_gain_swb_tables.h
SRC_ALL += codecs/isac/main/source/lpc_analysis.h
SRC_ALL += codecs/isac/main/source/lpc_shape_swb12_tables.h
SRC_ALL += codecs/isac/main/source/lpc_shape_swb16_tables.h
SRC_ALL += codecs/isac/main/source/lpc_tables.h
SRC_ALL += codecs/isac/main/source/pitch_estimator.h
SRC_ALL += codecs/isac/main/source/pitch_gain_tables.h
SRC_ALL += codecs/isac/main/source/pitch_lag_tables.h
SRC_ALL += codecs/isac/main/source/settings.h
SRC_ALL += codecs/isac/main/source/spectrum_ar_model_tables.h
SRC_ALL += codecs/isac/main/source/structs.h
SRC_ALL += codecs/isac/main/source/os_specific_inline.h

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

	


