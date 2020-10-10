
project(STAGEFRIGHT_OMX)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright_omx/include.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/vndksupport/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/hidl/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/interfaces/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/media/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright_foundation/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright/xmlparser/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright/bqhelper/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/frameworks/native/ui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/gui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/include.cmake)

#include(${M3E_SOURCE_DIR}/cmake/av/stagefright/include.cmake)

set(${PROJECT_NAME}_DEPLIB
log
utils
hidl
binder
media
stagefright_foundation
stagefright_xmlparser
stagefright_bufferqueue_helper
vndksupport
interfaces
)

if(MSVC)
    add_definitions(-Dstrcasecmp=_stricmp)

    include(${M3E_SOURCE_DIR}/cmake/core/msvc/include.cmake)
    list(APPEND ${PROJECT_NAME}_DEPLIB ${LIB_MSVC_WRAP})
elseif(APPLE)
    set(CMAKE_CXX_FLAGS "-std=c++1z -stdlib=libc++" ${CMAKE_CXX_FLAGS})  
endif()

# include files
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/native/headers/media_plugin/media/openmax)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/native/headers/media_plugin/media/hardware)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/av/media/libmedia/aidl)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/omx/include/media/stagefright/omx )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/omx )

include_directories(AFTER ${HEADER_PATH})

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES 
${HEADER_PATH}/*.h 
${M3E_SOURCE_DIR}/src/frameworks/native/include/media/hardware/HardwareAPI.h
)

# source files
set(${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/BWGraphicBufferSource.cpp
${SOURCE_PATH}/OMXMaster.cpp
${SOURCE_PATH}/OMXNodeInstance.cpp
${SOURCE_PATH}/OMXUtils.cpp
${SOURCE_PATH}/OmxGraphicBufferSource
${SOURCE_PATH}/SimpleSoftOMXComponent.cpp
${SOURCE_PATH}/SoftOMXComponent.cpp
${SOURCE_PATH}/SoftOMXPlugin.cpp
${SOURCE_PATH}/SoftVideoDecoderOMXComponent.cpp
${SOURCE_PATH}/SoftVideoEncoderOMXComponent.cpp

#${SOURCE_PATH}/OMX.cpp
#${SOURCE_PATH}/GraphicBufferSource.cpp
#${SOURCE_PATH}/FrameDropper.cpp
#${SOURCE_PATH}/OMXStore.cpp

${SOURCE_PATH}/1.0/Omx.cpp
${SOURCE_PATH}/1.0/OmxStore.cpp
${SOURCE_PATH}/1.0/WGraphicBufferSource.cpp
${SOURCE_PATH}/1.0/WOmxNode.cpp
${SOURCE_PATH}/1.0/WOmxObserver.cpp
${SOURCE_PATH}/1.0/WOmxBufferSource.cpp
)

# target files
set(LIB_TYPE SHARED)
ADD_LIB(stagefright_omx)
