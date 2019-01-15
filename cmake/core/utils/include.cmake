
# define
DLL_PUBLIC(UTILS)

if(MSVC)
    add_definitions(-DHAVE_MS_C_RUNTIME)
    add_definitions(-DHAVE_WIN32_THREADS)
    add_definitions(-D__PRETTY_FUNCTION__=__FUNCTION__)
    add_definitions(-D__STDC_LIMIT_MACROS=1)
    include_directories(AFTER ${MSVC_PATH})

elseif(APPLE)
    add_definitions(-D_MACOSX)
    add_definitions(-DHAVE_PTHREADS)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -stdlib=libc++")

elseif(CYGWIN)
    add_definitions(-D_CYGWIN)
    add_definitions(-DHAVE_WIN32_THREADS)
    #add_definitions(-Dffs=__builtin_ffs)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=gnu++11")

elseif(UNIX)
    add_definitions(-D_LINUX)
    add_definitions(-DHAVE_PTHREADS)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++0x")
endif()

# include
include_directories(AFTER ${M3E_SOURCE_DIR}/src/system/core/libutils/include)

