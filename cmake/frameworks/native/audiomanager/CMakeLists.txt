
project(AUDIOMANAGER)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/audiomanager/include.cmake)

# dependency
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/media/include.cmake)

# for VolumeShaper.h which is included by IAudioTrack.h
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/av/include)

set(${PROJECT_NAME}_DEPLIB
log
utils
cutils
binder
)

if(MSVC)
    add_definitions(-DNOMINMAX=1)
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/include/audiomanager )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/services/audiomanager )

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES  
${HEADER_PATH}/*.h
)

# source files
set(${PROJECT_NAME}_SOURCE_FILES 
${SOURCE_PATH}/IPlayer.cpp
${SOURCE_PATH}/IAudioManager.cpp
)

# target files
#set(LIB_TYPE SHARED)
ADD_LIB(audiomanager)
