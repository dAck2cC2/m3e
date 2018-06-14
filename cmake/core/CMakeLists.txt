# the subdirectory
add_subdirectory(log)
add_subdirectory(cutils)
add_subdirectory(utils)
add_subdirectory(sync)

if(ENABLE_AV_UTILS)
    add_subdirectory(base)
    add_subdirectory(ziparchive)
endif(ENABLE_AV_UTILS)
