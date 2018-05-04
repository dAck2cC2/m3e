
project(GUI)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/gui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/angle/include.cmake)

#include_directories(AFTER ${M3E_SOURCE_DIR}/src/native/include/private)

add_definitions(-DANDROID_IMPLEMENTATION=1)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/gui )

# dependency
set(GUI_DEPLIB
angle
ui
binder
utils
cutils
log
)

# header files
file(GLOB GUI_HEADER_FILES  ${HEADER_PATH}/gui/*.h)

#file(GLOB GUI_PRIVATE_HEADER ${HEADER_PATH}/private/gui/*.h)
#list(APPEND GUI_HEADER_FILES ${GUI_PRIVATE_HEADER})

# source files
set(GUI_SOURCE_FILES 
${SOURCE_PATH}/BitTube.cpp
${SOURCE_PATH}/BufferItem.cpp
${SOURCE_PATH}/BufferItemConsumer.cpp
${SOURCE_PATH}/BufferQueue.cpp
${SOURCE_PATH}/BufferQueueProducer.cpp
${SOURCE_PATH}/BufferSlot.cpp
${SOURCE_PATH}/Surface.cpp
${SOURCE_PATH}/ConsumerBase.cpp
${SOURCE_PATH}/BufferQueueCore.cpp
${SOURCE_PATH}/SurfaceComposerClient.cpp
${SOURCE_PATH}/CpuConsumer.cpp
${SOURCE_PATH}/LayerState.cpp
${SOURCE_PATH}/SurfaceControl.cpp
${SOURCE_PATH}/ISurfaceComposer.cpp
${SOURCE_PATH}/ISurfaceComposerClient.cpp
${SOURCE_PATH}/IConsumerListener.cpp
${SOURCE_PATH}/IProducerListener.cpp
${SOURCE_PATH}/BufferQueueConsumer.cpp
${SOURCE_PATH}/IGraphicBufferAlloc.cpp
${SOURCE_PATH}/IGraphicBufferConsumer.cpp
${SOURCE_PATH}/IGraphicBufferProducer.cpp
${SOURCE_PATH}/IDisplayEventConnection.cpp
${SOURCE_PATH}/IProducerListener.cpp
${SOURCE_PATH}/OccupancyTracker.cpp
${SOURCE_PATH}/GLConsumer.cpp
${SOURCE_PATH}/SyncFeatures.cpp
${SOURCE_PATH}/ISurfaceHandle.cpp
)

if(APPLE)
    list(APPEND GUI_SOURCE_FILES
        ${SOURCE_PATH}/eglext.c
    )
elseif(MSVC)
    add_definitions(-DNOMINMAX=1)
    add_definitions(-D_ALLOW_KEYWORD_MACROS=1)

    list(REMOVE_ITEM GUI_SOURCE_FILES
    ${SOURCE_PATH}/BitTube.cpp
    )

    list(APPEND GUI_SOURCE_FILES
    ${SOURCE_PATH}/BitTube_msvc.cpp
    )
endif()

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(gui SHARED ${GUI_SOURCE_FILES} ${GUI_HEADER_FILES})
target_link_libraries(gui ${GUI_DEPLIB})
