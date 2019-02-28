
project(GRALLOCUSAGE)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/grallocusage/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)
#include(${M3E_SOURCE_DIR}/cmake/frameworks/native/nativebase/include.cmake)
#include(${M3E_SOURCE_DIR}/cmake/frameworks/native/nativewindow/include.cmake)

set(${PROJECT_NAME}_DEPLIB
)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/system/core/libgrallocusage/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/system/core/libgrallocusage )

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES
${SOURCE_PATH}/*.h 
)

# source files
file(GLOB ${PROJECT_NAME}_SOURCE_FILES 
${SOURCE_PATH}/*.cpp
)

# target files
ADD_LIB(grallocusage)
