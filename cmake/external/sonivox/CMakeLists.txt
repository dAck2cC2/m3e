
project(SONIVOX)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
#include(${M3E_SOURCE_DIR}/cmake/external/sonivox/include.cmake)

GET_ANDROID_MODULE(sonivox)

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/include.cmake)

set(SONIC_DEPLIB
log
)

#add_definitions(-D_lint)

add_definitions(-DUNIFIED_DEBUG_MESSAGES)
add_definitions(-DEAS_WT_SYNTH)
add_definitions(-D_IMELODY_PARSER)
add_definitions(-D_RTTTL_PARSER)
add_definitions(-D_OTA_PARSER)
add_definitions(-D_XMF_PARSER )
add_definitions(-DNUM_OUTPUT_CHANNELS=2 )
add_definitions(-D_SAMPLE_RATE_22050 )
add_definitions(-DMAX_SYNTH_VOICES=64)
add_definitions(-D_8_BIT_SAMPLES )
add_definitions(-D_FILTER_ENABLED)
add_definitions(-DDLS_SYNTHESIZER)
add_definitions(-D_REVERB_ENABLED)

set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/sonivox/ )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/sonivox/arm-wt-22k )

include_directories(AFTER ${SOURCE_PATH}/host_src)
file(GLOB HOST_SOURCE_FILES 
${SOURCE_PATH}/host_src/*.h
)
list(APPEND HOST_SOURCE_FILES
${SOURCE_PATH}/host_src/eas_config.c 
${SOURCE_PATH}/host_src/eas_hostmm.c 
${SOURCE_PATH}/host_src/eas_report.c
)
source_group(host FILES ${HOST_SOURCE_FILES})

include_directories(AFTER ${SOURCE_PATH}/lib_src)
file(GLOB LIB_SOURCE_FILES 
${SOURCE_PATH}/lib_src/*.h
)
list(APPEND LIB_SOURCE_FILES
${SOURCE_PATH}/lib_src/eas_chorus.c 
${SOURCE_PATH}/lib_src/eas_chorusdata.c 
${SOURCE_PATH}/lib_src/eas_data.c 
${SOURCE_PATH}/lib_src/eas_dlssynth.c 
${SOURCE_PATH}/lib_src/eas_flog.c 
${SOURCE_PATH}/lib_src/eas_ima_tables.c 
${SOURCE_PATH}/lib_src/eas_imaadpcm.c 
${SOURCE_PATH}/lib_src/eas_imelody.c 
${SOURCE_PATH}/lib_src/eas_imelodydata.c 
${SOURCE_PATH}/lib_src/eas_math.c 
${SOURCE_PATH}/lib_src/eas_mdls.c 
${SOURCE_PATH}/lib_src/eas_midi.c 
${SOURCE_PATH}/lib_src/eas_mididata.c 
${SOURCE_PATH}/lib_src/eas_mixbuf.c 
${SOURCE_PATH}/lib_src/eas_mixer.c 
${SOURCE_PATH}/lib_src/eas_ota.c 
${SOURCE_PATH}/lib_src/eas_otadata.c 
${SOURCE_PATH}/lib_src/eas_pan.c 
${SOURCE_PATH}/lib_src/eas_pcm.c 
${SOURCE_PATH}/lib_src/eas_pcmdata.c 
${SOURCE_PATH}/lib_src/eas_public.c 
${SOURCE_PATH}/lib_src/eas_reverb.c 
${SOURCE_PATH}/lib_src/eas_reverbdata.c 
${SOURCE_PATH}/lib_src/eas_rtttl.c 
${SOURCE_PATH}/lib_src/eas_rtttldata.c 
${SOURCE_PATH}/lib_src/eas_smf.c 
${SOURCE_PATH}/lib_src/eas_smfdata.c 
${SOURCE_PATH}/lib_src/eas_voicemgt.c 
${SOURCE_PATH}/lib_src/eas_wtengine.c 
${SOURCE_PATH}/lib_src/eas_wtsynth.c 
${SOURCE_PATH}/lib_src/eas_xmf.c 
${SOURCE_PATH}/lib_src/eas_xmfdata.c 
${SOURCE_PATH}/lib_src/wt_22khz.c 
${SOURCE_PATH}/lib_src/jet.c 
)
source_group(lib FILES ${LIB_SOURCE_FILES})

set(SONIC_SOURCE_FILES
${HOST_SOURCE_FILES}
${LIB_SOURCE_FILES}
)

set(LIB_TYPE SHARED)
set(LIB_NAME sonivox)

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${LIB_NAME} ${LIB_TYPE} ${SONIC_HEADER_FILES} ${SONIC_SOURCE_FILES})
target_link_libraries(${LIB_NAME} ${SONIC_DEPLIB})

add_custom_command(TARGET ${LIB_NAME} POST_BUILD
COMMAND ${CMAKE_COMMAND} -E make_directory 
${HEADER_PATH}/libsonivox/
)

add_custom_command(TARGET ${LIB_NAME} POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy
${SOURCE_PATH}/host_src/eas.h 
${SOURCE_PATH}/host_src/eas_types.h 
${SOURCE_PATH}/host_src/eas_reverb.h 
${SOURCE_PATH}/host_src/jet.h
${HEADER_PATH}/libsonivox/
)
