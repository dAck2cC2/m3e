
project(MEDIA)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/include.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright_foundation/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/audio_utils/include.cmake)

set(MEDIA_DEPLIB
utils
binder
stagefright_foundation
audioutils
)

# define
if(APPLE)
    add_definitions(-Disnanf=isnan)
elseif(MSVC)
    add_definitions(-D__unused= )
    add_definitions(-Disnanf=isnan)
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/include/media )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libmedia )

# header files
file(GLOB MEDIA_HEADER_FILES 
${HEADER_PATH}/*.h 
${M3E_SOURCE_DIR}/src/frameworks/av/include/private/media/*.h
)

# source files
#file(GLOB MEDIA_SOURCE_FILES 
#${M3E_SOURCE_DIR}/src/av/media/libmedia/*.cpp
#)
set(MEDIA_SOURCE_FILES
${SOURCE_PATH}/AudioParameter.cpp
${SOURCE_PATH}/AudioSystem.cpp
${SOURCE_PATH}/AudioPolicy.cpp
${SOURCE_PATH}/AudioTrack.cpp
${SOURCE_PATH}/AudioTrackShared.cpp
${SOURCE_PATH}/IEffect.cpp
${SOURCE_PATH}/IEffectClient.cpp
${SOURCE_PATH}/IAudioTrack.cpp
${SOURCE_PATH}/IAudioRecord.cpp
${SOURCE_PATH}/IAudioFlinger.cpp
${SOURCE_PATH}/IAudioFlingerClient.cpp
${SOURCE_PATH}/IAudioPolicyService.cpp
${SOURCE_PATH}/IAudioPolicyServiceClient.cpp
${SOURCE_PATH}/IDataSource.cpp
${SOURCE_PATH}/IMediaExtractor.cpp
${SOURCE_PATH}/IMediaExtractorService.cpp
${SOURCE_PATH}/IMediaSource.cpp
${SOURCE_PATH}/IMediaLogService.cpp
${SOURCE_PATH}/MemoryLeakTrackUtil.cpp
)

if(ENABLE_AV_CODEC)
    include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright)

    set(MEDIA_SOURCE_FILES ${MEDIA_SOURCE_FILES}
    ${SOURCE_PATH}/IOMX.cpp
    ${SOURCE_PATH}/IMediaCodecList.cpp
    ${SOURCE_PATH}/IMediaCodecService.cpp
    ${SOURCE_PATH}/IResourceManagerClient.cpp
    ${SOURCE_PATH}/IResourceManagerService.cpp
    ${SOURCE_PATH}/MediaCodecInfo.cpp
    ${SOURCE_PATH}/MediaResource.cpp
    ${SOURCE_PATH}/MediaResourcePolicy.cpp
    ${SOURCE_PATH}/IMediaPlayerService.cpp
)
endif(ENABLE_AV_CODEC)

if (MSVC OR APPLE)
    list(APPEND MEDIA_SOURCE_FILES
    ${SOURCE_PATH}/backtrace.cpp
    )
endif()

if(MSVC)
    list(APPEND MEDIA_SOURCE_FILES
    ${MSVC_PATH}/sys/time.c
    ) 
endif()

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(media SHARED ${MEDIA_SOURCE_FILES} ${MEDIA_HEADER_FILES})
target_link_libraries(media ${MEDIA_DEPLIB})

