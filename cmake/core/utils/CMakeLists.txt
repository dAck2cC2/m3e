
project(UTILS)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
#include(${M3E_SOURCE_DIR}/cmake/external/safe-iop/include.cmake)

add_definitions(-DANDROID_IMPLEMENTATION=1)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/system/core/include/utils )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/system/core/libutils/ )

# dependency

set(UTILS_DEPLIB
log
cutils
#safeiop
)

# header files
file(GLOB UTILS_HEADER_FILES ${HEADER_PATH}/*.h)

# source files
file(GLOB UTILS_SOURCE_FILES ${SOURCE_PATH}/*.cpp)

# header and source code for MSVC
if(MSVC)
    set(UTILS_HEADER_FILES ${UTILS_HEADER_FILES} ${MSVC_PATH}/stdint.h)
    set(UTILS_HEADER_FILES ${UTILS_HEADER_FILES} ${MSVC_PATH}/sys/time.h)
    set(UTILS_SOURCE_FILES ${UTILS_SOURCE_FILES} ${MSVC_PATH}/sys/time.c)
endif(MSVC)

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(utils SHARED ${UTILS_SOURCE_FILES} ${UTILS_HEADER_FILES})
target_link_libraries(utils ${UTILS_DEPLIB})

if(UNIX AND NOT APPLE)
    find_package(Threads)
    target_link_libraries(utils ${CMAKE_THREAD_LIBS_INIT})
endif()

