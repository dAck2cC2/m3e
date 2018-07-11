# the subdirectory
add_subdirectory(av)
add_subdirectory(external)

if(ENABLE_CORE)
    add_subdirectory(core)
endif(ENABLE_CORE)

if(ENABLE_NATIVE)
    add_subdirectory(native)
endif(ENABLE_NATIVE)
