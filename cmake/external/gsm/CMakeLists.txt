project(GSM)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/gsm/include.cmake)

GET_ANDROID_MODULE(libgsm)

add_definitions(-DSASR)
add_definitions(-DWAV49)


set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/libgsm/inc )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/libgsm/src )

include_directories(AFTER ${HEADER_PATH})

file(GLOB ${PROJECT_NAME}_HEADER_FILES
${HEADER_PATH}/*.h
)

set(${PROJECT_NAME}_SOURCE_FILES 
${SOURCE_PATH}/add.c 
${SOURCE_PATH}/code.c 
${SOURCE_PATH}/decode.c 
${SOURCE_PATH}/gsm_create.c 
${SOURCE_PATH}/gsm_decode.c 
${SOURCE_PATH}/gsm_destroy.c 
${SOURCE_PATH}/gsm_encode.c 
${SOURCE_PATH}/gsm_option.c 
${SOURCE_PATH}/long_term.c 
${SOURCE_PATH}/lpc.c 
${SOURCE_PATH}/preprocess.c 
${SOURCE_PATH}/rpe.c 
${SOURCE_PATH}/short_term.c 
${SOURCE_PATH}/table.c
)

set(LIB_TYPE STATIC)
set(LIB_NAME gsm)
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${LIB_NAME} ${LIB_TYPE} ${${PROJECT_NAME}_HEADER_FILES} ${${PROJECT_NAME}_SOURCE_FILES})
target_link_libraries(${LIB_NAME} ${${PROJECT_NAME}_DEPLIB})
