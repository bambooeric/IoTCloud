#=================================================================================
# export variable
#=================================================================================
ifeq ($(CFG_EXPORT_FLAG),)
include ../../config.mak
endif

#=================================================================================
# local variable
#=================================================================================
LIBS :=librtc_base
WEBRTC_PATH = ../../webrtc
INSTALL_DIR := ../../out/lib

##################################################################################
CFLAGS += -I$(WEBRTC_PATH)/../third_party/expat/files/lib
CFLAGS += -I$(WEBRTC_PATH)/../third_party/openssl/include
CFLAGS += -I$(WEBRTC_PATH)/../third_party/jsoncpp/source/include

##################################################################################
CFLAGS += -I./
CFLAGS += -I$(WEBRTC_PATH)/../
CFLAGS += -I$(WEBRTC_PATH)
CFLAGS += -I$(WEBRTC_PATH)/overrides/webrtc/
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
SRC_ALL += arraysize.h
SRC_ALL += asyncfile.cc
SRC_ALL += asyncfile.h
SRC_ALL += asynchttprequest.cc
SRC_ALL += asynchttprequest.h
SRC_ALL += asyncinvoker.cc
SRC_ALL += asyncinvoker.h
SRC_ALL += asyncinvoker-inl.h
SRC_ALL += asyncpacketsocket.cc
SRC_ALL += asyncpacketsocket.h
SRC_ALL += asyncresolverinterface.cc
SRC_ALL += asyncresolverinterface.h
SRC_ALL += asyncsocket.cc
SRC_ALL += asyncsocket.h
SRC_ALL += asynctcpsocket.cc
SRC_ALL += asynctcpsocket.h
SRC_ALL += asyncudpsocket.cc
SRC_ALL += asyncudpsocket.h
SRC_ALL += autodetectproxy.cc
SRC_ALL += autodetectproxy.h
SRC_ALL += bandwidthsmoother.cc
SRC_ALL += bandwidthsmoother.h
SRC_ALL += base64.cc
SRC_ALL += base64.h
SRC_ALL += basicdefs.h
SRC_ALL += bind.h
SRC_ALL += callback.h
SRC_ALL += common.cc
SRC_ALL += common.h
SRC_ALL += crc32.cc
SRC_ALL += crc32.h
SRC_ALL += cryptstring.cc
SRC_ALL += cryptstring.h
SRC_ALL += dbus.cc
SRC_ALL += dbus.h
SRC_ALL += diskcache.cc
SRC_ALL += diskcache.h
SRC_ALL += filerotatingstream.cc
SRC_ALL += filerotatingstream.h
SRC_ALL += fileutils.cc
SRC_ALL += fileutils.h
SRC_ALL += fileutils_mock.h
SRC_ALL += firewallsocketserver.cc
SRC_ALL += firewallsocketserver.h
SRC_ALL += flags.cc
SRC_ALL += flags.h
SRC_ALL += format_macros.h
SRC_ALL += gunit_prod.h
SRC_ALL += helpers.cc
SRC_ALL += helpers.h
SRC_ALL += httpbase.cc
SRC_ALL += httpbase.h
SRC_ALL += httpclient.cc
SRC_ALL += httpclient.h
SRC_ALL += httpcommon-inl.h
SRC_ALL += httpcommon.cc
SRC_ALL += httpcommon.h
SRC_ALL += httprequest.cc
SRC_ALL += httprequest.h
SRC_ALL += httpserver.cc
SRC_ALL += httpserver.h
SRC_ALL += ifaddrs-android.cc
SRC_ALL += ifaddrs-android.h
SRC_ALL += iosfilesystem.mm
SRC_ALL += ipaddress.cc
SRC_ALL += ipaddress.h
SRC_ALL += json.cc
SRC_ALL += json.h
SRC_ALL += latebindingsymboltable.cc
SRC_ALL += latebindingsymboltable.h
SRC_ALL += libdbusglibsymboltable.cc
SRC_ALL += libdbusglibsymboltable.h
SRC_ALL += linux.cc
SRC_ALL += linux.h
SRC_ALL += linuxfdwalk.c
SRC_ALL += linuxfdwalk.h
SRC_ALL += linked_ptr.h
SRC_ALL += logsinks.cc
SRC_ALL += logsinks.h
SRC_ALL += mathutils.h
SRC_ALL += messagedigest.cc
SRC_ALL += messagedigest.h
SRC_ALL += messagehandler.cc
SRC_ALL += messagehandler.h
SRC_ALL += messagequeue.cc
SRC_ALL += messagequeue.h
SRC_ALL += multipart.cc
SRC_ALL += multipart.h
SRC_ALL += natserver.cc
SRC_ALL += natserver.h
SRC_ALL += natsocketfactory.cc
SRC_ALL += natsocketfactory.h
SRC_ALL += nattypes.cc
SRC_ALL += nattypes.h
SRC_ALL += nethelpers.cc
SRC_ALL += nethelpers.h
SRC_ALL += network.cc
SRC_ALL += network.h
SRC_ALL += nullsocketserver.h
SRC_ALL += optionsfile.cc
SRC_ALL += optionsfile.h
SRC_ALL += pathutils.cc
SRC_ALL += pathutils.h
SRC_ALL += physicalsocketserver.cc
SRC_ALL += physicalsocketserver.h
SRC_ALL += posix.cc
SRC_ALL += posix.h
SRC_ALL += profiler.cc
SRC_ALL += profiler.h
SRC_ALL += proxydetect.cc
SRC_ALL += proxydetect.h
SRC_ALL += proxyinfo.cc
SRC_ALL += proxyinfo.h
SRC_ALL += proxyserver.cc
SRC_ALL += proxyserver.h
SRC_ALL += ratelimiter.cc
SRC_ALL += ratelimiter.h
SRC_ALL += refcount.h
SRC_ALL += referencecountedsingletonfactory.h
SRC_ALL += rollingaccumulator.h
SRC_ALL += rtccertificate.cc
SRC_ALL += rtccertificate.h
SRC_ALL += scoped_autorelease_pool.h
SRC_ALL += scoped_autorelease_pool.mm
SRC_ALL += scoped_ref_ptr.h
SRC_ALL += scopedptrcollection.h
SRC_ALL += sec_buffer.h
SRC_ALL += sha1.cc
SRC_ALL += sha1.h
SRC_ALL += sha1digest.cc
SRC_ALL += sha1digest.h
SRC_ALL += sharedexclusivelock.cc
SRC_ALL += sharedexclusivelock.h
SRC_ALL += signalthread.cc
SRC_ALL += signalthread.h
SRC_ALL += sigslot.cc
SRC_ALL += sigslot.h
SRC_ALL += sigslotrepeater.h
SRC_ALL += socket.h
SRC_ALL += socketadapters.cc
SRC_ALL += socketadapters.h
SRC_ALL += socketaddress.cc
SRC_ALL += socketaddress.h
SRC_ALL += socketaddresspair.cc
SRC_ALL += socketaddresspair.h
SRC_ALL += socketfactory.h
SRC_ALL += socketpool.cc
SRC_ALL += socketpool.h
SRC_ALL += socketserver.h
SRC_ALL += socketstream.cc
SRC_ALL += socketstream.h
SRC_ALL += ssladapter.cc
SRC_ALL += ssladapter.h
SRC_ALL += sslconfig.h
SRC_ALL += sslfingerprint.cc
SRC_ALL += sslfingerprint.h
SRC_ALL += sslidentity.cc
SRC_ALL += sslidentity.h
SRC_ALL += sslroots.h
SRC_ALL += sslsocketfactory.cc
SRC_ALL += sslsocketfactory.h
SRC_ALL += sslstreamadapter.cc
SRC_ALL += sslstreamadapter.h
SRC_ALL += sslstreamadapterhelper.cc
SRC_ALL += sslstreamadapterhelper.h
SRC_ALL += stream.cc
SRC_ALL += stream.h
SRC_ALL += task.cc
SRC_ALL += task.h
SRC_ALL += taskparent.cc
SRC_ALL += taskparent.h
SRC_ALL += taskrunner.cc
SRC_ALL += taskrunner.h
SRC_ALL += testclient.cc
SRC_ALL += testclient.h
SRC_ALL += thread.cc
SRC_ALL += thread.h
SRC_ALL += timing.cc
SRC_ALL += timing.h
SRC_ALL += transformadapter.cc
SRC_ALL += transformadapter.h
SRC_ALL += unixfilesystem.cc
SRC_ALL += unixfilesystem.h
SRC_ALL += urlencode.cc
SRC_ALL += urlencode.h
SRC_ALL += versionparsing.cc
SRC_ALL += versionparsing.h
SRC_ALL += virtualsocketserver.cc
SRC_ALL += virtualsocketserver.h
SRC_ALL += ../overrides/webrtc/base/basictypes.h
SRC_ALL += ../overrides/webrtc/base/constructormagic.h
SRC_ALL += atomicops.h
SRC_ALL += basictypes.h
SRC_ALL += bitbuffer.cc
SRC_ALL += bitbuffer.h
SRC_ALL += buffer.cc
SRC_ALL += buffer.h
SRC_ALL += bufferqueue.cc
SRC_ALL += bufferqueue.h
SRC_ALL += bytebuffer.cc
SRC_ALL += bytebuffer.h
SRC_ALL += byteorder.h
SRC_ALL += checks.cc
SRC_ALL += checks.h
SRC_ALL += constructormagic.h
SRC_ALL += criticalsection.cc
SRC_ALL += criticalsection.h
SRC_ALL += event.cc
SRC_ALL += event.h
SRC_ALL += event_tracer.cc
SRC_ALL += event_tracer.h
SRC_ALL += exp_filter.cc
SRC_ALL += exp_filter.h
SRC_ALL += logging.cc
SRC_ALL += logging.h
SRC_ALL += md5.cc
SRC_ALL += md5.h
SRC_ALL += md5digest.cc
SRC_ALL += md5digest.h
SRC_ALL += platform_file.cc
SRC_ALL += platform_file.h
SRC_ALL += platform_thread.cc
SRC_ALL += platform_thread.h
SRC_ALL += ratetracker.cc
SRC_ALL += ratetracker.h
SRC_ALL += safe_conversions.h
SRC_ALL += safe_conversions_impl.h
SRC_ALL += scoped_ptr.h
SRC_ALL += stringencode.cc
SRC_ALL += stringencode.h
SRC_ALL += stringutils.cc
SRC_ALL += stringutils.h
SRC_ALL += systeminfo.cc
SRC_ALL += systeminfo.h
SRC_ALL += template_util.h
SRC_ALL += thread_annotations.h
SRC_ALL += thread_checker.h
SRC_ALL += thread_checker_impl.cc
SRC_ALL += thread_checker_impl.h
SRC_ALL += timeutils.cc
SRC_ALL += timeutils.h
SRC_ALL += trace_event.h
#SRC_ALL += ../overrides/webrtc/base/logging.cc
#SRC_ALL += ../overrides/webrtc/base/logging.h
SRC_ALL += openssl.h
SRC_ALL += openssladapter.cc
SRC_ALL += openssladapter.h
SRC_ALL += openssldigest.cc
SRC_ALL += openssldigest.h
SRC_ALL += opensslidentity.cc
SRC_ALL += opensslidentity.h
SRC_ALL += opensslstreamadapter.cc
SRC_ALL += opensslstreamadapter.h

SRC_C := $(filter %.c,$(SRC_ALL))
SRC_CC := $(filter %.cc,$(SRC_ALL))

OBJ_C = $(patsubst %.c,%.o,$(sort $(SRC_C)))
OBJ_CC = $(patsubst %.cc,%.o,$(sort $(SRC_CC)))

.PHONY : all lib clean

all:$(OBJ_C) $(OBJ_CC) 

lib: $(OBJ_C) $(OBJ_CC)
	$(AR) -rc $(LIBS).a $(OBJ_C) $(OBJ_CC)

install:
	cp -af $(LIBS).a $(INSTALL_DIR)
	
clean:
	$(AT)-rm -rf $(OBJ_C)
	$(AT)-rm -rf $(OBJ_CC)
	$(AT)-rm -rf $(lib).a

$(OBJ_C):%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_CC):%.o: %.cc
	$(CXX) $(CFLAGS) -c $< -o $@



