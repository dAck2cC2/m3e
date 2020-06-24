# the subdirectory
add_subdirectory(binder)
add_subdirectory(servicemanager)

add_subdirectory(ui)
add_subdirectory(gui)
if (ENABLE_SURFACE_FLINGER)
    add_subdirectory(surfaceflinger)
endif(ENABLE_SURFACE_FLINGER)

add_subdirectory(audiomanager)

add_subdirectory(opengl)
