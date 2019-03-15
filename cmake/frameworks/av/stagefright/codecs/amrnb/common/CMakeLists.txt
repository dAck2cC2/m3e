
project(STAGEFRIGHT_AMRNB_COMMON)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright/codecs/amrnb/common/include.cmake)

set(${PROJECT_NAME}_DEPLIB
)

if(APPLE)
    add_definitions(-Dregister= )
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/codecs/amrnb/common/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/codecs/amrnb/common/src )

include_directories(AFTER ${HEADER_PATH})

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES  
${HEADER_PATH}/*.h 
)

set(${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/add.cpp 
${SOURCE_PATH}/az_lsp.cpp 
${SOURCE_PATH}/bitno_tab.cpp 
${SOURCE_PATH}/bitreorder_tab.cpp 
${SOURCE_PATH}/bits2prm.cpp 
${SOURCE_PATH}/c2_9pf_tab.cpp 
${SOURCE_PATH}/copy.cpp 
${SOURCE_PATH}/div_32.cpp 
${SOURCE_PATH}/div_s.cpp 
${SOURCE_PATH}/extract_h.cpp 
${SOURCE_PATH}/extract_l.cpp 
${SOURCE_PATH}/gains_tbl.cpp 
${SOURCE_PATH}/gc_pred.cpp 
${SOURCE_PATH}/gmed_n.cpp 
${SOURCE_PATH}/grid_tbl.cpp 
${SOURCE_PATH}/gray_tbl.cpp 
${SOURCE_PATH}/int_lpc.cpp 
${SOURCE_PATH}/inv_sqrt.cpp 
${SOURCE_PATH}/inv_sqrt_tbl.cpp 
${SOURCE_PATH}/l_abs.cpp 
${SOURCE_PATH}/l_deposit_h.cpp 
${SOURCE_PATH}/l_deposit_l.cpp 
${SOURCE_PATH}/l_shr_r.cpp 
${SOURCE_PATH}/log2.cpp 
${SOURCE_PATH}/log2_norm.cpp 
${SOURCE_PATH}/log2_tbl.cpp 
${SOURCE_PATH}/lsfwt.cpp 
${SOURCE_PATH}/lsp.cpp 
${SOURCE_PATH}/lsp_az.cpp 
${SOURCE_PATH}/lsp_lsf.cpp 
${SOURCE_PATH}/lsp_lsf_tbl.cpp 
${SOURCE_PATH}/lsp_tab.cpp 
${SOURCE_PATH}/mult_r.cpp 
${SOURCE_PATH}/norm_l.cpp 
${SOURCE_PATH}/norm_s.cpp 
${SOURCE_PATH}/ph_disp_tab.cpp 
${SOURCE_PATH}/pow2.cpp 
${SOURCE_PATH}/pow2_tbl.cpp 
${SOURCE_PATH}/pred_lt.cpp 
${SOURCE_PATH}/q_plsf.cpp 
${SOURCE_PATH}/q_plsf_3.cpp 
${SOURCE_PATH}/q_plsf_3_tbl.cpp 
${SOURCE_PATH}/q_plsf_5.cpp 
${SOURCE_PATH}/q_plsf_5_tbl.cpp 
${SOURCE_PATH}/qua_gain_tbl.cpp 
${SOURCE_PATH}/reorder.cpp 
${SOURCE_PATH}/residu.cpp 
${SOURCE_PATH}/round.cpp 
${SOURCE_PATH}/set_zero.cpp 
${SOURCE_PATH}/shr.cpp 
${SOURCE_PATH}/shr_r.cpp 
${SOURCE_PATH}/sqrt_l.cpp 
${SOURCE_PATH}/sqrt_l_tbl.cpp 
${SOURCE_PATH}/sub.cpp 
${SOURCE_PATH}/syn_filt.cpp 
${SOURCE_PATH}/vad1.cpp 
${SOURCE_PATH}/weight_a.cpp 
${SOURCE_PATH}/window_tab.cpp
)

# target files
set(LIB_NAME stagefright_amrnb_common)
#set(LIB_TYPE SHARED)
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${LIB_NAME} ${LIB_TYPE} ${${PROJECT_NAME}_SOURCE_FILES} ${${PROJECT_NAME}_HEADER_FILES})
target_link_libraries(${LIB_NAME} ${${PROJECT_NAME}_DEPLIB})
