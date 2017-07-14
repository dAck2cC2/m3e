
project(UTILS)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/utils.cmake)

# header files
file(GLOB UTILS_HEADER_FILES
${M3E_SOURCE_DIR}/src/native/include/cutils/*.h
${M3E_SOURCE_DIR}/src/native/include/utils/*.h
)

# source files
file(GLOB UTILS_SOURCE_FILES 
${M3E_SOURCE_DIR}/src/native/libutils/*.c 
${M3E_SOURCE_DIR}/src/native/libutils/*.cpp
${M3E_SOURCE_DIR}/src/native/libutils/cutils/*.c
)

# header and source code for MSVC
if(MSVC)
set(UTILS_HEADER_FILES ${UTILS_HEADER_FILES} ${M3E_SOURCE_DIR}/src/native/msvc/stdint.h)
set(UTILS_HEADER_FILES ${UTILS_HEADER_FILES} ${M3E_SOURCE_DIR}/src/native/msvc/sys/time.h)
set(UTILS_SOURCE_FILES ${UTILS_SOURCE_FILES} ${M3E_SOURCE_DIR}/src/native/msvc/sys/time.c)
endif()

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(utils SHARED ${UTILS_SOURCE_FILES} ${UTILS_HEADER_FILES})

if(UNIX AND NOT APPLE)
find_package(Threads)
target_link_libraries(utils ${CMAKE_THREAD_LIBS_INIT})
endif()

