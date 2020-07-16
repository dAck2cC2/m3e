project(AUDIOFLINGER)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/nbaio/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/audiohal/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/audioprocessing/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/audioclient/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/media/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/effects/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/mediametrics/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/nblog/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/audio_utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/sonic/include.cmake)

set( ${PROJECT_NAME}_DEPLIB
log
cutils
utils
hardware
binder
audioutils
audiospdif
audioclient
audiohal
audioprocessing
nbaio
media
mediautils
medialogservice
effects
sonic
)

if (MSVC)
    add_definitions(-DNOMINMAX=1)
    add_definitions(-D__unused= )
    add_definitions(-Dmemalign=_aligned_malloc)

    include(${M3E_SOURCE_DIR}/cmake/core/msvc/include.cmake)
    list(APPEND ${PROJECT_NAME}_DEPLIB ${LIB_MSVC_WRAP})
elseif(LINUX)
    add_definitions(-D__unused= )
endif()

add_definitions(-DSTATE_QUEUE_INSTANTIATIONS=\"StateQueueInstantiations.cpp\")

include_directories(AFTER ${M3E_SOURCE_DIR}/src/system/media/audio_effects/include)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/services/audioflinger )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/services/audioflinger )

include_directories(AFTER ${HEADER_PATH})

# header files
file(GLOB AUDIOFLINGER_HEADER_FILES  
${HEADER_PATH}/*.h
)

set(AUDIOFLINGER_SOURCE_FILES
# libserviceutility
${SOURCE_PATH}/ServiceUtilities.cpp

# libaudioflinger
${SOURCE_PATH}/AudioFlinger.cpp            
${SOURCE_PATH}/Threads.cpp                 
${SOURCE_PATH}/Tracks.cpp                  
${SOURCE_PATH}/AudioHwDevice.cpp           
${SOURCE_PATH}/AudioStreamOut.cpp          
#${SOURCE_PATH}/SpdifStreamOut.cpp          
${SOURCE_PATH}/Effects.cpp                       
${SOURCE_PATH}/PatchPanel.cpp              
${SOURCE_PATH}/StateQueue.cpp
${SOURCE_PATH}/BufLog.cpp
${SOURCE_PATH}/TypedLogger.cpp

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

${SOURCE_PATH}/main_audioflinger.cpp
)

# target files
set(LIB_NAME audioflinger_default)
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${LIB_NAME} SHARED ${AUDIOFLINGER_SOURCE_FILES} ${AUDIOFLINGER_HEADER_FILES})
target_link_libraries(${LIB_NAME} ${${PROJECT_NAME}_DEPLIB})
