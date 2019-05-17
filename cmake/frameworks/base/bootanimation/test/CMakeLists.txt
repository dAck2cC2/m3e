# demo program

project(TEST_BOOTANIMATION)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/initrc/include.cmake)

set(DEMO_DEPLIBS
initrc
)

ADD_DEMO(bootanimation   ${M3E_SOURCE_DIR}/src/frameworks/base/cmds/bootanimation/test/test_bootanimation.cpp)
