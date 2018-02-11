# the subdirectory
if(ENABLE_CORE)
add_subdirectory(core)
endif(ENABLE_CORE)

if(ENABLE_MISC)
add_subdirectory(misc)
endif(ENABLE_MISC)

add_subdirectory(av)
