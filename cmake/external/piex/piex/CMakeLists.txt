# piex
project(PIEX)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/piex/include.cmake)

set(PIEX_DEPLIB
binary_parse
image_type_recognition
tiff_directory
)

set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/piex/src/ )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/piex/src/ )

file(GLOB PIEX_HDR ${HEADER_PATH}/*.h)

set(PIEX_SRC
${SOURCE_PATH}/tiff_parser.cc 
${SOURCE_PATH}/piex.cc
)

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(piex ${LIB_TYPE} ${PIEX_SRC} ${PIEX_HDR})
target_link_libraries(piex ${PIEX_DEPLIB})
