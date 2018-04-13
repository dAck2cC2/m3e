# demo program

project(TEST_SURFACEFLINGER)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/initrc/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/gui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/angle/include.cmake)

# dependency

set(DEMO_DEPLIBS
cutils
initrc
gui
angle
#hardware
)

ADD_DEMO(surfaceflinger   ${M3E_SOURCE_DIR}/src/test/native/surfaceflinger/test_surfaceflinger.cpp)
