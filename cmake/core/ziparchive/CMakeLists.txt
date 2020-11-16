
project(ZIPARCHIVE)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/ziparchive/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/base/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/zlib/include.cmake)

set(${PROJECT_NAME}_DEPLIB
utils
base
zlib
)

if (MSVC)
    include(${MSVC_INCLUDE})
    #list(APPEND ZIPARCHIVE_DEPLIB ${LIB_MSVC_WRAP})

    add_definitions(-Dlseek64=_lseeki64)
    add_definitions(-D__typeof__=decltype)

elseif(APPLE)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -stdlib=libc++")

elseif(LINUX)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17")
endif()


set( HEADER_PATH ${M3E_SOURCE_DIR}/src/system/core/libziparchive/include/ziparchive )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/system/core/libziparchive )

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES
${HEADER_PATH}/*.h
${SOURCE_PATH}/*.h 
)

# source files
file(GLOB ${PROJECT_NAME}_SOURCE_FILES 
${SOURCE_PATH}/zip_archive.cc
${SOURCE_PATH}/zip_archive_stream_entry.cc
${SOURCE_PATH}/zip_writer.cc
)

# target files
ADD_SHARED_LIB(ziparchive)

set(ENABLE_TEST TRUE)
if(ENABLE_TEST)
    add_subdirectory(test)
endif(ENABLE_TEST)
