
project(CUTILS)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)

add_definitions(-DANDROID_IMPLEMENTATION=1)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/system/core/include/cutils )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/system/core/libcutils )

include_directories(AFTER ${SOURCE_PATH})

# dependency

set(CUTILS_DEPLIB
log
)

# header files
file(GLOB CUTILS_HEADER_FILES
${HEADER_PATH}/*.h
${SOURCE_PATH}/*.h
${SOURCE_PATH}/sys/*.h
)

# source files
file(GLOB CUTILS_SOURCE_FILES 
${SOURCE_PATH}/*.c
${SOURCE_PATH}/sys/*.cpp
)

# header and source code for MSVC
if(MSVC)
    set(CUTILS_HEADER_FILES ${CUTILS_HEADER_FILES} ${MSVC_PATH}/stdint.h)
    set(CUTILS_SOURCE_FILES ${CUTILS_SOURCE_FILES} ${MSVC_PATH}/ffs.c)
    #set(CUTILS_HEADER_FILES ${CUTILS_HEADER_FILES} ${MSVC_PATH}/sys/time.h)
elseif(APPLE)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -stdlib=libc++")
elseif(CYGWIN)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=gnu++11")
elseif(UNIX)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++0x")
endif()

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(cutils SHARED ${CUTILS_HEADER_FILES} ${CUTILS_SOURCE_FILES})
target_link_libraries(cutils ${CUTILS_DEPLIB})

if(UNIX AND NOT APPLE)
    #find_package(Threads)
    #target_link_libraries(cutils ${CMAKE_THREAD_LIBS_INIT})
endif()

