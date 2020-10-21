
# gtest program

project(TEST_LOG)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/${EXT_PATH}/gtest/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)

# dependency

set(TEST_LOG_DEPLIB
gtest
log
)

if(MSVC)
    add_definitions(-D__STDC_LIMIT_MACROS)
    include(${MSVC_INCLUDE})
    list(APPEND TEST_LOG_DEPLIB ${LIB_MSVC_WRAP})
endif(MSVC)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/system/core/liblog/tests )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/system/core/liblog/tests )

include_directories(AFTER ${HEADER_PATH})

# main source

set(TEST_LOG_SOURCE_FILES 
${GTEST_MAIN_CC}
)

# test log

list(APPEND TEST_LOG_SOURCE_FILES
# liblog-tests-default
${SOURCE_PATH}/libc_test.cpp
${SOURCE_PATH}/liblog_test_default.cpp
#${SOURCE_PATH}/liblog_test_stderr.cpp
${SOURCE_PATH}/log_id_test.cpp
${SOURCE_PATH}/log_radio_test.cpp
${SOURCE_PATH}/log_read_test.cpp
${SOURCE_PATH}/log_system_test.cpp
#${SOURCE_PATH}/log_time_test.cpp
${SOURCE_PATH}/log_wrap_test.cpp

# M3E: add
${SOURCE_PATH}/AndroidLog_test.cpp
)

# project
set(EXECUTABLE_OUTPUT_PATH ${BUILD_PATH})
add_executable(test_log ${TEST_LOG_SOURCE_FILES})
target_link_libraries(test_log ${TEST_LOG_DEPLIB})
