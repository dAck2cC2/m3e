
project(FLAC)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/flac/include.cmake)

GET_ANDROID_MODULE(flac)

add_definitions(-DFLAC_API_EXPORTS)
add_definitions(-DHAVE_CONFIG_H)
add_definitions(-DFLAC__NO_MD5)
add_definitions(-DFLAC__INTEGER_ONLY_LIBRARY)
add_definitions(-D_REENTRANT)
#add_definitions(-DPIC)
add_definitions(-DU_COMMON_IMPLEMENTATIO)


set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/flac/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/flac/libFLAC )


include_directories(AFTER ${SOURCE_PATH}/../)
include_directories(AFTER ${SOURCE_PATH}/include/)

file(GLOB ${PROJECT_NAME}_HEADER_FILES
${HEADER_PATH}/FLAC/*.h
${HEADER_PATH}/share/*.h
${HEADER_PATH}/share/grabbag/*.h
${SOURCE_PATH}/include/private/*.h
${SOURCE_PATH}/include/protected/*.h
${SOURCE_PATH}/../*.h
)

set(${PROJECT_NAME}_SOURCE_FILES 
${SOURCE_PATH}/bitmath.c 
${SOURCE_PATH}/bitreader.c 
${SOURCE_PATH}/bitwriter.c 
${SOURCE_PATH}/cpu.c 
${SOURCE_PATH}/crc.c 
${SOURCE_PATH}/fixed.c 
${SOURCE_PATH}/float.c 
${SOURCE_PATH}/format.c 
${SOURCE_PATH}/lpc.c 
${SOURCE_PATH}/memory.c 
${SOURCE_PATH}/md5.c 
${SOURCE_PATH}/stream_decoder.c 
${SOURCE_PATH}/stream_encoder.c 
${SOURCE_PATH}/stream_encoder_framing.c 
${SOURCE_PATH}/window.c
)

if (MSVC)
    list(APPEND ${PROJECT_NAME}_SOURCE_FILES
    ${SOURCE_PATH}/windows_unicode_filenames.c
    )
endif()

set(LIB_TYPE SHARED)
ADD_LIB(FLAC)
