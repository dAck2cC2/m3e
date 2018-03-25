LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
        ColorConvert.cpp          \
        GraphicBufferListener.cpp \
        IntrinsicBlurFilter.cpp   \
        MediaFilter.cpp           \
        RSFilter.cpp              \
        SaturationFilter.cpp      \
        SimpleFilter.cpp          \
        ZeroFilter.cpp

#        saturationARGB.rs         \


LOCAL_C_INCLUDES := \
        $(TOP)/src/av/include \
        $(TOP)/src/native/include \
        $(TOP)/src/av/external \
        $(TOP)/src/av/external/rs/cpp \
        $(TOP)/src/av/external/rs \
        $(TOP)/src/av/external/media/openmax \


intermediates := $(call intermediates-dir-for,STATIC_LIBRARIES,libRS,TARGET,)
LOCAL_C_INCLUDES += $(intermediates)

LOCAL_CFLAGS += -Wno-multichar -Werror -Wall
LOCAL_CLANG := true

LOCAL_MODULE:= libstagefright_mediafilter

ifdef BUILD_CYGWIN
LOCAL_CFLAGS += -DPATH_MAX=4096
LOCAL_NO_PIC := true
endif

include $(BUILD_STATIC_LIBRARY)
