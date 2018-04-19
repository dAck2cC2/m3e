
if(ENABLE_GLUT)
    add_subdirectory(freeglut)
    add_subdirectory(glui)
    add_subdirectory(assimp)
endif(ENABLE_GLUT)

if(ENABLE_SKIA)
    add_subdirectory(skia)
endif(ENABLE_SKIA)

#if(ENABLE_ANGLE)
    add_subdirectory(angle)
#endif(ENABLE_ANGLE)
