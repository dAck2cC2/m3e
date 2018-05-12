
if(APPLE)
    set(PNG m3e_png)
else()
    set(PNG png)
endif()

# include
set(PNG_LIBRARIES ${PNG})
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/libpng)
