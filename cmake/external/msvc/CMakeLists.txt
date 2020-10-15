
project(MSVC_WRAP)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${MSVC_INCLUDE})

add_definitions(-DMSVC_WRAP_IMPLEMENTATION=1)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/external/msvc/ )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/external/msvc/ )

# header files
file(GLOB MSVC_HEADER_FILES  
${HEADER_PATH}/*.h
${HEADER_PATH}/arpa/*.h
${HEADER_PATH}/netinet/*.h
${HEADER_PATH}/sys/*.h
)

# source files
file(GLOB MSVC_SOURCE_FILES 
${SOURCE_PATH}/*.c
${SOURCE_PATH}/*.cc
${SOURCE_PATH}/*.cpp
${HEADER_PATH}/sys/*.c
)

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${LIB_MSVC_WRAP} SHARED ${MSVC_SOURCE_FILES} ${MSVC_HEADER_FILES})
