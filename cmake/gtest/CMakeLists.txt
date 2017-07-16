
# gtest
project(GTEST)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/gtest/include.cmake)

include_directories(AFTER
${M3E_SOURCE_DIR}/${EXT_PATH}/gtest
${M3E_SOURCE_DIR}/${EXT_PATH}/gtest/include
)

file(GLOB LIBGTEST_HEADER_FILES
${M3E_SOURCE_DIR}/${EXT_PATH}/gtest/include/*.h
${M3E_SOURCE_DIR}/${EXT_PATH}/gtest/include/internal/*.h
)

set(LIBGTEST_SOURCE_FILES 
${M3E_SOURCE_DIR}/${EXT_PATH}/gtest/src/gtest-all.cc
)

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(gtest STATIC ${LIBGTEST_SOURCE_FILES} ${LIBGTEST_HEADER_FILES})
