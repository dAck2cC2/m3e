LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE:= libmedia

LOCAL_SRC_FILES:= \
          AudioParameter.cpp \
          AudioSystem.cpp \
          IAudioFlinger.cpp \
          IAudioFlingerClient.cpp \
          IAudioPolicyService.cpp \
          IAudioPolicyServiceClient.cpp \
          IDataSource.cpp \
          IMediaExtractor.cpp \
          IMediaExtractorService.cpp \
	  IMediaSource.cpp

LOCAL_C_INCLUDES:= \
    $(TOPDIR)src/native \
    $(TOPDIR)src/av/include \
    $(TOPDIR)src/av/external

LOCAL_SHARED_LIBRARIES := libmisc libutils libstagefright_foundation


LOCAL_ADDITIONAL_DEPENDENCIES := $(LOCAL_PATH)/Android.mk

LOCAL_CFLAGS += -Wno-multichar -Wall
LOCAL_CLANG := true
LOCAL_SANITIZE := unsigned-integer-overflow signed-integer-overflow


include $(BUILD_SHARED_LIBRARY)
