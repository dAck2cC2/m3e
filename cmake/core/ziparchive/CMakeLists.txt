
project(ZIPARCHIVE)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/ziparchive/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/base/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/zlib/include.cmake)

set(ZIPARCHIVE_DEPLIB
utils
base
zlib
)

if (MSVC)
    include(${M3E_SOURCE_DIR}/cmake/core/msvc/include.cmake)
    #list(APPEND ZIPARCHIVE_DEPLIB ${LIB_MSVC_WRAP})
elseif(APPLE)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -stdlib=libc++")
endif(MSVC)


set( HEADER_PATH ${M3E_SOURCE_DIR}/src/system/core/libziparchive/include/ziparchive )
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

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(ziparchive SHARED ${ZIPARCHIVE_SOURCE_FILES} ${ZIPARCHIVE_HEADER_FILES})
target_link_libraries(ziparchive ${ZIPARCHIVE_DEPLIB})

#set(ENABLE_TEST TRUE)
if(ENABLE_TEST)
    add_subdirectory(test)
endif(ENABLE_TEST)
