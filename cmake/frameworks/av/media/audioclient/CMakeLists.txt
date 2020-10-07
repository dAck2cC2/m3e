project(AUDIOCLIENT)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/audioclient/include.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/audiomanager/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/audioprocessing/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/media/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/nblog/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/mediametrics/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright_foundation/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/audio_utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)

# for private headers
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/av/include)

set(${PROJECT_NAME}_DEPLIB
log
cutils
utils
binder
audioutils
audiomanager
nblog
media
mediametrics
)

if(MSVC)
    add_definitions(-D__unused= )
    add_definitions(-Disnanf=isnan)
    add_definitions(-DNOMINMAX=1)

    include(${M3E_SOURCE_DIR}/cmake/core/msvc/include.cmake)
    list(APPEND ${PROJECT_NAME}_DEPLIB ${LIB_MSVC_WRAP})

elseif(APPLE)
    add_definitions(-Disnanf=isnan)

elseif(LINUX)
    add_definitions(-D__unused= )

endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libaudioclient/include/media )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libaudioclient )

include_directories(AFTER ${HEADER_PATH})

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES 
${HEADER_PATH}/*.h 
)

set(${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/AudioEffect.cpp 
${SOURCE_PATH}/AudioPolicy.cpp 
${SOURCE_PATH}/AudioRecord.cpp 
${SOURCE_PATH}/AudioSystem.cpp 
${SOURCE_PATH}/AudioTrack.cpp 
${SOURCE_PATH}/AudioTrackShared.cpp 
${SOURCE_PATH}/IAudioFlinger.cpp 
${SOURCE_PATH}/IAudioFlingerClient.cpp 
${SOURCE_PATH}/IAudioPolicyService.cpp 
${SOURCE_PATH}/IAudioPolicyServiceClient.cpp 
${SOURCE_PATH}/IAudioTrack.cpp 
${SOURCE_PATH}/IEffect.cpp 
${SOURCE_PATH}/IEffectClient.cpp 
${SOURCE_PATH}/ToneGenerator.cpp 
${SOURCE_PATH}/PlayerBase.cpp 
${SOURCE_PATH}/TrackPlayerBase.cpp 
)

# generate aidl cpp files
set(AIDL_MODULES
android/media/IAudioRecord.aidl
android/media/IPlayer.aidl
)
foreach(module ${AIDL_MODULES})
    ADD_AIDL_SOURCE(${module})
endforeach()

# target files
set(LIB_TYPE SHARED)
ADD_LIB(audioclient)
