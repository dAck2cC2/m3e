
project(SONIC)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/sonic/include.cmake)

GET_ANDROID_MODULE(sonic)

set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/sonic )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/sonic )

file(GLOB SONIC_HEADER_FILES ${HEADER_PATH}/*.h)

set(SONIC_SOURCE_FILES
${SOURCE_PATH}/sonic.c
)

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(sonic ${LIB_TYPE} ${SONIC_HEADER_FILES} ${SONIC_SOURCE_FILES})
target_link_libraries(sonic ${SONIC_DEPLIB})
