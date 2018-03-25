LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE:= libmisc

LOCAL_SRC_FILES:= \
          audio_utils/primitives.cpp \
          binder/MemoryDealer.cpp \
          binder/Parcel.cpp \
          binder/IInterface.cpp \
          binder/IMemory.cpp \
          binder/IPCThreadState.cpp \
          libdrmframework/DrmManagerClient.cpp \
          netd/NetdClient.cpp

ifdef ENABLE_CODEC_SELECTOR
LOCAL_SRC_FILES += \
          ui/Fence.cpp \
          mediautils/BatteryNotifier.cpp \
          rs/cpp/Allocation.cpp \
          rs/cpp/BaseObj.cpp

#          gui/Surface.cpp \

LOCAL_C_INCLUDES += \
    $(TOPDIR)src/av/external/rs \
    $(TOPDIR)src/av/external/rs/cpp 

LOCAL_CFLAGS += -DMESA_EGL_NO_X11_HEADERS -DPATH_MAX=4096
endif

LOCAL_C_INCLUDES += \
    $(LOCAL_PATH) \
    $(TOPDIR)src/native/include \
    $(TOPDIR)src/av/include

LOCAL_SHARED_LIBRARIES := libutils

LOCAL_ADDITIONAL_DEPENDENCIES := $(LOCAL_PATH)/Android.mk

LOCAL_CFLAGS += -Wall
LOCAL_CLANG := true
#LOCAL_SANITIZE := unsigned-integer-overflow signed-integer-overflow

ifdef BUILD_CYGWIN
LOCAL_CPPFLAGS += -fpermissive
LOCAL_NO_PIC := true
endif

include $(BUILD_SHARED_LIBRARY)

