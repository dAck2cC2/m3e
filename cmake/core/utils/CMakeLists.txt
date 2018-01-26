
project(UTILS)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
#include(${M3E_SOURCE_DIR}/cmake/external/safe-iop/include.cmake)

# dependency

set(UTILS_DEPLIB
log
cutils
#safeiop
)

set(UTILS_DEP ${UTILS_DEPLIB})

# header files
file(GLOB UTILS_HEADER_FILES
${M3E_SOURCE_DIR}/src/core/include/utils/*.h
)

# source files
file(GLOB UTILS_SOURCE_FILES 
#${M3E_SOURCE_DIR}/src/core/libutils/*.c 
${M3E_SOURCE_DIR}/src/core/libutils/*.cpp
)

# header and source code for MSVC
if(MSVC)
set(UTILS_HEADER_FILES ${UTILS_HEADER_FILES} ${M3E_SOURCE_DIR}/src/core/msvc/stdint.h)
set(UTILS_HEADER_FILES ${UTILS_HEADER_FILES} ${M3E_SOURCE_DIR}/src/core/msvc/sys/time.h)
set(UTILS_SOURCE_FILES ${UTILS_SOURCE_FILES} ${M3E_SOURCE_DIR}/src/core/msvc/sys/time.c)
endif()

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(utils SHARED ${UTILS_SOURCE_FILES} ${UTILS_HEADER_FILES})
target_link_libraries(utils ${UTILS_DEPLIB})

if(UNIX AND NOT APPLE)
find_package(Threads)
target_link_libraries(utils ${CMAKE_THREAD_LIBS_INIT})
endif()

