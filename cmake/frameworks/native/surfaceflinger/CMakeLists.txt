# CompositionEngine
add_subdirectory(compositionengine)

project(SURFACEFLINGER)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

# dependency
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/hidl/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/hwbinder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/interfaces/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)
include(${INITRC_INCLUDE})
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/math/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/ui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/gui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/renderengine/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/base/android/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/surfaceflinger/compositionengine/include.cmake)

# private header of initrc_if.h
include_directories(AFTER ${INITRC_PATH})

set( SURFACEFLINGER_DEPLIB
log
cutils
utils
binder
gui
${OPENGL_DEPLIB}
compositionengine
renderengine
nativewindow
)

if(MSVC)
    add_definitions(-D_ALLOW_KEYWORD_MACROS=1)
    #add_definitions(-D__STDC_LIMIT_MACROS=1)
    add_definitions(-D_USE_MATH_DEFINES=1)
    add_definitions(-DNOMINMAX=1)
    
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_flag_suppoted)
    if (_cpp_flag_suppoted)
        add_compile_options("/std:c++latest")
    endif()
elseif(APPLE)
    set(CMAKE_CXX_FLAGS "-std=c++1z -stdlib=libc++" ${CMAKE_CXX_FLAGS})    
    add_definitions(-DPRId64= )
    add_definitions(-Dtimer_t=void*)
elseif(LINUX)
    add_definitions(-D__STDC_HOSTED__=1)
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/services/surfaceflinger )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/services/surfaceflinger )

include_directories(AFTER ${HEADER_PATH})

###############################################################################
#  Flinger
#  libsurfaceflinger_sources
###############################################################################
file(GLOB ${PROJECT_NAME}_FLINGER
${SOURCE_PATH}/*.h
)
list(APPEND ${PROJECT_NAME}_FLINGER
${SOURCE_PATH}/BufferLayer.cpp 
${SOURCE_PATH}/BufferLayerConsumer.cpp 
${SOURCE_PATH}/BufferQueueLayer.cpp
${SOURCE_PATH}/BufferStateLayer.cpp
${SOURCE_PATH}/ClientCache.cpp
${SOURCE_PATH}/Client.cpp 
${SOURCE_PATH}/ColorLayer.cpp 
${SOURCE_PATH}/ContainerLayer.cpp 
${SOURCE_PATH}/DisplayDevice.cpp 
#DisplayHardware
#Effects
#EventLog
${SOURCE_PATH}/FrameTracker.cpp 
${SOURCE_PATH}/Layer.cpp 
${SOURCE_PATH}/LayerProtoHelper.cpp 
${SOURCE_PATH}/LayerRejecter.cpp 
${SOURCE_PATH}/LayerStats.cpp 
${SOURCE_PATH}/LayerVector.cpp 
${SOURCE_PATH}/MonitoredProducer.cpp 
${SOURCE_PATH}/NativeWindowSurface.cpp
${SOURCE_PATH}/RefreshRateOverlay.cpp
${SOURCE_PATH}/RegionSamplingThread.cpp
${SOURCE_PATH}/RenderArea.cpp 
#Scheduler
${SOURCE_PATH}/StartPropertySetThread.cpp 
${SOURCE_PATH}/SurfaceFlinger.cpp
#${SOURCE_PATH}/SurfaceInterceptor.cpp 
${SOURCE_PATH}/SurfaceTracing.cpp 
#TimeStats
${SOURCE_PATH}/TransactionCompletedThread.cpp 
)
source_group(Flinger FILES ${${PROJECT_NAME}_FLINGER})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_FLINGER})

###############################################################################
#  Disaplay Hardware
###############################################################################
file(GLOB ${PROJECT_NAME}_DISPLAYHW
${SOURCE_PATH}/DisplayHardware/*.h
)
list(APPEND ${PROJECT_NAME}_DISPLAYHW
${SOURCE_PATH}/DisplayHardware/ComposerHal.cpp 
${SOURCE_PATH}/DisplayHardware/DisplayIdentification.cpp
${SOURCE_PATH}/DisplayHardware/FramebufferSurface.cpp  
${SOURCE_PATH}/DisplayHardware/HWC2.cpp
${SOURCE_PATH}/DisplayHardware/HWComposer.cpp
${SOURCE_PATH}/DisplayHardware/PowerAdvisor.cpp 
${SOURCE_PATH}/DisplayHardware/VirtualDisplaySurface.cpp 
)
source_group(DisplayHardware FILES ${${PROJECT_NAME}_DISPLAYHW})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_DISPLAYHW})

###############################################################################
#  Effects
###############################################################################
file(GLOB ${PROJECT_NAME}_EFFECTS
${SOURCE_PATH}/Effects/*.h
)
list(APPEND ${PROJECT_NAME}_EFFECTS
${SOURCE_PATH}/Effects/Daltonizer.cpp
)
source_group(effects FILES ${${PROJECT_NAME}_EFFECTS})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_EFFECTS})

###############################################################################
#  EventLog
###############################################################################
file(GLOB ${PROJECT_NAME}_EVENTLOG
${SOURCE_PATH}/EventLog/*.h
)
list(APPEND ${PROJECT_NAME}_EVENTLOG
${SOURCE_PATH}/EventLog/EventLog.cpp
${SOURCE_PATH}/EventLog/EventLogTags.logtags
)
source_group(EventLog FILES ${${PROJECT_NAME}_EVENTLOG})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_EVENTLOG})

###############################################################################
#  Scheduler
###############################################################################
file(GLOB ${PROJECT_NAME}_SCHEDULER
${SOURCE_PATH}/Scheduler/*.h
)
list(APPEND ${PROJECT_NAME}_SCHEDULER
${SOURCE_PATH}/Scheduler/DispSync.cpp
${SOURCE_PATH}/Scheduler/DispSyncSource.cpp
${SOURCE_PATH}/Scheduler/EventControlThread.cpp
${SOURCE_PATH}/Scheduler/EventThread.cpp
${SOURCE_PATH}/Scheduler/IdleTimer.cpp 
${SOURCE_PATH}/Scheduler/LayerHistory.cpp
${SOURCE_PATH}/Scheduler/LayerInfo.cpp 
${SOURCE_PATH}/Scheduler/MessageQueue.cpp 
${SOURCE_PATH}/Scheduler/PhaseOffsets.cpp
${SOURCE_PATH}/Scheduler/Scheduler.cpp
${SOURCE_PATH}/Scheduler/SchedulerUtils.cpp
${SOURCE_PATH}/Scheduler/VSyncModulator.cpp
)
source_group(Scheduler FILES ${${PROJECT_NAME}_SCHEDULER})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_SCHEDULER})

###############################################################################
#  TimeStats
###############################################################################
file(GLOB ${PROJECT_NAME}_TIMESTATS
${SOURCE_PATH}/TimeStats/*.h
)
list(APPEND ${PROJECT_NAME}_TIMESTATS
${SOURCE_PATH}/TimeStats/TimeStats.cpp
)
source_group(TimeStats FILES ${${PROJECT_NAME}_TIMESTATS})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_TIMESTATS})

###############################################################################
#  LayerProto
###############################################################################

#include_directories(AFTER ${SOURCE_PATH}/layerproto/include)

###############################################################################
#  libSurfaceFlingerProp
###############################################################################
list(APPEND ${PROJECT_NAME}_PROP
${SOURCE_PATH}/SurfaceFlingerProperties.h
${SOURCE_PATH}/SurfaceFlingerProperties.cpp
)
source_group(SurfaceFlingerProp FILES ${${PROJECT_NAME}_PROP})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_PROP})

###############################################################################
#  Customized
###############################################################################
file(GLOB ${PROJECT_NAME}_CUSTOMIZED
${SOURCE_PATH}/customized/*.h
)
list(APPEND ${PROJECT_NAME}_CUSTOMIZED
${SOURCE_PATH}/customized/NSurfaceFlingerFactory.cpp
${SOURCE_PATH}/customized/main_surfaceflinger.cpp
)
if(ENABLE_ANDROID_GL)
    list(APPEND ${PROJECT_NAME}_CUSTOMIZED
    ${SOURCE_PATH}/customized/NBufferProducer.cpp
    )
endif(ENABLE_ANDROID_GL)
source_group(customized FILES ${${PROJECT_NAME}_CUSTOMIZED})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_CUSTOMIZED})



set(LIB_NAME surfaceflinger_default)

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${LIB_NAME} SHARED ${${PROJECT_NAME}_SOURCE_FILES})
target_link_libraries(${LIB_NAME} ${SURFACEFLINGER_DEPLIB})


#set(ENABLE_TEST TRUE)
if(ENABLE_TEST)
    add_subdirectory(test)
endif(ENABLE_TEST)
