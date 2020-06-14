
if(CYGWIN)
    add_definitions(-DGTEST_OS_CYGWIN=1)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=gnu++11")
elseif(APPLE)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -stdlib=libc++")
elseif(MSVC)
    add_definitions(-D_HAS_TR1_NAMESPACE=1)
endif()

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/gtest/include)
