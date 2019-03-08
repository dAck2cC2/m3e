project(AUDIOHAL)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/audiohal/include.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/audio_utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/effects/include.cmake)
#include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/audioclient/include.cmake)
#include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/media/include.cmake)

set(${PROJECT_NAME}_DEPLIB
log
cutils
utils
audioutils
hardware
)

if (MSVC)
    #add_definitions(-DNOMINMAX=1)
    #dd_definitions(-D__unused= )
    add_definitions(-D_ALLOW_KEYWORD_MACROS=1)

    #include(${M3E_SOURCE_DIR}/cmake/core/msvc/include.cmake)
    #list(APPEND ${PROJECT_NAME}_DEPLIB ${LIB_MSVC_WRAP})
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libaudiohal/include/media/audiohal )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libaudiohal )

#include_directories(AFTER ${HEADER_PATH})

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES 
${HEADER_PATH}/*.h 
${HEADER_PATH}/hidl/*.h 
)

set(${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/DeviceHalLocal.cpp          
${SOURCE_PATH}/DevicesFactoryHalHybrid.cpp 
${SOURCE_PATH}/DevicesFactoryHalLocal.cpp  
${SOURCE_PATH}/StreamHalLocal.cpp
)


add_definitions(-DUSE_LEGACY_LOCAL_AUDIO_HAL=1)

list(APPEND ${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/EffectBufferHalLocal.cpp    
${SOURCE_PATH}/EffectsFactoryHalLocal.cpp  
${SOURCE_PATH}/EffectHalLocal.cpp
)

list(APPEND ${PROJECT_NAME}_DEPLIB
effects
)

# target files
set(LIB_TYPE SHARED)
ADD_LIB(audiohal)
