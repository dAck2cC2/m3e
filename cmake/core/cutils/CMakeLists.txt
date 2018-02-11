
project(CUTILS)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)

include_directories(AFTER ${M3E_SOURCE_DIR}/src/core/libcutils)

# dependency

set(CUTILS_DEPLIB
log
)

set(CUTILS_DEP ${CUTILS_DEPLIB})

# header files
file(GLOB CUTILS_HEADER_FILES
${M3E_SOURCE_DIR}/src/core/include/cutils/*.h
${M3E_SOURCE_DIR}/src/core/libcutils/*.h
)

# source files
file(GLOB CUTILS_SOURCE_FILES 
${M3E_SOURCE_DIR}/src/core/libcutils/*.c
${M3E_SOURCE_DIR}/src/core/libcutils/*.cpp
)

# header and source code for MSVC
if(MSVC)
set(CUTILS_HEADER_FILES ${CUTILS_HEADER_FILES} ${M3E_SOURCE_DIR}/src/core/msvc/stdint.h)
#set(CUTILS_HEADER_FILES ${CUTILS_HEADER_FILES} ${M3E_SOURCE_DIR}/src/core/msvc/sys/time.h)
#set(CUTILS_SOURCE_FILES ${CUTILS_SOURCE_FILES} ${M3E_SOURCE_DIR}/src/core/msvc/sys/time.c)
endif()

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(cutils SHARED ${CUTILS_HEADER_FILES} ${CUTILS_SOURCE_FILES})
target_link_libraries(cutils ${CUTILS_DEPLIB})

if(UNIX AND NOT APPLE)
#find_package(Threads)
#target_link_libraries(cutils ${CMAKE_THREAD_LIBS_INIT})
endif()

