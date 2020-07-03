project(HWCOMPOSER2_GLFW)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/hidl/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/interfaces/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/glfw/include.cmake)

set( ${PROJECT_NAME}_DEPLIB
log
cutils
utils
interfaces
${OPENGL_DEPLIB}
glfw
)

add_definitions(-DENABLE_GLFW=1)

if(MSVC)
    add_definitions(-DNOMINMAX)
    add_definitions(-D_ALLOW_KEYWORD_MACROS=1)
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/hardware/hwcomposer )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/hardware/hwcomposer )

include_directories(AFTER ${HEADER_PATH})

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES  
${HEADER_PATH}/hwc2/*.h
${HEADER_PATH}/com/*.h
)

# source files
file(GLOB ${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/hwc2/*.cpp
${SOURCE_PATH}/com/*.cpp
)

list(APPEND ${PROJECT_NAME}_HEADER_FILES ${${PROJECT_NAME}_HEADER_GLFW})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_SOURCE_GLFW})

# target files
ADD_LIB(hwcomposer2_glfw)
