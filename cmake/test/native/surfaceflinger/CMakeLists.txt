# demo program

project(TEST_SURFACEFLINGER)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/initrc/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/gui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/EGL/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/external/angle/include_util.cmake)

# dependency

set(DEMO_DEPLIBS
cutils
initrc
gui
${OPENGL_DEPLIB}
)

# EGL and OpenGL
if (ENABLE_ANGLE)
    include(${M3E_SOURCE_DIR}/cmake/external/angle/include.cmake)
    list(APPEND DEMO_DEPLIBS angle_util)
endif()

ADD_DEMO(surfaceflinger   ${M3E_SOURCE_DIR}/src/test/native/surfaceflinger/test_surfaceflinger.cpp)
