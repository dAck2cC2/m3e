LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE:= libmisc

LOCAL_SRC_FILES:= \
          audio_utils/primitives.c \
          binder/MemoryDealer.cpp \
          binder/Parcel.cpp \
          binder/IInterface.cpp \
          binder/IMemory.cpp \
          cutils/properties.c \
          cutils/qtaguid.c \
          libdrmframework/DrmManagerClient.cpp \
          netd/NetdClient.cpp 

LOCAL_C_INCLUDES:= \
    $(LOCAL_PATH) \
    $(TOPDIR)src/native \
    $(TOPDIR)src/av/include

LOCAL_SHARED_LIBRARIES := libutils


LOCAL_ADDITIONAL_DEPENDENCIES := $(LOCAL_PATH)/Android.mk

LOCAL_CFLAGS += -Wno-multichar -Wall
LOCAL_CLANG := true
LOCAL_SANITIZE := unsigned-integer-overflow signed-integer-overflow
#LOCAL_NO_LIBGCC := true
#LOCAL_NO_CRT := true


include $(BUILD_SHARED_LIBRARY)
