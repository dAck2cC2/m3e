project(SURFACEFLINGER)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/gui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/EGL/include.cmake)

add_definitions(-DANDROID_IMPLEMENTATION=1)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/surfaceflinger )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/surfaceflinger )

include_directories(AFTER ${HEADER_PATH})
add_definitions(-D_LIBCPP_HAS_NO_ATOMIC_HEADER=1)

if(MSVC)
    #add_definitions(-D_ALLOW_KEYWORD_MACROS=1)
    #add_definitions(-D__STDC_LIMIT_MACROS=1)
    add_definitions(-D_USE_MATH_DEFINES=1)
    add_definitions(-DNOMINMAX=1)
endif()

# dependency
set( SURFACEFLINGER_DEPLIB
log
cutils
utils
binder
gui
${OPENGL_DEPLIB}
)

# test function for angle
if (ENABLE_ANGLE)
    #set(ENABLE_ANGLE_TEST       "TRUE")  
endif(ENABLE_ANGLE) 

if (ENABLE_ANGLE_TEST)
    add_definitions(-DENABLE_ANGLE_TEST=1)
    include(${M3E_SOURCE_DIR}/cmake/${EXT_PATH}/angle/include_util.cmake)
    include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/src)    
    include_directories(AFTER ${M3E_SOURCE_DIR}/src/${EXT_PATH}/angle)
    list(APPEND SURFACEFLINGER_DEPLIB angle_util)
endif(ENABLE_ANGLE_TEST)

###############################################################################
#  Flinger
###############################################################################
set( SF_FLINGER_SOURCE_FILES 
${HEADER_PATH}/clz.h
${HEADER_PATH}/Barrier.h
${HEADER_PATH}/Transform.h
${SOURCE_PATH}/Transform.cpp
${HEADER_PATH}/Client.h
${SOURCE_PATH}/Client.cpp
${HEADER_PATH}/Layer.h
${SOURCE_PATH}/Layer.cpp
${SOURCE_PATH}/MessageQueue.cpp
${SOURCE_PATH}/DisplayDevice.h
${SOURCE_PATH}/DisplayDevice.cpp
${SOURCE_PATH}/SurfaceFlinger.h
${SOURCE_PATH}/SurfaceFlinger.cpp
${SOURCE_PATH}/main_surfaceflinger.cpp
)
source_group(Flinger FILES ${SF_FLINGER_SOURCE_FILES})

list(APPEND SURFACEFLINGER_SOURCE_FILES
${SF_FLINGER_SOURCE_FILES}
)

###############################################################################
#  RenderEngine
###############################################################################
set( SF_RENDERENGINE_SOURCE_FILES 
${HEADER_PATH}/RenderEngine/Texture.h
${HEADER_PATH}/RenderEngine/Description.h
${HEADER_PATH}/RenderEngine/GLExtensions.h
${HEADER_PATH}/RenderEngine/Mesh.h
${HEADER_PATH}/RenderEngine/RenderEngine.h
${SOURCE_PATH}/RenderEngine/Texture.cpp
${SOURCE_PATH}/RenderEngine/Description.cpp
${SOURCE_PATH}/RenderEngine/GLExtensions.cpp
${SOURCE_PATH}/RenderEngine/Mesh.cpp
${SOURCE_PATH}/RenderEngine/RenderEngine.cpp
)
if (ENABLE_DESKTOP_GL)
    list(APPEND SF_RENDERENGINE_SOURCE_FILES
    ${HEADER_PATH}/RenderEngine/GLRenderEngine.h 
    ${SOURCE_PATH}/RenderEngine/GLRenderEngine.cpp
    )
else ()
    list(APPEND SF_RENDERENGINE_SOURCE_FILES
    ${HEADER_PATH}/RenderEngine/Program.h
    ${SOURCE_PATH}/RenderEngine/Program.cpp
    ${HEADER_PATH}/RenderEngine/ProgramCache.h  
    ${SOURCE_PATH}/RenderEngine/ProgramCache.cpp  
    ${HEADER_PATH}/RenderEngine/GLES20RenderEngine.h
    ${SOURCE_PATH}/RenderEngine/GLES20RenderEngine.cpp 
    #${SOURCE_PATH}/RenderEngine/GLES11RenderEngine.cpp
    #${HEADER_PATH}/RenderEngine/GLES11RenderEngine.h
    #${HEADER_PATH}/RenderEngine/GLES10RenderEngine.h
    #${SOURCE_PATH}/RenderEngine/GLES10RenderEngine.cpp 
    )
endif ()
source_group(RenderEngine FILES ${SF_RENDERENGINE_SOURCE_FILES})

list(APPEND SURFACEFLINGER_SOURCE_FILES
${SF_RENDERENGINE_SOURCE_FILES}
)

###############################################################################
#  NariveWindow
###############################################################################
set( NATIVE_WINDOW_SOURCE
${SOURCE_PATH}/NativeWindow/NativeWindow.h
${SOURCE_PATH}/NativeWindow/Event.h
${SOURCE_PATH}/NativeWindow/keyboard.h
${SOURCE_PATH}/NativeWindow/mouse.h
${SOURCE_PATH}/NativeWindow/Timer.h
)

list( APPEND NATIVE_WINDOW_SOURCE
${SOURCE_PATH}/NativeWindow/NativeWindow.cpp
)

if(APPLE)
    find_library(APPKIT_LIBRARY AppKit)
    list(APPEND SURFACEFLINGER_DEPLIB ${APPKIT_LIBRARY})

    list(APPEND NATIVE_WINDOW_SOURCE 
    ${SOURCE_PATH}/NativeWindow/osx/OSXtimer.h
    ${SOURCE_PATH}/NativeWindow/osx/OSXWindow.h
    )

    list(APPEND NATIVE_WINDOW_SOURCE 
    ${SOURCE_PATH}/NativeWindow/osx/OSXtimer.cpp
    ${SOURCE_PATH}/NativeWindow/osx/OSXWindow.mm
    )
elseif(MSVC)
    list(APPEND NATIVE_WINDOW_SOURCE 
    ${SOURCE_PATH}/NativeWindow/win32/Win32Window.h
    ${SOURCE_PATH}/NativeWindow/win32/Win32Timer.h
    )

    list(APPEND NATIVE_WINDOW_SOURCE 
    ${SOURCE_PATH}/NativeWindow/win32/Win32Window.cpp
    ${SOURCE_PATH}/NativeWindow/win32/Win32Timer.cpp 
    )    
endif()

source_group(NativeWindow FILES ${NATIVE_WINDOW_SOURCE})

list(APPEND SURFACEFLINGER_SOURCE_FILES
${NATIVE_WINDOW_SOURCE}
)



set(LIB_NAME surfaceflinger_default)

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${LIB_NAME} SHARED ${SURFACEFLINGER_SOURCE_FILES})
target_link_libraries(${LIB_NAME} ${SURFACEFLINGER_DEPLIB})
