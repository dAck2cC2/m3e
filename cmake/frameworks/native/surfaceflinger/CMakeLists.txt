project(SURFACEFLINGER)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/gui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/angle/include.cmake)

add_definitions(-DANDROID_IMPLEMENTATION=1)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/surfaceflinger )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/surfaceflinger )

include_directories(AFTER ${HEADER_PATH})
#include_directories(AFTER ${M3E_SOURCE_DIR}/NativeWindow)
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
angle
)

# source files
set( SURFACEFLINGER_HEADER_FILES 
${HEADER_PATH}/clz.h
${HEADER_PATH}/Transform.h
${HEADER_PATH}/Barrier.h
${HEADER_PATH}/Client.h
${HEADER_PATH}/Layer.h
${HEADER_PATH}/MessageQueue.h
${HEADER_PATH}/DisplayDevice.h
${HEADER_PATH}/SurfaceFlinger.h
${HEADER_PATH}/RenderEngine/Texture.h
${HEADER_PATH}/RenderEngine/Description.h
${HEADER_PATH}/RenderEngine/GLExtensions.h
${HEADER_PATH}/RenderEngine/Mesh.h
${HEADER_PATH}/RenderEngine/Program.h
${HEADER_PATH}/RenderEngine/ProgramCache.h
${HEADER_PATH}/RenderEngine/RenderEngine.h
${HEADER_PATH}/RenderEngine/GLES20RenderEngine.h
#${HEADER_PATH}/RenderEngine/GLES11RenderEngine.h
#${HEADER_PATH}/RenderEngine/GLES10RenderEngine.h
)

set( SURFACEFLINGER_SOURCE_FILES  
${SOURCE_PATH}/Transform.cpp
${SOURCE_PATH}/Client.cpp
${SOURCE_PATH}/Layer.cpp
${SOURCE_PATH}/MessageQueue.cpp
${SOURCE_PATH}/DisplayDevice.cpp
${SOURCE_PATH}/SurfaceFlinger.cpp
${SOURCE_PATH}/main_surfaceflinger.cpp
${SOURCE_PATH}/RenderEngine/Texture.cpp
${SOURCE_PATH}/RenderEngine/Description.cpp
${SOURCE_PATH}/RenderEngine/GLExtensions.cpp
${SOURCE_PATH}/RenderEngine/Mesh.cpp
${SOURCE_PATH}/RenderEngine/Program.cpp
${SOURCE_PATH}/RenderEngine/ProgramCache.cpp
${SOURCE_PATH}/RenderEngine/RenderEngine.cpp
${SOURCE_PATH}/RenderEngine/GLES20RenderEngine.cpp
#${SOURCE_PATH}/RenderEngine/GLES11RenderEngine.cpp
#${SOURCE_PATH}/RenderEngine/GLES10RenderEngine.cpp
)

set( NATIVE_WINDOW_HEADER
${SOURCE_PATH}/NativeWindow/NativeWindow.h
${SOURCE_PATH}/NativeWindow/Event.h
${SOURCE_PATH}/NativeWindow/keyboard.h
${SOURCE_PATH}/NativeWindow/mouse.h
${SOURCE_PATH}/NativeWindow/Timer.h
)

set( NATIVE_WINDOW_SOURCE
${SOURCE_PATH}/NativeWindow/NativeWindow.cpp
)

if(APPLE)
    find_library(APPKIT_LIBRARY AppKit)
    list(APPEND SURFACEFLINGER_DEPLIB ${APPKIT_LIBRARY})

    list(APPEND NATIVE_WINDOW_HEADER 
    ${SOURCE_PATH}/NativeWindow/osx/OSXtimer.h
    ${SOURCE_PATH}/NativeWindow/osx/OSXWindow.h
    )

    list(APPEND NATIVE_WINDOW_SOURCE 
    ${SOURCE_PATH}/NativeWindow/osx/OSXtimer.cpp
    ${SOURCE_PATH}/NativeWindow/osx/OSXWindow.mm
    )
elseif(MSVC)
    list(APPEND NATIVE_WINDOW_HEADER 
    ${SOURCE_PATH}/NativeWindow/win32/Win32Window.h
    ${SOURCE_PATH}/NativeWindow/win32/Win32Timer.h
    )

    list(APPEND NATIVE_WINDOW_SOURCE 
    ${SOURCE_PATH}/NativeWindow/win32/Win32Window.cpp
    ${SOURCE_PATH}/NativeWindow/win32/Win32Timer.cpp 
    )    
endif()

set( SURFACEFLINGER_HEADER_FILES ${SURFACEFLINGER_HEADER_FILES}
${NATIVE_WINDOW_HEADER}
)

set( SURFACEFLINGER_SOURCE_FILES ${SURFACEFLINGER_SOURCE_FILES}
${NATIVE_WINDOW_SOURCE}
)

set(LIB_NAME surfaceflinger_default)

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${LIB_NAME} SHARED ${SURFACEFLINGER_SOURCE_FILES} ${SURFACEFLINGER_HEADER_FILES})
target_link_libraries(${LIB_NAME} ${SURFACEFLINGER_DEPLIB})
