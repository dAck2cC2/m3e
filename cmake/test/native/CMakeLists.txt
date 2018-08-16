# the subdirectory

add_subdirectory(binder)

if (ENABLE_DESKTOP_GL)
    add_subdirectory(opengl)
endif(ENABLE_DESKTOP_GL)
