# gtest program

project(TEST_ZIPARCHIVE)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/${EXT_PATH}/gtest/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/base/include.cmake)

# dependency

set(${PROJECT_NAME}_DEPLIB
gtest
log
cutils
utils
base
zlib
)

if (MSVC)
    include(${MSVC_INCLUDE})
    #list(APPEND ZIPARCHIVE_DEPLIB ${LIB_MSVC_WRAP})
elseif(APPLE)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -stdlib=libc++")
endif(MSVC)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/system/core/libziparchive/include/ )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/system/core/libziparchive/ )

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES
${HEADER_PATH}/*.h
)

# main source

set(${PROJECT_NAME}_SOURCE_FILES
#${GTEST_MAIN_CC}
)

# test file
list(APPEND ${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/zip_archive.cc
${SOURCE_PATH}/zip_archive_stream_entry.cc
${SOURCE_PATH}/zip_writer.cc
${SOURCE_PATH}/entry_name_utils_test.cc
${SOURCE_PATH}/zip_archive_test.cc
${SOURCE_PATH}/zip_writer_test.cc
)

# project
set(EXECUTABLE_OUTPUT_PATH ${BUILD_PATH})
add_executable(test_ziparchive ${${PROJECT_NAME}_SOURCE_FILES} ${${PROJECT_NAME}_HEADER_FILES})
target_link_libraries(test_ziparchive ${${PROJECT_NAME}_DEPLIB})
