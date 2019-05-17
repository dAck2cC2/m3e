project(SURFACEFLINGER)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

# dependency
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/hidl/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/interfaces/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/initrc/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/math/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/ui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/gui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/EGL/include.cmake)

include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/initrc)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/native/include)

set( SURFACEFLINGER_DEPLIB
log
cutils
utils
binder
gui
${OPENGL_DEPLIB}
)

if(MSVC)
    add_definitions(-D_ALLOW_KEYWORD_MACROS=1)
    #add_definitions(-D__STDC_LIMIT_MACROS=1)
    add_definitions(-D_USE_MATH_DEFINES=1)
    add_definitions(-DNOMINMAX=1)
elseif(APPLE)
    set(CMAKE_CXX_FLAGS "-std=c++1z -stdlib=libc++" ${CMAKE_CXX_FLAGS})    
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/services/surfaceflinger )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/services/surfaceflinger )

include_directories(AFTER ${HEADER_PATH})

###############################################################################
#  Flinger
###############################################################################
file(GLOB ${PROJECT_NAME}_FLINGER
${SOURCE_PATH}/*.h
)
list(APPEND ${PROJECT_NAME}_FLINGER
${SOURCE_PATH}/Client.cpp 
${SOURCE_PATH}/DisplayDevice.cpp 
${SOURCE_PATH}/DispSync.cpp 
${SOURCE_PATH}/EventControlThread.cpp 
${SOURCE_PATH}/StartPropertySetThread.cpp 
${SOURCE_PATH}/EventThread.cpp 
${SOURCE_PATH}/FrameTracker.cpp 
${SOURCE_PATH}/GpuService.cpp 
${SOURCE_PATH}/Layer.cpp 
${SOURCE_PATH}/LayerDim.cpp 
${SOURCE_PATH}/LayerRejecter.cpp 
${SOURCE_PATH}/LayerVector.cpp 
${SOURCE_PATH}/MessageQueue.cpp 
${SOURCE_PATH}/MonitoredProducer.cpp 
${SOURCE_PATH}/SurfaceFlingerConsumer.cpp 
${SOURCE_PATH}/Transform.cpp 
${SOURCE_PATH}/SurfaceFlinger_hwc1.cpp
#${SOURCE_PATH}/SurfaceInterceptor.cpp 
#${SOURCE_PATH}/SurfaceFlinger.cpp
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
${SOURCE_PATH}/DisplayHardware/FramebufferSurface.cpp  
${SOURCE_PATH}/DisplayHardware/HWComposerBufferCache.cpp 
${SOURCE_PATH}/DisplayHardware/PowerHAL.cpp 
${SOURCE_PATH}/DisplayHardware/VirtualDisplaySurface.cpp 
${SOURCE_PATH}/DisplayHardware/HWComposer_hwc1.cpp
#${SOURCE_PATH}/DisplayHardware/ComposerHal.cpp 
#${SOURCE_PATH}/DisplayHardware/HWC2.cpp
#${SOURCE_PATH}/DisplayHardware/HWComposer.cpp
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
#  RenderEngine
###############################################################################
file(GLOB ${PROJECT_NAME}_RENDERENGINE
${SOURCE_PATH}/RenderEngine/*.h
)
list(APPEND ${PROJECT_NAME}_RENDERENGINE
${SOURCE_PATH}/RenderEngine/Description.cpp 
${SOURCE_PATH}/RenderEngine/Mesh.cpp 
${SOURCE_PATH}/RenderEngine/Program.cpp 
${SOURCE_PATH}/RenderEngine/ProgramCache.cpp 
${SOURCE_PATH}/RenderEngine/GLExtensions.cpp 
${SOURCE_PATH}/RenderEngine/RenderEngine.cpp 
${SOURCE_PATH}/RenderEngine/Texture.cpp 
${SOURCE_PATH}/RenderEngine/GLES20RenderEngine.cpp 
)
source_group(RenderEngine FILES ${${PROJECT_NAME}_RENDERENGINE})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_RENDERENGINE})

###############################################################################
#  Customized
###############################################################################
file(GLOB ${PROJECT_NAME}_CUSTOMIZED
${SOURCE_PATH}/customized/*.h
)
list(APPEND ${PROJECT_NAME}_CUSTOMIZED
#${SOURCE_PATH}/customized/SurfaceHandler.cpp
${SOURCE_PATH}/customized/main_surfaceflinger.cpp
)
source_group(customized FILES ${${PROJECT_NAME}_CUSTOMIZED})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_CUSTOMIZED})



set(LIB_NAME surfaceflinger_default)

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${LIB_NAME} SHARED ${${PROJECT_NAME}_SOURCE_FILES})
target_link_libraries(${LIB_NAME} ${SURFACEFLINGER_DEPLIB})


if(ENABLE_TEST)
    add_subdirectory(test)
endif(ENABLE_TEST)
