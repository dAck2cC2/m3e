project(AUDIOPROCESSING)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/audioprocessing/include.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/nbaio/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/audioclient/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/audiohal/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/media/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/audio_utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/sonic/include.cmake)

set(${PROJECT_NAME}_DEPLIB
log
cutils
utils
binder
audioutils
nbaio
sonic
audiohal
)

if (MSVC)
    add_definitions(-DNOMINMAX=1)
    add_definitions(-D__unused= )
    #add_definitions(-Dmemalign=_aligned_malloc)

    include(${M3E_SOURCE_DIR}/cmake/core/msvc/include.cmake)
    list(APPEND ${PROJECT_NAME}_DEPLIB ${LIB_MSVC_WRAP})

elseif(LINUX)
    add_definitions(-D__unused= )

endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libaudioprocessing/include/media )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libaudioprocessing )

#include_directories(AFTER ${HEADER_PATH})

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES 
${HEADER_PATH}/*.h 
)

set(${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/AudioMixer.cpp  
${SOURCE_PATH}/AudioResampler.cpp  
${SOURCE_PATH}/AudioResamplerCubic.cpp  
${SOURCE_PATH}/AudioResamplerSinc.cpp  
${SOURCE_PATH}/AudioResamplerDyn.cpp  
${SOURCE_PATH}/BufferProviders.cpp 
${SOURCE_PATH}/RecordBufferConverter.cpp 
)

# target files
set(LIB_TYPE SHARED)
ADD_LIB(audioprocessing)
