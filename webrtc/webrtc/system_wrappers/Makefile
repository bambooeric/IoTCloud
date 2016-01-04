#=================================================================================
# export variable
#=================================================================================
ifeq ($(CFG_EXPORT_FLAG),)
include ../../config.mak
endif

#=================================================================================
# local variable
#=================================================================================
LIBS :=librtc_system_wrappers
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
SRC_ALL += interface/aligned_array.h
SRC_ALL += interface/aligned_malloc.h
SRC_ALL += interface/atomic32.h
SRC_ALL += interface/clock.h
SRC_ALL += interface/condition_variable_wrapper.h
SRC_ALL += interface/cpu_info.h
SRC_ALL += interface/cpu_features_wrapper.h
SRC_ALL += interface/critical_section_wrapper.h
SRC_ALL += interface/data_log.h
SRC_ALL += interface/data_log_c.h
SRC_ALL += interface/data_log_impl.h
SRC_ALL += interface/event_tracer.h
SRC_ALL += interface/event_wrapper.h
SRC_ALL += interface/field_trial.h
SRC_ALL += interface/field_trial_default.h
SRC_ALL += interface/file_wrapper.h
SRC_ALL += interface/logging.h
SRC_ALL += interface/metrics.h
SRC_ALL += interface/ref_count.h
SRC_ALL += interface/rtp_to_ntp.h
SRC_ALL += interface/rw_lock_wrapper.h
SRC_ALL += interface/scoped_vector.h
SRC_ALL += interface/sleep.h
SRC_ALL += interface/sort.h
SRC_ALL += interface/static_instance.h
SRC_ALL += interface/stl_util.h
SRC_ALL += interface/stringize_macros.h
SRC_ALL += interface/thread_wrapper.h
SRC_ALL += interface/tick_util.h
SRC_ALL += interface/timestamp_extrapolator.h
SRC_ALL += interface/trace.h
SRC_ALL += interface/trace_event.h
SRC_ALL += interface/utf_util_win.h
SRC_ALL += source/aligned_malloc.cc
SRC_ALL += source/atomic32_posix.cc
SRC_ALL += source/clock.cc
SRC_ALL += source/condition_variable.cc
SRC_ALL += source/condition_variable_posix.cc
SRC_ALL += source/condition_variable_posix.h
SRC_ALL += source/cpu_info.cc
SRC_ALL += source/cpu_features.cc
SRC_ALL += source/critical_section.cc
SRC_ALL += source/critical_section_posix.cc
SRC_ALL += source/critical_section_posix.h
SRC_ALL += source/data_log.cc
SRC_ALL += source/data_log_c.cc
SRC_ALL += source/data_log_no_op.cc
SRC_ALL += source/event.cc
SRC_ALL += source/event_timer_posix.cc
SRC_ALL += source/event_timer_posix.h
SRC_ALL += source/event_tracer.cc
SRC_ALL += source/field_trial_default.cc
SRC_ALL += source/file_impl.cc
SRC_ALL += source/file_impl.h
SRC_ALL += source/logging.cc
SRC_ALL += source/metrics_default.cc
SRC_ALL += source/rtp_to_ntp.cc
SRC_ALL += source/rw_lock.cc
SRC_ALL += source/rw_lock_generic.cc
SRC_ALL += source/rw_lock_generic.h
SRC_ALL += source/rw_lock_posix.cc
SRC_ALL += source/rw_lock_posix.h
SRC_ALL += source/sleep.cc
SRC_ALL += source/sort.cc
SRC_ALL += source/tick_util.cc
SRC_ALL += source/thread.cc
SRC_ALL += source/thread_posix.cc
SRC_ALL += source/thread_posix.h
SRC_ALL += source/timestamp_extrapolator.cc
SRC_ALL += source/trace_impl.cc
SRC_ALL += source/trace_impl.h
SRC_ALL += source/trace_posix.cc
SRC_ALL += source/trace_posix.h

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



