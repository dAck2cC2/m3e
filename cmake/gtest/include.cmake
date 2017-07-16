
if(CYGWIN)
add_definitions(-DGTEST_OS_CYGWIN=1)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=gnu++11")
endif()
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/gtest/include)
