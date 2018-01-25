
project(LOG)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)

add_definitions(-DFAKE_LOG_DEVICE=1)

# header files
file(GLOB LOG_HEADER_FILES
${M3E_SOURCE_DIR}/src/native/include/log/*.h
${M3E_SOURCE_DIR}/src/native/liblog/*.h 
)

# source files
file(GLOB LOG_SOURCE_FILES 
${M3E_SOURCE_DIR}/src/native/liblog/*.c 
)

if(MSVC)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/native/msvc)
set(LOG_HEADER_FILES ${LOG_HEADER_FILES} ${M3E_SOURCE_DIR}/src/native/msvc/unistd.h)
set(LOG_HEADER_FILES ${LOG_HEADER_FILES} ${M3E_SOURCE_DIR}/src/native/msvc/sys/time.h)
set(LOG_SOURCE_FILES ${LOG_SOURCE_FILES} ${M3E_SOURCE_DIR}/src/native/msvc/sys/time.c)
endif()

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(log SHARED ${LOG_SOURCE_FILES} ${LOG_HEADER_FILES})
