
# gtest
project(GTEST)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/gtest/include.cmake)

if(NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH}/googletest)
  message(STATUS "Download\t googletest")
  exec_program("git clone https://github.com/google/googletest.git" ${M3E_SOURCE_DIR}/${EXT_PATH})
  exec_program("git checkout release-1.10.0" ${M3E_SOURCE_DIR}/${EXT_PATH}/googletest)
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/googletest/googletest/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/googletest/googletest )

include_directories(AFTER
${HEADER_PATH}
${SOURCE_PATH}
)

file(GLOB LIBGTEST_HEADER_FILES
${HEADER_PATH}/gtest/*.h
${HEADER_PATH}/gtest/internal/*.h
)

set(LIBGTEST_SOURCE_FILES 
${SOURCE_PATH}/src/gtest-all.cc
)

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(gtest STATIC ${LIBGTEST_SOURCE_FILES} ${LIBGTEST_HEADER_FILES})
