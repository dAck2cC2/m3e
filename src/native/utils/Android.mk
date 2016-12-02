LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE:= libutils

LOCAL_SRC_FILES:= \
          RefBase.cpp \
          SharedBuffer.cpp \
          VectorImpl.cpp \
          String8.cpp \
          String16.cpp \
          Unicode.cpp \
          Static.cpp \
          Timers.cpp \
          Threads.cpp \
          atomic.c \
          Log.c

LOCAL_C_INCLUDES:= \
    $(TOPDIR)src/native

LOCAL_SHARED_LIBRARIES := \


LOCAL_ADDITIONAL_DEPENDENCIES := $(LOCAL_PATH)/Android.mk

LOCAL_CFLAGS += -Wno-multichar -Wall
LOCAL_CLANG := true
LOCAL_SANITIZE := unsigned-integer-overflow signed-integer-overflow


include $(BUILD_SHARED_LIBRARY)
