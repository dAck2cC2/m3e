project(RS)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/rs/include.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/system/hidl/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/interfaces/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/ui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/gui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/EGL/include.cmake)

set(${PROJECT_NAME}_DEPLIB
log
utils
gui
)

if(MSVC)
    include(${M3E_SOURCE_DIR}/cmake/core/msvc/include.cmake)
    list(APPEND ${PROJECT_NAME}_DEPLIB ${LIB_MSVC_WRAP})
endif()

add_definitions(-DRS_VERSION=19)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/rs )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/rs/cpp )

file(GLOB ${PROJECT_NAME}_HEADER_FILES
${HEADER_PATH}/*.h 
${SOURCE_PATH}/*.h 
)

set(${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/RenderScript.cpp
${SOURCE_PATH}/rsDispatch.cpp
${SOURCE_PATH}/Allocation.cpp
${SOURCE_PATH}/BaseObj.cpp
${SOURCE_PATH}/Type.cpp
${SOURCE_PATH}/Element.cpp
${SOURCE_PATH}/ScriptIntrinsics.cpp
${SOURCE_PATH}/Script.cpp
)


# target files
set(LIB_TYPE SHARED)
set(LIB_NAME RScpp)
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${LIB_NAME} ${LIB_TYPE} ${${PROJECT_NAME}_SOURCE_FILES} ${${PROJECT_NAME}_HEADER_FILES})
target_link_libraries(${LIB_NAME} ${${PROJECT_NAME}_DEPLIB})
