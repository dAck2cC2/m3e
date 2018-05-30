
project(ZLIB)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/zlib/include.cmake)

GET_ANDROID_MODULE(zlib)

# define
if(MSVC)
    add_definitions(-DZLIB_INTERNAL)
endif(MSVC)

set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/zlib/src )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/zlib/src )

file(GLOB ZLIB_HEADER_FILES
${HEADER_PATH}/*.h
)

set(ZLIB_SOURCE_FILES
${SOURCE_PATH}/adler32.c
${SOURCE_PATH}/compress.c
${SOURCE_PATH}/crc32.c
${SOURCE_PATH}/deflate.c
${SOURCE_PATH}/gzclose.c
${SOURCE_PATH}/gzlib.c
${SOURCE_PATH}/gzread.c 
${SOURCE_PATH}/gzwrite.c
${SOURCE_PATH}/infback.c 
${SOURCE_PATH}/inffast.c
${SOURCE_PATH}/inflate.c
${SOURCE_PATH}/inftrees.c 
${SOURCE_PATH}/trees.c
${SOURCE_PATH}/uncompr.c 
${SOURCE_PATH}/zutil.c
)

if(MSVC)
    include_directories(AFTER ${MSVC_PATH})
    list(APPEND ZIPARCHIVE_HEADER_FILES ${MSVC_PATH}/unistd.h)
endif()

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(zlib SHARED ${ZLIB_SOURCE_FILES} ${ZLIB_HEADER_FILES})
