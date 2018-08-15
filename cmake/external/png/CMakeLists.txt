
project(PNG)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/png/include.cmake)

GET_ANDROID_MODULE(libpng)

if(MSVC)
    include_directories(AFTER ${MSVC_PATH})
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/libpng )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/libpng )

# Copyright (C) 2007,2009-2016 Glenn Randers-Pehrson
# Written by Christian Ehrlicher, 2007
# Revised by Roger Lowman, 2009-2010
# Revised by Clifford Yapp, 2011-2012
# Revised by Roger Leigh, 2016

# This code is released under the libpng license.
# For conditions of distribution and use, see the disclaimer
# and license in png.h

cmake_minimum_required(VERSION 2.8.3)
cmake_policy(VERSION 2.8.3)

# Set MacOSX @rpath usage globally.
if (POLICY CMP0020)
  cmake_policy(SET CMP0020 NEW)
endif(POLICY CMP0020)
if (POLICY CMP0042)
  cmake_policy(SET CMP0042 NEW)
endif(POLICY CMP0042)
# Use new variable expansion policy.
if (POLICY CMP0053)
  cmake_policy(SET CMP0053 NEW)
endif(POLICY CMP0053)
if (POLICY CMP0054)
  cmake_policy(SET CMP0054 NEW)
endif(POLICY CMP0054)

set(CMAKE_CONFIGURATION_TYPES "Release;Debug;MinSizeRel;RelWithDebInfo")

enable_testing()

set(PNGLIB_MAJOR 1)
set(PNGLIB_MINOR 6)
set(PNGLIB_RELEASE 22)
set(PNGLIB_NAME libpng${PNGLIB_MAJOR}${PNGLIB_MINOR})
set(PNGLIB_VERSION ${PNGLIB_MAJOR}.${PNGLIB_MINOR}.${PNGLIB_RELEASE})

set(SO_COMPATVERSION "${PNGLIB_MAJOR}")
set(SO_VERSION "${PNGLIB_VERSION}")


# needed packages
include(${M3E_SOURCE_DIR}/cmake/external/zlib/include.cmake)
set(PNG_DEPLIB zlib)


if(NOT WIN32)
  find_library(M_LIBRARY
    NAMES m
    PATHS /usr/lib /usr/local/lib
  )
  if(NOT M_LIBRARY)
    message(STATUS "math lib 'libm' not found; floating point support disabled")
  endif()
else()
  # not needed on windows
  set(M_LIBRARY "")
endif()

# COMMAND LINE OPTIONS
option(PNG_SHARED "Build shared lib" ON)
option(PNG_STATIC "Build static lib" OFF)
option(PNG_TESTS  "Build libpng tests" OFF)

# Many more configuration options could be added here
option(PNG_FRAMEWORK "Build OS X framework" OFF)
option(PNG_DEBUG     "Build with debug output" OFF)
option(PNGARG        "Disable ANSI-C prototypes" OFF)

set(PNG_PREFIX "" CACHE STRING "Prefix to add to the API function names")
set(DFA_XTRA "" CACHE FILEPATH "File containing extra configuration settings")

file(GLOB PNG_HEADER_FILES
${HEADER_PATH}/*.h
)

set(PNG_SOURCE_FILES
${SOURCE_PATH}/png.c
${SOURCE_PATH}/pngerror.c 
${SOURCE_PATH}/pngget.c
${SOURCE_PATH}/pngmem.c 
${SOURCE_PATH}/pngpread.c
${SOURCE_PATH}/pngread.c 
${SOURCE_PATH}/pngrio.c 
${SOURCE_PATH}/pngrtran.c 
${SOURCE_PATH}/pngrutil.c
${SOURCE_PATH}/pngset.c
${SOURCE_PATH}/pngtrans.c
${SOURCE_PATH}/pngwio.c 
${SOURCE_PATH}/pngwrite.c 
${SOURCE_PATH}/pngwtran.c 
${SOURCE_PATH}/pngwutil.c 
)

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${PNG} SHARED ${PNG_SOURCE_FILES} ${PNG_HEADER_FILES})
target_link_libraries(${PNG} ${PNG_DEPLIB})

set_target_properties(${PNG} PROPERTIES SOVERSION ${SO_COMPATVERSION})
if(NOT CYGWIN)
    set_target_properties(${PNG} PROPERTIES VERSION ${SO_VERSION})
endif()
