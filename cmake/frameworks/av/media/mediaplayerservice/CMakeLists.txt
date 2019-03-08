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

include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/ui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/gui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/EGL/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/audioclient/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/audioprocessing/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/media/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/drm/drmframework/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright_foundation/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright_omx/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/camera/include.cmake)

set( ${PROJECT_NAME}_DEPLIB
log
cutils
utils
binder
gui
media
stagefright_omx
stagefright_foundation
stagefright
)

include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/native/headers/media_plugin/media/openmax)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/native/headers/media_plugin/media/hardware)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/include)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/wifi-display)

if (MSVC)
    add_definitions(-DNOMINMAX=1)
    add_definitions(-D__unused= )
    add_definitions(-Dstrcasecmp=_stricmp)
    add_definitions(-Dstrncasecmp=_strnicmp)
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libmediaplayerservice )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libmediaplayerservice )

include_directories(AFTER ${SOURCE_PATH})
include_directories(AFTER ${SOURCE_PATH}/nuplayer)


# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES  
${HEADER_PATH}/*.h
${HEADER_PATH}/nuplayer/*.h
)

set(${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/main_mediaplayerservice.cpp
${SOURCE_PATH}/MediaPlayerService.cpp
${SOURCE_PATH}/MediaPlayerFactory.cpp
${SOURCE_PATH}/TestPlayerStub.cpp
${SOURCE_PATH}/HDCP.cpp
${SOURCE_PATH}/MetadataRetrieverClient.cpp
${SOURCE_PATH}/MediaRecorderClient.cpp
${SOURCE_PATH}/ActivityManager.cpp
#${SOURCE_PATH}/StagefrightRecorder.cpp
#${SOURCE_PATH}/nuplayer/NuPlayerDriver.cpp
#${SOURCE_PATH}/nuplayer/NuPlayer.cpp
)

if(MSVC)
    include_directories(AFTER ${MSVC_PATH})

    list(APPEND ${PROJECT_NAME}_HEADER_FILES
    ${MSVC_PATH}/unistd.h
    ${MSVC_PATH}/sys/time.h
    )
    list(APPEND ${PROJECT_NAME}_SOURCE_FILES
    ${MSVC_PATH}/sys/time.c
    )    
endif(MSVC)

set(LIB_TYPE SHARED)
ADD_LIB(mediaplayerservice_default)
