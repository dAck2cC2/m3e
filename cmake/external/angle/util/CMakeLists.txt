project(ANGLE_UTIL)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/${EXT_PATH}/angle/include.cmake)

if(ENABLE_ANGLE)
    OPTION( BUILD_NATIVE_WINDOW
    "Build package to support the native window system."
    ON
    )
else(ENABLE_ANGLE)
    OPTION( BUILD_NATIVE_WINDOW
    "Build package to support the native window system."
    OFF
    )
endif(ENABLE_ANGLE)

add_definitions(-DLIBANGLE_UTIL_IMPLEMENTATION=1)
add_definitions(-DGL_GLEXT_PROTOTYPES=1)

set(ANGLE_UTIL_DEPLIB
EGL
GLESv2
)

set(HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/util/)
set(SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/util/)

#file(GLOB ANGLE_UTIL_HEAD ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/util/*.h)
#file(GLOB ANGLE_UTIL_SRC  ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/util/*.cpp)

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/angle)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/util)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/include)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/src)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/src/common/third_party/base)

set(_util_sources
${SOURCE_PATH}/EGLPlatformParameters.h 
${SOURCE_PATH}/EGLWindow.cpp 
${SOURCE_PATH}/EGLWindow.h 
${SOURCE_PATH}/Event.h 
${SOURCE_PATH}/Matrix.cpp 
${SOURCE_PATH}/Matrix.h 
${SOURCE_PATH}/OSPixmap.h 
${SOURCE_PATH}/OSWindow.cpp 
${SOURCE_PATH}/OSWindow.h 
${SOURCE_PATH}/com_utils.h 
${SOURCE_PATH}/frame_capture_utils.h 
${SOURCE_PATH}/geometry_utils.cpp 
${SOURCE_PATH}/geometry_utils.h 
${SOURCE_PATH}/keyboard.h 
${SOURCE_PATH}/mouse.h 
${SOURCE_PATH}/random_utils.cpp 
${SOURCE_PATH}/random_utils.h 
${SOURCE_PATH}/shader_utils.cpp 
${SOURCE_PATH}/shader_utils.h 
${SOURCE_PATH}/util_export.h 
${SOURCE_PATH}/util_gl.h 
)
if(APPLE)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14 -stdlib=libc++")
    set(CMAKE_C_FLAGS "-x objective-c")
    if (BUILD_NATIVE_WINDOW)
        list(APPEND _util_sources 
        ${SOURCE_PATH}/osx/OSXPixmap.h
        ${SOURCE_PATH}/osx/OSXPixmap.mm
        ${SOURCE_PATH}/osx/OSXWindow.h
        ${SOURCE_PATH}/osx/OSXWindow.mm
        )

        find_library(APPKIT_LIBRARY AppKit)
        list(APPEND ANGLE_UTIL_DEPLIB ${APPKIT_LIBRARY})
        find_library(QUARTYCORE_LIBRARY QuartzCore)
        list(APPEND ANGLE_UTIL_DEPLIB ${QUARTYCORE_LIBRARY})
    endif(BUILD_NATIVE_WINDOW)
elseif(MSVC)
    #if (BUILD_NATIVE_WINDOW)
        list(APPEND ANGLE_UTIL_HEAD 
        ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/util/windows/WindowsTimer.h
        ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/util/windows/win32/Win32Pixmap.h
        ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/util/windows/win32/Win32Window.h
        )
        list(APPEND ANGLE_UTIL_SRC 
        ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/util/windows/Windows_system_utils.cpp
        ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/util/windows/WindowsTimer.cpp
        ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/util/windows/win32/Win32Pixmap.cpp
        ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/util/windows/win32/Win32Window.cpp
        ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/util/windows/win32/Win32_system_utils.cpp
        )
    #endif(BUILD_NATIVE_WINDOW)
endif()
source_group(_util_sources FILES ${_util_sources})


set(angle_test_utils
${SOURCE_PATH}/Timer.cpp
${SOURCE_PATH}/Timer.h
${SOURCE_PATH}/test_utils.cpp
${SOURCE_PATH}/test_utils.h
)
if (MSVC)
list(APPEND angle_test_utils
${SOURCE_PATH}/windows/test_utils_win.cpp
${SOURCE_PATH}/windows/win32/test_utils_win32.cpp
)
else()
list(APPEND angle_test_utils
${SOURCE_PATH}/posix/crash_handler_posix.cpp
${SOURCE_PATH}/posix/test_utils_posix.cpp
)
endif()
source_group(angle_test_utils FILES ${angle_test_utils})

set(ANGLE_UTIL_SRC 
${_util_sources}
${angle_test_utils}
)

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(angle_util SHARED ${ANGLE_UTIL_SRC})
target_link_libraries(angle_util ${ANGLE_UTIL_DEPLIB})

