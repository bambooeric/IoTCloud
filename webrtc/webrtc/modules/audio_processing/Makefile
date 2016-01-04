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
SRC_ALL += aec/aec_core.c
SRC_ALL += aec/aec_core.h
SRC_ALL += aec/aec_core_internal.h
SRC_ALL += aec/aec_rdft.c
SRC_ALL += aec/aec_rdft.h
SRC_ALL += aec/aec_resampler.c
SRC_ALL += aec/aec_resampler.h
SRC_ALL += aec/echo_cancellation.c
SRC_ALL += aec/echo_cancellation_internal.h
SRC_ALL += aec/include/echo_cancellation.h
SRC_ALL += aecm/aecm_core.c
SRC_ALL += aecm/aecm_core.h
SRC_ALL += aecm/aecm_core_c.c
SRC_ALL += aecm/echo_control_mobile.c
SRC_ALL += aecm/include/echo_control_mobile.h
SRC_ALL += agc/agc.cc
SRC_ALL += agc/agc.h
SRC_ALL += agc/agc_manager_direct.cc
SRC_ALL += agc/agc_manager_direct.h
SRC_ALL += agc/gain_map_internal.h
SRC_ALL += agc/histogram.cc
SRC_ALL += agc/histogram.h
SRC_ALL += agc/legacy/analog_agc.c
SRC_ALL += agc/legacy/analog_agc.h
SRC_ALL += agc/legacy/digital_agc.c
SRC_ALL += agc/legacy/digital_agc.h
SRC_ALL += agc/legacy/gain_control.h
SRC_ALL += agc/utility.cc
SRC_ALL += agc/utility.h
SRC_ALL += audio_buffer.cc
SRC_ALL += audio_buffer.h
SRC_ALL += audio_processing_impl.cc
SRC_ALL += audio_processing_impl.h
SRC_ALL += beamformer/beamformer.h
SRC_ALL += beamformer/complex_matrix.h
SRC_ALL += beamformer/covariance_matrix_generator.cc
SRC_ALL += beamformer/covariance_matrix_generator.h
SRC_ALL += beamformer/matrix.h
SRC_ALL += beamformer/nonlinear_beamformer.cc
SRC_ALL += beamformer/nonlinear_beamformer.h
SRC_ALL += common.h
SRC_ALL += echo_cancellation_impl.cc
SRC_ALL += echo_cancellation_impl.h
SRC_ALL += echo_control_mobile_impl.cc
SRC_ALL += echo_control_mobile_impl.h
SRC_ALL += gain_control_impl.cc
SRC_ALL += gain_control_impl.h
SRC_ALL += high_pass_filter_impl.cc
SRC_ALL += high_pass_filter_impl.h
SRC_ALL += include/audio_processing.h
SRC_ALL += intelligibility/intelligibility_enhancer.cc
SRC_ALL += intelligibility/intelligibility_enhancer.h
SRC_ALL += intelligibility/intelligibility_utils.cc
SRC_ALL += intelligibility/intelligibility_utils.h
SRC_ALL += level_estimator_impl.cc
SRC_ALL += level_estimator_impl.h
SRC_ALL += noise_suppression_impl.cc
SRC_ALL += noise_suppression_impl.h
SRC_ALL += processing_component.cc
SRC_ALL += processing_component.h
SRC_ALL += rms_level.cc
SRC_ALL += rms_level.h
SRC_ALL += splitting_filter.cc
SRC_ALL += splitting_filter.h
SRC_ALL += three_band_filter_bank.cc
SRC_ALL += three_band_filter_bank.h
SRC_ALL += transient/common.h
SRC_ALL += transient/daubechies_8_wavelet_coeffs.h
SRC_ALL += transient/dyadic_decimator.h
SRC_ALL += transient/moving_moments.cc
SRC_ALL += transient/moving_moments.h
SRC_ALL += transient/transient_detector.cc
SRC_ALL += transient/transient_detector.h
SRC_ALL += transient/transient_suppressor.cc
SRC_ALL += transient/transient_suppressor.h
SRC_ALL += transient/wpd_node.cc
SRC_ALL += transient/wpd_node.h
SRC_ALL += transient/wpd_tree.cc
SRC_ALL += transient/wpd_tree.h
SRC_ALL += typing_detection.cc
SRC_ALL += typing_detection.h
SRC_ALL += utility/delay_estimator.c
SRC_ALL += utility/delay_estimator.h
SRC_ALL += utility/delay_estimator_internal.h
SRC_ALL += utility/delay_estimator_wrapper.c
SRC_ALL += utility/delay_estimator_wrapper.h
SRC_ALL += vad/common.h
SRC_ALL += vad/gmm.cc
SRC_ALL += vad/gmm.h
SRC_ALL += vad/noise_gmm_tables.h
SRC_ALL += vad/pitch_based_vad.cc
SRC_ALL += vad/pitch_based_vad.h
SRC_ALL += vad/pitch_internal.cc
SRC_ALL += vad/pitch_internal.h
SRC_ALL += vad/pole_zero_filter.cc
SRC_ALL += vad/pole_zero_filter.h
SRC_ALL += vad/standalone_vad.cc
SRC_ALL += vad/standalone_vad.h
SRC_ALL += vad/vad_audio_proc.cc
SRC_ALL += vad/vad_audio_proc.h
SRC_ALL += vad/vad_audio_proc_internal.h
SRC_ALL += vad/vad_circular_buffer.cc
SRC_ALL += vad/vad_circular_buffer.h
SRC_ALL += vad/voice_activity_detector.cc
SRC_ALL += vad/voice_activity_detector.h
SRC_ALL += vad/voice_gmm_tables.h
SRC_ALL += voice_detection_impl.cc
SRC_ALL += voice_detection_impl.h

SRC_ALL += ns/defines.h
SRC_ALL += ns/include/noise_suppression.h
SRC_ALL += ns/noise_suppression.c
SRC_ALL += ns/ns_core.c
SRC_ALL += ns/ns_core.h
SRC_ALL += ns/windows_private.h


############################## arm neon ############################
#SRC_ALL += aec/aec_core_neon.c
#SRC_ALL += aec/aec_rdft_neon.c
#SRC_ALL += aecm/aecm_core_neon.c
#SRC_ALL += ns/nsx_core_neon.c

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

	


