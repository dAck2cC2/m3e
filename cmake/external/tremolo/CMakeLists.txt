project(TREMOLO)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/tremolo/include.cmake)

GET_ANDROID_MODULE(tremolo)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)

set(${PROJECT_NAME}_DEPLIB
log
)

add_definitions(-DONLY_C=1)

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/tremolo/Tremolo)

set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/tremolo )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/tremolo/Tremolo )

file(GLOB ${PROJECT_NAME}_HEADER_FILES ${SOURCE_PATH}/*.h)

set(${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/bitwise.c 
${SOURCE_PATH}/codebook.c 
${SOURCE_PATH}/dsp.c 
${SOURCE_PATH}/floor0.c 
${SOURCE_PATH}/floor1.c 
${SOURCE_PATH}/floor_lookup.c 
${SOURCE_PATH}/framing.c 
${SOURCE_PATH}/mapping0.c 
${SOURCE_PATH}/mdct.c 
${SOURCE_PATH}/misc.c 
${SOURCE_PATH}/res012.c 
${SOURCE_PATH}/treminfo.c 
${SOURCE_PATH}/vorbisfile.c
)


#set(LIB_TYPE SHARED)
ADD_LIB(vorbisidec)
