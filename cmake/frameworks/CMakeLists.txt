
if(ENABLE_NATIVE)
    add_subdirectory(native)
endif(ENABLE_NATIVE)

if(ENABLE_AV_CODEC)
    add_subdirectory(rs)
    add_subdirectory(wilhelm)
endif(ENABLE_AV_CODEC)

add_subdirectory(av)
add_subdirectory(base)
