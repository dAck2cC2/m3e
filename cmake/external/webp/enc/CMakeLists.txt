# webp
project(WEBP_ENC)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/webp/include.cmake)

set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/webp/src/enc )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/webp/src )

include_directories(AFTER ${HEADER_PATH})

set(WEBP_ENC_SRC
${SOURCE_PATH}/dsp/alpha_processing.c 
${SOURCE_PATH}/dsp/alpha_processing_mips_dsp_r2.c 
${SOURCE_PATH}/dsp/alpha_processing_sse2.c 
${SOURCE_PATH}/dsp/alpha_processing_sse41.c 
${SOURCE_PATH}/dsp/argb.c 
${SOURCE_PATH}/dsp/argb_mips_dsp_r2.c 
${SOURCE_PATH}/dsp/argb_sse2.c 
${SOURCE_PATH}/dsp/cost.c 
${SOURCE_PATH}/dsp/cost_mips32.c 
${SOURCE_PATH}/dsp/cost_mips_dsp_r2.c 
${SOURCE_PATH}/dsp/cost_sse2.c 
#${SOURCE_PATH}/dsp/cpu-features.c 
${SOURCE_PATH}/dsp/cpu.c 
${SOURCE_PATH}/dsp/enc.c 
${SOURCE_PATH}/dsp/enc_avx2.c 
${SOURCE_PATH}/dsp/enc_mips32.c 
${SOURCE_PATH}/dsp/enc_mips_dsp_r2.c 
${SOURCE_PATH}/dsp/enc_neon.c 
${SOURCE_PATH}/dsp/enc_sse2.c 
${SOURCE_PATH}/dsp/enc_sse41.c 
${SOURCE_PATH}/dsp/lossless_enc.c 
${SOURCE_PATH}/dsp/lossless_enc_mips32.c 
${SOURCE_PATH}/dsp/lossless_enc_mips_dsp_r2.c 
${SOURCE_PATH}/dsp/lossless_enc_neon.c 
${SOURCE_PATH}/dsp/lossless_enc_sse2.c 
${SOURCE_PATH}/dsp/lossless_enc_sse41.c 
${SOURCE_PATH}/enc/alpha.c 
${SOURCE_PATH}/enc/analysis.c 
${SOURCE_PATH}/enc/backward_references.c 
${SOURCE_PATH}/enc/config.c 
${SOURCE_PATH}/enc/cost.c 
${SOURCE_PATH}/enc/delta_palettization.c 
${SOURCE_PATH}/enc/filter.c 
${SOURCE_PATH}/enc/frame.c 
${SOURCE_PATH}/enc/histogram.c 
${SOURCE_PATH}/enc/iterator.c 
${SOURCE_PATH}/enc/near_lossless.c 
${SOURCE_PATH}/enc/picture.c 
${SOURCE_PATH}/enc/picture_csp.c 
${SOURCE_PATH}/enc/picture_psnr.c 
${SOURCE_PATH}/enc/picture_rescale.c 
${SOURCE_PATH}/enc/picture_tools.c 
${SOURCE_PATH}/enc/quant.c 
${SOURCE_PATH}/enc/syntax.c 
${SOURCE_PATH}/enc/token.c 
${SOURCE_PATH}/enc/tree.c 
${SOURCE_PATH}/enc/vp8l.c 
${SOURCE_PATH}/enc/webpenc.c 
${SOURCE_PATH}/utils/bit_reader.c 
${SOURCE_PATH}/utils/bit_writer.c 
${SOURCE_PATH}/utils/color_cache.c 
${SOURCE_PATH}/utils/filters.c 
${SOURCE_PATH}/utils/huffman.c 
${SOURCE_PATH}/utils/huffman_encode.c 
${SOURCE_PATH}/utils/quant_levels.c 
${SOURCE_PATH}/utils/random.c 
${SOURCE_PATH}/utils/rescaler.c 
${SOURCE_PATH}/utils/thread.c 
${SOURCE_PATH}/utils/utils.c
)

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${WEBP_ENC} STATIC ${WEBP_ENC_SRC})
