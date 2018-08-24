if(ENABLE_AV_UTILS)
    add_subdirectory(audioflinger) 
endif(ENABLE_AV_UTILS)

if(ENABLE_AV_CODEC)
    add_subdirectory(mediacodec) 
endif(ENABLE_AV_CODEC)
