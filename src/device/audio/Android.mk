LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE:= libaudio

LOCAL_SRC_FILES:= \
          AudioSinkFactory.cpp \
          AudioSinkBase.cpp \
          OpenALSink.cpp \
          DumpSink.cpp


LOCAL_C_INCLUDES:= \
    $(LOCAL_PATH) \
    $(TOPDIR)src/native/include \
    $(TOPDIR)src/av/include \
    $(TOPDIR)src/av/external

LOCAL_SHARED_LIBRARIES := libutils 


LOCAL_ADDITIONAL_DEPENDENCIES := $(LOCAL_PATH)/Android.mk

LOCAL_CFLAGS += -Wno-multichar -Wall
LOCAL_CLANG := true
LOCAL_SANITIZE := unsigned-integer-overflow signed-integer-overflow
#LOCAL_NO_LIBGCC := true
#LOCAL_NO_CRT := true


include $(BUILD_SHARED_LIBRARY)
