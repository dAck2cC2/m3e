
if(APPLE)
    set(JPEG m3e_jpeg)
else()
    set(JPEG jpeg)
endif()

# include
set(JPEG_LIBRARIES ${JPEG})
set(JPEG_INCLUDE_DIR ${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/jpeg)
