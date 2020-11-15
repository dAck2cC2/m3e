
#####################################################################
# create the folder for external module

if(NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH})
    message(STATUS "Create\t${M3E_SOURCE_DIR}/${EXT_PATH}")
    exec_program("mkdir ${EXT_PATH}" ${M3E_SOURCE_DIR})
endif()

#####################################################################
# download and include external module

add_subdirectory(gtest)

# wxWidgets
if (ENABLE_WXWIDGETS)
    add_subdirectory(wxwidgets)
    add_subdirectory(zlib)
    add_subdirectory(expat)      
    add_subdirectory(jpeg)  
#    add_subdirectory(jpeg-turbo)
    add_subdirectory(png)
    add_subdirectory(tiff)
endif(ENABLE_WXWIDGETS)

# angle for EGL and OpenGLES
if (ENABLE_ANGLE)
    add_subdirectory(angle)
endif()

# skia
if(ENABLE_SKIA_CHROME)
    add_subdirectory(skia_chrome)
    add_subdirectory(freeglut)
    #add_subdirectory(imgui)

    #add_subdirectory(jsoncpp)
endif(ENABLE_SKIA_CHROME)

# freeglut
if(ENABLE_GLUT)
    add_subdirectory(freeglut)
    add_subdirectory(glui)
    add_subdirectory(assimp)
endif(ENABLE_GLUT)

if (ENABLE_CORE)
    # safe-iop is not used in latest libutils (VectorImpl.cpp)
    #if (APPLE)
    #    add_subdirectory(safe-iop)
    #endif()

    # use condition instead of epoll in libutils (Looper.cpp)
    #if (APPLE OR MSVC)
    #    add_subdirectory(wepoll)
    #endif ()
endif(ENABLE_CORE)

if (ENABLE_AV_UTILS)
    add_subdirectory(zlib)
    
    add_subdirectory(skia_android) 
    add_subdirectory(png) 
    add_subdirectory(jpeg-turbo) 
    add_subdirectory(gif)  
    add_subdirectory(dng_sdk)
    add_subdirectory(webp)
    add_subdirectory(piex)

    add_subdirectory(sonic) 
    add_subdirectory(sonivox) 
    add_subdirectory(vpx) 

    add_subdirectory(hidlservice)
endif(ENABLE_AV_UTILS)

if(ENABLE_AV_CODEC)
    add_subdirectory(expat)
    add_subdirectory(yuv)
    add_subdirectory(tremolo)
    add_subdirectory(flac)
    add_subdirectory(aac)
    add_subdirectory(gsm)
    #add_subdirectory(boringssl)
    #add_subdirectory(hevc)
    #add_subdirectory(tinyxml2)
    add_subdirectory(avc)
endif(ENABLE_AV_CODEC)

if(MSVC)
    # We have wasapi audio now, should not need openal.
    #add_subdirectory(openal-soft)
endif(MSVC)

if (ENABLE_RAYLIB)
    add_subdirectory(raylib)
    add_subdirectory(raygui)
endif(ENABLE_RAYLIB)

if (ENABLE_GLFW)
    add_subdirectory(glfw)
endif(ENABLE_GLFW)

if (ENABLE_HIDL_GEN)
    add_subdirectory(aidl)
    add_subdirectory(hidl)
    add_subdirectory(boringssl)
endif(ENABLE_HIDL_GEN)

if (MSVC)
    add_subdirectory(msvc)
endif(MSVC)

if(ENABLE_HARDWARE)
    add_subdirectory(initrc)
endif(ENABLE_HARDWARE)
