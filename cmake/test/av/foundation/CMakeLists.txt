
# gtest program

project(TEST_FOUNDATION)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright_foundation/include.cmake)

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/gtest/include)

if(MSVC)
#add_definitions(-D__STDC_LIMIT_MACROS)
endif()

# dependency

set(TEST_FOUNDATION_DEPLIB
gtest
stagefright_foundation
)

set(TEST_FOUNDATION_DEP ${TEST_FOUNDATION_DEPLIB})

# test file

file(GLOB TEST_FOUNDATION_SOURCE_FILES 
${M3E_SOURCE_DIR}/src/test/av/foundation/*.cpp
)

# main source

set(TEST_FOUNDATION_SOURCE_FILES ${TEST_FOUNDATION_SOURCE_FILES}
${M3E_SOURCE_DIR}/src/test/main.cpp
)

# project
set(EXECUTABLE_OUTPUT_PATH ${BUILD_PATH})
add_executable(test_foundation ${TEST_FOUNDATION_SOURCE_FILES})
target_link_libraries(test_foundation ${TEST_FOUNDATION_DEPLIB})

