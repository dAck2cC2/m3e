
#####################################################################
# create the folder for external module

if(NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH})
    message(STATUS "Create\t${M3E_SOURCE_DIR}/${EXT_PATH}")
    exec_program("mkdir ${EXT_PATH}" ${M3E_SOURCE_DIR})
endif()

#####################################################################
# download and include external module

# wxWidgets
if (ENABLE_WXWIDGETS)
    add_subdirectory(wxwidgets)
    add_subdirectory(zlib)
    add_subdirectory(expat)        
    add_subdirectory(jpeg)
    add_subdirectory(png)
    add_subdirectory(tiff)
endif(ENABLE_WXWIDGETS)

# angle for EGL and OpenGL
if (ENABLE_ANGLE OR ENABLE_AV_UTILS)
    add_subdirectory(angle)
endif()

# skia
if(ENABLE_SKIA)
    add_subdirectory(skia)
    add_subdirectory(freeglut)
    #add_subdirectory(imgui)

    #add_subdirectory(jsoncpp)
endif(ENABLE_SKIA)

# freeglut
if(ENABLE_GLUT)
    add_subdirectory(freeglut)
    add_subdirectory(glui)
    add_subdirectory(assimp)
endif(ENABLE_GLUT)

if (ENABLE_CORE)
    #add_subdirectory(safe-iop)
    #if (APPLE OR MSVC)
    #    add_subdirectory(wepoll)
    #endif ()
endif(ENABLE_CORE)

if(ENABLE_TEST)
    set(EXT_MODULES ${EXT_MODULES} gtest)
    add_subdirectory(gtest)
endif(ENABLE_TEST)

if(ENABLE_AV_CODEC)
    add_subdirectory(expat)
    add_subdirectory(jpeg)
    add_subdirectory(yuv)
endif(ENABLE_AV_CODEC)
