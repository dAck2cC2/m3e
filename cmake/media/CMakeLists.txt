
project(MEDIA)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/misc/include.cmake)

set(MEDIA_DEPLIB
utils
misc
stagefright_foundation
)

# dependency
set(MEDIA_DEP 
${MEDIA_DEPLIB}
)

# define
if(APPLE)
add_definitions(-Disnanf=isnan)
endif()

# include files
include_directories(AFTER ${M3E_SOURCE_DIR}/src/av/include)

# header files
file(GLOB MEDIA_HEADER_FILES 
${M3E_SOURCE_DIR}/src/av/include/media/*.h 
)

# source files
#file(GLOB MEDIA_SOURCE_FILES 
#${M3E_SOURCE_DIR}/src/av/media/libmedia/*.cpp
#)
set(MEDIA_SOURCE_FILES
${M3E_SOURCE_DIR}/src/av/media/libmedia/AudioParameter.cpp
${M3E_SOURCE_DIR}/src/av/media/libmedia/AudioSystem.cpp
${M3E_SOURCE_DIR}/src/av/media/libmedia/IAudioFlinger.cpp
${M3E_SOURCE_DIR}/src/av/media/libmedia/IAudioFlingerClient.cpp
${M3E_SOURCE_DIR}/src/av/media/libmedia/IAudioPolicyService.cpp
${M3E_SOURCE_DIR}/src/av/media/libmedia/IAudioPolicyServiceClient.cpp
${M3E_SOURCE_DIR}/src/av/media/libmedia/IDataSource.cpp
${M3E_SOURCE_DIR}/src/av/media/libmedia/IMediaExtractor.cpp
${M3E_SOURCE_DIR}/src/av/media/libmedia/IMediaExtractorService.cpp
${M3E_SOURCE_DIR}/src/av/media/libmedia/IMediaSource.cpp
)

if(ENABLE_CODEC_SELECTOR)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/av/media/libstagefright)

set(MEDIA_SOURCE_FILES ${MEDIA_SOURCE_FILES}
${M3E_SOURCE_DIR}/src/av/media/libmedia/IOMX.cpp
${M3E_SOURCE_DIR}/src/av/media/libmedia/IMediaCodecService.cpp
${M3E_SOURCE_DIR}/src/av/media/libmedia/IResourceManagerClient.cpp
${M3E_SOURCE_DIR}/src/av/media/libmedia/IResourceManagerService.cpp
${M3E_SOURCE_DIR}/src/av/media/libmedia/MediaCodecInfo.cpp
${M3E_SOURCE_DIR}/src/av/media/libmedia/MediaResource.cpp
${M3E_SOURCE_DIR}/src/av/media/libmedia/MediaResourcePolicy.cpp
)
endif(ENABLE_CODEC_SELECTOR)

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(media SHARED ${MEDIA_SOURCE_FILES} ${MEDIA_HEADER_FILES})
target_link_libraries(media ${MEDIA_DEPLIB})

