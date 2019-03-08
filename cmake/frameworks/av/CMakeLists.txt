# the subdirectory
if(ENABLE_AV_UTILS)
    add_subdirectory(stagefright_foundation)
    add_subdirectory(media) 
    add_subdirectory(services) 
endif(ENABLE_AV_UTILS)

if(ENABLE_AV_BASE)
    add_subdirectory(stagefright)
    add_subdirectory(drm) 
endif(ENABLE_AV_BASE)

if(ENABLE_AV_CODEC)
    add_subdirectory(cmds) 
    add_subdirectory(camera)
    add_subdirectory(stagefright_omx)
    add_subdirectory(soundtrigger)
endif(ENABLE_AV_CODEC)
