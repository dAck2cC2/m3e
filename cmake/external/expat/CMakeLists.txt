
project(EXPAT)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/expat/include.cmake)

GET_ANDROID_MODULE(expat)

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/expat)

add_definitions(-DHAVE_EXPAT_CONFIG_H)

file(GLOB EXPAT_HEADER_FILES
${M3E_SOURCE_DIR}/${EXT_PATH}/expat/lib/*.h
)

set(EXPAT_SOURCE_FILES 
${M3E_SOURCE_DIR}/${EXT_PATH}/expat/lib/xmlparse.c
${M3E_SOURCE_DIR}/${EXT_PATH}/expat/lib/xmlrole.c
${M3E_SOURCE_DIR}/${EXT_PATH}/expat/lib/xmltok.c
)

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(expat SHARED ${EXPAT_SOURCE_FILES} ${EXPAT_HEADER_FILES})
