# gtest program

project(TEST_BASE)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/${EXT_PATH}/gtest/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)

# dependency

set(TEST_BASE_DEPLIB
gtest
log
)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/system/core/base/ )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/system/core/base/ )

# header files
file(GLOB TEST_BASE_HEADER_FILES
${HEADER_PATH}/*.h
)

# main source

set(TEST_BASE_SOURCE_FILES
#${GTEST_MAIN_CC}
)

# test file

list(APPEND TEST_BASE_SOURCE_FILES
${SOURCE_PATH}/file.cpp
${SOURCE_PATH}/logging.cpp
${SOURCE_PATH}/parsenetaddress.cpp
${SOURCE_PATH}/quick_exit.cpp
${SOURCE_PATH}/stringprintf.cpp
${SOURCE_PATH}/strings.cpp
${SOURCE_PATH}/test_utils.cpp
${SOURCE_PATH}/endian_test.cpp
${SOURCE_PATH}/errors_test.cpp
${SOURCE_PATH}/file_test.cpp
${SOURCE_PATH}/logging_test.cpp
${SOURCE_PATH}/parsedouble_test.cpp
${SOURCE_PATH}/parseint_test.cpp
${SOURCE_PATH}/parsenetaddress_test.cpp
${SOURCE_PATH}/quick_exit_test.cpp
${SOURCE_PATH}/scopeguard_test.cpp
${SOURCE_PATH}/stringprintf_test.cpp
${SOURCE_PATH}/strings_test.cpp
${SOURCE_PATH}/test_main.cpp
)

if(MSVC)
    list(APPEND TEST_BASE_SOURCE_FILES
    ${SOURCE_PATH}/errors_windows.cpp
    ${SOURCE_PATH}/utf8.cpp
    ${SOURCE_PATH}/utf8_test.cpp
    )
else()
    list(APPEND TEST_BASE_SOURCE_FILES
    ${SOURCE_PATH}/errors_unix.cpp  
    )
endif()

# project
set(EXECUTABLE_OUTPUT_PATH ${BUILD_PATH})
add_executable(test_base ${TEST_BASE_SOURCE_FILES} ${TEST_BASE_HEADER_FILES})
target_link_libraries(test_base ${TEST_BASE_DEPLIB})
