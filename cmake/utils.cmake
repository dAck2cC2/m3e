
# include and define
#SET(CMAKE_INCLUDE_DIRECTORIES_BEFORE, ON)
if(MSVC)
ADD_DEFINITIONS(-DHAVE_MS_C_RUNTIME)
ADD_DEFINITIONS(-DHAVE_WIN32_THREADS)
INCLUDE_DIRECTORIES(AFTER ${M3E_SOURCE_DIR}/src/native/msvc)
elseif(APPLE)
ADD_DEFINITIONS(-D_MACOSX)
ADD_DEFINITIONS(-DHAVE_PTHREADS)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -stdlib=libc++")
endif()
INCLUDE_DIRECTORIES(AFTER ${M3E_SOURCE_DIR}/src/native/include)

# header files
FILE(GLOB LIBUTILS_HEADER_FILES
${M3E_SOURCE_DIR}/src/native/include/cutils/*.h
${M3E_SOURCE_DIR}/src/native/include/utils/*.h
)

# source files
FILE(GLOB LIBUTILS_SOURCE_FILES 
${M3E_SOURCE_DIR}/src/native/libutils/*.c 
${M3E_SOURCE_DIR}/src/native/libutils/*.cpp
${M3E_SOURCE_DIR}/src/native/libutils/cutils/*.c
)

# header and source code for MSVC
if(MSVC)
SET(LIBUTILS_HEADER_FILES ${LIBUTILS_HEADER_FILES} ${M3E_SOURCE_DIR}/src/native/msvc/stdint.h)
SET(LIBUTILS_HEADER_FILES ${LIBUTILS_HEADER_FILES} ${M3E_SOURCE_DIR}/src/native/msvc/sys/time.h)
SET(LIBUTILS_SOURCE_FILES ${LIBUTILS_SOURCE_FILES} ${M3E_SOURCE_DIR}/src/native/msvc/sys/time.c)
endif()

# target files
ADD_LIBRARY(utils SHARED ${LIBUTILS_SOURCE_FILES} ${LIBUTILS_HEADER_FILES})
