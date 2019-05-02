
project(MEDIA)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/media/include.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/hidl/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/interfaces/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/audioclient/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/audioprocessing/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/mediametrics/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright_foundation/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/drm/drmframework/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/audio_utils/include.cmake)

set(${PROJECT_NAME}_DEPLIB
utils
binder
stagefright_foundation
audioutils
gui
)

# define
if(APPLE)
    add_definitions(-Dtypeof=__typeof__)
    set(CMAKE_CXX_FLAGS "-std=c++1z -stdlib=libc++" ${CMAKE_CXX_FLAGS})    

elseif(MSVC)
    add_definitions(-D__unused= )
    add_definitions(-Dtypeof=decltype)

    include(${M3E_SOURCE_DIR}/cmake/core/msvc/include.cmake)
    list(APPEND ${PROJECT_NAME}_DEPLIB ${LIB_MSVC_WRAP})

elseif(LINUX)
    add_definitions(-D__unused= )

endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libmedia/include/media )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libmedia )

include_directories(AFTER ${HEADER_PATH})
include_directories(AFTER ${SOURCE_PATH}/aidl)

# header files
file(GLOB MEDIA_HEADER_FILES 
${HEADER_PATH}/*.h 
${HEADER_PATH}/omx/1.0/*.h 
${SOURCE_PATH}/aidl/android/*.h
#${M3E_SOURCE_DIR}/src/frameworks/av/include/media/*.h 
${M3E_SOURCE_DIR}/src/frameworks/av/include/private/media/*.h
)

# source files
#file(GLOB MEDIA_SOURCE_FILES 
#${M3E_SOURCE_DIR}/src/av/media/libmedia/*.cpp
#)
set(MEDIA_SOURCE_FILES
${SOURCE_PATH}/AudioParameter.cpp
${SOURCE_PATH}/IDataSource.cpp
${SOURCE_PATH}/IMediaExtractor.cpp
${SOURCE_PATH}/IMediaExtractorService.cpp
${SOURCE_PATH}/IMediaSource.cpp
${SOURCE_PATH}/MediaDefs.cpp
)

if(ENABLE_AV_CODEC)
    include(${M3E_SOURCE_DIR}/cmake/frameworks/native/ui/include.cmake)
    include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/EGL/include.cmake)
    include(${M3E_SOURCE_DIR}/cmake/frameworks/native/gui/include.cmake)
    include(${M3E_SOURCE_DIR}/cmake/frameworks/av/camera/include.cmake)
    include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright_omx/include.cmake)
    include(${M3E_SOURCE_DIR}/cmake/external/sonivox/include.cmake)

    include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/native/include/media/openmax)
    include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright)
    include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/av/include/media)
    
    list(APPEND MEDIA_DEPLIB
    ui
    gui
    camera_client
    sonivox
    interfaces
    )

    list(APPEND MEDIA_SOURCE_FILES
    ${SOURCE_PATH}/BufferingSettings.cpp
    ${SOURCE_PATH}/IOMXStore.cpp
    ${SOURCE_PATH}/OMXBuffer.cpp
    ${SOURCE_PATH}/MediaCodecBuffer.cpp
    ${SOURCE_PATH}/IOMX.cpp
    ${SOURCE_PATH}/IMediaCodecList.cpp
    ${SOURCE_PATH}/IMediaCodecService.cpp
    ${SOURCE_PATH}/IResourceManagerClient.cpp
    ${SOURCE_PATH}/IResourceManagerService.cpp
    ${SOURCE_PATH}/MediaCodecInfo.cpp
    ${SOURCE_PATH}/MediaResource.cpp
    ${SOURCE_PATH}/MediaResourcePolicy.cpp
    ${SOURCE_PATH}/IMediaPlayerService.cpp    
    ${SOURCE_PATH}/IMediaPlayerClient.cpp 
    ${SOURCE_PATH}/IMediaPlayer.cpp 
    ${SOURCE_PATH}/IMediaMetadataRetriever.cpp
    ${SOURCE_PATH}/IMediaRecorder.cpp
    ${SOURCE_PATH}/IMediaRecorderClient.cpp
    ${SOURCE_PATH}/IRemoteDisplay.cpp
    ${SOURCE_PATH}/IRemoteDisplayClient.cpp
    ${SOURCE_PATH}/IMediaHTTPService.cpp
    ${SOURCE_PATH}/IMediaHTTPConnection.cpp
    ${SOURCE_PATH}/IStreamSource.cpp
    ${SOURCE_PATH}/IHDCP.cpp
    ${SOURCE_PATH}/Metadata.cpp
    ${SOURCE_PATH}/MediaScanner.cpp
    ${SOURCE_PATH}/MediaScannerClient.cpp
    ${SOURCE_PATH}/MidiIoWrapper.cpp
    ${SOURCE_PATH}/TypeConverter.cpp
    ${SOURCE_PATH}/omx/1.0/WOmxNode.cpp
    ${SOURCE_PATH}/omx/1.0/WOmxBufferSource.cpp
    #${SOURCE_PATH}/omx/1.0/WOmx.cpp
    ${SOURCE_PATH}/aidl/IGraphicBufferSource.cpp
    ${SOURCE_PATH}/aidl/IOMXBufferSource.cpp
    )
endif(ENABLE_AV_CODEC)

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(media SHARED ${MEDIA_SOURCE_FILES} ${MEDIA_HEADER_FILES})
target_link_libraries(media ${${PROJECT_NAME}_DEPLIB})

