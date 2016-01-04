#=================================================================================
# export variable
#=================================================================================
ifeq ($(CFG_EXPORT_FLAG),)
include ../../config.mak
endif

#=================================================================================
# local variable
#=================================================================================
LIBS := libjpeg
INSTALL_DIR := ../../out/lib

##################################################################################
CFLAGS += -I./

##################################################################################
#CFLAGS += -DWITH_SIMD
#CFLAGS += -DMOTION_JPEG_SUPPORTED
#CFLAGS += -DNO_GETENV

#################################################################################
SRC_ALL += jcapimin.c
SRC_ALL += jcapistd.c
SRC_ALL += jccoefct.c
SRC_ALL += jccolor.c
SRC_ALL += jcdctmgr.c
SRC_ALL += jchuff.c
SRC_ALL += jchuff.h
SRC_ALL += jcinit.c
SRC_ALL += jcmainct.c
SRC_ALL += jcmarker.c
SRC_ALL += jcmaster.c
SRC_ALL += jcomapi.c
SRC_ALL += jconfig.h
SRC_ALL += jcparam.c
SRC_ALL += jcphuff.c
SRC_ALL += jcprepct.c
SRC_ALL += jcsample.c
SRC_ALL += jdapimin.c
SRC_ALL += jdapistd.c
SRC_ALL += jdatadst.c
SRC_ALL += jdatasrc.c
SRC_ALL += jdcoefct.c
SRC_ALL += jdcolor.c
SRC_ALL += jdct.h
SRC_ALL += jddctmgr.c
SRC_ALL += jdhuff.c
SRC_ALL += jdhuff.h
SRC_ALL += jdinput.c
SRC_ALL += jdmainct.c
SRC_ALL += jdmarker.c
SRC_ALL += jdmaster.c
SRC_ALL += jdmerge.c
SRC_ALL += jdphuff.c
SRC_ALL += jdpostct.c
SRC_ALL += jdsample.c
SRC_ALL += jerror.c
SRC_ALL += jerror.h
SRC_ALL += jfdctflt.c
SRC_ALL += jfdctfst.c
SRC_ALL += jfdctint.c
SRC_ALL += jidctflt.c
SRC_ALL += jidctfst.c
SRC_ALL += jidctint.c
SRC_ALL += jinclude.h
SRC_ALL += jmemmgr.c
SRC_ALL += jmemnobs.c
SRC_ALL += jmemsys.h
SRC_ALL += jmorecfg.h
SRC_ALL += jpegint.h
SRC_ALL += jpeglib.h
SRC_ALL += jquant1.c
SRC_ALL += jquant2.c
SRC_ALL += jutils.c
SRC_ALL += jversion.h

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



