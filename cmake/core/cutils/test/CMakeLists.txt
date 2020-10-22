
# gtest program

project(TEST_CUTILS)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/${EXT_PATH}/gtest/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/base/include.cmake)

# dependency

set(TEST_CUTILS_DEPLIB
gtest
cutils
)

if(MSVC)
    add_definitions(-D__STDC_LIMIT_MACROS)
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/system/core/libcutils )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/system/core/libcutils )

# main source

set(TEST_CUTILS_SOURCE_FILES
${GTEST_MAIN_CC}
)

# test file

list(APPEND TEST_CUTILS_SOURCE_FILES
#${SOURCE_PATH}/sockets_test.cpp

#${SOURCE_PATH}/android_get_control_file_test.cpp
#${SOURCE_PATH}/android_get_control_socket_test.cpp
#${SOURCE_PATH}/ashmem_test.cpp    # using android::base
#${SOURCE_PATH}/fs_config_test.cpp
#${SOURCE_PATH}/memset_test.cpp    # assemble implmentation of memset
${SOURCE_PATH}/multiuser_test.cpp
${SOURCE_PATH}/properties_test.cpp
#${SOURCE_PATH}/sched_policy_test.cpp
#${SOURCE_PATH}/str_parms_test.cpp
#${SOURCE_PATH}/trace-dev_test.cpp
)

# M3E: add
list(APPEND TEST_CUTILS_SOURCE_FILES
${SOURCE_PATH}/tests/bitops_test.cpp
${SOURCE_PATH}/tests/config_utils_test.cpp
${SOURCE_PATH}/tests/native_handle_test.cpp
)

# project
set(EXECUTABLE_OUTPUT_PATH ${BUILD_PATH})
add_executable(test_cutils ${TEST_CUTILS_SOURCE_FILES})
target_link_libraries(test_cutils ${TEST_CUTILS_DEPLIB})
