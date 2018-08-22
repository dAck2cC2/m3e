
project(STAGEFRIGHT)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/audio_utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/ui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/EGL/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright_foundation/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/drm/drmframework/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/sonivox/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/vpx/include.cmake)

set(STAGEFRIGHT_DEPLIB
log
utils
binder
media
stagefright_foundation
drmframework
)

# define
if(APPLE OR CYGWIN)
    add_definitions(-DO_LARGEFILE=0)
    add_definitions(-Dlseek64=lseek)
    add_definitions(-Wno-enum-compare)
endif()

if(CYGWIN)
    add_definitions(-D_GNU_SOURCE)
elseif(MSVC)
    add_definitions(-DNOMINMAX)
    add_definitions(-Dstrncasecmp=strncmp)
    add_definitions(-Dstrcasecmp=strcmp)
    add_definitions(-Dlstat=_stat)
    add_definitions(-Dstat=_stat)
endif()

# include files
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/native/include/media/openmax)
#include_directories(AFTER ${M3E_SOURCE_DIR}/src/system/netd/include)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/stagefright/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/ )

# include files
include_directories(AFTER ${HEADER_PATH})
include_directories(AFTER ${SOURCE_PATH})

# header files
file(GLOB STAGEFRIGHT_HEADER_FILES 
${M3E_SOURCE_DIR}/src/frameworks/av/include/media/stagefright/*.h 
${HEADER_PATH}/*.h 
${SOURCE_PATH}/*.h 
)

# source files
#file(GLOB STAGEFRIGHT_SOURCE_FILES 
#  ${SOURCE_PATH}/*.cpp
#)
set(STAGEFRIGHT_SOURCE_FILES
${SOURCE_PATH}/avc_utils.cpp
${SOURCE_PATH}/CallbackDataSource.cpp
${SOURCE_PATH}/DataSource.cpp
${SOURCE_PATH}/DataURISource.cpp
${SOURCE_PATH}/DRMExtractor.cpp
${SOURCE_PATH}/ESDS.cpp
${SOURCE_PATH}/FileSource.cpp
${SOURCE_PATH}/HevcUtils.cpp
${SOURCE_PATH}/http/MediaHTTP.cpp
${SOURCE_PATH}/HTTPBase.cpp
${SOURCE_PATH}/MediaDefs.cpp
${SOURCE_PATH}/NuCachedSource2.cpp
${SOURCE_PATH}/Utils.cpp
${SOURCE_PATH}/WAVExtractor.cpp
${SOURCE_PATH}/MediaSource.cpp
${SOURCE_PATH}/MediaExtractor_legacy.cpp
${SOURCE_PATH}/AudioPlayer.cpp
)

# codec selector
if(ENABLE_AV_CODEC)
    message(STATUS "ENABLE_AV_CODEC:${ENABLE_AV_CODEC}")

    set(STAGEFRIGHT_DEPLIB ${STAGEFRIGHT_DEPLIB}
    expat
    stagefright_mediafilter
    stagefright_omx
    stagefright_color_conversion
    )

    include(${M3E_SOURCE_DIR}/cmake/external/expat/include.cmake)

    set(STAGEFRIGHT_HEADER_FILES ${STAGEFRIGHT_HEADER_FILES}
    ${SOURCE_PATH}/MediaCodecListOverrides.h
    )

    set(STAGEFRIGHT_SOURCE_FILES ${STAGEFRIGHT_SOURCE_FILES}
    ${SOURCE_PATH}/SimpleDecodingSource.cpp
    ${SOURCE_PATH}/MediaCodecListOverrides.cpp
    ${SOURCE_PATH}/MediaCodecList.cpp
    ${SOURCE_PATH}/CodecBase.cpp
    ${SOURCE_PATH}/MediaCodec.cpp
    ${SOURCE_PATH}/SurfaceUtils.cpp
    ${SOURCE_PATH}/ACodec.cpp
    ${SOURCE_PATH}/DataConverter.cpp
    ${SOURCE_PATH}/OMXClient.cpp
    ${SOURCE_PATH}/SkipCutBuffer.cpp
    ${SOURCE_PATH}/FrameRenderTracker.cpp
    )
endif(ENABLE_AV_CODEC)


if(MSVC)
    include_directories(AFTER ${MSVC_PATH})

    list(APPEND STAGEFRIGHT_HEADER_FILES
    ${MSVC_PATH}/unistd.h
    ${MSVC_PATH}/sys/time.h
    )
    list(APPEND STAGEFRIGHT_SOURCE_FILES
    ${MSVC_PATH}/memmem.cc
    ${MSVC_PATH}/sys/time.c
    )    
endif(MSVC)

# target files
# dependency
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(stagefright SHARED ${STAGEFRIGHT_SOURCE_FILES} ${STAGEFRIGHT_HEADER_FILES})
target_link_libraries(stagefright ${STAGEFRIGHT_DEPLIB})
