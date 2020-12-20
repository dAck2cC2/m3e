project(JPEG-TURBO)

if(NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH}/libjpeg-turbo)
    message(STATUS "Download\t libjpeg-turbo")
    exec_program("git clone https://github.com/libjpeg-turbo/libjpeg-turbo.git" ${M3E_SOURCE_DIR}/${EXT_PATH})
    exec_program("git checkout 1.5.3" ${M3E_SOURCE_DIR}/${EXT_PATH}/libjpeg-turbo)
endif()

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/jpeg-turbo/include.cmake)

set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/libjpeg-turbo )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/libjpeg-turbo )

#
# Setup
#

#cmake_minimum_required(VERSION 2.8.11)
# Use LINK_INTERFACE_LIBRARIES instead of INTERFACE_LINK_LIBRARIES
#if(POLICY CMP0022)
#  cmake_policy(SET CMP0022 OLD)
#endif()

set(VERSION 1.5.3)
string(REPLACE "." ";" VERSION_TRIPLET ${VERSION})
list(GET VERSION_TRIPLET 0 VERSION_MAJOR)
list(GET VERSION_TRIPLET 1 VERSION_MINOR)
list(GET VERSION_TRIPLET 2 VERSION_REVISION)
function(pad_number NUMBER OUTPUT_LEN)
  string(LENGTH "${${NUMBER}}" INPUT_LEN)
  if(INPUT_LEN LESS OUTPUT_LEN)
    math(EXPR ZEROES "${OUTPUT_LEN} - ${INPUT_LEN} - 1")
    set(NUM ${${NUMBER}})
    foreach(C RANGE ${ZEROES})
      set(NUM "0${NUM}")
    endforeach()
    set(${NUMBER} ${NUM} PARENT_SCOPE)
  endif()
endfunction()
pad_number(VERSION_MINOR 3)
pad_number(VERSION_REVISION 3)
set(LIBJPEG_TURBO_VERSION_NUMBER ${VERSION_MAJOR}${VERSION_MINOR}${VERSION_REVISION})

#if(NOT WIN32)
#  message(FATAL_ERROR "Platform not supported by this build system.  Use autotools instead.")
#endif()

string(TIMESTAMP BUILD "%Y%m%d")

# This does nothing except when using MinGW.  CMAKE_BUILD_TYPE has no meaning
# in Visual Studio, and it always defaults to Debug when using NMake.
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

message(STATUS "CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")

# This only works if building from the command line.  There is currently no way
# to set a variable's value based on the build type when using Visual Studio.
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(BUILD "${BUILD}d")
endif()

message(STATUS "VERSION = ${VERSION}, BUILD = ${BUILD}")

option(WITH_SIMD "Include SIMD extensions" FALSE)
option(WITH_ARITH_ENC "Include arithmetic encoding support when emulating the libjpeg v6b API/ABI" TRUE)
option(WITH_ARITH_DEC "Include arithmetic decoding support when emulating the libjpeg v6b API/ABI" TRUE)
option(WITH_JPEG7 "Emulate libjpeg v7 API/ABI (this makes libjpeg-turbo backward incompatible with libjpeg v6b)" FALSE)
option(WITH_JPEG8 "Emulate libjpeg v8 API/ABI (this makes libjpeg-turbo backward incompatible with libjpeg v6b)" TRUE)
option(WITH_MEM_SRCDST "Include in-memory source/destination manager functions when emulating the libjpeg v6b or v7 API/ABI" TRUE)
option(WITH_TURBOJPEG "Include the TurboJPEG wrapper library and associated test programs" FALSE)
option(WITH_JAVA "Build Java wrapper for the TurboJPEG library" FALSE)
option(WITH_12BIT "Encode/decode JPEG images with 12-bit samples (implies WITH_SIMD=0 WITH_TURBOJPEG=0 WITH_ARITH_ENC=0 WITH_ARITH_DEC=0)" FALSE)
option(ENABLE_STATIC "Build static libraries" FALSE)
option(ENABLE_SHARED "Build shared libraries" TRUE)

if(WITH_12BIT)
  set(WITH_SIMD FALSE)
  set(WITH_TURBOJPEG FALSE)
  set(WITH_JAVA FALSE)
  set(WITH_ARITH_ENC FALSE)
  set(WITH_ARITH_DEC FALSE)
  set(BITS_IN_JSAMPLE 12)
  message(STATUS "12-bit JPEG support enabled")
else()
  set(BITS_IN_JSAMPLE 8)
endif()

if(WITH_JPEG8 OR WITH_JPEG7)
  set(WITH_ARITH_ENC 1)
  set(WITH_ARITH_DEC 1)
endif()
if(WITH_JPEG8)
  set(WITH_MEM_SRCDST 1)
endif()

if(WITH_ARITH_ENC)
  set(C_ARITH_CODING_SUPPORTED 1)
  message(STATUS "Arithmetic encoding support enabled")
else()
  message(STATUS "Arithmetic encoding support disabled")
endif()

if(WITH_ARITH_DEC)
  set(D_ARITH_CODING_SUPPORTED 1)
  message(STATUS "Arithmetic decoding support enabled")
else()
  message(STATUS "Arithmetic decoding support disabled")
endif()

if(WITH_TURBOJPEG)
  message(STATUS "TurboJPEG C wrapper enabled")
else()
  message(STATUS "TurboJPEG C wrapper disabled")
endif()

if(WITH_JAVA)
  message(STATUS "TurboJPEG Java wrapper enabled")
else()
  message(STATUS "TurboJPEG Java wrapper disabled")
endif()

set(SO_AGE 0)
if(WITH_MEM_SRCDST)
  set(SO_AGE 1)
endif()

set(JPEG_LIB_VERSION 62)
set(DLL_VERSION ${JPEG_LIB_VERSION})
set(FULLVERSION ${DLL_VERSION}.${SO_AGE}.0)
if(WITH_JPEG8)
  set(JPEG_LIB_VERSION 80)
  set(DLL_VERSION 8)
  set(FULLVERSION ${DLL_VERSION}.0.2)
  message(STATUS "Emulating libjpeg v8 API/ABI")
elseif(WITH_JPEG7)
  set(JPEG_LIB_VERSION 70)
  set(DLL_VERSION 7)
  set(FULLVERSION ${DLL_VERSION}.${SO_AGE}.0)
  message(STATUS "Emulating libjpeg v7 API/ABI")
endif(WITH_JPEG8)

if(WITH_MEM_SRCDST)
  set(MEM_SRCDST_SUPPORTED 1)
  message(STATUS "In-memory source/destination managers enabled")
else()
  message(STATUS "In-memory source/destination managers disabled")
endif()

if(MSVC)
  option(WITH_CRT_DLL
    "Link all libjpeg-turbo libraries and executables with the C run-time DLL (msvcr*.dll) instead of the static C run-time library (libcmt*.lib.)  The default is to use the C run-time DLL only with the libraries and executables that need it."
    FALSE)
  if(NOT WITH_CRT_DLL)
    # Use the static C library for all build types
    foreach(var CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
      CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO)
      if(${var} MATCHES "/MD")
        string(REGEX REPLACE "/MD" "/MT" ${var} "${${var}}")
      endif()
    endforeach()
  endif()
  add_definitions(-W3 -wd4996)
endif()

# Detect whether compiler is 64-bit
if(MSVC AND CMAKE_CL_64)
  set(SIMD_X86_64 1)
  set(64BIT 1)
elseif(CMAKE_SIZEOF_VOID_P MATCHES 8)
  set(SIMD_X86_64 1)
  set(64BIT 1)
endif()

if(64BIT)
  message(STATUS "64-bit build")
else()
  message(STATUS "32-bit build")
endif()

configure_file(${SOURCE_PATH}/win/jconfig.h.in ${HEADER_PATH}/jconfig.h)
configure_file(${SOURCE_PATH}/win/jconfigint.h.in ${HEADER_PATH}/jconfigint.h)

string(TOUPPER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_UC)

set(EFFECTIVE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_${CMAKE_BUILD_TYPE_UC}}")
message(STATUS "Compiler flags = ${EFFECTIVE_C_FLAGS}")

set(EFFECTIVE_LD_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${CMAKE_EXE_LINKER_FLAGS_${CMAKE_BUILD_TYPE_UC}}")
message(STATUS "Linker flags = ${EFFECTIVE_LD_FLAGS}")

if(WITH_JAVA)
  find_package(Java)
  find_package(JNI)
  if(DEFINED JAVACFLAGS)
    message(STATUS "Java compiler flags = ${JAVACFLAGS}")
  endif()
endif()


#
# Targets
#
include(CheckTypeSize)
check_type_size("size_t" SIZEOF_SIZE_T)
if (SIZEOF_SIZE_T EQUAL 8)
    add_definitions(-DSIZEOF_SIZE_T=8)
else ()
    add_definitions(-DSIZEOF_SIZE_T=4)
endif ()

set(JPEG_SOURCES jcapimin.c jcapistd.c jccoefct.c jccolor.c jcdctmgr.c jchuff.c
  jcinit.c jcmainct.c jcmarker.c jcmaster.c jcomapi.c jcparam.c jcphuff.c
  jcprepct.c jcsample.c jctrans.c jdapimin.c jdapistd.c jdatadst.c jdatasrc.c
  jdcoefct.c jdcolor.c jddctmgr.c jdhuff.c jdinput.c jdmainct.c jdmarker.c
  jdmaster.c jdmerge.c jdphuff.c jdpostct.c jdsample.c jdtrans.c jerror.c
  jfdctflt.c jfdctfst.c jfdctint.c jidctflt.c jidctfst.c jidctint.c jidctred.c
  jquant1.c jquant2.c jutils.c jmemmgr.c jmemnobs.c)

if(WITH_ARITH_ENC OR WITH_ARITH_DEC)
  set(JPEG_SOURCES ${JPEG_SOURCES} jaricom.c)
endif()

if(WITH_ARITH_ENC)
  set(JPEG_SOURCES ${JPEG_SOURCES} jcarith.c)
endif()

if(WITH_ARITH_DEC)
  set(JPEG_SOURCES ${JPEG_SOURCES} jdarith.c)
endif()

if(WITH_SIMD)
  add_definitions(-DWITH_SIMD)
  add_subdirectory(simd)
  if(SIMD_X86_64)
    set(JPEG_SOURCES ${JPEG_SOURCES} simd/jsimd_x86_64.c)
  else()
    set(JPEG_SOURCES ${JPEG_SOURCES} simd/jsimd_i386.c)
  endif()
  # This tells CMake that the "source" files haven't been generated yet
  set_source_files_properties(${SIMD_OBJS} PROPERTIES GENERATED 1)
else()
  set(JPEG_SOURCES ${JPEG_SOURCES} jsimd_none.c)
  message(STATUS "Not using SIMD acceleration")
endif()

if(WITH_JAVA)
  add_subdirectory(java)
  set(ENABLE_SHARED TRUE)
endif()

if(MSVC)
  # Build all configurations against shared C library
  foreach(var CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
    CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO)
    if(${var} MATCHES "/MT")
      string(REGEX REPLACE "/MT" "/MD" ${var} "${${var}}")
    endif()
  endforeach()
endif()

foreach(src ${JPEG_SOURCES})
  set(JPEG_SRCS ${JPEG_SRCS} ${SOURCE_PATH}/${src})
endforeach()

if(WITH_SIMD)
  # This tells CMake that the "source" files haven't been generated yet
  set_source_files_properties(${SIMD_OBJS} PROPERTIES GENERATED 1)
endif()

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})

if(WITH_MEM_SRCDST AND NOT WITH_JPEG8)
  add_library(jpeg-turbo SHARED ${JPEG_SRCS} ${SIMD_OBJS}
    ${SOURCE_PATH}/win/jpeg${DLL_VERSION}-memsrcdst.def)
else()
  add_library(jpeg-turbo SHARED ${JPEG_SRCS} ${SIMD_OBJS}
    ${SOURCE_PATH}/win/jpeg${DLL_VERSION}.def)
endif()
set_target_properties(jpeg-turbo PROPERTIES SOVERSION ${DLL_VERSION}
  VERSION ${FULLVERSION})
if(MSVC)
  set_target_properties(jpeg-turbo PROPERTIES SUFFIX ${DLL_VERSION}.dll)
elseif(MINGW OR CYGWIN)
  set_target_properties(jpeg-trubo PROPERTIES SUFFIX -${DLL_VERSION}.dll)
endif(MSVC)

