
project(SOUNDTRIGGER)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/soundtrigger/include.cmake)

# dependency
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)

set( ${PROJECT_NAME}_DEPLIB
log
cutils
utils
binder
audioutils
)

if (MSVC)
    include(${M3E_SOURCE_DIR}/cmake/core/msvc/include.cmake)
    list(APPEND UTILS_DEPLIB ${LIB_MSVC_WRAP})
endif(MSVC)

if (MSVC OR LINUX)
    add_definitions(-D__unused= )
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/include/soundtrigger )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/soundtrigger )

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES  
${HEADER_PATH}/*.h
)

set(${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/SoundTrigger.cpp   
${SOURCE_PATH}/ISoundTrigger.cpp          
${SOURCE_PATH}/ISoundTriggerClient.cpp         
${SOURCE_PATH}/ISoundTriggerHwService.cpp                       
)

# target files
set(LIB_NAME soundtrigger)
set(LIB_TYPE SHARED)
ADD_LIB(${LIB_NAME})
