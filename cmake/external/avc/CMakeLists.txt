project(AVC)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
#include(${M3E_SOURCE_DIR}/cmake/external/avc/include.cmake)

GET_ANDROID_MODULE(libavc)

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)

set(${PROJECT_NAME}_DEPLIB
log
cutils
)

if (MSVC)
    add_definitions(-D__sync_synchronize=__nop)
    add_definitions(-Dasm=__noop)

    include(${M3E_SOURCE_DIR}/cmake/core/msvc/include.cmake)
    list(APPEND ${PROJECT_NAME}_DEPLIB ${LIB_MSVC_WRAP})
endif(MSVC)

set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/libavc )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/libavc )

add_definitions(-DX86)
add_definitions(-DDEFAULT_ARCH=D_ARCH_X86_SSE42)
include_directories(AFTER ${SOURCE_PATH}/common/x86)
include_directories(AFTER ${SOURCE_PATH}/decoder/x86)
include_directories(AFTER ${SOURCE_PATH}/encoder/x86)

###############################################################################
#  avc dec
###############################################################################

set(${PROJECT_NAME}_SOURCE_FILES )

include_directories(AFTER ${SOURCE_PATH}/common)
file(GLOB   AVCDEC_COMMON_SOURCES ${SOURCE_PATH}/common/*.h)
list(APPEND AVCDEC_COMMON_SOURCES
${SOURCE_PATH}/common/ih264_buf_mgr.c 
${SOURCE_PATH}/common/ih264_disp_mgr.c 
${SOURCE_PATH}/common/ih264_inter_pred_filters.c 
${SOURCE_PATH}/common/ih264_luma_intra_pred_filters.c 
${SOURCE_PATH}/common/ih264_chroma_intra_pred_filters.c 
${SOURCE_PATH}/common/ih264_padding.c 
${SOURCE_PATH}/common/ih264_mem_fns.c 
${SOURCE_PATH}/common/ih264_deblk_edge_filters.c 
${SOURCE_PATH}/common/ih264_iquant_itrans_recon.c 
${SOURCE_PATH}/common/ih264_ihadamard_scaling.c 
${SOURCE_PATH}/common/ih264_weighted_pred.c 
${SOURCE_PATH}/common/ithread.c 
)
source_group(common FILES ${AVCDEC_COMMON_SOURCES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${AVCDEC_COMMON_SOURCES})

include_directories(AFTER ${SOURCE_PATH}/decoder)
file(GLOB   AVCDEC_DECODER_SOURCES ${SOURCE_PATH}/decoder/*.h)
list(APPEND AVCDEC_DECODER_SOURCES
${SOURCE_PATH}/decoder/ih264d_cabac.c 
${SOURCE_PATH}/decoder/ih264d_parse_mb_header.c 
${SOURCE_PATH}/decoder/ih264d_parse_cabac.c 
${SOURCE_PATH}/decoder/ih264d_process_intra_mb.c 
${SOURCE_PATH}/decoder/ih264d_inter_pred.c 
${SOURCE_PATH}/decoder/ih264d_parse_bslice.c 
${SOURCE_PATH}/decoder/ih264d_parse_pslice.c 
${SOURCE_PATH}/decoder/ih264d_parse_islice.c 
${SOURCE_PATH}/decoder/ih264d_cabac_init_tables.c 
${SOURCE_PATH}/decoder/ih264d_bitstrm.c 
${SOURCE_PATH}/decoder/ih264d_compute_bs.c 
${SOURCE_PATH}/decoder/ih264d_deblocking.c 
${SOURCE_PATH}/decoder/ih264d_parse_headers.c 
${SOURCE_PATH}/decoder/ih264d_mb_utils.c 
${SOURCE_PATH}/decoder/ih264d_mvpred.c 
${SOURCE_PATH}/decoder/ih264d_utils.c 
${SOURCE_PATH}/decoder/ih264d_process_bslice.c 
${SOURCE_PATH}/decoder/ih264d_process_pslice.c 
${SOURCE_PATH}/decoder/ih264d_parse_slice.c 
${SOURCE_PATH}/decoder/ih264d_quant_scaling.c 
${SOURCE_PATH}/decoder/ih264d_parse_cavlc.c 
${SOURCE_PATH}/decoder/ih264d_dpb_mgr.c 
${SOURCE_PATH}/decoder/ih264d_nal.c 
${SOURCE_PATH}/decoder/ih264d_sei.c 
${SOURCE_PATH}/decoder/ih264d_tables.c 
${SOURCE_PATH}/decoder/ih264d_vui.c 
${SOURCE_PATH}/decoder/ih264d_format_conv.c 
${SOURCE_PATH}/decoder/ih264d_thread_parse_decode.c 
${SOURCE_PATH}/decoder/ih264d_api.c 
${SOURCE_PATH}/decoder/ih264d_thread_compute_bs.c 
${SOURCE_PATH}/decoder/ih264d_function_selector_generic.c 
)
source_group(decoder FILES ${AVCDEC_DECODER_SOURCES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${AVCDEC_DECODER_SOURCES})

file(GLOB   AVCDEC_X86_SOURCES ${SOURCE_PATH}/decoder/x86/*.h ${SOURCE_PATH}/common/x86/*.h)
list(APPEND AVCDEC_X86_SOURCES
${SOURCE_PATH}/decoder/x86/ih264d_function_selector.c 
${SOURCE_PATH}/decoder/x86/ih264d_function_selector_sse42.c 
${SOURCE_PATH}/decoder/x86/ih264d_function_selector_ssse3.c 
${SOURCE_PATH}/common/x86/ih264_inter_pred_filters_ssse3.c 
${SOURCE_PATH}/common/x86/ih264_deblk_luma_ssse3.c 
${SOURCE_PATH}/common/x86/ih264_deblk_chroma_ssse3.c 
${SOURCE_PATH}/common/x86/ih264_padding_ssse3.c 
${SOURCE_PATH}/common/x86/ih264_mem_fns_ssse3.c 
${SOURCE_PATH}/common/x86/ih264_iquant_itrans_recon_dc_ssse3.c 
${SOURCE_PATH}/common/x86/ih264_iquant_itrans_recon_ssse3.c 
${SOURCE_PATH}/common/x86/ih264_luma_intra_pred_filters_ssse3.c 
${SOURCE_PATH}/common/x86/ih264_chroma_intra_pred_filters_ssse3.c 
${SOURCE_PATH}/common/x86/ih264_iquant_itrans_recon_sse42.c 
${SOURCE_PATH}/common/x86/ih264_weighted_pred_sse42.c 
${SOURCE_PATH}/common/x86/ih264_ihadamard_scaling_sse42.c 
)
source_group(x86 FILES ${AVCDEC_X86_SOURCES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${AVCDEC_X86_SOURCES})

ADD_LIB(avcdec)

###############################################################################
#  avc enc
###############################################################################

set(${PROJECT_NAME}_SOURCE_FILES )

include_directories(AFTER ${SOURCE_PATH}/common)
file(GLOB   AVCENC_COMMON_SOURCES ${SOURCE_PATH}/common/*.h)
list(APPEND AVCENC_COMMON_SOURCES
${SOURCE_PATH}/common/ih264_resi_trans_quant.c 
${SOURCE_PATH}/common/ih264_iquant_itrans_recon.c 
${SOURCE_PATH}/common/ih264_ihadamard_scaling.c 
${SOURCE_PATH}/common/ih264_inter_pred_filters.c 
${SOURCE_PATH}/common/ih264_luma_intra_pred_filters.c 
${SOURCE_PATH}/common/ih264_chroma_intra_pred_filters.c 
${SOURCE_PATH}/common/ih264_padding.c 
${SOURCE_PATH}/common/ih264_mem_fns.c 
${SOURCE_PATH}/common/ih264_deblk_edge_filters.c 
${SOURCE_PATH}/common/ih264_deblk_tables.c 
${SOURCE_PATH}/common/ih264_cavlc_tables.c 
${SOURCE_PATH}/common/ih264_cabac_tables.c 
${SOURCE_PATH}/common/ih264_common_tables.c 
${SOURCE_PATH}/common/ih264_trans_data.c 
${SOURCE_PATH}/common/ih264_buf_mgr.c 
${SOURCE_PATH}/common/ih264_dpb_mgr.c 
${SOURCE_PATH}/common/ih264_list.c 
${SOURCE_PATH}/common/ithread.c  
)
source_group(common FILES ${AVCENC_COMMON_SOURCES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${AVCENC_COMMON_SOURCES})

include_directories(AFTER ${SOURCE_PATH}/encoder)
file(GLOB   AVCENC_ENCODER_SOURCES ${SOURCE_PATH}/encoder/*.h)
list(APPEND AVCENC_ENCODER_SOURCES
${SOURCE_PATH}/encoder/ih264e_globals.c 
${SOURCE_PATH}/encoder/ih264e_intra_modes_eval.c 
${SOURCE_PATH}/encoder/ih264e_half_pel.c 
${SOURCE_PATH}/encoder/ih264e_mc.c 
${SOURCE_PATH}/encoder/ih264e_me.c 
${SOURCE_PATH}/encoder/ih264e_rc_mem_interface.c 
${SOURCE_PATH}/encoder/ih264e_time_stamp.c 
${SOURCE_PATH}/encoder/ih264e_modify_frm_rate.c 
${SOURCE_PATH}/encoder/ih264e_rate_control.c 
${SOURCE_PATH}/encoder/ih264e_core_coding.c 
${SOURCE_PATH}/encoder/ih264e_deblk.c 
${SOURCE_PATH}/encoder/ih264e_api.c 
${SOURCE_PATH}/encoder/ih264e_process.c 
${SOURCE_PATH}/encoder/ih264e_encode.c 
${SOURCE_PATH}/encoder/ih264e_utils.c 
${SOURCE_PATH}/encoder/ih264e_version.c 
${SOURCE_PATH}/encoder/ih264e_bitstream.c 
${SOURCE_PATH}/encoder/ih264e_cavlc.c 
${SOURCE_PATH}/encoder/ih264e_cabac_init.c 
${SOURCE_PATH}/encoder/ih264e_cabac.c 
${SOURCE_PATH}/encoder/ih264e_cabac_encode.c 
${SOURCE_PATH}/encoder/ih264e_encode_header.c 
${SOURCE_PATH}/encoder/ih264e_function_selector_generic.c 
${SOURCE_PATH}/encoder/ih264e_fmt_conv.c 
${SOURCE_PATH}/encoder/irc_rate_control_api.c 
${SOURCE_PATH}/encoder/irc_bit_allocation.c 
${SOURCE_PATH}/encoder/irc_cbr_buffer_control.c 
${SOURCE_PATH}/encoder/irc_est_sad.c 
${SOURCE_PATH}/encoder/irc_fixed_point_error_bits.c 
${SOURCE_PATH}/encoder/irc_frame_info_collector.c 
${SOURCE_PATH}/encoder/irc_mb_model_based.c 
${SOURCE_PATH}/encoder/irc_picture_type.c 
${SOURCE_PATH}/encoder/irc_rd_model.c 
${SOURCE_PATH}/encoder/irc_vbr_storage_vbv.c 
${SOURCE_PATH}/encoder/irc_vbr_str_prms.c 
${SOURCE_PATH}/encoder/ime.c 
${SOURCE_PATH}/encoder/ime_distortion_metrics.c 
)
source_group(encoder FILES ${AVCENC_ENCODER_SOURCES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${AVCENC_ENCODER_SOURCES})

file(GLOB   AVCENC_X86_SOURCES ${SOURCE_PATH}/encoder/x86/*.h ${SOURCE_PATH}/common/x86/*.h)
list(APPEND AVCENC_X86_SOURCES
${SOURCE_PATH}/encoder/x86/ih264e_function_selector.c
${SOURCE_PATH}/encoder/x86/ih264e_function_selector_sse42.c
${SOURCE_PATH}/encoder/x86/ih264e_function_selector_ssse3.c
${SOURCE_PATH}/common/x86/ih264_iquant_itrans_recon_ssse3.c
${SOURCE_PATH}/common/x86/ih264_iquant_itrans_recon_dc_ssse3.c
${SOURCE_PATH}/common/x86/ih264_ihadamard_scaling_ssse3.c
${SOURCE_PATH}/common/x86/ih264_inter_pred_filters_ssse3.c
${SOURCE_PATH}/common/x86/ih264_mem_fns_ssse3.c
${SOURCE_PATH}/common/x86/ih264_padding_ssse3.c
${SOURCE_PATH}/common/x86/ih264_luma_intra_pred_filters_ssse3.c
${SOURCE_PATH}/common/x86/ih264_chroma_intra_pred_filters_ssse3.c
${SOURCE_PATH}/common/x86/ih264_deblk_chroma_ssse3.c
${SOURCE_PATH}/common/x86/ih264_deblk_luma_ssse3.c
${SOURCE_PATH}/common/x86/ih264_iquant_itrans_recon_sse42.c
${SOURCE_PATH}/common/x86/ih264_ihadamard_scaling_sse42.c
${SOURCE_PATH}/common/x86/ih264_resi_trans_quant_sse42.c
${SOURCE_PATH}/common/x86/ih264_weighted_pred_sse42.c
${SOURCE_PATH}/encoder/x86/ih264e_half_pel_ssse3.c
${SOURCE_PATH}/encoder/x86/ih264e_intra_modes_eval_ssse3.c
${SOURCE_PATH}/encoder/x86/ime_distortion_metrics_sse42.c
)
source_group(x86 FILES ${AVCENC_X86_SOURCES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${AVCENC_X86_SOURCES})

ADD_LIB(avcenc)
