project(ANGLE_UTIL)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

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

file(GLOB ANGLE_UTIL_HEAD ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/util/*.h)
file(GLOB ANGLE_UTIL_SRC  ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/util/*.cpp)

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/include)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/src)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/util)

if(APPLE)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -stdlib=libc++")
    if (BUILD_NATIVE_WINDOW)
        find_library(APPKIT_LIBRARY AppKit)
        list(APPEND ANGLE_UTIL_DEPLIB ${APPKIT_LIBRARY})

        list(APPEND ANGLE_UTIL_HEAD 
        ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/util/osx/OSXPixmap.h
        ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/util/osx/OSXtimer.h
        ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/util/osx/OSXWindow.h
        )
        list(APPEND ANGLE_UTIL_SRC 
        ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/util/osx/OSXPixmap.mm
        ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/util/osx/OSXtimer.cpp
        ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/util/osx/OSXWindow.mm
        ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/util/posix/Posix_system_utils.cpp
        )
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

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(angle_util SHARED ${ANGLE_UTIL_SRC} ${ANGLE_UTIL_HEAD})
target_link_libraries(angle_util ${ANGLE_UTIL_DEPLIB})

