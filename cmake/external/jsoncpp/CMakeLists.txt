
project(jsoncpp)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/jsoncpp/include.cmake)

GET_ANDROID_MODULE(jsoncpp)

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/jsoncpp/src/lib_json)

add_definitions(-DJSON_DLL_BUILD)

file(GLOB JSONCPP_HEADER_FILES
${M3E_SOURCE_DIR}/${EXT_PATH}/jsoncpp/include/json/*.h
${M3E_SOURCE_DIR}/${EXT_PATH}/jsoncpp/src/lib_json/*.h
)

set(JSONCPP_SOURCE_FILES 
${M3E_SOURCE_DIR}/${EXT_PATH}/jsoncpp/src/lib_json/json_reader.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/jsoncpp/src/lib_json/json_value.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/jsoncpp/src/lib_json/json_writer.cpp
)

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(jsoncpp SHARED ${JSONCPP_SOURCE_FILES} ${JSONCPP_HEADER_FILES})
