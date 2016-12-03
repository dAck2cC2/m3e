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
          impl/CEncoderLame.cpp \
          impl/CEngineAnalyzer.cpp \
          impl/CEngineFactory.cpp \
	  impl/CEngineMonitor.cpp

LOCAL_C_INCLUDES:= \
    $(TOPDIR)src \
    $(TOPDIR)src/native \
    $(TOPDIR)src/codec/lame/include \
    $(TOPDIR)src/av/include \
    $(TOPDIR)src/av/external \
    $(LOCAL_PATH) \

LOCAL_SHARED_LIBRARIES := \
    libstagefright_foundation \
    libstagefright \
    libutils

#LOCAL_REQUIRED_MODULES := libmp3lame
LOCAL_STATIC_LIBRARIES := libmp3lame


LOCAL_ADDITIONAL_DEPENDENCIES := $(LOCAL_PATH)/Android.mk

LOCAL_CFLAGS += -Wno-multichar -Wall
LOCAL_CLANG := true
LOCAL_SANITIZE := unsigned-integer-overflow signed-integer-overflow


include $(BUILD_SHARED_LIBRARY)
