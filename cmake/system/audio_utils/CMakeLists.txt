
project(AUDIO_UTILS)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/audio_utils/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)

include_directories(AFTER ${M3E_SOURCE_DIR}/src/system/media/audio/include)

set(AUDIO_UTILS_DEPLIB
log
)

add_definitions(-Dtypeof=decltype)
if (MSVC)
    add_definitions(-D__unused= )
    add_definitions(-D_USE_MATH_DEFINES=1)
endif(MSVC)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/system/media/audio_utils/include/ )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/system/media/audio_utils/ )

# header files
file(GLOB AUDIO_UTILS_HEADER_FILES
${HEADER_PATH}/*.h
${SOURCE_PATH}/*.h 
)

# source files
set(AUDIO_UTILS_SOURCE_FILES 
${SOURCE_PATH}/channels.c 
${SOURCE_PATH}/fifo.c 
${SOURCE_PATH}/format.c 
${SOURCE_PATH}/limiter.c 
${SOURCE_PATH}/minifloat.c 
${SOURCE_PATH}/primitives.c 
${SOURCE_PATH}/roundup.c
)

set_source_files_properties( ${AUDIO_UTILS_SOURCE_FILES} PROPERTIES LANGUAGE "CXX" )

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(audioutils ${LIB_TYPE} ${AUDIO_UTILS_SOURCE_FILES} ${AUDIO_UTILS_HEADER_FILES})
target_link_libraries(audioutils ${AUDIO_UTILS_DEPLIB})

