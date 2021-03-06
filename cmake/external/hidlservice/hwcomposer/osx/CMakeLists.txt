
project(HWCOMPOSER_OSX)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)

set( ${PROJECT_NAME}_DEPLIB
log
cutils
utils
${OPENGL_DEPLIB}
)

find_library(APPKIT_LIBRARY AppKit)
list(APPEND ${PROJECT_NAME}_DEPLIB ${APPKIT_LIBRARY})

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/${EXT_PATH}/hidlservice/hwcomposer )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/${EXT_PATH}/hidlservice/hwcomposer )

include_directories(AFTER ${HEADER_PATH})
include_directories(AFTER ${HEADER_PATH}/angle)

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES  
${HEADER_PATH}/hwc/*.h
${HEADER_PATH}/angle/com/*.h
${HEADER_PATH}/angle/osx/*.h
)

file(GLOB ${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/hwc/*.cpp
${SOURCE_PATH}/angle/com/*.cpp
${SOURCE_PATH}/angle/osx/*.cpp
${SOURCE_PATH}/angle/osx/*.mm
)

# target files
set(LIB_TYPE SHARED)
ADD_LIB(hwcomposer_osx)
