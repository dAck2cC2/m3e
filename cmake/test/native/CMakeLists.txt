# the subdirectory

add_subdirectory(binder)
add_subdirectory(surfaceflinger)

if (ENABLE_NATIVE_GL)
    add_subdirectory(opengl)
endif(ENABLE_NATIVE_GL)
