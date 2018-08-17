
project(ZIPARCHIVE)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/ziparchive/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/base/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/zlib/include.cmake)

set(ZIPARCHIVE_DEPLIB
base
utils
zlib
)

add_definitions(-DANDROID_IMPLEMENTATION=1)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/system/core/include/ziparchive )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/system/core/libziparchive )

# header files
file(GLOB ZIPARCHIVE_HEADER_FILES
${HEADER_PATH}/*.h
${SOURCE_PATH}/*.h 
)

# source files
file(GLOB ZIPARCHIVE_SOURCE_FILES 
${SOURCE_PATH}/zip_archive.cc
${SOURCE_PATH}/zip_archive_stream_entry.cc
${SOURCE_PATH}/zip_writer.cc
)

if(MSVC)
    include_directories(AFTER ${MSVC_PATH})
    list(APPEND ZIPARCHIVE_HEADER_FILES ${MSVC_PATH}/unistd.h)
elseif(APPLE)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -stdlib=libc++")
endif()

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(ziparchive SHARED ${ZIPARCHIVE_SOURCE_FILES} ${ZIPARCHIVE_HEADER_FILES})
target_link_libraries(ziparchive ${ZIPARCHIVE_DEPLIB})
