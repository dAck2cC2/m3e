
project(STAGEFRIGHT)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/misc/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/media/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/av/stagefright_foundation/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/av/stagefright/include.cmake)

set(STAGEFRIGHT_DEPLIB
utils
misc
media
stagefright_foundation
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
add_definitions(-Dstrncasecmp=strncmp)
add_definitions(-Dstrcasecmp=strcmp)
endif()

# include files
include_directories(AFTER ${M3E_SOURCE_DIR}/src/av/media/libstagefright)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/av/media/libstagefright/include)
#include_directories(AFTER ${M3E_SOURCE_DIR}/src/av/include)

# header files
file(GLOB STAGEFRIGHT_HEADER_FILES 
${M3E_SOURCE_DIR}/src/av/include/media/stagefright/*.h 
${M3E_SOURCE_DIR}/src/av/media/libstagefright/include/*.h 
)

# source files
#file(GLOB STAGEFRIGHT_SOURCE_FILES 
#${M3E_SOURCE_DIR}/src/av/media/libstagefright/*.cpp
#)
set(STAGEFRIGHT_SOURCE_FILES
${M3E_SOURCE_DIR}/src/av/media/libstagefright/avc_utils.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/CallbackDataSource.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/DataSource.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/DataURISource.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/DRMExtractor.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/ESDS.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/FileSource.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/HevcUtils.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/http/MediaHTTP.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/HTTPBase.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/MediaDefs.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/NuCachedSource2.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/Utils.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/WAVExtractor.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/MediaSource.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/MediaExtractor_legacy.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/AudioPlayer.cpp
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
${M3E_SOURCE_DIR}/src/av/media/libstagefright/MediaCodecListOverrides.h
)

set(STAGEFRIGHT_SOURCE_FILES ${STAGEFRIGHT_SOURCE_FILES}
${M3E_SOURCE_DIR}/src/av/media/libstagefright/SimpleDecodingSource.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/MediaCodecListOverrides.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/MediaCodecList.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/CodecBase.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/MediaCodec.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/SurfaceUtils.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/ACodec.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/DataConverter.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/OMXClient.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/SkipCutBuffer.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/FrameRenderTracker.cpp
)
endif(ENABLE_AV_CODEC)


# target files
# dependency
set(STAGEFRIGHT_DEP ${STAGEFRIGHT_DEPLIB})
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(stagefright SHARED ${STAGEFRIGHT_SOURCE_FILES} ${STAGEFRIGHT_HEADER_FILES})
target_link_libraries(stagefright ${STAGEFRIGHT_DEPLIB})