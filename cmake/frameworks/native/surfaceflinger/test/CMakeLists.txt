
# demo program

project(TEST_SURFACEFLINGER)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)
include(${INITRC_INCLUDE})
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/ui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/gui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/include.cmake)

set(DEMO_DEPLIBS
cutils
utils
initrc
gui
${OPENGL_DEPLIB}
)

# EGL and OpenGL
if (ENABLE_ANGLE)
    include(${M3E_SOURCE_DIR}/cmake/external/angle/include.cmake)
    list(APPEND DEMO_DEPLIBS angle_util)
endif()

ADD_DEMO(surfaceflinger_Triangle      ${M3E_SOURCE_DIR}/src/frameworks/native/services/surfaceflinger/tests/test_Triangle.cpp)
ADD_DEMO(surfaceflinger_DrawTexture   ${M3E_SOURCE_DIR}/src/frameworks/native/services/surfaceflinger/tests/test_DrawTexture.cpp)
