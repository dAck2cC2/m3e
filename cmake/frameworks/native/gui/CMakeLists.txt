
project(GUI)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/gui/include.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/system/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/hidl/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/interfaces/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/ui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/EGL/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/nativewindow/include.cmake)

#include_directories(AFTER ${M3E_SOURCE_DIR}/src/native/include/private)

set(GUI_DEPLIB
ui
hidl
interfaces
binder
utils
cutils
log
${OPENGL_DEPLIB}
)

if (MSVC)
    add_definitions(-DNOMINMAX=1)
    add_definitions(-D_ALLOW_KEYWORD_MACROS=1)

    include(${M3E_SOURCE_DIR}/cmake/core/msvc/include.cmake)
    list(APPEND GUI_DEPLIB ${LIB_MSVC_WRAP})
elseif(APPLE)
    set(CMAKE_CXX_FLAGS "-std=c++1z -stdlib=libc++" ${CMAKE_CXX_FLAGS})    
    add_definitions(-DMSG_NOSIGNAL=0)
elseif(LINUX)
    set(CMAKE_CXX_FLAGS "-std=c++14" ${CMAKE_CXX_FLAGS})    
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/libs/gui/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/libs/gui )

# header files
file(GLOB 
GUI_HEADER_FILES  
${HEADER_PATH}/gui/*.h
${HEADER_PATH}/gui/bufferqueue/*.h
${HEADER_PATH}/gui/view/*.h
${HEADER_PATH}/private/gui/*.h
${HEADER_PATH}/gui/customized/*.h
)

# source files
set(GUI_SOURCE_FILES 
${SOURCE_PATH}/BitTube.cpp
${SOURCE_PATH}/BufferItem.cpp
${SOURCE_PATH}/BufferItemConsumer.cpp
${SOURCE_PATH}/BufferQueue.cpp
${SOURCE_PATH}/BufferQueueConsumer.cpp
${SOURCE_PATH}/BufferQueueCore.cpp
${SOURCE_PATH}/BufferQueueProducer.cpp
${SOURCE_PATH}/BufferSlot.cpp
${SOURCE_PATH}/ConsumerBase.cpp
${SOURCE_PATH}/CpuConsumer.cpp
${SOURCE_PATH}/DisplayEventReceiver.cpp
${SOURCE_PATH}/FrameTimestamps.cpp
${SOURCE_PATH}/GLConsumer.cpp
${SOURCE_PATH}/GuiConfig.cpp
${SOURCE_PATH}/IDisplayEventConnection.cpp
${SOURCE_PATH}/IConsumerListener.cpp
${SOURCE_PATH}/IGraphicBufferConsumer.cpp
${SOURCE_PATH}/IGraphicBufferProducer.cpp
${SOURCE_PATH}/IProducerListener.cpp
${SOURCE_PATH}/ISurfaceComposer.cpp
${SOURCE_PATH}/ISurfaceComposerClient.cpp
${SOURCE_PATH}/LayerState.cpp
${SOURCE_PATH}/OccupancyTracker.cpp
${SOURCE_PATH}/StreamSplitter.cpp
${SOURCE_PATH}/Surface.cpp
${SOURCE_PATH}/SurfaceControl.cpp
${SOURCE_PATH}/SurfaceComposerClient.cpp
${SOURCE_PATH}/SyncFeatures.cpp
${SOURCE_PATH}/view/Surface.cpp
${SOURCE_PATH}/bufferqueue/1.0/B2HProducerListener.cpp
${SOURCE_PATH}/bufferqueue/1.0/H2BGraphicBufferProducer.cpp

# !!!!!!!!!!
# we need it for PC version to pass EGL window from SurfaceFlinger to Client.
${SOURCE_PATH}/customized/ISurfaceHandle.cpp
)

if(APPLE)
#    list(APPEND GUI_SOURCE_FILES
#        ${SOURCE_PATH}/eglext.c
#    )
endif()

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(gui SHARED ${GUI_SOURCE_FILES} ${GUI_HEADER_FILES})
target_link_libraries(gui ${GUI_DEPLIB})
