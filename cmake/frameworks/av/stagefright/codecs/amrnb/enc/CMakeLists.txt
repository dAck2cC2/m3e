
project(STAGEFRIGHT_SOFT_AMRNBENC)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright/codecs/amrnb/common/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright_omx/include.cmake)

set(${PROJECT_NAME}_DEPLIB
stagefright_amrnb_common
stagefright_omx
)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/codecs/amrnb/enc/src )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/codecs/amrnb/enc )

include_directories(AFTER ${HEADER_PATH})
#include_directories(AFTER ${SOURCE_PATH}/src)

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES  
${HEADER_PATH}/*.h 
${SOURCE_PATH}/SoftAMRNBEncoder.h
)

set(${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/src/amrencode.cpp 
${SOURCE_PATH}/src/autocorr.cpp 
${SOURCE_PATH}/src/c1035pf.cpp 
${SOURCE_PATH}/src/c2_11pf.cpp 
${SOURCE_PATH}/src/c2_9pf.cpp 
${SOURCE_PATH}/src/c3_14pf.cpp 
${SOURCE_PATH}/src/c4_17pf.cpp 
${SOURCE_PATH}/src/c8_31pf.cpp 
${SOURCE_PATH}/src/calc_cor.cpp 
${SOURCE_PATH}/src/calc_en.cpp 
${SOURCE_PATH}/src/cbsearch.cpp 
${SOURCE_PATH}/src/cl_ltp.cpp 
${SOURCE_PATH}/src/cod_amr.cpp 
${SOURCE_PATH}/src/convolve.cpp 
${SOURCE_PATH}/src/cor_h.cpp 
${SOURCE_PATH}/src/cor_h_x.cpp 
${SOURCE_PATH}/src/cor_h_x2.cpp 
${SOURCE_PATH}/src/corrwght_tab.cpp 
${SOURCE_PATH}/src/dtx_enc.cpp 
${SOURCE_PATH}/src/enc_lag3.cpp 
${SOURCE_PATH}/src/enc_lag6.cpp 
${SOURCE_PATH}/src/enc_output_format_tab.cpp 
${SOURCE_PATH}/src/ets_to_if2.cpp 
${SOURCE_PATH}/src/ets_to_wmf.cpp 
${SOURCE_PATH}/src/g_adapt.cpp 
${SOURCE_PATH}/src/g_code.cpp 
${SOURCE_PATH}/src/g_pitch.cpp 
${SOURCE_PATH}/src/gain_q.cpp 
${SOURCE_PATH}/src/hp_max.cpp 
${SOURCE_PATH}/src/inter_36.cpp 
${SOURCE_PATH}/src/inter_36_tab.cpp 
${SOURCE_PATH}/src/l_comp.cpp 
${SOURCE_PATH}/src/l_extract.cpp 
${SOURCE_PATH}/src/l_negate.cpp 
${SOURCE_PATH}/src/lag_wind.cpp 
${SOURCE_PATH}/src/lag_wind_tab.cpp 
${SOURCE_PATH}/src/levinson.cpp 
${SOURCE_PATH}/src/lpc.cpp 
${SOURCE_PATH}/src/ol_ltp.cpp 
${SOURCE_PATH}/src/p_ol_wgh.cpp 
${SOURCE_PATH}/src/pitch_fr.cpp 
${SOURCE_PATH}/src/pitch_ol.cpp 
${SOURCE_PATH}/src/pre_big.cpp 
${SOURCE_PATH}/src/pre_proc.cpp 
${SOURCE_PATH}/src/prm2bits.cpp 
${SOURCE_PATH}/src/q_gain_c.cpp 
${SOURCE_PATH}/src/q_gain_p.cpp 
${SOURCE_PATH}/src/qgain475.cpp 
${SOURCE_PATH}/src/qgain795.cpp 
${SOURCE_PATH}/src/qua_gain.cpp 
${SOURCE_PATH}/src/s10_8pf.cpp 
${SOURCE_PATH}/src/set_sign.cpp 
${SOURCE_PATH}/src/sid_sync.cpp 
${SOURCE_PATH}/src/sp_enc.cpp 
${SOURCE_PATH}/src/spreproc.cpp 
${SOURCE_PATH}/src/spstproc.cpp 
${SOURCE_PATH}/src/ton_stab.cpp
${SOURCE_PATH}/SoftAMRNBEncoder.cpp
)

# target files
set(LIB_NAME stagefright_soft_amrnbenc)
set(LIB_TYPE SHARED)
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${LIB_NAME} ${LIB_TYPE} ${${PROJECT_NAME}_SOURCE_FILES} ${${PROJECT_NAME}_HEADER_FILES})
target_link_libraries(${LIB_NAME} ${${PROJECT_NAME}_DEPLIB})
