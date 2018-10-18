
# gtest program

project(TEST_UTILS)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/gtest/include)

# dependency

set(TEST_UTILS_DEPLIB
gtest
utils
)

set(TEST_UTILS_DEP ${TEST_UTILS_DEPLIB})

# main source

set(TEST_UTILS_SOURCE_FILES 
${M3E_SOURCE_DIR}/src/external/gtest/main.cpp
)

# test utils

set(TEST_UTILS_SOURCE_FILES ${TEST_UTILS_SOURCE_FILES}
${M3E_SOURCE_DIR}/src/system/core/libutils/test/BitSet_test.cpp
${M3E_SOURCE_DIR}/src/system/core/libutils/test/BlobCache_test.cpp
${M3E_SOURCE_DIR}/src/system/core/libutils/test/Looper_test.cpp
${M3E_SOURCE_DIR}/src/system/core/libutils/test/LruCache_test.cpp
${M3E_SOURCE_DIR}/src/system/core/libutils/test/RefBase_test.cpp
#${M3E_SOURCE_DIR}/src/system/core/libutils/test/Singleton_test.cpp
#${M3E_SOURCE_DIR}/src/system/core/libutils/test/Singleton_test1.cpp
#${M3E_SOURCE_DIR}/src/system/core/libutils/test/Singleton_test2.cpp
${M3E_SOURCE_DIR}/src/system/core/libutils/test/String8_test.cpp
${M3E_SOURCE_DIR}/src/system/core/libutils/test/StrongPointer_test.cpp
${M3E_SOURCE_DIR}/src/system/core/libutils/test/SystemClock_test.cpp
${M3E_SOURCE_DIR}/src/system/core/libutils/test/Unicode_test.cpp
${M3E_SOURCE_DIR}/src/system/core/libutils/test/Vector_test.cpp
)

if(MSVC)
    add_definitions(-D__STDC_LIMIT_MACROS)
    list(REMOVE_ITEM TEST_UTILS_SOURCE_FILES ${M3E_SOURCE_DIR}/src/system/core/libutils/test/Looper_test.cpp)
endif (MSVC)

# project
set(EXECUTABLE_OUTPUT_PATH ${BUILD_PATH})
add_executable(test_utils ${TEST_UTILS_SOURCE_FILES})
target_link_libraries(test_utils ${TEST_UTILS_DEPLIB})
