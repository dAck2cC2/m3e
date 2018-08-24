
if(ENABLE_NATIVE)
    add_subdirectory(native)
endif(ENABLE_NATIVE)

if(ENABLE_HARDWARE)
    add_subdirectory(initrc)
endif(ENABLE_HARDWARE)

if(ENABLE_AV_CODEC)
    add_subdirectory(rs)
endif(ENABLE_AV_CODEC)

add_subdirectory(av)
add_subdirectory(base)
