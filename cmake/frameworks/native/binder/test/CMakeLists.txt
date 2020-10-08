
# gtest program

project(TEST_BINDER)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
#include(${M3E_SOURCE_DIR}/cmake/core/base/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/initrc/include.cmake)

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/gtest/include)

if(MSVC)
    add_definitions(-D__STDC_LIMIT_MACROS)
endif()

# dependency
set(TEST_BINDER_DEPLIB
gtest
binder
log
utils
initrc
#base
)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/libs/binder/tests )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/libs/binder/tests )


# main source
set(TEST_BINDER_SOURCE_FILES
${GTEST_MAIN_CC}
)

list(APPEND TEST_BINDER_SOURCE_FILES
${SOURCE_PATH}/Binder_test.cpp
${SOURCE_PATH}/MemoryDealer_test.cpp
${SOURCE_PATH}/Parcel_test.cpp
#${SOURCE_PATH}/binderTextOutputTest.cpp
)

if(MSVC)
    list(APPEND TEST_BINDER_SOURCE_FILES
    ${SOURCE_PATH}/binderValueTypeTest.cpp
    )
endif()

# project
set(EXECUTABLE_OUTPUT_PATH ${BUILD_PATH})
add_executable(test_binder ${TEST_BINDER_SOURCE_FILES})
target_link_libraries(test_binder ${TEST_BINDER_DEPLIB})
