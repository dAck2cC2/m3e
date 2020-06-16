project(XAPLAY)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/wilhelm/openmaxal/include.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/initrc/include.cmake)

#include(${M3E_SOURCE_DIR}/cmake/system/hidl/include.cmake)
#include(${M3E_SOURCE_DIR}/cmake/hardware/interfaces/include.cmake)
#include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/include.cmake)
#include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
#include(${M3E_SOURCE_DIR}/cmake/frameworks/native/ui/include.cmake)
#include(${M3E_SOURCE_DIR}/cmake/frameworks/native/gui/include.cmake)


set(${PROJECT_NAME}_DEPLIB
OpenMAXAL
initrc
)

if(MSVC)
    #add_definitions(-D_USE_MATH_DEFINES=1)

    include(${M3E_SOURCE_DIR}/cmake/core/msvc/include.cmake)
    list(APPEND ${PROJECT_NAME}_DEPLIB ${LIB_MSVC_WRAP})
endif()

set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/wilhelm/tests/sandbox )

# test

list(APPEND ${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/xaplay.c
)

# project
set(EXECUTABLE_OUTPUT_PATH ${BUILD_PATH})
add_executable(test_xaplay ${${PROJECT_NAME}_SOURCE_FILES})
target_link_libraries(test_xaplay ${${PROJECT_NAME}_DEPLIB})
