
project(STAGEFRIGHT_SOFT_MP3DEC)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/frameworks/native/ui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/gui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright_foundation/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright_omx/include.cmake)

set(${PROJECT_NAME}_DEPLIB
log 
utils 
stagefright_foundation
stagefright
stagefright_omx
)

add_definitions(-DOSCL_UNUSED_ARG=\(void\) )

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/codecs/mp3dec/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/codecs/mp3dec )

include_directories(AFTER ${HEADER_PATH})
include_directories(AFTER ${SOURCE_PATH}/src)

file(GLOB ${PROJECT_NAME}_HEADER_FILES
${HEADER_PATH}/*.h
${SOURCE_PATH}/src/*.h
)

set(${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/src/pvmp3_normalize.cpp 
${SOURCE_PATH}/src/pvmp3_alias_reduction.cpp 
${SOURCE_PATH}/src/pvmp3_crc.cpp 
${SOURCE_PATH}/src/pvmp3_decode_header.cpp 
${SOURCE_PATH}/src/pvmp3_decode_huff_cw.cpp 
${SOURCE_PATH}/src/pvmp3_getbits.cpp 
${SOURCE_PATH}/src/pvmp3_dequantize_sample.cpp 
${SOURCE_PATH}/src/pvmp3_framedecoder.cpp 
${SOURCE_PATH}/src/pvmp3_get_main_data_size.cpp 
${SOURCE_PATH}/src/pvmp3_get_side_info.cpp 
${SOURCE_PATH}/src/pvmp3_get_scale_factors.cpp 
${SOURCE_PATH}/src/pvmp3_mpeg2_get_scale_data.cpp 
${SOURCE_PATH}/src/pvmp3_mpeg2_get_scale_factors.cpp 
${SOURCE_PATH}/src/pvmp3_mpeg2_stereo_proc.cpp 
${SOURCE_PATH}/src/pvmp3_huffman_decoding.cpp 
${SOURCE_PATH}/src/pvmp3_huffman_parsing.cpp 
${SOURCE_PATH}/src/pvmp3_tables.cpp 
${SOURCE_PATH}/src/pvmp3_imdct_synth.cpp 
${SOURCE_PATH}/src/pvmp3_mdct_6.cpp 
${SOURCE_PATH}/src/pvmp3_dct_6.cpp 
${SOURCE_PATH}/src/pvmp3_poly_phase_synthesis.cpp 
${SOURCE_PATH}/src/pvmp3_equalizer.cpp 
${SOURCE_PATH}/src/pvmp3_seek_synch.cpp 
${SOURCE_PATH}/src/pvmp3_stereo_proc.cpp 
${SOURCE_PATH}/src/pvmp3_reorder.cpp 
${SOURCE_PATH}/src/pvmp3_polyphase_filter_window.cpp 
${SOURCE_PATH}/src/pvmp3_mdct_18.cpp 
${SOURCE_PATH}/src/pvmp3_dct_9.cpp 
${SOURCE_PATH}/src/pvmp3_dct_16.cpp
${SOURCE_PATH}/SoftMP3.cpp
)

# target files
set(LIB_NAME stagefright_soft_mp3dec)
set(LIB_TYPE SHARED)
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${LIB_NAME} ${LIB_TYPE} ${${PROJECT_NAME}_SOURCE_FILES} ${${PROJECT_NAME}_HEADER_FILES})
target_link_libraries(${LIB_NAME} ${${PROJECT_NAME}_DEPLIB})
