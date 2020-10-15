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

include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/audioclient/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/system/fmq/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/hidl/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/interfaces/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/media/include.cmake)

set(${PROJECT_NAME}_DEPLIB
log
cutils
utils
audioutils
hardware
)

# let's just use version 2.0 for now
set(ENABLE_AUDIOHAL_2_0  TRUE)
set(ENABLE_AUDIOHAL_4_0  FALSE)

if (MSVC)
    add_definitions(-DNOMINMAX=1)
    add_definitions(-D__unused= )
    add_definitions(-D_ALLOW_KEYWORD_MACROS=1)

    include(${MSVC_INCLUDE})
    list(APPEND ${PROJECT_NAME}_DEPLIB ${LIB_MSVC_WRAP})
endif()

add_definitions(-DUSE_LEGACY_LOCAL_AUDIO_HAL=1)

list(APPEND ${PROJECT_NAME}_DEPLIB
effects
media
mediautils
fmq
)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libaudiohal/include/media/audiohal )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libaudiohal )

#include_directories(AFTER ${HEADER_PATH})
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/av/media/libaudiohal/2.0)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/av/media/libaudiohal/4.0/include)

###############################################################################
# libaudiohal
file(GLOB AUDIOHAL_SOURCE_FILES 
${HEADER_PATH}/*.h 
${HEADER_PATH}/hidl/*.h 
)
list(APPEND AUDIOHAL_SOURCE_FILES
${SOURCE_PATH}/DevicesFactoryHalInterface.cpp
${SOURCE_PATH}/EffectsFactoryHalInterface.cpp
${SOURCE_PATH}/HalDeathHandlerHidl.cpp
)
source_group(audiohal FILES ${AUDIOHAL_SOURCE_FILES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${AUDIOHAL_SOURCE_FILES})

###############################################################################
# libaudiohal/2.0
if (ENABLE_AUDIOHAL_2_0)
    add_definitions(-DENABLE_AUDIOHAL_2_0=1)

    set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libaudiohal/2.0 )
    file(GLOB AUDIOHAL_2_0_SOURCE_FILES 
    ${SOURCE_PATH}/*.h 
    )
    list(APPEND AUDIOHAL_2_0_SOURCE_FILES
    ${SOURCE_PATH}/DeviceHalLocal.cpp 
    ${SOURCE_PATH}/DevicesFactoryHalHybrid.cpp 
    ${SOURCE_PATH}/DevicesFactoryHalLocal.cpp 
    ${SOURCE_PATH}/StreamHalLocal.cpp 

    ${SOURCE_PATH}/ConversionHelperHidl.cpp 
    ${SOURCE_PATH}/DeviceHalHidl.cpp 
    ${SOURCE_PATH}/DevicesFactoryHalHidl.cpp 
    ${SOURCE_PATH}/EffectBufferHalHidl.cpp 
    ${SOURCE_PATH}/EffectHalHidl.cpp 
    ${SOURCE_PATH}/EffectsFactoryHalHidl.cpp 
    ${SOURCE_PATH}/StreamHalHidl.cpp 
    )
    source_group(audiohal2.0 FILES ${AUDIOHAL_2_0_SOURCE_FILES})
    list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${AUDIOHAL_2_0_SOURCE_FILES})
endif(ENABLE_AUDIOHAL_2_0)

###############################################################################
# libaudiohal/4.0
if (ENABLE_AUDIOHAL_4_0)
    add_definitions(-DENABLE_AUDIOHAL_4_0=1)

    if(APPLE)
        set(CMAKE_CXX_FLAGS "-std=c++1z -stdlib=libc++" ${CMAKE_CXX_FLAGS})
    endif()

    set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libaudiohal/4.0 )
    file(GLOB AUDIOHAL_4_0_SOURCE_FILES 
    ${SOURCE_PATH}/include/libaudiohal/4.0/*.h 
    )
    list(APPEND AUDIOHAL_4_0_SOURCE_FILES
    ${SOURCE_PATH}/DeviceHalLocal.cpp 
    ${SOURCE_PATH}/DevicesFactoryHalHybrid.cpp 
    ${SOURCE_PATH}/DevicesFactoryHalLocal.cpp 
    ${SOURCE_PATH}/StreamHalLocal.cpp 

    ${SOURCE_PATH}/ConversionHelperHidl.cpp 
    ${SOURCE_PATH}/DeviceHalHidl.cpp 
    ${SOURCE_PATH}/DevicesFactoryHalHidl.cpp 
    ${SOURCE_PATH}/EffectBufferHalHidl.cpp 
    ${SOURCE_PATH}/EffectHalHidl.cpp 
    ${SOURCE_PATH}/EffectsFactoryHalHidl.cpp 
    ${SOURCE_PATH}/StreamHalHidl.cpp 
    )
    source_group(audiohal4.0 FILES ${AUDIOHAL_4_0_SOURCE_FILES})
    list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${AUDIOHAL_4_0_SOURCE_FILES})
endif(ENABLE_AUDIOHAL_4_0)

###############################################################################
# target files
set(LIB_TYPE SHARED)
ADD_LIB(audiohal)
