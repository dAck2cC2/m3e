
if(ENABLE_GLUT)
    add_subdirectory(freeglut)
    add_subdirectory(glui)
    add_subdirectory(assimp)
endif(ENABLE_GLUT)

if(ENABLE_SKIA_CHROME)
    add_subdirectory(skia_chrome)
endif(ENABLE_SKIA_CHROME)

if(ENABLE_ANGLE AND NOT ENABLE_AV_UTILS)
    add_subdirectory(angle)
endif()

if (ENABLE_WXWIDGETS)
    add_subdirectory(wxwidgets)
endif()

#add_subdirectory(jpeg)
