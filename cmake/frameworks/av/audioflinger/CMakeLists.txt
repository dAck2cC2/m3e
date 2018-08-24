project(AUDIOFLINGER)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/nbaio/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/mediautils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/effects/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/audio_utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/sonic/include.cmake)

set( AUDIOFLINGER_DEPLIB
log
cutils
utils
hardware
binder
audioutils
audiospdif
nbaio
media
mediautils
effects
sonic
)

if (MSVC)
    add_definitions(-DNOMINMAX=1)
    add_definitions(-D__unused= )
    add_definitions(-Dmemalign=_aligned_malloc)
else(APPLE)
    #add_definitions(-D_LIBCPP_HAS_NO_ATOMIC_HEADER)
    #add_definitions(-D_LIBCPP_HAS_NO_THREADS)
    add_definitions(-D_STDATOMIC_HAVE_ATOMIC)
endif()

add_definitions(-DSTATE_QUEUE_INSTANTIATIONS=\"StateQueueInstantiations.cpp\")

include_directories(AFTER ${M3E_SOURCE_DIR}/src/system/media/audio_effects/include)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/services/audioflinger )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/services/audioflinger )

# header files
file(GLOB AUDIOFLINGER_HEADER_FILES  
${HEADER_PATH}/*.h
)

set(AUDIOFLINGER_SOURCE_FILES
${SOURCE_PATH}/ServiceUtilities.cpp
${SOURCE_PATH}/AudioFlinger.cpp            
${SOURCE_PATH}/Threads.cpp                 
${SOURCE_PATH}/Tracks.cpp                  
${SOURCE_PATH}/AudioHwDevice.cpp           
${SOURCE_PATH}/AudioStreamOut.cpp          
${SOURCE_PATH}/SpdifStreamOut.cpp          
${SOURCE_PATH}/Effects.cpp                 
${SOURCE_PATH}/AudioMixer.cpp          
${SOURCE_PATH}/BufferProviders.cpp         
${SOURCE_PATH}/PatchPanel.cpp              
${SOURCE_PATH}/StateQueue.cpp
${SOURCE_PATH}/AudioWatchdog.cpp        
${SOURCE_PATH}/FastCapture.cpp          
${SOURCE_PATH}/FastCaptureDumpState.cpp 
${SOURCE_PATH}/FastCaptureState.cpp     
${SOURCE_PATH}/FastMixer.cpp            
${SOURCE_PATH}/FastMixerDumpState.cpp   
${SOURCE_PATH}/FastMixerState.cpp       
${SOURCE_PATH}/FastThread.cpp           
${SOURCE_PATH}/FastThreadDumpState.cpp  
${SOURCE_PATH}/FastThreadState.cpp
${SOURCE_PATH}/AudioResampler.cpp
${SOURCE_PATH}/AudioResamplerCubic.cpp
${SOURCE_PATH}/AudioResamplerDyn.cpp
${SOURCE_PATH}/AudioResamplerSinc.cpp
${SOURCE_PATH}/main_audioflinger.cpp
)

if(MSVC)
    include_directories(AFTER ${MSVC_PATH})

    list(APPEND AUDIOFLINGER_HEADER_FILES
    ${MSVC_PATH}/sys/time.h
    )
    list(APPEND AUDIOFLINGER_SOURCE_FILES
    ${MSVC_PATH}/sys/time.c
    )    
endif(MSVC)

# target files
set(LIB_NAME audioflinger_default)
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${LIB_NAME} SHARED ${AUDIOFLINGER_SOURCE_FILES} ${AUDIOFLINGER_HEADER_FILES})
target_link_libraries(${LIB_NAME} ${AUDIOFLINGER_DEPLIB})
