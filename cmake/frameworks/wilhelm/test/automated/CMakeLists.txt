project(BUFFERQUEUE_TEST)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/${EXT_PATH}/gtest/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/wilhelm/opensles/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/wilhelm/openslesut/include.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/initrc/include.cmake)

set(${PROJECT_NAME}_DEPLIB
gtest
OpenSLES
OpenSLESUT
initrc
)

if(MSVC)
    add_definitions(-D_USE_MATH_DEFINES=1)

    include(${MSVC_INCLUDE})
    list(APPEND ${PROJECT_NAME}_DEPLIB ${LIB_MSVC_WRAP})
endif()

set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/wilhelm/tests/automated )

# test

list(APPEND ${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/BufferQueue_test.cpp
)

# project
set(EXECUTABLE_OUTPUT_PATH ${BUILD_PATH})
add_executable(test_bufferqueuetest ${${PROJECT_NAME}_SOURCE_FILES})
target_link_libraries(test_bufferqueuetest ${${PROJECT_NAME}_DEPLIB})

