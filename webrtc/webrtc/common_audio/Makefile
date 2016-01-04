#=================================================================================
# export variable
#=================================================================================
ifeq ($(CFG_EXPORT_FLAG),)
include ../../config.mak
endif

#=================================================================================
# local variable
#=================================================================================
LIBS :=librtc_common_audio
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

CFLAGS += -mfloat-abi=softfp -mfpu=neon
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
CFLAGS += -DWEBRTC_HAS_NEON

CXXFLAGS += $(CFLAGS)
CXXFLAGS += -std=c++11 -fpermissive

#################################################################################
SRC_ALL += audio_converter.cc
SRC_ALL += audio_converter.h
SRC_ALL += audio_ring_buffer.cc
SRC_ALL += audio_ring_buffer.h
SRC_ALL += audio_util.cc
SRC_ALL += blocker.cc
SRC_ALL += blocker.h
SRC_ALL += channel_buffer.cc
SRC_ALL += channel_buffer.h
SRC_ALL += fft4g.c
SRC_ALL += fft4g.h
SRC_ALL += fir_filter.cc
SRC_ALL += fir_filter.h
SRC_ALL += fir_filter_neon.h
SRC_ALL += fir_filter_sse.h
SRC_ALL += include/audio_util.h
SRC_ALL += lapped_transform.cc
SRC_ALL += lapped_transform.h
SRC_ALL += real_fourier.cc
SRC_ALL += real_fourier.h
SRC_ALL += real_fourier_ooura.cc
SRC_ALL += real_fourier_ooura.h
SRC_ALL += resampler/include/push_resampler.h
SRC_ALL += resampler/include/resampler.h
SRC_ALL += resampler/push_resampler.cc
SRC_ALL += resampler/push_sinc_resampler.cc
SRC_ALL += resampler/push_sinc_resampler.h
SRC_ALL += resampler/resampler.cc
SRC_ALL += resampler/sinc_resampler.cc
SRC_ALL += resampler/sinc_resampler.h
SRC_ALL += ring_buffer.c
SRC_ALL += ring_buffer.h
SRC_ALL += signal_processing/include/real_fft.h
SRC_ALL += signal_processing/include/signal_processing_library.h
SRC_ALL += signal_processing/include/spl_inl.h
SRC_ALL += signal_processing/auto_corr_to_refl_coef.c
SRC_ALL += signal_processing/auto_correlation.c
SRC_ALL += signal_processing/complex_fft.c
SRC_ALL += signal_processing/complex_fft_tables.h
SRC_ALL += signal_processing/complex_bit_reverse_arm.S
SRC_ALL += signal_processing/copy_set_operations.c
SRC_ALL += signal_processing/cross_correlation.c
SRC_ALL += signal_processing/division_operations.c
SRC_ALL += signal_processing/dot_product_with_scale.c
SRC_ALL += signal_processing/downsample_fast.c
SRC_ALL += signal_processing/energy.c
SRC_ALL += signal_processing/filter_ar.c
SRC_ALL += signal_processing/filter_ar_fast_q12.c
SRC_ALL += signal_processing/filter_ma_fast_q12.c
SRC_ALL += signal_processing/get_hanning_window.c
SRC_ALL += signal_processing/get_scaling_square.c
SRC_ALL += signal_processing/ilbc_specific_functions.c
SRC_ALL += signal_processing/levinson_durbin.c
SRC_ALL += signal_processing/lpc_to_refl_coef.c
SRC_ALL += signal_processing/min_max_operations.c
SRC_ALL += signal_processing/randomization_functions.c
SRC_ALL += signal_processing/refl_coef_to_lpc.c
SRC_ALL += signal_processing/real_fft.c
SRC_ALL += signal_processing/resample.c
SRC_ALL += signal_processing/resample_48khz.c
SRC_ALL += signal_processing/resample_by_2.c
SRC_ALL += signal_processing/resample_by_2_internal.c
SRC_ALL += signal_processing/resample_by_2_internal.h
SRC_ALL += signal_processing/resample_fractional.c
SRC_ALL += signal_processing/spl_init.c
SRC_ALL += signal_processing/spl_sqrt.c
SRC_ALL += signal_processing/spl_sqrt_floor_arm.S
SRC_ALL += signal_processing/splitting_filter.c
SRC_ALL += signal_processing/sqrt_of_one_minus_x_squared.c
SRC_ALL += signal_processing/vector_scaling_operations.c
SRC_ALL += sparse_fir_filter.cc
SRC_ALL += sparse_fir_filter.h
SRC_ALL += vad/include/vad.h
SRC_ALL += vad/include/webrtc_vad.h
SRC_ALL += vad/vad.cc
SRC_ALL += vad/webrtc_vad.c
SRC_ALL += vad/vad_core.c
SRC_ALL += vad/vad_core.h
SRC_ALL += vad/vad_filterbank.c
SRC_ALL += vad/vad_filterbank.h
SRC_ALL += vad/vad_gmm.c
SRC_ALL += vad/vad_gmm.h
SRC_ALL += vad/vad_sp.c
SRC_ALL += vad/vad_sp.h
SRC_ALL += wav_header.cc
SRC_ALL += wav_header.h
SRC_ALL += wav_file.cc
SRC_ALL += wav_file.h
SRC_ALL += window_generator.cc
SRC_ALL += window_generator.h

################################## arm neno #################################
SRC_ALL += fir_filter_neon.cc
SRC_ALL += resampler/sinc_resampler_neon.cc
SRC_ALL += signal_processing/cross_correlation_neon.c
SRC_ALL += signal_processing/downsample_fast_neon.c
SRC_ALL += signal_processing/min_max_operations_neon.c

SRC_C := $(filter %.c,$(SRC_ALL))
SRC_S := $(filter %.S,$(SRC_ALL))
SRC_CC := $(filter %.cc,$(SRC_ALL))

OBJ_C := $(patsubst %.c,%.o,$(sort $(SRC_C)))
OBJ_S := $(patsubst %.S,%.o,$(sort $(SRC_S)))
OBJ_CC := $(patsubst %.cc,%.o,$(sort $(SRC_CC)))

.PHONY : all lib clean

all:$(OBJ_C) $(OBJ_S) $(OBJ_CC) 

lib: $(OBJ_C) $(OBJ_S) $(OBJ_CC)
	$(AR) -rc $(LIBS).a $(OBJ_C) $(OBJ_CC)

	
clean:
	$(AT)-rm -rf $(OBJ_C)
	$(AT)-rm -rf $(OBJ_CC)
	$(AT)-rm -rf $(LIBS).a

$(OBJ_C):%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_S):%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_CC):%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@



