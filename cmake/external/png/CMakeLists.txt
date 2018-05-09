
project(PNG)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/png/include.cmake)

GET_ANDROID_MODULE(libpng)

set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/libpng )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/libpng )

include(${M3E_SOURCE_DIR}/cmake/external/zlib/include.cmake)
set(PNG_DEPLIB 
zlib
)

file(GLOB PNG_HEADER_FILES
${HEADER_PATH}/*.h
)

set(PNG_SOURCE_FILES
${SOURCE_PATH}/png.c
${SOURCE_PATH}/pngerror.c 
${SOURCE_PATH}/pngget.c
${SOURCE_PATH}/pngmem.c 
${SOURCE_PATH}/pngpread.c
${SOURCE_PATH}/pngread.c 
${SOURCE_PATH}/pngrio.c 
${SOURCE_PATH}/pngrtran.c 
${SOURCE_PATH}/pngrutil.c
${SOURCE_PATH}/pngset.c
${SOURCE_PATH}/pngtrans.c
${SOURCE_PATH}/pngwio.c 
${SOURCE_PATH}/pngwrite.c 
${SOURCE_PATH}/pngwtran.c 
${SOURCE_PATH}/pngwutil.c 
)

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(png SHARED ${PNG_SOURCE_FILES} ${PNG_HEADER_FILES})
target_link_libraries(png ${PNG_DEPLIB})
