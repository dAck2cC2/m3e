project(AAC)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
#include(${M3E_SOURCE_DIR}/cmake/external/aac/include.cmake)

GET_ANDROID_MODULE(aac)

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)

set(${PROJECT_NAME}_DEPLIB
log
)

set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/aac )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/aac )

###############################################################################
#  aacdec_sources
###############################################################################

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/aac/libAACdec/include)
file(GLOB  AACDEC_SOURCES
${SOURCE_PATH}/libAACdec/src/*.cpp 
${SOURCE_PATH}/libAACdec/src/*.h
${SOURCE_PATH}/libAACdec/include/*.h
)
source_group(aacdec FILES ${AACDEC_SOURCES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${AACDEC_SOURCES})

###############################################################################
#  aacenc_sources
###############################################################################

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/aac/libAACenc/include)
file(GLOB  AACENC_SOURCES
${SOURCE_PATH}/libAACenc/src/*.cpp 
${SOURCE_PATH}/libAACenc/src/*.h
${SOURCE_PATH}/libAACenc/include/*.h
)
source_group(aacenc FILES ${AACENC_SOURCES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${AACENC_SOURCES})

###############################################################################
#  pcmutils_sources
###############################################################################

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/aac/libPCMutils/include)
file(GLOB  PCMUTILS_SOURCES
${SOURCE_PATH}/libPCMutils/src/*.cpp 
${SOURCE_PATH}/libPCMutils/src/*.h
${SOURCE_PATH}/libPCMutils/include/*.h
)
source_group(pcmutils FILES ${PCMUTILS_SOURCES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${PCMUTILS_SOURCES})

###############################################################################
#  fdk_sources
###############################################################################

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/aac/libFDK/include)
file(GLOB  FDK_SOURCES
${SOURCE_PATH}/libFDK/src/*.cpp 
${SOURCE_PATH}/libFDK/src/*.h
${SOURCE_PATH}/libFDK/include/*.h
)
source_group(fdk FILES ${FDK_SOURCES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${FDK_SOURCES})

###############################################################################
#  sys_sources
###############################################################################

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/aac/libSYS/include)
file(GLOB  SYS_SOURCES
${SOURCE_PATH}/libSYS/src/*.cpp 
${SOURCE_PATH}/libSYS/src/*.h
${SOURCE_PATH}/libSYS/include/*.h
)
source_group(sys FILES ${SYS_SOURCES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${SYS_SOURCES})

###############################################################################
#  mpegtpdec_sources
###############################################################################

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/aac/libMpegTPDec/include)
file(GLOB  MPEGTPDEC_SOURCES
${SOURCE_PATH}/libMpegTPDec/src/*.cpp 
${SOURCE_PATH}/libMpegTPDec/src/*.h
${SOURCE_PATH}/libMpegTPDec/include/*.h
)
source_group(mpegtpdec FILES ${MPEGTPDEC_SOURCES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${MPEGTPDEC_SOURCES})

###############################################################################
#  mpegtpenc_sources
###############################################################################

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/aac/libMpegTPEnc/include)
file(GLOB  MPEGTPENC_SOURCES
${SOURCE_PATH}/libMpegTPEnc/src/*.cpp 
${SOURCE_PATH}/libMpegTPEnc/src/*.h
${SOURCE_PATH}/libMpegTPEnc/include/*.h
)
source_group(mpegtpenc FILES ${MPEGTPENC_SOURCES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${MPEGTPENC_SOURCES})

###############################################################################
#  sbrdec_sources
###############################################################################

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/aac/libSBRdec/include)
file(GLOB  SBRDEC_SOURCES
${SOURCE_PATH}/libSBRdec/src/*.cpp 
${SOURCE_PATH}/libSBRdec/src/*.h
${SOURCE_PATH}/libSBRdec/include/*.h
)
source_group(sbrdec FILES ${SBRDEC_SOURCES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${SBRDEC_SOURCES})

###############################################################################
#  sbrenc_sources
###############################################################################

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/aac/libSBRenc/include)
file(GLOB  SBRENC_SOURCES
${SOURCE_PATH}/libSBRenc/src/*.cpp 
${SOURCE_PATH}/libSBRenc/src/*.h
${SOURCE_PATH}/libSBRenc/include/*.h
)
source_group(sbrenc FILES ${SBRENC_SOURCES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${SBRENC_SOURCES})



set(LIB_TYPE STATIC)
set(LIB_NAME FraunhoferAAC)
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${LIB_NAME} ${LIB_TYPE}  ${${PROJECT_NAME}_SOURCE_FILES})
target_link_libraries(${LIB_NAME} ${${PROJECT_NAME}_DEPLIB})
