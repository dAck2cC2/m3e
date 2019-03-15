
project(AUDIOFLINGER)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/audioclient/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/audioprocessing/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/media/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/effects/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/soundtrigger/include.cmake)

set( ${PROJECT_NAME}_DEPLIB
log
cutils
utils
binder
audioclient
media
soundtrigger
)

if (MSVC)
    add_definitions(-DNOMINMAX=1)
    add_definitions(-D__unused= )
    add_definitions(-Dstrlcpy=strncpy)
    #add_definitions(-Dmemalign=_aligned_malloc)
elseif(APPLE)
    set(CMAKE_CXX_FLAGS "-std=c++1z -stdlib=libc++" ${CMAKE_CXX_FLAGS})  
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/services/audiopolicy )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/services/audiopolicy )

include_directories(AFTER ${HEADER_PATH})
include_directories(AFTER ${M3E_SOURCE_DIR}/src/system/media/audio/include)

###############################################################################
#  utilities
###############################################################################
include_directories(AFTER ${SOURCE_PATH}/utilities)

###############################################################################
#  common
###############################################################################
set(${PROJECT_NAME}_COMMON_PATH ${SOURCE_PATH}/common/managerdefinitions/src)

include_directories(AFTER ${SOURCE_PATH}/common)
include_directories(AFTER ${SOURCE_PATH}/common/include)
include_directories(AFTER ${SOURCE_PATH}/common/managerdefinitions/include)
file(GLOB ${PROJECT_NAME}_COMMON   
${SOURCE_PATH}/common/include/*.h
${SOURCE_PATH}/common/managerdefinitions/include/*.h
)
list(APPEND ${PROJECT_NAME}_COMMON 
${${PROJECT_NAME}_COMMON_PATH}/DeviceDescriptor.cpp 
${${PROJECT_NAME}_COMMON_PATH}/AudioGain.cpp 
${${PROJECT_NAME}_COMMON_PATH}/HwModule.cpp 
${${PROJECT_NAME}_COMMON_PATH}/IOProfile.cpp 
${${PROJECT_NAME}_COMMON_PATH}/AudioPort.cpp 
${${PROJECT_NAME}_COMMON_PATH}/AudioProfile.cpp 
${${PROJECT_NAME}_COMMON_PATH}/AudioRoute.cpp 
${${PROJECT_NAME}_COMMON_PATH}/AudioPolicyMix.cpp 
${${PROJECT_NAME}_COMMON_PATH}/AudioPatch.cpp 
${${PROJECT_NAME}_COMMON_PATH}/AudioInputDescriptor.cpp 
${${PROJECT_NAME}_COMMON_PATH}/AudioOutputDescriptor.cpp 
${${PROJECT_NAME}_COMMON_PATH}/AudioCollections.cpp 
${${PROJECT_NAME}_COMMON_PATH}/EffectDescriptor.cpp 
${${PROJECT_NAME}_COMMON_PATH}/SoundTriggerSession.cpp 
${${PROJECT_NAME}_COMMON_PATH}/SessionRoute.cpp 
${${PROJECT_NAME}_COMMON_PATH}/AudioSourceDescriptor.cpp 
${${PROJECT_NAME}_COMMON_PATH}/VolumeCurve.cpp 
${${PROJECT_NAME}_COMMON_PATH}/TypeConverter.cpp 
${${PROJECT_NAME}_COMMON_PATH}/AudioSession.cpp
${${PROJECT_NAME}_COMMON_PATH}/ConfigParsingUtils.cpp 
${${PROJECT_NAME}_COMMON_PATH}/StreamDescriptor.cpp 
${${PROJECT_NAME}_COMMON_PATH}/Gains.cpp
)
source_group(Common FILES ${${PROJECT_NAME}_COMMON})

list(APPEND ${PROJECT_NAME}_SOURCE_FILES
${${PROJECT_NAME}_COMMON}
)

###############################################################################
#  service
###############################################################################
set(${PROJECT_NAME}_SERVICE_PATH ${SOURCE_PATH}/service)

include_directories(AFTER ${M3E_SOURCE_DIR}/src/system/media/audio_effects/include)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/av/services/audioflinger)
include_directories(AFTER ${${PROJECT_NAME}_SERVICE_PATH})
file(GLOB ${PROJECT_NAME}_SERVICE   
${${PROJECT_NAME}_SERVICE_PATH}/*.h
)
list(APPEND ${PROJECT_NAME}_SERVICE
${${PROJECT_NAME}_SERVICE_PATH}/AudioPolicyService.cpp
${${PROJECT_NAME}_SERVICE_PATH}/AudioPolicyEffects.cpp
${${PROJECT_NAME}_SERVICE_PATH}/AudioPolicyInterfaceImpl.cpp
${${PROJECT_NAME}_SERVICE_PATH}/AudioPolicyClientImpl.cpp
#${${PROJECT_NAME}_SERVICE_PATH}/AudioPolicyInterfaceImplLegacy.cpp
#${${PROJECT_NAME}_SERVICE_PATH}/AudioPolicyClientImplLegacy.cpp
)
if(MSVC)
    list(APPEND ${PROJECT_NAME}_SERVICE
    ${MSVC_PATH}/sys/time.h
    ${MSVC_PATH}/sys/time.c
    ${M3E_SOURCE_DIR}/src/frameworks/av/services/audioflinger/ServiceUtilities.h 
    ${M3E_SOURCE_DIR}/src/frameworks/av/services/audioflinger/ServiceUtilities.cpp
    )
else()
    list(APPEND ${PROJECT_NAME}_DEPLIB 
    audioflinger_default
    )
endif()
list(APPEND ${PROJECT_NAME}_SERVICE
${SOURCE_PATH}/main_audiopolicyservice.cpp
)
source_group(Service FILES ${${PROJECT_NAME}_SERVICE})

list(APPEND ${PROJECT_NAME}_SOURCE_FILES
${${PROJECT_NAME}_SERVICE}
)

#add_definitions(-DUSE_LEGACY_AUDIO_POLICY=1)


###############################################################################
#  engine
###############################################################################
set(${PROJECT_NAME}_ENGINE_PATH ${SOURCE_PATH}/enginedefault)

include_directories(AFTER ${SOURCE_PATH}/engine/interface)
include_directories(AFTER ${${PROJECT_NAME}_ENGINE_PATH}/include)
file(GLOB ${PROJECT_NAME}_ENGINE   
${${PROJECT_NAME}_ENGINE_PATH}/include/*.h
${${PROJECT_NAME}_ENGINE_PATH}/src/*.h
)
list(APPEND ${PROJECT_NAME}_ENGINE
${${PROJECT_NAME}_ENGINE_PATH}/src/Engine.cpp
${${PROJECT_NAME}_ENGINE_PATH}/src/EngineInstance.cpp
)
source_group(Engine FILES ${${PROJECT_NAME}_ENGINE})

list(APPEND ${PROJECT_NAME}_SOURCE_FILES
${${PROJECT_NAME}_ENGINE}
)

###############################################################################
#  manager
###############################################################################
include_directories(AFTER ${SOURCE_PATH}/managerdefault)

file(GLOB ${PROJECT_NAME}_MANAGER   
${SOURCE_PATH}/managerdefault/*.h
)
list(APPEND ${PROJECT_NAME}_MANAGER
${SOURCE_PATH}/managerdefault/AudioPolicyManager.cpp
${SOURCE_PATH}/manager/AudioPolicyFactory.cpp
)
source_group(Manager FILES ${${PROJECT_NAME}_MANAGER})

list(APPEND ${PROJECT_NAME}_SOURCE_FILES
${${PROJECT_NAME}_MANAGER}
)


# target files
set(LIB_NAME audiopolicy_default)
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${LIB_NAME} SHARED ${${PROJECT_NAME}_SOURCE_FILES})
target_link_libraries(${LIB_NAME} ${${PROJECT_NAME}_DEPLIB})
