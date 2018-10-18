
# addtional package on Mac OSX for this cmake.
# brew install pkgconfig

project(ASSIMP)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

if(NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH}/assimp)
  message(STATUS "Download\t assimp")
  exec_program("git clone https://github.com/assimp/assimp.git" ${M3E_SOURCE_DIR}/${EXT_PATH})
  #exec_program("git reset --hard a9d70b2dbc620c52d6cbda53066c330e0c83125a" ${M3E_SOURCE_DIR}/${EXT_PATH}/assimp)
  exec_program("git checkout v4.1.0" ${M3E_SOURCE_DIR}/${EXT_PATH}/assimp)
endif()

# All supported options ###############################################
OPTION( BUILD_SHARED_LIBS
  "Build package with shared libraries."
  ON
)
OPTION( ASSIMP_DOUBLE_PRECISION
  "Set to ON to enable double precision processing"
  OFF
)
OPTION ( ASSIMP_COVERALLS
  "Enable this to measure test coverage."
  OFF
)
OPTION ( ASSIMP_WERROR
  "Treat warnings as errors."
  OFF
)
OPTION ( ASSIMP_ASAN
  "Enable AddressSanitizer."
  OFF
)
OPTION ( ASSIMP_UBSAN
  "Enable Undefined Behavior sanitizer."
  OFF
)
OPTION ( SYSTEM_IRRXML
  "Use system installed Irrlicht/IrrXML library."
  OFF
)
OPTION( ASSIMP_BUILD_ZLIB
  "Build your own zlib"
  OFF
)
OPTION( ASSIMP_NO_EXPORT
  "Disable Assimp's export functionality."
  NO
)


# Use subset of Windows.h
if (WIN32)
  ADD_DEFINITIONS( -DWIN32_LEAN_AND_MEAN )
endif()

IF(MSVC)
  SET (CMAKE_PREFIX_PATH ".\\assimp\\devil")
  OPTION( ASSIMP_INSTALL_PDB
    "Install MSVC debug files."
    ON
  )
ENDIF(MSVC)

IF(NOT BUILD_SHARED_LIBS)
  MESSAGE(STATUS "Shared libraries disabled")
  SET(LINK_SEARCH_START_STATIC TRUE)
ELSE()
  MESSAGE(STATUS "Shared libraries enabled")
ENDIF(NOT BUILD_SHARED_LIBS)

# Define here the needed parameters
SET (ASSIMP_VERSION_MAJOR 4)
SET (ASSIMP_VERSION_MINOR 1)
SET (ASSIMP_VERSION_PATCH 0)
SET (ASSIMP_VERSION ${ASSIMP_VERSION_MAJOR}.${ASSIMP_VERSION_MINOR}.${ASSIMP_VERSION_PATCH})
SET (ASSIMP_SOVERSION 4)
SET (PROJECT_VERSION "${ASSIMP_VERSION}")

SET( ASSIMP_PACKAGE_VERSION "0" CACHE STRING "the package-specific version used for uploading the sources" )

# Needed for openddl_parser config, no use of c++11 at this moment
ADD_DEFINITIONS( -DOPENDDL_NO_USE_CPP11 )
set_property( GLOBAL PROPERTY CXX_STANDARD 11 )


# Get the current working branch
EXECUTE_PROCESS(
  COMMAND git rev-parse --abbrev-ref HEAD
  WORKING_DIRECTORY ${M3E_SOURCE_DIR}/${EXT_PATH}/assimp
  OUTPUT_VARIABLE GIT_BRANCH
  OUTPUT_STRIP_TRAILING_WHITESPACE
  ERROR_QUIET
)

# Get the latest abbreviated commit hash of the working branch
EXECUTE_PROCESS(
  COMMAND git log -1 --format=%h
  WORKING_DIRECTORY ${M3E_SOURCE_DIR}/${EXT_PATH}/assimp
  OUTPUT_VARIABLE GIT_COMMIT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE
  ERROR_QUIET
)

IF(NOT GIT_COMMIT_HASH)
    SET(GIT_COMMIT_HASH 0)
ENDIF(NOT GIT_COMMIT_HASH)

IF(ASSIMP_DOUBLE_PRECISION)
    ADD_DEFINITIONS(-DASSIMP_DOUBLE_PRECISION)
ENDIF(ASSIMP_DOUBLE_PRECISION)

CONFIGURE_FILE(
    ${M3E_SOURCE_DIR}/${EXT_PATH}/assimp/revision.h.in
    ${CMAKE_BINARY_DIR}/assimp/revision.h
)

CONFIGURE_FILE(
    ${M3E_SOURCE_DIR}/${EXT_PATH}/assimp/include/assimp/config.h.in
    ${CMAKE_BINARY_DIR}/assimp/include/assimp/config.h
)

INCLUDE_DIRECTORIES(
    ${M3E_SOURCE_DIR}/${EXT_PATH}/assimp
	${M3E_SOURCE_DIR}/${EXT_PATH}/assimp/include
    ${CMAKE_BINARY_DIR}/assimp
    ${CMAKE_BINARY_DIR}/assimp/include
)

LIST(APPEND CMAKE_MODULE_PATH "${M3E_SOURCE_DIR}/${EXT_PATH}/assimp/cmake-modules" )

IF( UNIX )
  # Ensure that we do not run into issues like http://www.tcm.phy.cam.ac.uk/sw/inodes64.html on 32 bit linux
  IF( ${OPERATING_SYSTEM} MATCHES "Android")
  ELSE()
    IF ( CMAKE_SIZEOF_VOID_P EQUAL 4) # only necessary for 32-bit linux
      #ADD_DEFINITIONS(-D_FILE_OFFSET_BITS=64 )
    ENDIF()
  ENDIF()

  # Use GNUInstallDirs for Unix predefined directories
  INCLUDE(GNUInstallDirs)
ENDIF( UNIX )

# Grouped compiler settings
IF ((CMAKE_C_COMPILER_ID MATCHES "GNU") AND NOT CMAKE_COMPILER_IS_MINGW)
  # hide all not-exported symbols
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fvisibility=hidden -fPIC -Wall -std=c++0x")
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
  SET(LIBSTDC++_LIBRARIES -lstdc++)
ELSEIF(MSVC)
  # enable multi-core compilation with MSVC
  add_compile_options(/MP)
  if("${CMAKE_GENERATOR}" MATCHES "(Win64|IA64)")
    add_compile_options( /bigobj )
  endif()
  # disable "elements of array '' will be default initialized" warning on MSVC2013
  IF(MSVC12)
    add_compile_options(/wd4351)
  ENDIF()
ELSEIF ( "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" )
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fvisibility=hidden -fPIC -Wall -Wno-long-long -std=c++11" )
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
ELSEIF( CMAKE_COMPILER_IS_MINGW )
  SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -Wall -Wno-long-long -std=c++11" )
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
  ADD_DEFINITIONS( -U__STRICT_ANSI__ )
ENDIF()

if (ASSIMP_COVERALLS)
    MESSAGE(STATUS "Coveralls enabled")
    INCLUDE(Coveralls)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
endif()

if (ASSIMP_WERROR)
  MESSAGE(STATUS "Treating warnings as errors")
  IF (MSVC)
    add_compile_options(/WX)
  ELSE()
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror")
  ENDIF()
endif()

if (ASSIMP_ASAN)
    MESSAGE(STATUS "AddressSanitizer enabled")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")
endif()

if (ASSIMP_UBSAN)
    MESSAGE(STATUS "Undefined Behavior sanitizer enabled")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined -fno-sanitize-recover=all")
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=undefined -fno-sanitize-recover=all")
endif()

INCLUDE (FindPkgMacros)
INCLUDE (PrecompiledHeader)

SET( ASSIMP_LIB_INSTALL_DIR ${BUILD_PATH} CACHE STRING
  "Path the built library files are installed to." )
SET( ASSIMP_BIN_INSTALL_DIR ${BUILD_PATH} CACHE STRING
  "Path the tool executables are installed to." )

SET(LIBASSIMP_COMPONENT     "libassimp${ASSIMP_VERSION_MAJOR}.${ASSIMP_VERSION_MINOR}.${ASSIMP_VERSION_PATCH}" )
SET(LIBASSIMP-DEV_COMPONENT "libassimp${ASSIMP_VERSION_MAJOR}.${ASSIMP_VERSION_MINOR}.${ASSIMP_VERSION_PATCH}-dev" )


# cmake configuration files
CONFIGURE_FILE("${M3E_SOURCE_DIR}/${EXT_PATH}/assimp/assimp-config.cmake.in"         "${CMAKE_BINARY_DIR}/assimp/assimp-config.cmake" @ONLY IMMEDIATE)
CONFIGURE_FILE("${M3E_SOURCE_DIR}/${EXT_PATH}/assimp/assimp-config-version.cmake.in" "${CMAKE_BINARY_DIR}/assimp/assimp-config-version.cmake" @ONLY IMMEDIATE)
install(FILES "${CMAKE_BINARY_DIR}/assimp/assimp-config.cmake"             "${CMAKE_BINARY_DIR}/assimp/assimp-config-version.cmake" DESTINATION "${ASSIMP_LIB_INSTALL_DIR}/cmake/assimp-${ASSIMP_VERSION_MAJOR}.${ASSIMP_VERSION_MINOR}" COMPONENT ${LIBASSIMP-DEV_COMPONENT})

FIND_PACKAGE( DirectX )

# Look for system installed irrXML
IF ( SYSTEM_IRRXML )
    find_package( IrrXML REQUIRED )
ENDIF( SYSTEM_IRRXML )

# Search for external dependencies, and build them from source if not found
# Search for zlib
IF ( NOT ASSIMP_BUILD_ZLIB )
    find_package(ZLIB)
ENDIF( NOT ASSIMP_BUILD_ZLIB )

IF( NOT ZLIB_FOUND )
  message(STATUS "compiling zlib from souces")
  INCLUDE(CheckIncludeFile)
  INCLUDE(CheckTypeSize)
  INCLUDE(CheckFunctionExists)
  # compile from sources
  add_subdirectory(zlib)
  SET(ZLIB_FOUND 1)
  SET(ZLIB_LIBRARIES zlibstatic)
  SET(ZLIB_INCLUDE_DIR ${M3E_SOURCE_DIR}/${EXT_PATH}/assimp/contrib/zlib ${CMAKE_BINARY_DIR}/zlib)
else(NOT ZLIB_FOUND)
  ADD_DEFINITIONS(-DASSIMP_BUILD_NO_OWN_ZLIB)
  SET(ZLIB_LIBRARIES_LINKED -lz)
ENDIF(NOT ZLIB_FOUND)
INCLUDE_DIRECTORIES(${ZLIB_INCLUDE_DIR})

# Search for unzip
use_pkgconfig(UNZIP minizip)

IF ( ASSIMP_NO_EXPORT )
  ADD_DEFINITIONS( -DASSIMP_BUILD_NO_EXPORT)
  MESSAGE( STATUS "Build an import-only version of Assimp." )
ENDIF( ASSIMP_NO_EXPORT )

SET ( ASSIMP_BUILD_ARCHITECTURE "" CACHE STRING
  "describe the current architecture."
)
IF    ( ASSIMP_BUILD_ARCHITECTURE STREQUAL "")
ELSE  ( ASSIMP_BUILD_ARCHITECTURE STREQUAL "")
  ADD_DEFINITIONS ( -D'ASSIMP_BUILD_ARCHITECTURE="${ASSIMP_BUILD_ARCHITECTURE}"' )
ENDIF ( ASSIMP_BUILD_ARCHITECTURE STREQUAL "")

# ${CMAKE_GENERATOR}
SET ( ASSIMP_BUILD_COMPILER "" CACHE STRING
  "describe the current compiler."
)
IF    ( ASSIMP_BUILD_COMPILER STREQUAL "")
ELSE  ( ASSIMP_BUILD_COMPILER STREQUAL "")
  ADD_DEFINITIONS ( -D'ASSIMP_BUILD_COMPILER="${ASSIMP_BUILD_COMPILER}"' )
ENDIF ( ASSIMP_BUILD_COMPILER STREQUAL "")

MARK_AS_ADVANCED ( ASSIMP_BUILD_ARCHITECTURE ASSIMP_BUILD_COMPILER )

ADD_DEFINITIONS( -DASSIMP_BUILD_NO_C4D_IMPORTER )

# Compile internal irrXML only if system is not requested
if( NOT SYSTEM_IRRXML )
    add_subdirectory(irrXML)
endif( NOT SYSTEM_IRRXML )

ADD_SUBDIRECTORY( code )

if(ENABLE_TEST)
    add_subdirectory(test)
endif(ENABLE_TEST)
