
project(YUV)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/jpeg/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/libyuv/include.cmake)

GET_ANDROID_MODULE(libyuv)

#include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/libyuv/files)

# dependency
set(YUV_DEPLIB
jpeg
)

add_definitions(-DHAVE_JPEG)

file(GLOB YUV_HEADER_FILES
${M3E_SOURCE_DIR}/${EXT_PATH}/libyuv/files/include/*.h
${M3E_SOURCE_DIR}/${EXT_PATH}/libyuv/files/include/libyuv/*.h
)

file(GLOB YUV_SOURCE_FILES 
${M3E_SOURCE_DIR}/${EXT_PATH}/libyuv/files/source/*.cc
)

set(YUV_DEP ${YUV_DEPLIB})
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(yuv STATIC ${YUV_SOURCE_FILES} ${YUV_HEADER_FILES})
target_link_libraries(yuv ${YUV_DEPLIB})

