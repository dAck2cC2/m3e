
# include and define
if(MSVC)
add_definitions(-DHAVE_MS_C_RUNTIME)
add_definitions(-DHAVE_WIN32_THREADS)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/native/msvc)
elseif(APPLE)
add_definitions(-D_MACOSX)
add_definitions(-DHAVE_PTHREADS)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -stdlib=libc++")
elseif(CYGWIN)
add_definitions(-D_CYGWIN)
add_definitions(-DHAVE_WIN32_THREADS)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=gnu++11")
elseif(UNIX)
add_definitions(-D_LINUX)
add_definitions(-DHAVE_PTHREADS)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++0x")
endif()

include_directories(AFTER ${M3E_SOURCE_DIR}/src/native/include)

