
# gtest program

project(TEST_UTILS)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)

#include(${M3E_SOURCE_DIR}/cmake/gtest.cmake)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/gtest/include)

if(MSVC)
add_definitions(-D__STDC_LIMIT_MACROS)
endif()

# dependency

set(TEST_UTILS_DEPLIB
gtest
utils
)

set(TEST_UTILS_DEP ${TEST_UTILS_DEPLIB})

# main source

set(TEST_UTILS_SOURCE_FILES 
${M3E_SOURCE_DIR}/src/test/main.cpp
)

# test utils

set(TEST_UTILS_SOURCE_FILES ${TEST_UTILS_SOURCE_FILES}
#${M3E_SOURCE_DIR}/src/test/utils/Bitset_test.cpp
#${M3E_SOURCE_DIR}/src/test/utils/BlobCache_test.cpp
#${M3E_SOURCE_DIR}/src/test/utils/Looper_test.cpp
#${M3E_SOURCE_DIR}/src/test/utils/LruCache_test.cpp
${M3E_SOURCE_DIR}/src/test/utils/RefBase_test.cpp
#${M3E_SOURCE_DIR}/src/test/utils/Singleton_test.cpp
#${M3E_SOURCE_DIR}/src/test/utils/Singleton_test1.cpp
#${M3E_SOURCE_DIR}/src/test/utils/Singleton_test2.cpp
${M3E_SOURCE_DIR}/src/test/utils/String8_test.cpp
${M3E_SOURCE_DIR}/src/test/utils/StrongPointer_test.cpp
#${M3E_SOURCE_DIR}/src/test/utils/SystemClock_test.cpp
${M3E_SOURCE_DIR}/src/test/utils/Unicode_test.cpp
#${M3E_SOURCE_DIR}/src/test/utils/Vector_test.cpp
)

# project
set(EXECUTABLE_OUTPUT_PATH ${BUILD_PATH})
add_executable(test_utils ${TEST_UTILS_SOURCE_FILES})
target_link_libraries(test_utils ${TEST_UTILS_DEPLIB})
