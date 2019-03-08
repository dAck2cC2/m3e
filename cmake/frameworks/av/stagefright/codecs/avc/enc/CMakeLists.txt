project(STAGEFRIGHT_SOFT_H264ENC)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/ui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/gui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/EGL/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/audioprocessing/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/media/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright_foundation/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright_omx/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright/codecs/common/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright/codecs/avc/common/include.cmake)

include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/native/headers/media_plugin/media/hardware)

set(${PROJECT_NAME}_DEPLIB
log
utils
ui
stagefright
stagefright_foundation
stagefright_omx
stagefright_enc_common
stagefright_avc_common
)

add_definitions(-DOSCL_IMPORT_REF= )
add_definitions(-DOSCL_EXPORT_REF= )
add_definitions(-DOSCL_UNUSED_ARG=\(void\) )

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/codecs/avc/enc/src )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/codecs/avc/enc )

include_directories(AFTER ${HEADER_PATH})

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES  
${HEADER_PATH}/*.h 
${SOURCE_PATH}/*.h
)

set(${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/src/avcenc_api.cpp 
${SOURCE_PATH}/src/bitstream_io.cpp 
${SOURCE_PATH}/src/block.cpp 
${SOURCE_PATH}/src/findhalfpel.cpp 
${SOURCE_PATH}/src/header.cpp 
${SOURCE_PATH}/src/init.cpp 
${SOURCE_PATH}/src/intra_est.cpp 
${SOURCE_PATH}/src/motion_comp.cpp 
${SOURCE_PATH}/src/motion_est.cpp 
${SOURCE_PATH}/src/rate_control.cpp 
${SOURCE_PATH}/src/residual.cpp 
${SOURCE_PATH}/src/sad.cpp 
${SOURCE_PATH}/src/sad_halfpel.cpp 
${SOURCE_PATH}/src/slice.cpp 
${SOURCE_PATH}/src/vlc_encode.cpp
${SOURCE_PATH}/SoftAVCEncoder.cpp
)

# target files
set(LIB_NAME stagefright_soft_h264enc)
set(LIB_TYPE SHARED)
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${LIB_NAME} ${LIB_TYPE} ${${PROJECT_NAME}_SOURCE_FILES} ${${PROJECT_NAME}_HEADER_FILES})
target_link_libraries(${LIB_NAME} ${${PROJECT_NAME}_DEPLIB})
