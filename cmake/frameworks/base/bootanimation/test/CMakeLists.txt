# demo program

project(TEST_BOOTANIMATION)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/initrc/include.cmake)

add_definitions(-DANDROID_IMPLEMENTATION=0)

# dependency

set(DEMO_DEPLIBS
cutils
utils
initrc
)

ADD_DEMO(bootanimation   ${M3E_SOURCE_DIR}/src/frameworks/base/cmds/bootanimation/test/test_bootanimation.cpp)
