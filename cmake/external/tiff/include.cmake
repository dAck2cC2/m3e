
if(APPLE)
    set(TIFF m3e_tiff)
else()
    set(TIFF tiff)
endif()

# include
set(TIFF_LIBRARIES ${TIFF})
include_directories(AFTER ${M3E_BINARY_DIR}/tiff)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/libtiff/libtiff)
