
project(UI)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/ui/include.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/sync/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/system/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/grallocusage/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/interfaces/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/hidl/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/hwbinder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/math/include.cmake)

include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/native/include/)

set(${PROJECT_NAME}_DEPLIB
binder
utils
log
sync
hardware
base
grallocusage
hidl
interfaces
)

if(MSVC)
    add_definitions(-D_ALLOW_KEYWORD_MACROS=1)
    #add_definitions(-D__STDC_LIMIT_MACROS=1)
    add_definitions(-DNOMINMAX)

    include(${MSVC_INCLUDE})
    add_definitions(-FI"predefine/posix_memalign")
elseif(APPLE)
    set(CMAKE_CXX_FLAGS "-std=c++1z -stdlib=libc++" ${CMAKE_CXX_FLAGS})    
    add_definitions(-DPRIx64= )
elseif(LINUX)
    set(CMAKE_CXX_FLAGS "-std=c++14" ${CMAKE_CXX_FLAGS})    
    add_definitions(-DPRIx64= )
endif()


set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/libs/ui/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/libs/ui )

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES  
${HEADER_PATH}/ui/*.h
${M3E_SOURCE_DIR}/src/frameworks/native/include/private/ui/*.h
)

# source files
set(${PROJECT_NAME}_SOURCE_FILES 
${SOURCE_PATH}/ColorSpace.cpp
${SOURCE_PATH}/BufferHubBuffer.cpp
${SOURCE_PATH}/BufferHubEventFd.cpp
${SOURCE_PATH}/BufferHubMetadata.cpp
${SOURCE_PATH}/DebugUtils.cpp
${SOURCE_PATH}/Fence.cpp
${SOURCE_PATH}/FenceTime.cpp
${SOURCE_PATH}/FrameStats.cpp
${SOURCE_PATH}/Gralloc.cpp
${SOURCE_PATH}/Gralloc2.cpp
${SOURCE_PATH}/Gralloc3.cpp
${SOURCE_PATH}/GraphicBuffer.cpp
${SOURCE_PATH}/GraphicBufferAllocator.cpp
${SOURCE_PATH}/GraphicBufferMapper.cpp
${SOURCE_PATH}/HdrCapabilities.cpp
${SOURCE_PATH}/PixelFormat.cpp
${SOURCE_PATH}/PublicFormat.cpp
${SOURCE_PATH}/Rect.cpp
${SOURCE_PATH}/Region.cpp
${SOURCE_PATH}/Size.cpp
${SOURCE_PATH}/Transform.cpp
${SOURCE_PATH}/UiConfig.cpp
)

if(MSVC)
else()
    list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${SOURCE_PATH}/ColorSpace.cpp)
endif()

# bufferhub is not used when building libgui for vendors
add_definitions(-DLIBUI_IN_VNDK)
list(REMOVE_ITEM ${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/BufferHubBuffer.cpp
${SOURCE_PATH}/BufferHubEventFd.cpp
${SOURCE_PATH}/BufferHubMetadata.cpp
)

# target files
ADD_SHARED_LIB(ui)

#set(ENABLE_TEST true)
if(ENABLE_TEST)
    add_subdirectory(test)
endif()
