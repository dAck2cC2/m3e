LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE:= libutils

LOCAL_SRC_FILES:= \
    cutils/atomic.c \
    cutils/properties.c \
    cutils/qtaguid.c \
    RefBase.cpp \
    SharedBuffer.cpp \
    VectorImpl.cpp \
    String8.cpp \
    String16.cpp \
    Unicode.cpp \
    Static.cpp \
    Timers.cpp \
    Threads.cpp \
    Log.c

LOCAL_C_INCLUDES:= \
    $(TOPDIR)src/native/include

LOCAL_SHARED_LIBRARIES := 

LOCAL_ADDITIONAL_DEPENDENCIES := $(LOCAL_PATH)/Android.mk

LOCAL_CFLAGS += -Wall
LOCAL_CLANG := true
#LOCAL_SANITIZE := unsigned-integer-overflow signed-integer-overflow

ifdef BUILD_CYGWIN
LOCAL_CFLAGS += -D_CYGWIN
LOCAL_NO_PIC := true
endif

include $(BUILD_SHARED_LIBRARY)
