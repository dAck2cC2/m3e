
if (MSVC)
add_definitions(-DSKIA_DLL)
endif ()

# core
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/include)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/include/config)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/include/core)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/include/gpu)

# additonal
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/include/views)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/include/utils)
