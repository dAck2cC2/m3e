
project(STAGEFRIGHT_SOFT_AMRNBDEC)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright/codecs/amrnb/common/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright/codecs/amrwb/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright_omx/include.cmake)

set(${PROJECT_NAME}_DEPLIB
stagefright_amrnb_common
stagefright_amrwbdec
stagefright_omx
)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/codecs/amrnb/dec/src )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/codecs/amrnb/dec )

include_directories(AFTER ${HEADER_PATH})

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES  
${HEADER_PATH}/*.h 
${SOURCE_PATH}/SoftAMR.h
)

set(${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/src/a_refl.cpp 
${SOURCE_PATH}/src/agc.cpp 
${SOURCE_PATH}/src/amrdecode.cpp 
${SOURCE_PATH}/src/b_cn_cod.cpp 
${SOURCE_PATH}/src/bgnscd.cpp 
${SOURCE_PATH}/src/c_g_aver.cpp 
${SOURCE_PATH}/src/d1035pf.cpp 
${SOURCE_PATH}/src/d2_11pf.cpp 
${SOURCE_PATH}/src/d2_9pf.cpp 
${SOURCE_PATH}/src/d3_14pf.cpp 
${SOURCE_PATH}/src/d4_17pf.cpp 
${SOURCE_PATH}/src/d8_31pf.cpp 
${SOURCE_PATH}/src/d_gain_c.cpp 
${SOURCE_PATH}/src/d_gain_p.cpp 
${SOURCE_PATH}/src/d_plsf.cpp 
${SOURCE_PATH}/src/d_plsf_3.cpp 
${SOURCE_PATH}/src/d_plsf_5.cpp 
${SOURCE_PATH}/src/dec_amr.cpp 
${SOURCE_PATH}/src/dec_gain.cpp 
${SOURCE_PATH}/src/dec_input_format_tab.cpp 
${SOURCE_PATH}/src/dec_lag3.cpp 
${SOURCE_PATH}/src/dec_lag6.cpp 
${SOURCE_PATH}/src/dtx_dec.cpp 
${SOURCE_PATH}/src/ec_gains.cpp 
${SOURCE_PATH}/src/ex_ctrl.cpp 
${SOURCE_PATH}/src/if2_to_ets.cpp 
${SOURCE_PATH}/src/int_lsf.cpp 
${SOURCE_PATH}/src/lsp_avg.cpp 
${SOURCE_PATH}/src/ph_disp.cpp 
${SOURCE_PATH}/src/post_pro.cpp 
${SOURCE_PATH}/src/preemph.cpp 
${SOURCE_PATH}/src/pstfilt.cpp 
${SOURCE_PATH}/src/qgain475_tab.cpp 
${SOURCE_PATH}/src/sp_dec.cpp 
${SOURCE_PATH}/src/wmf_to_ets.cpp
${SOURCE_PATH}/SoftAMR.cpp
)

# target files
set(LIB_NAME stagefright_soft_amrdec)
set(LIB_TYPE SHARED)
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${LIB_NAME} ${LIB_TYPE} ${${PROJECT_NAME}_SOURCE_FILES} ${${PROJECT_NAME}_HEADER_FILES})
target_link_libraries(${LIB_NAME} ${${PROJECT_NAME}_DEPLIB})
