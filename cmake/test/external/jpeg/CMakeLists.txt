
# demo program

project(TEST_JPEG)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/jpeg/include.cmake)

# core ####################################
set(DEMO_DEPLIBS
jpeg
)
ADD_DEMO(djpeg   
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/djpeg.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/cdjpeg.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/wrppm.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/wrgif.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/wrbmp.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/rdcolmap.c
${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg/wrtarga.c
)

