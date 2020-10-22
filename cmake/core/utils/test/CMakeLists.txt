
# gtest program

project(TEST_UTILS)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/base/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/${EXT_PATH}/gtest/include.cmake)

# dependency

set(TEST_UTILS_DEPLIB
gtest
utils
base
)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/system/core/libutils )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/system/core/libutils )

# main source

set(TEST_UTILS_SOURCE_FILES 
${GTEST_MAIN_CC}
)

# test utils

list(APPEND TEST_UTILS_SOURCE_FILES 
${SOURCE_PATH}/BitSet_test.cpp
${SOURCE_PATH}/FileMap_test.cpp
${SOURCE_PATH}/LruCache_test.cpp
${SOURCE_PATH}/Mutex_test.cpp
${SOURCE_PATH}/SharedBuffer_test.cpp
${SOURCE_PATH}/String8_test.cpp
${SOURCE_PATH}/StrongPointer_test.cpp
${SOURCE_PATH}/Unicode_test.cpp
${SOURCE_PATH}/Vector_test.cpp
)

list(APPEND TEST_UTILS_SOURCE_FILES 
${SOURCE_PATH}/SystemClock_test.cpp

${SOURCE_PATH}/Looper_test.cpp
${SOURCE_PATH}/RefBase_test.cpp
)

if(MSVC)
    add_definitions(-D__STDC_LIMIT_MACROS)
    list(REMOVE_ITEM TEST_UTILS_SOURCE_FILES 
    ${SOURCE_PATH}/Looper_test.cpp 
    ${SOURCE_PATH}/LruCache_test.cpp
    )
endif (MSVC)

# project
set(EXECUTABLE_OUTPUT_PATH ${BUILD_PATH})
add_executable(test_utils ${TEST_UTILS_SOURCE_FILES})
target_link_libraries(test_utils ${TEST_UTILS_DEPLIB})

add_executable(test_utils_singleton_1 ${GTEST_MAIN_CC} ${SOURCE_PATH}/Singleton_test1.cpp)
target_link_libraries(test_utils_singleton_1 ${TEST_UTILS_DEPLIB})
