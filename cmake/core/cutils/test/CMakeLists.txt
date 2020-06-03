
# gtest program

project(TEST_CUTILS)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/${EXT_PATH}/gtest/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)

# dependency

set(TEST_CUTILS_DEPLIB
gtest
cutils
)

if(MSVC)
    add_definitions(-D__STDC_LIMIT_MACROS)
else(LINUX)
    list(APPEND TEST_CUTILS_DEPLIB dl)
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/system/core/libcutils/tests )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/system/core/libcutils/tests )

# main source

set(TEST_CUTILS_SOURCE_FILES
${M3E_SOURCE_DIR}/src/external/gtest/main.cpp
)

# test file

list(APPEND TEST_CUTILS_SOURCE_FILES
${SOURCE_PATH}/config_utils_test.cpp
${SOURCE_PATH}/native_handle_test.cpp
${SOURCE_PATH}/PropertiesTest.cpp
${SOURCE_PATH}/sockets_test.cpp
)

# project
set(EXECUTABLE_OUTPUT_PATH ${BUILD_PATH})
add_executable(test_cutils ${TEST_CUTILS_SOURCE_FILES})
target_link_libraries(test_cutils ${TEST_CUTILS_DEPLIB})
