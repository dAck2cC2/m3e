
if (APPLE)
	set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -stdlib=libc++")
elseif (MSVC)
    add_definitions(-DSKIA_DLL)
endif ()

# core
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia_chrome/include)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia_chrome/include/config)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia_chrome/include/core)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia_chrome/include/gpu)

# additonal
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia_chrome/include/views)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia_chrome/include/utils)

#extend
include_directories(AFTER ${M3E_SOURCE_DIR}/src/${EXT_PATH}/skia_chrome/include)
