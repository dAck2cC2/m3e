project(VPX)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/vpx/include.cmake)

GET_ANDROID_MODULE(libvpx)

set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/libvpx/libwebm/mkvparser )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/libvpx/libwebm/mkvparser )

file(GLOB WEBM_HEADER_FILES ${HEADER_PATH}/*.h)

set(WEBM_SOURCE_FILES
${SOURCE_PATH}/mkvparser.cc
)

set(LIB_TYPE STATIC)
set(LIB_NAME webm)

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${LIB_NAME} ${LIB_TYPE} ${WEBM_SOURCE_FILES} ${WEBM_HEADER_FILES})
target_link_libraries(${LIB_NAME} ${WEBM_DEPLIB})
