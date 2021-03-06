LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE:= libengine

LOCAL_SRC_FILES:= \
          media/CFileSink.cpp \
          media/CMediaFileScanner.cpp \
          media/CPathScanner.cpp \
          impl/CAsyncEncoder.cpp \
          impl/CAsyncEncoderGroup.cpp \
          impl/CEncoderClient.cpp \
          impl/CEngineAnalyzer.cpp \
          impl/CEngineFactory.cpp \
          impl/CEngineMonitor.cpp \
          impl/CPlayerClient.cpp 

LOCAL_C_INCLUDES:= \
    $(TOPDIR)src \
    $(TOPDIR)src/native/include \
    $(TOPDIR)src/av/include \
    $(TOPDIR)src/av/external \
    $(TOPDIR)src/device \
    $(TOPDIR)src/engine/include \
    $(TOPDIR)src/engine/impl \
    $(TOPDIR)src/engine/media

LOCAL_SHARED_LIBRARIES := \
    libstagefright_foundation \
    libstagefright \
    libutils \
    libaudio 

LOCAL_ADDITIONAL_DEPENDENCIES := $(LOCAL_PATH)/Android.mk

LOCAL_CFLAGS += -Wno-multichar -Wall
LOCAL_CLANG := true
LOCAL_SANITIZE := unsigned-integer-overflow signed-integer-overflow

ifdef ENABLE_CODEC_LAME
LOCAL_CFLAGS += -DENABLE_CODEC_LAME
LOCAL_SRC_FILES += impl/CEncoderLame.cpp
LOCAL_C_INCLUDES += $(TOPDIR)src/codec/lame/include
LOCAL_STATIC_LIBRARIES := libmp3lame
endif

ifdef BUILD_CYGWIN
LOCAL_CFLAGS += -fpermissive
LOCAL_NO_PIC := true
endif

include $(BUILD_SHARED_LIBRARY)

include $(call first-makefiles-under, $(LOCAL_PATH))
