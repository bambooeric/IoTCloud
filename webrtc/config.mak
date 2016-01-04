# configure
CFG_SDK_TOOLCHAIN_HISIV200 = y

#CFG_SDK_TOOLCHAIN = arm-linux-gnueabihf-
#CFG_SDK_TOOLCHAIN = arm-hisiv200-linux-
CFG_SDK_TOOLCHAIN = arm-openwrt-linux-gnueabi-

CFG_HI_RTC_VERSION = 1.0.0.1

CFG_DISABLE_DEBUG = y
CFG_VERSION = release
CFG_HI_PKCS_SUPPORT = y

CFG_SSL_LIB_OPENSSL = y

CC := $(CFG_SDK_TOOLCHAIN)gcc
CXX := $(CFG_SDK_TOOLCHAIN)g++
AR := $(CFG_SDK_TOOLCHAIN)ar
STRIP := $(CFG_SDK_TOOLCHAIN)strip

#base information
OPENSSL_DIR := ./thirdparty/openssl
SRTP_DIR := ./thirdparty/srtp
TALK_DIR := ./talk
WEBRTC_DIR := ./webrtc

CFLAGS = -g -ffunction-sections -fdata-sections -fPIC

AT := @

ifeq ($(CFG_CHIP_TYPE), hi3516a)
CFLAGS += -mcpu=cortex-a7 -mfpu=neon -mfloat-abi=softfp -ffast-math -fno-aggressive-loop-optimizations
endif

ifeq ($(CFG_CHIP_TYPE), hi3518ev200)
CFLAGS += -mcpu=arm926ej-s
endif

ifeq ($(CFG_VERSION), debug)
CFLAGS += -g -Os
else
CFLAGS += -Os
endif

//LDFLAGS = -W1,--gc-sections

