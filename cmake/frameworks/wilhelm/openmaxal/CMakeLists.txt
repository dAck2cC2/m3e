project(OPENMAXAL)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/wilhelm/openmaxal/include.cmake)

# dependency
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/wilhelm/wilhelm/include.cmake)

#add_definitions(-DANDROID)
#include(${M3E_SOURCE_DIR}/cmake/system/audio_utils/include.cmake)
#include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)
#include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/audioclient/include.cmake)
#include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/system/hidl/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/interfaces/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/EGL/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/ui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/gui/include.cmake)

set( ${PROJECT_NAME}_DEPLIB
log
wilhelm
)

if(MSVC)
    add_definitions(-DXA_API=__declspec\(dllexport\))
elseif(APPLE)
    set(CMAKE_CXX_FLAGS "-std=c++1z -stdlib=libc++" ${CMAKE_CXX_FLAGS})  
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/wilhelm/include/OMXAL/ )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/wilhelm/src/ )

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES  
${HEADER_PATH}/*.h
)

set(${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/xa_entry.cpp
${SOURCE_PATH}/xa_iid.cpp
${SOURCE_PATH}/assert.cpp
${M3E_SOURCE_DIR}/src/external/openmaxal/OpenMAXAL_Android.cpp
)

set(LIB_TYPE SHARED)
ADD_LIB(OpenMAXAL)
