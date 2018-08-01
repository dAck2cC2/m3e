# the subdirectory
add_subdirectory(binder)
add_subdirectory(servicemanager)

add_subdirectory(ui)
add_subdirectory(gui)
add_subdirectory(surfaceflinger)

if (ENABLE_DESKTOP_GL)
    add_subdirectory(opengl)
endif(ENABLE_DESKTOP_GL)
