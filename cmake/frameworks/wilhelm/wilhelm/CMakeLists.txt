project(WILHELM)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

# dependency
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/system/hidl/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/interfaces/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/audiomanager/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/nativewindow/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/nativebase/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/arect/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/ui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/gui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/drm/drmframework/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/mediametrics/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/audioclient/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/audioprocessing/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/media/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright_foundation/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/frameworks/wilhelm/opensles/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/wilhelm/openmaxal/include.cmake)

include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/http)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/mpeg2ts)

set( ${PROJECT_NAME}_DEPLIB
log
cutils
utils
media
audioclient
stagefright
OpenSLESUT
opensles_helper
)

# do not claim support for any OpenSL ES or OpenMAX AL profiles
add_definitions(-DUSE_PROFILES=0)

# enable API logging; details are set separately by SL_TRACE_DEFAULT below
# or -UUSE_TRACE to disable API logging
add_definitions(-DUSE_TRACE)

# see Configuration.h for USE_DEBUG

# enable assert() to do runtime checking
# or -DNDEBUG for no runtime checking
add_definitions(-UNDEBUG)

# select the level of log messages
# or -DUSE_LOG=SLAndroidLogLevel_Verbose for verbose logging
#add_definitions(-DUSE_LOG=SLAndroidLogLevel_Info)
add_definitions(-DUSE_LOG=SLAndroidLogLevel_Silent)

add_definitions(-DANDROID)

if (MSVC)
    add_definitions(-DLI_API=__declspec\(dllexport\))
else()
    add_definitions(-DLI_API= )
endif()

if (MSVC)
    add_definitions(-D__unused= )
    add_definitions(-Dstrncasecmp=_strnicmp)
    add_definitions(-Dstrcasecmp=_stricmp)

elseif(LINUX)
    add_definitions(-D__unused= )
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/wilhelm/src/ )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/wilhelm/src/ )

include_directories(AFTER ${SOURCE_PATH})

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES  
${HEADER_PATH}/*.h
)

set(${PROJECT_NAME}_SOURCE_FILES 
${SOURCE_PATH}/OpenSLES_IID.cpp
${SOURCE_PATH}/assert.cpp
${SOURCE_PATH}/classes.cpp
${SOURCE_PATH}/data.cpp
${SOURCE_PATH}/devices.cpp
${SOURCE_PATH}/entry.cpp
${SOURCE_PATH}/handler_bodies.cpp
${SOURCE_PATH}/trace.cpp
${SOURCE_PATH}/locks.cpp
${SOURCE_PATH}/sles.cpp
${SOURCE_PATH}/sl_iid.cpp
${SOURCE_PATH}/sllog.cpp
${SOURCE_PATH}/ThreadPool.cpp
${SOURCE_PATH}/autogen/IID_to_MPH.cpp
)

set(${PROJECT_NAME}_SOURCE_ANDROID
${SOURCE_PATH}/android/AudioPlayer_to_android.cpp 
${SOURCE_PATH}/android/AudioRecorder_to_android.cpp 
${SOURCE_PATH}/android/MediaPlayer_to_android.cpp 
${SOURCE_PATH}/android/OutputMix_to_android.cpp 
${SOURCE_PATH}/android/VideoCodec_to_android.cpp 
${SOURCE_PATH}/android/BufferQueueSource.cpp 
${SOURCE_PATH}/android/CallbackProtector.cpp 
${SOURCE_PATH}/android/AacBqToPcmCbRenderer.cpp 
${SOURCE_PATH}/android/android_AudioSfDecoder.cpp 
${SOURCE_PATH}/android/android_AudioToCbRenderer.cpp 
${SOURCE_PATH}/android/android_GenericMediaPlayer.cpp 
${SOURCE_PATH}/android/android_GenericPlayer.cpp 
${SOURCE_PATH}/android/android_LocAVPlayer.cpp 
${SOURCE_PATH}/android/android_StreamPlayer.cpp 
${SOURCE_PATH}/android/android_Effect.cpp 
${SOURCE_PATH}/android/util/AacAdtsExtractor.cpp 
${SOURCE_PATH}/android/channels.cpp 
)
source_group(android FILES ${${PROJECT_NAME}_SOURCE_ANDROID})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_SOURCE_ANDROID})

set(${PROJECT_NAME}_SOURCE_OBJECTS
${SOURCE_PATH}/objects/C3DGroup.cpp
${SOURCE_PATH}/objects/CAudioPlayer.cpp
${SOURCE_PATH}/objects/CAudioRecorder.cpp
${SOURCE_PATH}/objects/CEngine.cpp
${SOURCE_PATH}/objects/COutputMix.cpp
${SOURCE_PATH}/objects/CMediaPlayer.cpp
)
source_group(objects FILES ${${PROJECT_NAME}_SOURCE_OBJECTS})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_SOURCE_OBJECTS})

set(${PROJECT_NAME}_SOURCE_ITF
 ${SOURCE_PATH}/itf/IAndroidBufferQueue.cpp 
 ${SOURCE_PATH}/itf/IAndroidConfiguration.cpp 
 ${SOURCE_PATH}/itf/IAndroidEffect.cpp 
 ${SOURCE_PATH}/itf/IAndroidEffectCapabilities.cpp 
 ${SOURCE_PATH}/itf/IAndroidEffectSend.cpp 
 ${SOURCE_PATH}/itf/IAcousticEchoCancellation.cpp 
 ${SOURCE_PATH}/itf/IAutomaticGainControl.cpp 
 ${SOURCE_PATH}/itf/IBassBoost.cpp 
 ${SOURCE_PATH}/itf/IBufferQueue.cpp 
 ${SOURCE_PATH}/itf/IDynamicInterfaceManagement.cpp 
 ${SOURCE_PATH}/itf/IEffectSend.cpp 
 ${SOURCE_PATH}/itf/IEngine.cpp 
 ${SOURCE_PATH}/itf/IEngineCapabilities.cpp 
 ${SOURCE_PATH}/itf/IEnvironmentalReverb.cpp 
 ${SOURCE_PATH}/itf/IEqualizer.cpp 
 ${SOURCE_PATH}/itf/IMetadataExtraction.cpp 
 ${SOURCE_PATH}/itf/INoiseSuppression.cpp 
 ${SOURCE_PATH}/itf/IMuteSolo.cpp 
 ${SOURCE_PATH}/itf/IObject.cpp 
 ${SOURCE_PATH}/itf/IOutputMix.cpp 
 ${SOURCE_PATH}/itf/IPlay.cpp 
 ${SOURCE_PATH}/itf/IPlaybackRate.cpp 
 ${SOURCE_PATH}/itf/IPrefetchStatus.cpp 
 ${SOURCE_PATH}/itf/IPresetReverb.cpp 
 ${SOURCE_PATH}/itf/IRecord.cpp 
 ${SOURCE_PATH}/itf/ISeek.cpp 
 ${SOURCE_PATH}/itf/IStreamInformation.cpp 
 ${SOURCE_PATH}/itf/IVideoDecoderCapabilities.cpp 
 ${SOURCE_PATH}/itf/IVirtualizer.cpp 
 ${SOURCE_PATH}/itf/IVolume.cpp 
)
source_group(itf FILES ${${PROJECT_NAME}_SOURCE_ITF})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_SOURCE_ITF})

set(LIB_TYPE SHARED)
ADD_LIB(wilhelm)
