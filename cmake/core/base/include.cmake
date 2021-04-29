
if(LINUX)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17")
endif()

# include
include_directories(AFTER ${M3E_SOURCE_DIR}/src/system/core/base/include)
