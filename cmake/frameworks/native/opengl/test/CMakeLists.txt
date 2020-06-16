
project(TEST_OPENGL)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/initrc/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/include.cmake)

set(DEMO_DEPLIBS 
${OPENGL_DEPLIB}
)

set( NATIVE_WINDOW_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/surfaceflinger/NativeWindow )
file(GLOB NATIVE_WINDOW_SOURCE
${NATIVE_WINDOW_PATH}/*.h 
${NATIVE_WINDOW_PATH}/*.cpp 
)

include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/native/opengl/angle/third_party/khronos/GL)

if(APPLE)
    find_library(APPKIT_LIBRARY AppKit)
    list(APPEND DEMO_DEPLIBS ${APPKIT_LIBRARY})

    list(APPEND NATIVE_WINDOW_SOURCE 
    ${NATIVE_WINDOW_PATH}/osx/OSXtimer.h
    ${NATIVE_WINDOW_PATH}/osx/OSXWindow.h
    ${NATIVE_WINDOW_PATH}/osx/OSXtimer.cpp
    ${NATIVE_WINDOW_PATH}/osx/OSXWindow.mm 
    )

elseif(MSVC)
    list(APPEND NATIVE_WINDOW_SOURCE 
    ${NATIVE_WINDOW_PATH}/win32/Win32Window.h
    ${NATIVE_WINDOW_PATH}/win32/Win32Timer.h
    ${NATIVE_WINDOW_PATH}/win32/Win32Window.cpp
    ${NATIVE_WINDOW_PATH}/win32/Win32Timer.cpp 
    )
endif()

include_directories(AFTER ${NATIVE_WINDOW_PATH}/../)

ADD_DEMO(egl   
${M3E_SOURCE_DIR}/src/frameworks/native/opengl/test/test_egl.cpp
${NATIVE_WINDOW_SOURCE}        
)

if (MSVC)
    #list(APPEND DEMO_DEPLIBS nvoglv32)

    ADD_DEMO(wgl   
    ${M3E_SOURCE_DIR}/src/frameworks/native/opengl/test/test_wgl.cpp      
    ${NATIVE_WINDOW_SOURCE}    
    )
endif(MSVC)
