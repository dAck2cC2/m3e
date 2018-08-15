# binary_parse
project(BINARY_PARSE)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/piex/include.cmake)

set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/piex/src/binary_parse )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/piex/src/binary_parse )

file(GLOB BINARY_PARSE_HDR ${HEADER_PATH}/*.h)

set(BINARY_PARSE_SRC
${SOURCE_PATH}/cached_paged_byte_array.cc 
${SOURCE_PATH}/range_checked_byte_ptr.cc
)

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(binary_parse ${LIB_TYPE} ${BINARY_PARSE_SRC} ${BINARY_PARSE_HDR})
