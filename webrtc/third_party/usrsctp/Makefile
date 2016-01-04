#=================================================================================
# export variable
#=================================================================================
ifeq ($(CFG_EXPORT_FLAG),)
include ../../config.mak
endif

#=================================================================================
# local variable
#=================================================================================
LIBS := libusrsctp

##################################################################################
CFLAGS += -Iusrsctplib
CFLAGS += -Iusrsctplib/netinet
CFLAGS += -I../../third_party/boringssl/src/include

##################################################################################
CFLAGS += -DSCTP_PROCESS_LEVEL_LOCKS
CFLAGS += -DSCTP_SIMPLE_ALLOCATOR
CFLAGS += -D__Userspace__
CFLAGS += -DSCTP_USE_OPENSSL_SHA1

CXXFLAGS += $(CFLAGS)
#################################################################################
SRC_ALL += usrsctplib/netinet/sctp.h
SRC_ALL += usrsctplib/netinet/sctp_asconf.c
SRC_ALL += usrsctplib/netinet/sctp_asconf.h
SRC_ALL += usrsctplib/netinet/sctp_auth.c
SRC_ALL += usrsctplib/netinet/sctp_auth.h
SRC_ALL += usrsctplib/netinet/sctp_bsd_addr.c
SRC_ALL += usrsctplib/netinet/sctp_bsd_addr.h
SRC_ALL += usrsctplib/netinet/sctp_callout.c
SRC_ALL += usrsctplib/netinet/sctp_callout.h
SRC_ALL += usrsctplib/netinet/sctp_cc_functions.c
SRC_ALL += usrsctplib/netinet/sctp_constants.h
SRC_ALL += usrsctplib/netinet/sctp_crc32.c
SRC_ALL += usrsctplib/netinet/sctp_crc32.h
SRC_ALL += usrsctplib/netinet/sctp_header.h
SRC_ALL += usrsctplib/netinet/sctp_indata.c
SRC_ALL += usrsctplib/netinet/sctp_indata.h
SRC_ALL += usrsctplib/netinet/sctp_input.c
SRC_ALL += usrsctplib/netinet/sctp_input.h
SRC_ALL += usrsctplib/netinet/sctp_lock_userspace.h
SRC_ALL += usrsctplib/netinet/sctp_os.h
SRC_ALL += usrsctplib/netinet/sctp_os_userspace.h
SRC_ALL += usrsctplib/netinet/sctp_output.c
SRC_ALL += usrsctplib/netinet/sctp_output.h
SRC_ALL += usrsctplib/netinet/sctp_pcb.c
SRC_ALL += usrsctplib/netinet/sctp_pcb.h
SRC_ALL += usrsctplib/netinet/sctp_peeloff.c
SRC_ALL += usrsctplib/netinet/sctp_peeloff.h
SRC_ALL += usrsctplib/netinet/sctp_process_lock.h
SRC_ALL += usrsctplib/netinet/sctp_sha1.c
SRC_ALL += usrsctplib/netinet/sctp_sha1.h
SRC_ALL += usrsctplib/netinet/sctp_ss_functions.c
SRC_ALL += usrsctplib/netinet/sctp_structs.h
SRC_ALL += usrsctplib/netinet/sctp_sysctl.c
SRC_ALL += usrsctplib/netinet/sctp_sysctl.h
SRC_ALL += usrsctplib/netinet/sctp_timer.c
SRC_ALL += usrsctplib/netinet/sctp_timer.h
SRC_ALL += usrsctplib/netinet/sctp_uio.h
SRC_ALL += usrsctplib/netinet/sctp_userspace.c
SRC_ALL += usrsctplib/netinet/sctp_usrreq.c
SRC_ALL += usrsctplib/netinet/sctp_var.h
SRC_ALL += usrsctplib/netinet/sctputil.c
SRC_ALL += usrsctplib/netinet/sctputil.h
SRC_ALL += usrsctplib/netinet6/sctp6_usrreq.c
SRC_ALL += usrsctplib/netinet6/sctp6_var.h
SRC_ALL += usrsctplib/user_atomic.h
SRC_ALL += usrsctplib/user_environment.c
SRC_ALL += usrsctplib/user_environment.h
SRC_ALL += usrsctplib/user_inpcb.h
SRC_ALL += usrsctplib/user_ip6_var.h
SRC_ALL += usrsctplib/user_ip_icmp.h
SRC_ALL += usrsctplib/user_malloc.h
SRC_ALL += usrsctplib/user_mbuf.c
SRC_ALL += usrsctplib/user_mbuf.h
SRC_ALL += usrsctplib/user_queue.h
SRC_ALL += usrsctplib/user_recv_thread.c
SRC_ALL += usrsctplib/user_recv_thread.h
SRC_ALL += usrsctplib/user_route.h
SRC_ALL += usrsctplib/user_socket.c
SRC_ALL += usrsctplib/user_socketvar.h
SRC_ALL += usrsctplib/user_uma.h
SRC_ALL += usrsctplib/usrsctp.h

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
	$(CXX) $(CXXFLAGS) -c $< -o $@



