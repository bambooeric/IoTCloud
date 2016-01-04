#=================================================================================
# export variable
#=================================================================================
ifeq ($(CFG_EXPORT_FLAG),)
include ../../config.mak
endif

#=================================================================================
# local variable
#=================================================================================
LIBS :=librtc_jingle
WEBRTC_PATH := ../../webrtc
INSTALL_DIR := ../../out/lib/

##################################################################################
CFLAGS += -I$(WEBRTC_PATH)/../third_party/expat/files/lib

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
#CFLAGS += -D_DEBUG
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
SRC_ALL += xmllite/qname.cc
SRC_ALL += xmllite/qname.h
SRC_ALL += xmllite/xmlbuilder.cc
SRC_ALL += xmllite/xmlbuilder.h
SRC_ALL += xmllite/xmlconstants.cc
SRC_ALL += xmllite/xmlconstants.h
SRC_ALL += xmllite/xmlelement.cc
SRC_ALL += xmllite/xmlelement.h
SRC_ALL += xmllite/xmlnsstack.cc
SRC_ALL += xmllite/xmlnsstack.h
SRC_ALL += xmllite/xmlparser.cc
SRC_ALL += xmllite/xmlparser.h
SRC_ALL += xmllite/xmlprinter.cc
SRC_ALL += xmllite/xmlprinter.h
SRC_ALL += xmpp/asyncsocket.h
SRC_ALL += xmpp/chatroommodule.h
SRC_ALL += xmpp/chatroommoduleimpl.cc
SRC_ALL += xmpp/constants.cc
SRC_ALL += xmpp/constants.h
SRC_ALL += xmpp/discoitemsquerytask.cc
SRC_ALL += xmpp/discoitemsquerytask.h
SRC_ALL += xmpp/extdiscoservicestask.cc
SRC_ALL += xmpp/extdiscoservicestask.h
SRC_ALL += xmpp/hangoutpubsubclient.cc
SRC_ALL += xmpp/hangoutpubsubclient.h
SRC_ALL += xmpp/iqtask.cc
SRC_ALL += xmpp/iqtask.h
SRC_ALL += xmpp/jid.cc
SRC_ALL += xmpp/jid.h
SRC_ALL += xmpp/messagereceivetask.h
SRC_ALL += xmpp/messagereceivetask.cc
SRC_ALL += xmpp/module.h
SRC_ALL += xmpp/moduleimpl.cc
SRC_ALL += xmpp/moduleimpl.h
SRC_ALL += xmpp/mucroomconfigtask.cc
SRC_ALL += xmpp/mucroomconfigtask.h
SRC_ALL += xmpp/mucroomdiscoverytask.cc
SRC_ALL += xmpp/mucroomdiscoverytask.h
SRC_ALL += xmpp/mucroomlookuptask.cc
SRC_ALL += xmpp/mucroomlookuptask.h
SRC_ALL += xmpp/mucroomuniquehangoutidtask.cc
SRC_ALL += xmpp/mucroomuniquehangoutidtask.h
SRC_ALL += xmpp/pingtask.cc
SRC_ALL += xmpp/pingtask.h
SRC_ALL += xmpp/plainsaslhandler.h
SRC_ALL += xmpp/presenceouttask.cc
SRC_ALL += xmpp/presenceouttask.h
SRC_ALL += xmpp/presencereceivetask.cc
SRC_ALL += xmpp/presencereceivetask.h
SRC_ALL += xmpp/presencestatus.cc
SRC_ALL += xmpp/presencestatus.h
SRC_ALL += xmpp/prexmppauth.h
SRC_ALL += xmpp/pubsub_task.cc
SRC_ALL += xmpp/pubsub_task.h
SRC_ALL += xmpp/pubsubclient.cc
SRC_ALL += xmpp/pubsubclient.h
SRC_ALL += xmpp/pubsubstateclient.cc
SRC_ALL += xmpp/pubsubstateclient.h
SRC_ALL += xmpp/pubsubtasks.cc
SRC_ALL += xmpp/pubsubtasks.h
SRC_ALL += xmpp/receivetask.cc
SRC_ALL += xmpp/receivetask.h
SRC_ALL += xmpp/rostermodule.h
SRC_ALL += xmpp/rostermoduleimpl.cc
SRC_ALL += xmpp/rostermoduleimpl.h
SRC_ALL += xmpp/saslcookiemechanism.h
SRC_ALL += xmpp/saslhandler.h
SRC_ALL += xmpp/saslmechanism.cc
SRC_ALL += xmpp/saslmechanism.h
SRC_ALL += xmpp/saslplainmechanism.h
SRC_ALL += xmpp/xmppauth.cc
SRC_ALL += xmpp/xmppauth.h
SRC_ALL += xmpp/xmppclient.cc
SRC_ALL += xmpp/xmppclient.h
SRC_ALL += xmpp/xmppclientsettings.h
SRC_ALL += xmpp/xmppengine.h
SRC_ALL += xmpp/xmppengineimpl.cc
SRC_ALL += xmpp/xmppengineimpl.h
SRC_ALL += xmpp/xmppengineimpl_iq.cc
#SRC_ALL += xmpp/xmppregistertask.cc
#SRC_ALL += xmpp/xmppregistertask.h
SRC_ALL += xmpp/xmpplogintask.cc
SRC_ALL += xmpp/xmpplogintask.h
SRC_ALL += xmpp/xmpppump.cc
SRC_ALL += xmpp/xmpppump.h
SRC_ALL += xmpp/xmppsocket.cc
SRC_ALL += xmpp/xmppsocket.h
SRC_ALL += xmpp/xmppstanzaparser.cc
SRC_ALL += xmpp/xmppstanzaparser.h
SRC_ALL += xmpp/xmpptask.cc
SRC_ALL += xmpp/xmpptask.h
SRC_ALL += xmpp/xmppthread.cc
SRC_ALL += xmpp/xmppthread.h

SRC_C := $(filter %.c,$(SRC_ALL))
SRC_CC := $(filter %.cc,$(SRC_ALL))

OBJ_C = $(patsubst %.c,%.o,$(sort $(SRC_C)))
OBJ_CC = $(patsubst %.cc,%.o,$(sort $(SRC_CC)))

.PHONY : all lib clean install

all:$(OBJ_C) $(OBJ_CC)

lib: $(OBJ_C) $(OBJ_CC)
	$(AR) -rc $(LIBS).a $(OBJ_C) $(OBJ_CC)

	
clean:
	$(AT)-rm -rf $(OBJ_C)
	$(AT)-rm -rf $(OBJ_CC)
	$(AT)-rm -rf $(LIBS).a

install:
	cp -af $(LIBS).a $(INSTALL_DIR)

$(OBJ_C):%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_CC):%.o: %.cc
	$(CXX) $(CFLAGS) -c $< -o $@



