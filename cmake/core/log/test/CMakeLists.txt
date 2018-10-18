
# gtest program

project(TEST_LOG)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/gtest/include)

if(MSVC)
    add_definitions(-D__STDC_LIMIT_MACROS)
    include_directories(AFTER ${MSVC_PATH})
endif(MSVC)

# dependency

set(TEST_LOG_DEPLIB
gtest
log
)

set(TEST_LOG_DEP ${TEST_LOG_DEPLIB})

# main source

set(TEST_LOG_SOURCE_FILES 
${M3E_SOURCE_DIR}/src/external/gtest/main.cpp
)

# test log

set(TEST_LOG_SOURCE_FILES ${TEST_LOG_SOURCE_FILES}
${M3E_SOURCE_DIR}/src/system/core/liblog/test/AndroidLog_test.cpp
)

# project
set(EXECUTABLE_OUTPUT_PATH ${BUILD_PATH})
add_executable(test_log ${TEST_LOG_SOURCE_FILES})
target_link_libraries(test_log ${TEST_LOG_DEPLIB})