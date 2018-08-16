# image type recognition
project(IMAGE_TYPE)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/piex/include.cmake)

set(IMAGE_TYPE_DEPLIB
binary_parse
)

if(APPLE)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -stdlib=libc++")
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/piex/src/image_type_recognition )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/piex/src/image_type_recognition )

file(GLOB IMAGE_TYPE_HDR ${HEADER_PATH}/*.h)

set(IMAGE_TYPE_SRC
${SOURCE_PATH}/image_type_recognition_lite.cc
)

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(image_type_recognition ${LIB_TYPE} ${IMAGE_TYPE_SRC} ${IMAGE_TYPE_HDR})
target_link_libraries(image_type_recognition ${IMAGE_TYPE_DEPLIB})
