project(MEDIAPLAYERSERVICE)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/ui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/gui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/EGL/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/mediautils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/drm/drmframework/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright_foundation/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright_omx/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright/include.cmake)

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

include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/native/include/media/openmax)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/include)

if (MSVC)
    add_definitions(-DNOMINMAX=1)
    add_definitions(-D__unused= )
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libmediaplayerservice )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libmediaplayerservice )

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES  
${HEADER_PATH}/*.h
${HEADER_PATH}/nuplayer/*.h
)

set(${PROJECT_NAME}_HEADER_FILES
${SOURCE_PATH}/MediaPlayerService.cpp
)

set(LIB_TYPE SHARED)
ADD_LIB(mediaplayerservice_default)
