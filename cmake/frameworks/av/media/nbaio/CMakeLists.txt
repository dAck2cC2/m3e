project(NBAIO)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/nbaio/include.cmake)

# dependency
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/audioclient/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/audiohal/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/media/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/audio_utils/include.cmake)

set( ${PROJECT_NAME}_DEPLIB
log
cutils
utils
binder
audioutils
)

if (MSVC)
    add_definitions(-D_ALLOW_KEYWORD_MACROS=1)
    add_definitions(-DNOMINMAX=1)

    include(${M3E_SOURCE_DIR}/cmake/core/msvc/include.cmake)
    list(APPEND ${PROJECT_NAME}_DEPLIB ${LIB_MSVC_WRAP})

elseif(APPLE)
    set(CMAKE_CXX_FLAGS "-std=c++1z -stdlib=libc++" ${CMAKE_CXX_FLAGS})  
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libnbaio/include/media/nbaio )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libnbaio )

# header files
file(GLOB NBAIO_HEADER_FILES  
${HEADER_PATH}/*.h
)

set(NBAIO_SOURCE_FILES
${SOURCE_PATH}/MonoPipe.cpp                    
${SOURCE_PATH}/MonoPipeReader.cpp  
${SOURCE_PATH}/NBAIO.cpp    

${SOURCE_PATH}/AudioBufferProviderSource.cpp   
${SOURCE_PATH}/AudioStreamInSource.cpp
${SOURCE_PATH}/AudioStreamOutSink.cpp   
${SOURCE_PATH}/NBLog.cpp          
${SOURCE_PATH}/PerformanceAnalysis.cpp          
${SOURCE_PATH}/Pipe.cpp       
${SOURCE_PATH}/PipeReader.cpp 
${SOURCE_PATH}/ReportPerformance.cpp       
${SOURCE_PATH}/SourceAudioBufferProvider.cpp
)

# target files
set(LIB_NAME nbaio)
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${LIB_NAME} SHARED ${NBAIO_SOURCE_FILES} ${NBAIO_HEADER_FILES})
target_link_libraries(${LIB_NAME} ${${PROJECT_NAME}_DEPLIB})
