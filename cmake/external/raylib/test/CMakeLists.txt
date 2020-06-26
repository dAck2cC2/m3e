project(TEST_RAYLIB)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/raylib/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/frameworks/initrc/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/wilhelm/openmaxal/include.cmake)

set(DEMO_DEPLIBS
initrc
OpenMAXAL
raylib
)

#set(SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/raylib/examples)
#ADD_DEMO(raylib_template   ${SOURCE_PATH}/examples_template.c)

set(SOURCE_PATH  ${M3E_SOURCE_DIR}/src/${EXT_PATH}/raylib/)
ADD_DEMO(raylib  ${SOURCE_PATH}/test.c ${SOURCE_PATH}/test_case.h)
