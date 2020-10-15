# giflib
project(GIF)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/gif/include.cmake)

GET_ANDROID_MODULE(giflib)

set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/giflib )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/giflib )

add_definitions(-DHAVE_CONFIG_H)

file(GLOB GIF_HEADER_FILES
${HEADER_PATH}/*.h
)

set(GIF_SOURCE_FILES
${SOURCE_PATH}/dgif_lib.c 
${SOURCE_PATH}/egif_lib.c 
${SOURCE_PATH}/gifalloc.c 
${SOURCE_PATH}/gif_err.c  
${SOURCE_PATH}/gif_hash.c
${SOURCE_PATH}/openbsd-reallocarray.c
${SOURCE_PATH}/quantize.c
)

if(MSVC)
    include(${M3E_SOURCE_DIR}/cmake/core/msvc/include.cmake)
    list(APPEND GIF_HEADER_FILES 
    ${MSVC_PATH}/unistd.h
    )
endif()

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${GIF_LIBRARIES} STATIC ${GIF_SOURCE_FILES} ${GIF_HEADER_FILES})
