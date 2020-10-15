project(MEDIAPLAYERSERVICE)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/mediaplayerservice/include.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/hidl/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/interfaces/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/frameworks/native/media_plugin/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/ui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/gui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/audioclient/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/audioprocessing/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/media/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/mediametrics/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/mediaextractor/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/frameworks/av/drm/drmframework/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright_foundation/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright_omx/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright/xmlparser/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/camera/include.cmake)

set( ${PROJECT_NAME}_DEPLIB
log
cutils
utils
binder
gui
media
mediautils
#mediametrics
stagefright_omx
stagefright_foundation
stagefright
)

include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/wifi-display)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/httplive)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/mpeg2ts)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/timedtext)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/rtsp)

# option
set(ENABLE_NUPLAYER         "TRUE")
set(ENABLE_RTSP_SOURCE      "FALSE")
set(ENABLE_HTTP_LIVE_SOURCE "FALSE")


if (MSVC)
    add_definitions(-DNOMINMAX=1)
    add_definitions(-D__unused= )
    add_definitions(-Dstrcasecmp=_stricmp)
    add_definitions(-Dstrncasecmp=_strnicmp)

    include(${MSVC_INCLUDE})
    list(APPEND ${PROJECT_NAME}_DEPLIB ${LIB_MSVC_WRAP})
elseif(APPLE)
    set(CMAKE_CXX_FLAGS "-std=c++1z -stdlib=libc++" ${CMAKE_CXX_FLAGS})  
elseif(LINUX)
    add_definitions(-D__unused= )
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libmediaplayerservice )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libmediaplayerservice )

include_directories(AFTER ${SOURCE_PATH})
include_directories(AFTER ${SOURCE_PATH}/nuplayer)

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES  
${HEADER_PATH}/*.h
)

set(${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/main_mediaplayerservice.cpp
${SOURCE_PATH}/MediaPlayerService.cpp
${SOURCE_PATH}/MediaPlayerFactory.cpp
${SOURCE_PATH}/TestPlayerStub.cpp
${SOURCE_PATH}/MetadataRetrieverClient.cpp
${SOURCE_PATH}/MediaRecorderClient.cpp
${SOURCE_PATH}/ActivityManager.cpp
#${SOURCE_PATH}/StagefrightRecorder.cpp
)

if (ENABLE_NUPLAYER)
    add_definitions(-DENABLE_NUPLAYER=1)

    list(APPEND ${PROJECT_NAME}_DEPLIB
    stagefright_timedtext
    )

    file(GLOB ${PROJECT_NAME}_SOURCE_NUPLAYER
    ${HEADER_PATH}/nuplayer/*.h
    )
    list(APPEND ${PROJECT_NAME}_SOURCE_NUPLAYER
    ${SOURCE_PATH}/nuplayer/AWakeLock.cpp
    ${SOURCE_PATH}/nuplayer/GenericSource.cpp
    #${SOURCE_PATH}/nuplayer/HTTPLiveSsource.cpp
    ${SOURCE_PATH}/nuplayer/NuPlayer.cpp
    ${SOURCE_PATH}/nuplayer/NuPlayerCCDecoder.cpp
    ${SOURCE_PATH}/nuplayer/NuPlayerDecoder.cpp
    ${SOURCE_PATH}/nuplayer/NuPlayerDecoderBase.cpp
    ${SOURCE_PATH}/nuplayer/NuPlayerDecoderPassThrough.cpp
    ${SOURCE_PATH}/nuplayer/NuPlayerDriver.cpp
    ${SOURCE_PATH}/nuplayer/NuPlayerDrm.cpp
    ${SOURCE_PATH}/nuplayer/NuPlayerRenderer.cpp
    ${SOURCE_PATH}/nuplayer/NuPlayerStreamListener.cpp
    #${SOURCE_PATH}/nuplayer/RTSPSource.cpp
    ${SOURCE_PATH}/nuplayer/StreamingSource.cpp
    )

    if (ENABLE_RTSP_SOURCE)
        add_definitions(-DENABLE_RTSP_SOURCE=1)

        list(APPEND ${PROJECT_NAME}_SOURCE_NUPLAYER
        ${SOURCE_PATH}/nuplayer/RTSPSource.cpp
        )
    endif(ENABLE_RTSP_SOURCE)

    if (ENABLE_HTTP_LIVE_SOURCE)
        add_definitions(-DENABLE_HTTP_LIVE_SOURCE=1)
        
        list(APPEND ${PROJECT_NAME}_SOURCE_NUPLAYER
        ${SOURCE_PATH}/nuplayer/HTTPLiveSsource.cpp
        )
    endif(ENABLE_HTTP_LIVE_SOURCE)

    source_group(NuPlayer FILES ${${PROJECT_NAME}_SOURCE_NUPLAYER})
    list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_SOURCE_NUPLAYER})
endif(ENABLE_NUPLAYER)

set(LIB_TYPE SHARED)
ADD_LIB(mediaplayerservice_default)
