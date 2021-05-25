
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

ADD_DEMO(surfaceflinger      
${M3E_SOURCE_DIR}/src/frameworks/native/services/surfaceflinger/customized/test_surfaceflinger.cpp
)
