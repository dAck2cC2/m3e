
if(APPLE)
#add_definitions(-D_MACOSX)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -stdlib=libc++")
endif()

# core
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/include)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/include/config)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/include/core)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/include/gpu)

# additional
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/include/utils)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/src/gpu)
