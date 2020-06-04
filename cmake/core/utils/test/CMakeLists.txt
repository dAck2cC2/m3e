
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

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/system/core/libutils/tests )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/system/core/libutils/tests )

# main source

set(TEST_UTILS_SOURCE_FILES 
${M3E_SOURCE_DIR}/src/external/gtest/main.cpp
)

# test utils

list(APPEND TEST_UTILS_SOURCE_FILES 
${SOURCE_PATH}/BitSet_test.cpp
${SOURCE_PATH}/Looper_test.cpp
${SOURCE_PATH}/LruCache_test.cpp
${SOURCE_PATH}/RefBase_test.cpp
#${SOURCE_PATH}/Singleton_test.cpp
#${SOURCE_PATH}/Singleton_test1.cpp
#${SOURCE_PATH}/Singleton_test2.cpp
${SOURCE_PATH}/String8_test.cpp
${SOURCE_PATH}/StrongPointer_test.cpp
${SOURCE_PATH}/SystemClock_test.cpp
${SOURCE_PATH}/Unicode_test.cpp
${SOURCE_PATH}/Vector_test.cpp
${SOURCE_PATH}/Mutex_test.cpp
)

if(MSVC)
    add_definitions(-D__STDC_LIMIT_MACROS)
    list(REMOVE_ITEM TEST_UTILS_SOURCE_FILES ${M3E_SOURCE_DIR}/src/system/core/libutils/test/Looper_test.cpp)
endif (MSVC)

# project
set(EXECUTABLE_OUTPUT_PATH ${BUILD_PATH})
add_executable(test_utils ${TEST_UTILS_SOURCE_FILES})
target_link_libraries(test_utils ${TEST_UTILS_DEPLIB})
