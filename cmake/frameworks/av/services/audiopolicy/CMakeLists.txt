
project(AUDIOFLINGER)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/include.cmake)


include_directories(AFTER ${M3E_SOURCE_DIR}/src/system/media/audio/include)

set( ${PROJECT_NAME}_DEPLIB
log
cutils
utils
)

if (MSVC)
    #add_definitions(-DNOMINMAX=1)
    add_definitions(-D__unused= )
    #add_definitions(-Dmemalign=_aligned_malloc)
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/services/audiopolicy )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/services/audiopolicy )

include_directories(AFTER ${HEADER_PATH})

###############################################################################
#  common
###############################################################################
set(${PROCJECT_NAME}_COMMON_PATH ${SOURCE_PATH}/common/managerdefinitions/src)

include_directories(AFTER ${SOURCE_PATH}/common/include)
include_directories(AFTER ${SOURCE_PATH}/common/managerdefinitions/include)
file(GLOB ${PROCJECT_NAME}_COMMON   
${SOURCE_PATH}/common/include/*.h
${SOURCE_PATH}/common/managerdefinitions/include/*.h
)
list(APPEND ${PROCJECT_NAME}_COMMON 
${${PROCJECT_NAME}_COMMON_PATH}/DeviceDescriptor.cpp 
${${PROCJECT_NAME}_COMMON_PATH}/AudioGain.cpp 
${${PROCJECT_NAME}_COMMON_PATH}/HwModule.cpp 
${${PROCJECT_NAME}_COMMON_PATH}/IOProfile.cpp 
${${PROCJECT_NAME}_COMMON_PATH}/AudioPort.cpp 
${${PROCJECT_NAME}_COMMON_PATH}/AudioProfile.cpp 
${${PROCJECT_NAME}_COMMON_PATH}/AudioRoute.cpp 
${${PROCJECT_NAME}_COMMON_PATH}/AudioPolicyMix.cpp 
${${PROCJECT_NAME}_COMMON_PATH}/AudioPatch.cpp 
${${PROCJECT_NAME}_COMMON_PATH}/AudioInputDescriptor.cpp 
${${PROCJECT_NAME}_COMMON_PATH}/AudioOutputDescriptor.cpp 
${${PROCJECT_NAME}_COMMON_PATH}/AudioCollections.cpp 
${${PROCJECT_NAME}_COMMON_PATH}/EffectDescriptor.cpp 
${${PROCJECT_NAME}_COMMON_PATH}/SoundTriggerSession.cpp 
${${PROCJECT_NAME}_COMMON_PATH}/SessionRoute.cpp 
${${PROCJECT_NAME}_COMMON_PATH}/AudioSourceDescriptor.cpp 
${${PROCJECT_NAME}_COMMON_PATH}/VolumeCurve.cpp 
${${PROCJECT_NAME}_COMMON_PATH}/TypeConverter.cpp 
${${PROCJECT_NAME}_COMMON_PATH}/AudioSession.cpp
${${PROCJECT_NAME}_COMMON_PATH}/ConfigParsingUtils.cpp 
${${PROCJECT_NAME}_COMMON_PATH}/StreamDescriptor.cpp 
${${PROCJECT_NAME}_COMMON_PATH}/Gains.cpp
)
source_group(Common FILES ${${PROCJECT_NAME}_COMMON})

list(APPEND ${PROJECT_NAME}_SOURCE_FILES
${${PROCJECT_NAME}_COMMON}
)





# target files
set(LIB_NAME audiopolicy_default)
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${LIB_NAME} SHARED ${${PROJECT_NAME}_SOURCE_FILES})
target_link_libraries(${LIB_NAME} ${${PROJECT_NAME}_DEPLIB})
