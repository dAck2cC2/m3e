
# gtest program

project(TEST_CUTILS)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/gtest/include)

if(MSVC)
add_definitions(-D__STDC_LIMIT_MACROS)
endif()

# dependency

set(TEST_CUTILS_DEPLIB
gtest
cutils
)

set(TEST_CUTILS_DEP ${TEST_CUTILS_DEPLIB})

# main source

set(TEST_CUTILS_SOURCE_FILES 
${M3E_SOURCE_DIR}/src/test/main.cpp
)

# test log

set(TEST_CUTILS_SOURCE_FILES ${TEST_CUTILS_SOURCE_FILES}
${M3E_SOURCE_DIR}/src/test/core/cutils/config_utils_test.cpp
)

# project
set(EXECUTABLE_OUTPUT_PATH ${BUILD_PATH})
add_executable(test_cutils ${TEST_CUTILS_SOURCE_FILES})
target_link_libraries(test_cutils ${TEST_CUTILS_DEPLIB})
