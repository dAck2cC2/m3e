
if(APPLE)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14 -stdlib=libc++")
endif()

# angle util
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/util)
