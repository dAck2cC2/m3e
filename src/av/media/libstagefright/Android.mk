LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)


LOCAL_SRC_FILES:=                         \
        avc_utils.cpp                     \
        CallbackDataSource.cpp            \
        DataSource.cpp                    \
        DataURISource.cpp                 \
        DRMExtractor.cpp                  \
        ESDS.cpp                          \
        FileSource.cpp                    \
        HevcUtils.cpp                     \
        http/MediaHTTP.cpp                \
        HTTPBase.cpp                      \
        MediaDefs.cpp                     \
        NuCachedSource2.cpp               \
        Utils.cpp                         \
        WAVExtractor.cpp                  \
        MediaSource.cpp                   \
        MediaExtractor_legacy.cpp         \
        AudioPlayer.cpp                   \


#        ACodec.cpp                        \
        AACExtractor.cpp                  \
        AACWriter.cpp                     \
        AMRExtractor.cpp                  \
        AMRWriter.cpp                     \
        AudioSource.cpp                   \
        CameraSource.cpp                  \
        CameraSourceTimeLapse.cpp         \
        CodecBase.cpp                     \
        DataConverter.cpp                 \
        FLACExtractor.cpp                 \
        FrameRenderTracker.cpp            \
        HTTPBase.cpp                      \
        JPEGSource.cpp                    \
        MP3Extractor.cpp                  \
        MPEG2TSWriter.cpp                 \
        MPEG4Extractor.cpp                \
        MPEG4Writer.cpp                   \
        MediaAdapter.cpp                  \
        MediaClock.cpp                    \
        MediaCodec.cpp                    \
        MediaCodecList.cpp                \
        MediaCodecListOverrides.cpp       \
        MediaCodecSource.cpp              \
        MediaExtractor.cpp                \
        MediaSync.cpp                     \
        MidiExtractor.cpp                 \
        http/MediaHTTP.cpp                \
        MediaMuxer.cpp                    \
        NuMediaExtractor.cpp              \
        OMXClient.cpp                     \
        OggExtractor.cpp                  \
        ProcessInfo.cpp                   \
        SampleIterator.cpp                \
        SampleTable.cpp                   \
        SimpleDecodingSource.cpp          \
        SkipCutBuffer.cpp                 \
        StagefrightMediaScanner.cpp       \
        StagefrightMetadataRetriever.cpp  \
        SurfaceMediaSource.cpp            \
        SurfaceUtils.cpp                  \
        ThrottledSource.cpp               \
        VBRISeeker.cpp                    \
        VideoFrameScheduler.cpp           \
        WVMExtractor.cpp                  \
        XINGSeeker.cpp                    \


LOCAL_C_INCLUDES:= \
	$(LOCAL_PATH)/include \
        $(TOP)/src/av/include \
        $(TOP)/src/av/include/meida \
        $(TOP)/src/av/external \
        $(TOP)/src/av/external/media/hardware \
        $(TOP)/src/av/external/media/openmax \
        $(TOP)/src/av/external/netd \
        $(TOP)/src/native/include \


LOCAL_SHARED_LIBRARIES := \
        libmisc \
        libmedia \
        libutils \

#LOCAL_STATIC_LIBRARIES := \
        libstagefright_color_conversion \
        libyuv_static \
        libstagefright_aacenc \
        libstagefright_matroska \
        libstagefright_mediafilter \
        libstagefright_webm \
        libstagefright_timedtext \
        libvpx \
        libwebm \
        libstagefright_mpeg2ts \
        libstagefright_id3 \
        libFLAC \
        libmedia_helper \

LOCAL_SHARED_LIBRARIES += \
        libstagefright_foundation \


LOCAL_CFLAGS += \
        -Wno-multichar \
        -Wno-error=deprecated-declarations \
        -Wno-enum-compare \
        -Wno-attributes \
        -Wall

# enable experiments only in userdebug and eng builds
ifneq (,$(filter userdebug eng,$(TARGET_BUILD_VARIANT)))
LOCAL_CFLAGS += -DENABLE_STAGEFRIGHT_EXPERIMENTS
endif

LOCAL_CLANG := true
LOCAL_SANITIZE := unsigned-integer-overflow signed-integer-overflow

LOCAL_MODULE:= libstagefright

LOCAL_MODULE_TAGS := optional

ifdef BUILD_CYGWIN
LOCAL_CFLAGS += -fpermissive
LOCAL_CFLAGS += -DO_LARGEFILE=0
LOCAL_CFLAGS += -Dlseek64=lseek
LOCAL_NO_PIC := true
endif


include $(BUILD_SHARED_LIBRARY)

include $(call all-makefiles-under,$(LOCAL_PATH))
