
if(ENABLE_NATIVE)
    add_subdirectory(native)
endif(ENABLE_NATIVE)

if(ENABLE_HARDWARE)
    add_subdirectory(initrc)
endif(ENABLE_HARDWARE)

add_subdirectory(av)
