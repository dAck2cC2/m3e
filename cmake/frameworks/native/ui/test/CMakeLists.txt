# gtest program

project(TEST_UI)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
#include(${M3E_SOURCE_DIR}/cmake/core/base/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/ui/include.cmake)

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/gtest/include)


# dependency
set(TEST_BINDER_DEPLIB
gtest
binder
log
utils
initrc
ui
)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/libs/ui/tests )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/libs/ui/tests )


# main source
set(TEST_BINDER_SOURCE_FILES
${GTEST_MAIN_CC}
)

list(APPEND TEST_BINDER_SOURCE_FILES
#${SOURCE_PATH}/colorspace_test.cpp
${SOURCE_PATH}/Region_test.cpp
)

# project
set(EXECUTABLE_OUTPUT_PATH ${BUILD_PATH})
add_executable(test_ui ${TEST_BINDER_SOURCE_FILES})
target_link_libraries(test_ui ${TEST_BINDER_DEPLIB})
