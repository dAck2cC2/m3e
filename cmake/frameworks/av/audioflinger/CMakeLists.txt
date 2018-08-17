project(AUDIOFLINGER)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/audio_utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/sonic/include.cmake)

include_directories(AFTER ${M3E_SOURCE_DIR}/src/system/media/audio_effects/include)

# dependency
set( AUDIOFLINGER_DEPLIB
log
cutils
utils
binder
audioutils
)

add_definitions(-DANDROID_IMPLEMENTATION=1)
if (MSVC)
    add_definitions(-DNOMINMAX=1)
    add_definitions(-D__unused= )
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/services/audioflinger )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/services/audioflinger )

# header files
file(GLOB AUDIOFLINGER_HEADER_FILES  
${HEADER_PATH}/*.h
)

set(AUDIOFLINGER_SOURCE_FILES
${SOURCE_PATH}/AudioFlinger.cpp            
#${SOURCE_PATH}/Threads.cpp                 
${SOURCE_PATH}/Tracks.cpp                  
${SOURCE_PATH}/AudioHwDevice.cpp           
${SOURCE_PATH}/AudioStreamOut.cpp          
${SOURCE_PATH}/SpdifStreamOut.cpp          
${SOURCE_PATH}/Effects.cpp                 
#${SOURCE_PATH}/AudioMixer.cpp.arm          
${SOURCE_PATH}/BufferProviders.cpp         
${SOURCE_PATH}/PatchPanel.cpp              
${SOURCE_PATH}/StateQueue.cpp
)

# target files
set(LIB_NAME audioflinger)
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${LIB_NAME} SHARED ${AUDIOFLINGER_SOURCE_FILES} ${AUDIOFLINGER_HEADER_FILES})
target_link_libraries(${LIB_NAME} ${AUDIOFLINGER_DEPLIB})
