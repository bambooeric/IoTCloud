#=================================================================================
# export variable
#=================================================================================
ifeq ($(CFG_EXPORT_FLAG),)
include ../../config.mak
endif

#=================================================================================
# local variable
#=================================================================================
LIBS :=libexpat
INSTALL_DIR := ../../out/lib

##################################################################################
CFLAGS += -I./files/lib/

##################################################################################
CFLAGS += -DHAVE_EXPAT_CONFIG_H

#################################################################################
SRC_ALL += files/lib/expat.h
SRC_ALL += files/lib/xmlparse.c
SRC_ALL += files/lib/xmlrole.c
SRC_ALL += files/lib/xmltok.c

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



