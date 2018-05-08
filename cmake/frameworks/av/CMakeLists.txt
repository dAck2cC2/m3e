# the subdirectory
if(ENABLE_AV_UTILS)
    add_subdirectory(stagefright_foundation)
endif(ENABLE_AV_UTILS)

if(ENABLE_AV_BASE)
    add_subdirectory(media)
    add_subdirectory(stagefright)
endif(ENABLE_AV_BASE)

if(ENABLE_AV_CODEC)
    add_subdirectory(stagefright_mediafilter)
    add_subdirectory(stagefright_omx)
    add_subdirectory(stagefright_color_conversion)
endif(ENABLE_AV_CODEC)
