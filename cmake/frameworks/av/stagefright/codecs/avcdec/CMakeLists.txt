project(STAGEFRIGHT_SOFT_AVCDEC)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/external/avc/include.cmake)

set(${PROJECT_NAME}_DEPLIB
log 
utils 
stagefright_foundation
stagefright
stagefright_omx
avcdec
)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/codecs/avcdec )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/codecs/avcdec )

include_directories(AFTER ${HEADER_PATH})

file(GLOB ${PROJECT_NAME}_HEADER_FILES
${HEADER_PATH}/*.h
)

set(${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/SoftAVCDec.cpp
)

# target files
set(LIB_TYPE SHARED)
ADD_LIB(stagefright_soft_avcdec)
