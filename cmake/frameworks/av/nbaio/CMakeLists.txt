project(NBAIO)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/nbaio/include.cmake)

# dependency
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/audio_utils/include.cmake)

set( NBAIO_DEPLIB
log
cutils
utils
binder
audioutils
)

if (MSVC)
    add_definitions(-D_ALLOW_KEYWORD_MACROS=1)
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/include/media/nbaio )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libnbaio )

# header files
file(GLOB NBAIO_HEADER_FILES  
${HEADER_PATH}/*.h
)

set(NBAIO_SOURCE_FILES
${SOURCE_PATH}/AudioBufferProviderSource.cpp   
${SOURCE_PATH}/AudioStreamOutSink.cpp          
${SOURCE_PATH}/AudioStreamInSource.cpp         
${SOURCE_PATH}/NBAIO.cpp                       
${SOURCE_PATH}/MonoPipe.cpp                    
${SOURCE_PATH}/MonoPipeReader.cpp              
${SOURCE_PATH}/Pipe.cpp                        
${SOURCE_PATH}/PipeReader.cpp                  
${SOURCE_PATH}/SourceAudioBufferProvider.cpp
${SOURCE_PATH}/NBLog.cpp
)

if(MSVC)
    include_directories(AFTER ${MSVC_PATH})

    list(APPEND NBAIO_HEADER_FILES
    ${MSVC_PATH}/sys/time.h
    )
    list(APPEND NBAIO_SOURCE_FILES
    ${MSVC_PATH}/sys/time.c
    )    
endif(MSVC)

# target files
set(LIB_NAME nbaio)
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${LIB_NAME} SHARED ${NBAIO_SOURCE_FILES} ${NBAIO_HEADER_FILES})
target_link_libraries(${LIB_NAME} ${NBAIO_DEPLIB})
