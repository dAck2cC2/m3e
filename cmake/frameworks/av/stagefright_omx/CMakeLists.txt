
project(STAGEFRIGHT_OMX)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright_omx/include.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright_foundation/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/ui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/gui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/EGL/include.cmake)

#include(${M3E_SOURCE_DIR}/cmake/av/stagefright/include.cmake)

set(${PROJECT_NAME}_DEPLIB
log
utils
binder
media
stagefright_foundation
)

add_definitions(-Dtypeof=decltype)
if(MSVC)
    add_definitions(-Dstrcasecmp=_stricmp)
endif()

# include files
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/native/include/media/openmax)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/native/include/media/hardware)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/omx )

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES 
${SOURCE_PATH}/*.h 
${HEADER_PATH}/OMX.h
${M3E_SOURCE_DIR}/src/frameworks/native/include/media/hardware/HardwareAPI.h
)

# source files
#file(GLOB ${PROJECT_NAME}_SOURCE_FILES 
#${SOURCE_PATH}/*.cpp
#)
set(${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/OMX.cpp
${SOURCE_PATH}/OMXNodeInstance.cpp
${SOURCE_PATH}/GraphicBufferSource.cpp
${SOURCE_PATH}/FrameDropper.cpp
${SOURCE_PATH}/OMXUtils.cpp
${SOURCE_PATH}/OMXMaster.cpp
${SOURCE_PATH}/SoftOMXPlugin.cpp
${SOURCE_PATH}/SoftOMXComponent.cpp
)

if(MSVC)
    include_directories(AFTER ${MSVC_PATH})

    list(APPEND ${PROJECT_NAME}_HEADER_FILES
    ${MSVC_PATH}/unistd.h
    ${MSVC_PATH}/dlfcn.h
    ${MSVC_PATH}/sys/time.h
    )
    list(APPEND ${PROJECT_NAME}_SOURCE_FILES
    ${MSVC_PATH}/sys/time.c
    )    
endif(MSVC)

# target files
set(LIB_TYPE SHARED)
ADD_LIB(stagefright_omx)
