
project(BINDER)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/native/binder/include.cmake)

add_definitions(-DANDROID_IMPLEMENTATION=1)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/native/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/native/binder )

# dependency
set(BINDER_DEPLIB
utils
)

# include files
#include_directories(AFTER ${M3E_SOURCE_DIR}/src/av/include)

# header files
file(GLOB BINDER_HEADER_FILES 
${HEADER_PATH}/binder/*.h
)

# source files
file(GLOB BINDER_SOURCE_FILES 
${SOURCE_PATH}/*.cpp
)

if (MSVC)
    list(APPEND BINDER_SOURCE_FILES
    ${M3E_SOURCE_DIR}/src/core/msvc/getpagesize.c
    )
endif (MSVC)

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(binder SHARED ${BINDER_SOURCE_FILES} ${BINDER_HEADER_FILES})
target_link_libraries(binder ${BINDER_DEPLIB})
