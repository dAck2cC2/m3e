
# demo program

project(TEST_SKIA)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/skia/include.cmake)
#include(${M3E_SOURCE_DIR}/cmake/external/freeglut/include.cmake)

# dependency

set(DEMO_DEPLIBS
skia
)
ADD_DEMO(skia_core   ${M3E_SOURCE_DIR}/src/external/skia/test_core.cpp)
