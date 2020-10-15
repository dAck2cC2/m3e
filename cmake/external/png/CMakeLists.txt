
project(PNG)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/png/include.cmake)

GET_ANDROID_MODULE(libpng)

if(MSVC)
  include(${M3E_SOURCE_DIR}/cmake/core/msvc/include.cmake)
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/libpng )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/libpng )

# CMakeLists.txt

# Copyright (C) 2007,2009-2017 Glenn Randers-Pehrson
# Written by Christian Ehrlicher, 2007
# Revised by Roger Lowman, 2009-2010
# Revised by Clifford Yapp, 2011-2012
# Revised by Roger Leigh, 2016
# Revised by Andreas Franek, 2016

# This code is released under the libpng license.
# For conditions of distribution and use, see the disclaimer
# and license in png.h

cmake_minimum_required(VERSION 3.0.2)
cmake_policy(VERSION 3.0.2)

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

#project(libpng ASM C)
enable_testing()

set(PNGLIB_MAJOR 1)
set(PNGLIB_MINOR 6)
set(PNGLIB_RELEASE 34)
set(PNGLIB_NAME libpng${PNGLIB_MAJOR}${PNGLIB_MINOR})
set(PNGLIB_VERSION ${PNGLIB_MAJOR}.${PNGLIB_MINOR}.${PNGLIB_RELEASE})

#include(GNUInstallDirs)
set(SO_COMPATVERSION "${PNGLIB_MAJOR}")
set(SO_VERSION "${PNGLIB_VERSION}")


# needed packages

#Allow users to specify location of Zlib,
# Useful if zlib is being built alongside this as a sub-project
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

option(PNG_HARDWARE_OPTIMIZATIONS "Enable Hardware Optimizations" OFF)


set(PNG_PREFIX "" CACHE STRING "Prefix to add to the API function names")
set(DFA_XTRA "" CACHE FILEPATH "File containing extra configuration settings")

if(PNG_HARDWARE_OPTIMIZATIONS)
# set definitions and sources for arm
if(CMAKE_SYSTEM_PROCESSOR MATCHES "^arm" OR
  CMAKE_SYSTEM_PROCESSOR MATCHES "^aarch64")
  set(PNG_ARM_NEON_POSSIBLE_VALUES check on off)
  set(PNG_ARM_NEON "check" CACHE STRING "Enable ARM NEON optimizations:
     check: (default) use internal checking code;
     off: disable the optimizations;
     on: turn on unconditionally.")
  set_property(CACHE PNG_ARM_NEON PROPERTY STRINGS
     ${PNG_ARM_NEON_POSSIBLE_VALUES})
  list(FIND PNG_ARM_NEON_POSSIBLE_VALUES ${PNG_ARM_NEON} index)
  if(index EQUAL -1)
    message(FATAL_ERROR
      " PNG_ARM_NEON must be one of [${PNG_ARM_NEON_POSSIBLE_VALUES}]")
  elseif(NOT ${PNG_ARM_NEON} STREQUAL "no")
    set(libpng_arm_sources
      arm/arm_init.c
      arm/filter_neon.S
      arm/filter_neon_intrinsics.c)

    if(${PNG_ARM_NEON} STREQUAL "on")
      add_definitions(-DPNG_ARM_NEON_OPT=2)
    elseif(${PNG_ARM_NEON} STREQUAL "check")
      add_definitions(-DPNG_ARM_NEON_CHECK_SUPPORTED)
    endif()
  else()
    add_definitions(-DPNG_ARM_NEON_OPT=0)
  endif()
endif()

# set definitions and sources for powerpc
if(CMAKE_SYSTEM_PROCESSOR MATCHES "^powerpc*" OR
	CMAKE_SYSTEM_PROCESSOR MATCHES "^ppc64*" )
  set(PNG_POWERPC_VSX_POSSIBLE_VALUES on off)
  set(PNG_POWERPC_VSX "on" CACHE STRING "Enable POWERPC VSX optimizations:
     off: disable the optimizations.")
  set_property(CACHE PNG_POWERPC_VSX PROPERTY STRINGS
     ${PNG_POWERPC_VSX_POSSIBLE_VALUES})
  list(FIND PNG_POWERPC_VSX_POSSIBLE_VALUES ${PNG_POWERPC_VSX} index)
  if(index EQUAL -1)
    message(FATAL_ERROR
      " PNG_POWERPC_VSX must be one of [${PNG_POWERPC_VSX_POSSIBLE_VALUES}]")
  elseif(NOT ${PNG_POWERPC_VSX} STREQUAL "no")
    set(libpng_powerpc_sources
      powerpc/powerpc_init.c
      powerpc/filter_vsx_intrinsics.c)
    if(${PNG_POWERPC_VSX} STREQUAL "on")
      add_definitions(-DPNG_POWERPC_VSX_OPT=2)
    endif()
  else()
    add_definitions(-DPNG_POWERPC_VSX_OPT=0)
  endif()
endif()

# set definitions and sources for intel
if(CMAKE_SYSTEM_PROCESSOR MATCHES "^i?86" OR
	CMAKE_SYSTEM_PROCESSOR MATCHES "^x86_64*" )
  set(PNG_INTEL_SSE_POSSIBLE_VALUES on off)
  set(PNG_INTEL_SSE "on" CACHE STRING "Enable INTEL_SSE optimizations:
     off: disable the optimizations")
  set_property(CACHE PNG_INTEL_SSE PROPERTY STRINGS
     ${PNG_INTEL_SSE_POSSIBLE_VALUES})
  list(FIND PNG_INTEL_SSE_POSSIBLE_VALUES ${PNG_INTEL_SSE} index)
  if(index EQUAL -1)
    message(FATAL_ERROR
      " PNG_INTEL_SSE must be one of [${PNG_INTEL_SSE_POSSIBLE_VALUES}]")
  elseif(NOT ${PNG_INTEL_SSE} STREQUAL "no")
    set(libpng_intel_sources
      intel/intel_init.c
      intel/filter_sse2_intrinsics.c)
    if(${PNG_INTEL_SSE} STREQUAL "on")
      add_definitions(-DPNG_INTEL_SSE_OPT=1)
    endif()
  else()
    add_definitions(-DPNG_INTEL_SSE_OPT=0)
  endif()
endif()
endif(PNG_HARDWARE_OPTIMIZATIONS)

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
