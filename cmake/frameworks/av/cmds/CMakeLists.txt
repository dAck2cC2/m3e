
project(AV_CMDS)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/hidl/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/interfaces/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/initrc/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/ui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/gui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/math/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/audioclient/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/audioprocessing/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/media/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/mediametrics/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/mediaextractor/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/mediaplayerservice/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright_foundation/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/frameworks/av/drm/drmframework/include.cmake)

include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/native/include/media/openmax)

set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/cmds/stagefright )

if (MSVC)
    include(${MSVC_INCLUDE})
elseif(APPLE)
    set(CMAKE_CXX_FLAGS "-std=c++1z -stdlib=libc++" ${CMAKE_CXX_FLAGS})  
endif()

###############################################################################
# Audioloop
###############################################################################

set(CMDS_AUDIOLOOP_DEPLIBS
log
cutils
utils
initrc
media
stagefright_foundation
stagefright
)

if (MSVC)
    list(APPEND CMDS_AUDIOLOOP_DEPLIBS ${LIB_MSVC_WRAP})
endif()

set(CMDS_AUDIOLOOP_SOURCE_FILES
${SOURCE_PATH}/SineSource.cpp    
${SOURCE_PATH}/audioloop.cpp
)

set(EXECUTABLE_OUTPUT_PATH ${BUILD_PATH})
add_executable(audioloop ${CMDS_AUDIOLOOP_SOURCE_FILES})
target_link_libraries(audioloop ${CMDS_AUDIOLOOP_DEPLIBS})

###############################################################################
# Codec
###############################################################################

if (MSVC)
    add_definitions(-Dstrncasecmp=_strnicmp)
endif()

set(CMDS_CODEC_DEPLIBS
log
cutils
utils
binder
initrc
audioclient
media
stagefright_foundation
stagefright
gui
ui
)

if (MSVC)
    list(APPEND CMDS_CODEC_DEPLIBS ${LIB_MSVC_WRAP})
endif()

set(CMDS_CODEC_SOURCE_FILES
${SOURCE_PATH}/codec.cpp    
${SOURCE_PATH}/SimplePlayer.cpp
)

set(EXECUTABLE_OUTPUT_PATH ${BUILD_PATH})
add_executable(codec ${CMDS_CODEC_SOURCE_FILES})
target_link_libraries(codec ${CMDS_CODEC_DEPLIBS})
