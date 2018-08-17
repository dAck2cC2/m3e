
# gtest program

project(TEST_BINDER)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
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
initrc
)

set(TEST_BINDER_DEP ${TEST_BINDER_DEPLIB})

# test file

file(GLOB TEST_BINDER_SOURCE_FILES 
${M3E_SOURCE_DIR}/src/test/native/binder/*.cpp
)

# main source

set(TEST_BINDER_SOURCE_FILES ${TEST_BINDER_SOURCE_FILES}
${M3E_SOURCE_DIR}/src/test/main.cpp
)

# project
set(EXECUTABLE_OUTPUT_PATH ${BUILD_PATH})
add_executable(test_binder ${TEST_BINDER_SOURCE_FILES})
target_link_libraries(test_binder ${TEST_BINDER_DEPLIB})

