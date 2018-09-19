
project(STAGEFRIGHT_AMRWBDEC)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright/codecs/amrwb/include.cmake)

set(${PROJECT_NAME}_DEPLIB
)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/codecs/amrwb/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/codecs/amrwb/src )

#include_directories(AFTER ${HEADER_PATH})

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES  
${HEADER_PATH}/*.h 
)

set(${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/agc2_amr_wb.cpp 
${SOURCE_PATH}/band_pass_6k_7k.cpp 
${SOURCE_PATH}/dec_acelp_2p_in_64.cpp 
${SOURCE_PATH}/dec_acelp_4p_in_64.cpp 
${SOURCE_PATH}/dec_alg_codebook.cpp 
${SOURCE_PATH}/dec_gain2_amr_wb.cpp 
${SOURCE_PATH}/deemphasis_32.cpp 
${SOURCE_PATH}/dtx_decoder_amr_wb.cpp 
${SOURCE_PATH}/get_amr_wb_bits.cpp 
${SOURCE_PATH}/highpass_400hz_at_12k8.cpp 
${SOURCE_PATH}/highpass_50hz_at_12k8.cpp 
${SOURCE_PATH}/homing_amr_wb_dec.cpp 
${SOURCE_PATH}/interpolate_isp.cpp 
${SOURCE_PATH}/isf_extrapolation.cpp 
${SOURCE_PATH}/isp_az.cpp 
${SOURCE_PATH}/isp_isf.cpp 
${SOURCE_PATH}/lagconceal.cpp 
${SOURCE_PATH}/low_pass_filt_7k.cpp 
${SOURCE_PATH}/median5.cpp 
${SOURCE_PATH}/mime_io.cpp 
${SOURCE_PATH}/noise_gen_amrwb.cpp 
${SOURCE_PATH}/normalize_amr_wb.cpp 
${SOURCE_PATH}/oversamp_12k8_to_16k.cpp 
${SOURCE_PATH}/phase_dispersion.cpp 
${SOURCE_PATH}/pit_shrp.cpp 
${SOURCE_PATH}/pred_lt4.cpp 
${SOURCE_PATH}/preemph_amrwb_dec.cpp 
${SOURCE_PATH}/pvamrwb_math_op.cpp 
${SOURCE_PATH}/pvamrwbdecoder.cpp 
${SOURCE_PATH}/q_gain2_tab.cpp 
${SOURCE_PATH}/qisf_ns.cpp 
${SOURCE_PATH}/qisf_ns_tab.cpp 
${SOURCE_PATH}/qpisf_2s.cpp 
${SOURCE_PATH}/qpisf_2s_tab.cpp 
${SOURCE_PATH}/scale_signal.cpp 
${SOURCE_PATH}/synthesis_amr_wb.cpp 
${SOURCE_PATH}/voice_factor.cpp 
${SOURCE_PATH}/wb_syn_filt.cpp 
${SOURCE_PATH}/weight_amrwb_lpc.cpp
)

# target files
set(LIB_NAME stagefright_amrwbdec)
#set(LIB_TYPE SHARED)
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${LIB_NAME} ${LIB_TYPE} ${${PROJECT_NAME}_SOURCE_FILES} ${${PROJECT_NAME}_HEADER_FILES})
target_link_libraries(${LIB_NAME} ${${PROJECT_NAME}_DEPLIB})
