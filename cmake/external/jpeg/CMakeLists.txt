
project(JPEG)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/jpeg/include.cmake)

GET_ANDROID_MODULE(jpeg)

#include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/libyuv/files)

#add_definitions(-DHAVE_JPEG)

file(GLOB JPEG_HEADER_FILES
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/*.h
)

set(JPEG_SOURCE_FILES 
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jcapimin.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jcapistd.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jccoefct.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jccolor.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jcdctmgr.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jchuff.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jcinit.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jcmainct.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jcmarker.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jcmaster.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jcomapi.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jcparam.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jcphuff.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jcprepct.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jcsample.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jctrans.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jdapimin.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jdapistd.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jdatadst.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jdatasrc.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jdcoefct.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jdcolor.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jddctmgr.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jdhuff.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jdinput.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jdmainct.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jdmarker.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jdmaster.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jdmerge.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jdphuff.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jdpostct.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jdsample.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jdtrans.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jerror.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jfdctflt.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jfdctfst.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jfdctint.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jidctflt.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jidctfst.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jidctint.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jidctred.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jquant1.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jquant2.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jutils.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jmemmgr.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/jmemnobs.c
)

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${JPEG} SHARED ${JPEG_SOURCE_FILES} ${JPEG_HEADER_FILES})
