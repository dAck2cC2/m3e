
project(YUV)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/yuv/include.cmake)

GET_ANDROID_MODULE(libyuv)

# dependency

include(${M3E_SOURCE_DIR}/cmake/external/jpeg-turbo/include.cmake)

set(YUV_DEPLIB
${JPEG_LIBRARIES}
)

#include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/libyuv/files)

add_definitions(-DHAVE_JPEG)

file(GLOB YUV_HEADER_FILES
${M3E_SOURCE_DIR}/${EXT_PATH}/libyuv/files/include/*.h
${M3E_SOURCE_DIR}/${EXT_PATH}/libyuv/files/include/libyuv/*.h
)

file(GLOB YUV_SOURCE_FILES 
${M3E_SOURCE_DIR}/${EXT_PATH}/libyuv/files/source/*.cc
)

if(LINUX)
    set(LIB_TYPE SHARED)
else()
    set(LIB_TYPE STATIC)
endif()
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(yuv ${LIB_TYPE} ${YUV_SOURCE_FILES} ${YUV_HEADER_FILES})
target_link_libraries(yuv ${YUV_DEPLIB})

