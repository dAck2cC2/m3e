LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE:= m3e

LOCAL_SRC_FILES:= \
          main.cpp 

LOCAL_C_INCLUDES:= \
    $(TOPDIR)src \
    $(TOPDIR)src/native \
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


include $(BUILD_EXECUTABLE)
