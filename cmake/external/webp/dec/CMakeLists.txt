# webp
project(WEBP_DEC)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/webp/include.cmake)

set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/webp/src/dec )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/webp/src )

include_directories(AFTER ${HEADER_PATH})

set(WEBP_DEC_SRC
${SOURCE_PATH}/dec/alpha_dec.c 
${SOURCE_PATH}/dec/buffer_dec.c 
${SOURCE_PATH}/dec/frame_dec.c 
${SOURCE_PATH}/dec/idec_dec.c 
${SOURCE_PATH}/dec/io_dec.c 
${SOURCE_PATH}/dec/quant_dec.c 
${SOURCE_PATH}/dec/tree_dec.c 
${SOURCE_PATH}/dec/vp8_dec.c 
${SOURCE_PATH}/dec/vp8l_dec.c 
${SOURCE_PATH}/dec/webp_dec.c 
${SOURCE_PATH}/demux/demux.c 
${SOURCE_PATH}/dsp/alpha_processing.c 
${SOURCE_PATH}/dsp/alpha_processing_mips_dsp_r2.c 
${SOURCE_PATH}/dsp/alpha_processing_sse2.c 
${SOURCE_PATH}/dsp/alpha_processing_sse41.c 
${SOURCE_PATH}/dsp/cpu.c 
${SOURCE_PATH}/dsp/dec.c 
${SOURCE_PATH}/dsp/dec_clip_tables.c 
${SOURCE_PATH}/dsp/dec_mips32.c 
${SOURCE_PATH}/dsp/dec_mips_dsp_r2.c 
${SOURCE_PATH}/dsp/dec_msa.c 
${SOURCE_PATH}/dsp/dec_neon.c 
${SOURCE_PATH}/dsp/dec_sse2.c 
${SOURCE_PATH}/dsp/dec_sse41.c 
${SOURCE_PATH}/dsp/filters.c 
${SOURCE_PATH}/dsp/filters_mips_dsp_r2.c 
${SOURCE_PATH}/dsp/filters_msa.c 
${SOURCE_PATH}/dsp/filters_neon.c 
${SOURCE_PATH}/dsp/filters_sse2.c 
${SOURCE_PATH}/dsp/lossless.c 
${SOURCE_PATH}/dsp/lossless_mips_dsp_r2.c 
${SOURCE_PATH}/dsp/lossless_msa.c 
${SOURCE_PATH}/dsp/lossless_neon.c 
${SOURCE_PATH}/dsp/lossless_sse2.c 
${SOURCE_PATH}/dsp/rescaler.c 
${SOURCE_PATH}/dsp/rescaler_mips32.c 
${SOURCE_PATH}/dsp/rescaler_mips_dsp_r2.c 
${SOURCE_PATH}/dsp/rescaler_msa.c 
${SOURCE_PATH}/dsp/rescaler_neon.c 
${SOURCE_PATH}/dsp/rescaler_sse2.c 
${SOURCE_PATH}/dsp/upsampling.c 
${SOURCE_PATH}/dsp/upsampling_mips_dsp_r2.c 
${SOURCE_PATH}/dsp/upsampling_msa.c 
${SOURCE_PATH}/dsp/upsampling_neon.c 
${SOURCE_PATH}/dsp/upsampling_sse2.c 
${SOURCE_PATH}/dsp/yuv.c 
${SOURCE_PATH}/dsp/yuv_mips32.c 
${SOURCE_PATH}/dsp/yuv_mips_dsp_r2.c 
${SOURCE_PATH}/dsp/yuv_sse2.c 
${SOURCE_PATH}/utils/bit_reader_utils.c 
${SOURCE_PATH}/utils/color_cache_utils.c 
${SOURCE_PATH}/utils/filters_utils.c 
${SOURCE_PATH}/utils/huffman_utils.c 
${SOURCE_PATH}/utils/quant_levels_dec_utils.c 
${SOURCE_PATH}/utils/random_utils.c 
${SOURCE_PATH}/utils/rescaler_utils.c 
${SOURCE_PATH}/utils/thread_utils.c 
${SOURCE_PATH}/utils/utils.c 
)

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${WEBP_DEC} STATIC ${WEBP_DEC_SRC})
