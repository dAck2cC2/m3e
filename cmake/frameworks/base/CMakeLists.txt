
# the subdirectory
if(ENABLE_AV_UTILS)
    add_subdirectory(androidfw)
    if (NOT LINUX)
         add_subdirectory(bootanimation)
    endif()    
endif(ENABLE_AV_UTILS)
