
# the subdirectory
if(ENABLE_AV_UTILS)
    add_subdirectory(androidfw)
    add_subdirectory(android)
endif(ENABLE_AV_UTILS)

if (ENABLE_SURFACE_FLINGER)
    add_subdirectory(bootanimation)
endif(ENABLE_SURFACE_FLINGER)    
