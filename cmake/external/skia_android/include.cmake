
if(MSVC)
    add_definitions(-DSKIA_DLL)
endif()

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia_android/include/config)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia_android/include/core)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia_android/include/gpu)
