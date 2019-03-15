
project(AUDIO_UTILS)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/audio_utils/include.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)

include_directories(AFTER ${M3E_SOURCE_DIR}/src/system/media/audio/include)

set(AUDIO_UTILS_DEPLIB
log
)

if(APPLE)
    add_definitions(-Dtypeof=__typeof__)
elseif(MSVC)
    add_definitions(-Dtypeof=decltype)
    add_definitions(-D__unused= )
    add_definitions(-D_USE_MATH_DEFINES=1)
    add_definitions(-DNOMINMAX=1)
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/system/media/audio_utils/include/audio_utils )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/system/media/audio_utils/ )

# header files
file(GLOB AUDIO_UTILS_HEADER_FILES
${HEADER_PATH}/*.h
${SOURCE_PATH}/*.h 
)

# source files
set(AUDIO_UTILS_SOURCE_FILES 
${SOURCE_PATH}/channels.c 
${SOURCE_PATH}/ErrorLog.cpp 
${SOURCE_PATH}/fifo.cpp 
${SOURCE_PATH}/fifo_index.cpp 
${SOURCE_PATH}/fifo_writer32.cpp 
${SOURCE_PATH}/format.c 
${SOURCE_PATH}/limiter.c 
${SOURCE_PATH}/minifloat.c 
${SOURCE_PATH}/power.cpp
${SOURCE_PATH}/PowerLog.cpp
${SOURCE_PATH}/primitives.c 
${SOURCE_PATH}/roundup.c

${SOURCE_PATH}/mono_blend.cpp
)

set_source_files_properties( ${AUDIO_UTILS_SOURCE_FILES} PROPERTIES LANGUAGE "CXX" )

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(audioutils SHARED ${AUDIO_UTILS_SOURCE_FILES} ${AUDIO_UTILS_HEADER_FILES})
target_link_libraries(audioutils ${AUDIO_UTILS_DEPLIB})

###############################################################################
#  spdif
###############################################################################

# dependency

include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)

set(AUDIO_SPDIF_DEPLIB
log
)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/system/media/audio_utils/include/audio_utils/spdif )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/system/media/audio_utils/spdif )

# header files
file(GLOB AUDIO_SPDIF_HEADER_FILES
${HEADER_PATH}/*.h
${SOURCE_PATH}/*.h 
)

# source files
set(AUDIO_SPDIF_SOURCE_FILES 
${SOURCE_PATH}/BitFieldParser.cpp  
${SOURCE_PATH}/FrameScanner.cpp  
${SOURCE_PATH}/AC3FrameScanner.cpp  
${SOURCE_PATH}/DTSFrameScanner.cpp  
${SOURCE_PATH}/SPDIFEncoder.cpp
)

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(audiospdif SHARED ${AUDIO_SPDIF_SOURCE_FILES} ${AUDIO_SPDIF_HEADER_FILES})
target_link_libraries(audiospdif ${AUDIO_SPDIF_DEPLIB})
