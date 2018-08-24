
project(AV_CMDS)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/initrc/include.cmake)

set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/cmds/stagefright )

###############################################################################
# Audioloop
###############################################################################

include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/EGL/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/ui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/gui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright_foundation/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright/include.cmake)

set(AUDIOLOOP_DEPLIBS
initrc
media
stagefright_foundation
stagefright
)

include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/native/include/media/openmax)

set(AUDIOLOOP_SOURCE_FILES
${SOURCE_PATH}/SineSource.cpp    
${SOURCE_PATH}/audioloop.cpp
)

set(EXECUTABLE_OUTPUT_PATH ${BUILD_PATH})
add_executable(audioloop ${AUDIOLOOP_SOURCE_FILES})
target_link_libraries(audioloop ${AUDIOLOOP_DEPLIBS})

