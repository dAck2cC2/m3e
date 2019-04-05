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
${SOURCE_PATH}/dsp/alpha_processing_neon.c
${SOURCE_PATH}/dsp/alpha_processing_sse2.c
${SOURCE_PATH}/dsp/alpha_processing_sse41.c
${SOURCE_PATH}/dsp/argb.c
${SOURCE_PATH}/dsp/argb_mips_dsp_r2.c
${SOURCE_PATH}/dsp/argb_sse2.c
${SOURCE_PATH}/dsp/cost.c
${SOURCE_PATH}/dsp/cost_mips32.c
${SOURCE_PATH}/dsp/cost_mips_dsp_r2.c
${SOURCE_PATH}/dsp/cost_sse2.c
${SOURCE_PATH}/dsp/cpu.c
${SOURCE_PATH}/dsp/enc.c
${SOURCE_PATH}/dsp/enc_avx2.c
${SOURCE_PATH}/dsp/enc_mips32.c
${SOURCE_PATH}/dsp/enc_mips_dsp_r2.c
${SOURCE_PATH}/dsp/enc_msa.c
${SOURCE_PATH}/dsp/enc_neon.c
${SOURCE_PATH}/dsp/enc_sse2.c
${SOURCE_PATH}/dsp/enc_sse41.c
${SOURCE_PATH}/dsp/lossless_enc.c
${SOURCE_PATH}/dsp/lossless_enc_mips32.c
${SOURCE_PATH}/dsp/lossless_enc_mips_dsp_r2.c
${SOURCE_PATH}/dsp/lossless_enc_msa.c
${SOURCE_PATH}/dsp/lossless_enc_neon.c
${SOURCE_PATH}/dsp/lossless_enc_sse2.c
${SOURCE_PATH}/dsp/lossless_enc_sse41.c
${SOURCE_PATH}/enc/alpha_enc.c
${SOURCE_PATH}/enc/analysis_enc.c
${SOURCE_PATH}/enc/backward_references_enc.c
${SOURCE_PATH}/enc/config_enc.c
${SOURCE_PATH}/enc/cost_enc.c
${SOURCE_PATH}/enc/delta_palettization_enc.c
${SOURCE_PATH}/enc/filter_enc.c
${SOURCE_PATH}/enc/frame_enc.c
${SOURCE_PATH}/enc/histogram_enc.c
${SOURCE_PATH}/enc/iterator_enc.c
${SOURCE_PATH}/enc/near_lossless_enc.c
${SOURCE_PATH}/enc/picture_csp_enc.c
${SOURCE_PATH}/enc/picture_enc.c
${SOURCE_PATH}/enc/picture_psnr_enc.c
${SOURCE_PATH}/enc/picture_rescale_enc.c
${SOURCE_PATH}/enc/picture_tools_enc.c
${SOURCE_PATH}/enc/predictor_enc.c
${SOURCE_PATH}/enc/quant_enc.c
${SOURCE_PATH}/enc/syntax_enc.c
${SOURCE_PATH}/enc/token_enc.c
${SOURCE_PATH}/enc/tree_enc.c
${SOURCE_PATH}/enc/vp8l_enc.c
${SOURCE_PATH}/enc/webp_enc.c
${SOURCE_PATH}/mux/anim_encode.c
${SOURCE_PATH}/mux/muxedit.c
${SOURCE_PATH}/mux/muxinternal.c
${SOURCE_PATH}/mux/muxread.c
${SOURCE_PATH}/utils/bit_reader_utils.c
${SOURCE_PATH}/utils/bit_writer_utils.c
${SOURCE_PATH}/utils/color_cache_utils.c
${SOURCE_PATH}/utils/filters_utils.c
${SOURCE_PATH}/utils/huffman_encode_utils.c
${SOURCE_PATH}/utils/huffman_utils.c
${SOURCE_PATH}/utils/quant_levels_utils.c
${SOURCE_PATH}/utils/random_utils.c
${SOURCE_PATH}/utils/rescaler_utils.c
${SOURCE_PATH}/utils/thread_utils.c
${SOURCE_PATH}/utils/utils.c
)

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${WEBP_ENC} STATIC ${WEBP_ENC_SRC})
