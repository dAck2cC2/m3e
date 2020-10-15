project(xaVideoDecoderCapabilities)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/wilhelm/openmaxal/include.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/initrc/include.cmake)

set(${PROJECT_NAME}_DEPLIB
OpenMAXAL
initrc
)

if(MSVC)
    #add_definitions(-D_USE_MATH_DEFINES=1)

    include(${MSVC_INCLUDE})
    list(APPEND ${PROJECT_NAME}_DEPLIB ${LIB_MSVC_WRAP})
endif()

set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/wilhelm/tests/examples )

# test

list(APPEND ${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/xaVideoDecoderCapabilities.cpp
)

# project
set(EXECUTABLE_OUTPUT_PATH ${BUILD_PATH})
add_executable(test_xaVideoDecoderCapabilities ${${PROJECT_NAME}_SOURCE_FILES})
target_link_libraries(test_xaVideoDecoderCapabilities ${${PROJECT_NAME}_DEPLIB})
