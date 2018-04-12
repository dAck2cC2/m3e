# demo program

project(TEST_SURFACEFLINGER)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/include.cmake)

# dependency

set(DEMO_DEPLIBS
cutils
hardware
)

ADD_DEMO(surfaceflinger   ${M3E_SOURCE_DIR}/src/test/native/surfaceflinger/test_surfaceflinger.cpp)
