#=================================================================================
# export variable
#=================================================================================
ifeq ($(CFG_EXPORT_FLAG),)
include ../../config.mak
endif

#=================================================================================
# local variable
#=================================================================================
LIBS :=libjsoncpp

INSTALL_DIR := ../../out/lib

##################################################################################
CFLAGS += -I../../
CFLAGS += -Ioverrides/include
CFLAGS += -Isource/include
CFLAGS += -Isource/src/lib_json

##################################################################################
CFLAGS += 

CXXFLAGS += $(CFLAGS)

#################################################################################
SRC_ALL += source/include/json/assertions.h
SRC_ALL += source/include/json/autolink.h
SRC_ALL += source/include/json/config.h
SRC_ALL += source/include/json/features.h
SRC_ALL += source/include/json/forwards.h
SRC_ALL += source/include/json/json.h
SRC_ALL += source/include/json/reader.h
SRC_ALL += overrides/include/json/value.h
SRC_ALL += source/include/json/writer.h
SRC_ALL += source/src/lib_json/json_batchallocator.h
SRC_ALL += overrides/src/lib_json/json_reader.cpp
SRC_ALL += source/src/lib_json/json_tool.h
SRC_ALL += overrides/src/lib_json/json_value.cpp
SRC_ALL += source/src/lib_json/json_writer.cpp

SRC_C := $(filter %.c,$(SRC_ALL))
SRC_CC := $(filter %.cpp,$(SRC_ALL))

OBJ_C = $(patsubst %.c,%.o,$(sort $(SRC_C)))
OBJ_CC = $(patsubst %.cpp,%.o,$(sort $(SRC_CC)))

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

$(OBJ_CC):%.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@


