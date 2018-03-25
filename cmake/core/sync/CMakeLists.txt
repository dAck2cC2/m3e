
project(SYNC)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/sync/include.cmake)

add_definitions(-DANDROID_IMPLEMENTATION=1)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/system/core/libsync/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/system/core/libsync/ )

# header files
file(GLOB SYNC_HEADER_FILES  ${HEADER_PATH}/sync/*.h)

# source files
file(GLOB SYNC_SOURCE_FILES ${SOURCE_PATH}/*.c)

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(sync SHARED ${SYNC_SOURCE_FILES} ${SYNC_HEADER_FILES})
#target_link_libraries(sync ${SYNC_DEPLIB})
