
project(SYNC)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/sync/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/system/core/libsync/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/system/core/libsync/ )

add_definitions(-D__u8=uint8_t)
add_definitions(-D__u32=uint32_t)
add_definitions(-D__s32=int32_t)

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES  
${HEADER_PATH}/sync/*.h
${HEADER_PATH}/android/*.h
${HEADER_PATH}/ndk/*.h
${SOURCE_PATH}/*.h
)

# source files
set(${PROJECT_NAME}_SOURCE_FILES  
${SOURCE_PATH}/sync.c)

# target files
ADD_SHARED_LIB(sync)
