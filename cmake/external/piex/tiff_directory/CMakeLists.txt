# tiff directory
project(TIFF_DIR)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/piex/include.cmake)

set(TIFF_DIR_DEPLIB
binary_parse
)

set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/piex/src/tiff_directory )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/piex/src/tiff_directory )

file(GLOB TIFF_DIR_HDR ${HEADER_PATH}/*.h)

set(TIFF_DIR_SRC
${SOURCE_PATH}/tiff_directory.cc
)

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(tiff_directory ${LIB_TYPE} ${TIFF_DIR_SRC} ${TIFF_DIR_HDR})
target_link_libraries(tiff_directory ${TIFF_DIR_DEPLIB})
