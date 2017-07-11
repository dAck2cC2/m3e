
# gtest program

project(TESTALL)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
#include(${M3E_SOURCE_DIR}/cmake/gtest.cmake)
include(${M3E_SOURCE_DIR}/cmake/utils.cmake)

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/gtest/include)

if(MSVC)
add_definitions(-D__STDC_LIMIT_MACROS)
endif()

# dependency

set(TESTALL_DEPLIB
gtest
utils
)

set(LIBMISC_DEP ${TESTALL_DEPLIB})

# main source

set(TESTALL_SOURCE_FILES 
${M3E_SOURCE_DIR}/src/test/main.cpp
)

# test utils

set(TESTALL_SOURCE_FILES ${TESTALL_SOURCE_FILES}
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
add_executable(testall ${TESTALL_SOURCE_FILES})
target_link_libraries(testall ${TESTALL_DEPLIB})
