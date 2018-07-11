LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE:= m3e

LOCAL_SRC_FILES:= \
          main.cpp 

LOCAL_C_INCLUDES:= \
    $(TOPDIR)src/engine/include \
    $(TOPDIR)src/native/include \
    $(TOPDIR)src/av/include \


LOCAL_SHARED_LIBRARIES := \
    libstagefright_foundation \
    libstagefright \
    libutils \
    libengine


LOCAL_ADDITIONAL_DEPENDENCIES := $(LOCAL_PATH)/Android.mk

LOCAL_CFLAGS += -Wno-multichar -Wall
LOCAL_CLANG := true
LOCAL_SANITIZE := unsigned-integer-overflow signed-integer-overflow
LOCAL_NO_LIBGCC := true
LOCAL_NO_CRT := true

ifdef BUILD_CYGWIN
LOCAL_NO_PIC := true
endif 

include $(BUILD_EXECUTABLE)
