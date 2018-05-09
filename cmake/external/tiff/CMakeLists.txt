
project(TIFF)

if(NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH}/libtiff)
    message(STATUS "Download\t libtiff")
    exec_program("git clone https://gitlab.com/libtiff/libtiff.git" ${M3E_SOURCE_DIR}/${EXT_PATH})
    exec_program("git checkout Release-v4-0-9" ${M3E_SOURCE_DIR}/${EXT_PATH}/libtiff)
endif()

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/tiff/include.cmake)

# CMake build for libtiff
# Run "cmake" to generate the build files for your platform
#
# Copyright © 2015 Open Microscopy Environment / University of Dundee
# Written by Roger Leigh <rleigh@codelibre.net>

cmake_minimum_required(VERSION 2.8.9)

# Default policy is from 2.8.9
cmake_policy(VERSION 2.8.9)
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

