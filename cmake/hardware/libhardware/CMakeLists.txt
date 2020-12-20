
project(HARDWARE)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)

set( ${PROJECT_NAME}_DEPLIB
cutils
utils
)

add_definitions(-D__ANDROID_RECOVERY__=1)

if(LINUX)
    list(APPEND ${PROJECT_NAME}_DEPLIB dl)
    
elseif(MSVC)
    add_definitions(-Dstrlcpy=strncpy)
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/hardware/libhardware/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/hardware/libhardware )

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES  ${HEADER_PATH}/hardware/*.h)

# source files
file(GLOB ${PROJECT_NAME}_SOURCE_FILES ${SOURCE_PATH}/*.c)

# target files
ADD_SHARED_LIB(hardware)

# sub module of audio
add_subdirectory(audio)  

# we are using hwcomposer2 since Android 9
#add_subdirectory(hwcomposer)
