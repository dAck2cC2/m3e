# the subdirectory

add_subdirectory(binder)
add_subdirectory(surfaceflinger)

if (ENABLE_DESKTOP_GL)
    add_subdirectory(opengl)
endif(ENABLE_DESKTOP_GL)
