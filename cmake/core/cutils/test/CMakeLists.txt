
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
base
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
#${SOURCE_PATH}/sockets_test.cpp                     # not working on MSVC

#${SOURCE_PATH}/android_get_control_file_test.cpp    # no implementation of android_get_control_file
#${SOURCE_PATH}/android_get_control_socket_test.cpp  # not working on MSVC and Apple
#${SOURCE_PATH}/ashmem_test.cpp                      # not working on MSVC and Apple
#${SOURCE_PATH}/fs_config_test.cpp                   # no implmentation of fs_config
#${SOURCE_PATH}/memset_test.cpp                      # assemble implmentation of memset
${SOURCE_PATH}/multiuser_test.cpp
${SOURCE_PATH}/properties_test.cpp
#${SOURCE_PATH}/sched_policy_test.cpp                # no implmentation of sched_policy
#${SOURCE_PATH}/str_parms_test.cpp                   # no implmentation of str_parms
#${SOURCE_PATH}/trace-dev_test.cpp                   # no implmentation of trace-dev
)

# M3E: add
list(APPEND TEST_CUTILS_SOURCE_FILES
${SOURCE_PATH}/tests/bitops_test.cpp
${SOURCE_PATH}/tests/config_utils_test.cpp
${SOURCE_PATH}/tests/native_handle_test.cpp
)

if (APPLE)
list(APPEND TEST_CUTILS_SOURCE_FILES
${SOURCE_PATH}/sockets_test.cpp
)
endif()

# project
set(EXECUTABLE_OUTPUT_PATH ${BUILD_PATH})
add_executable(test_cutils ${TEST_CUTILS_SOURCE_FILES})
target_link_libraries(test_cutils ${TEST_CUTILS_DEPLIB})
