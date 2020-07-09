
add_subdirectory(dump)

if(MSVC)
    add_subdirectory(wasapi)
elseif(APPLE)
    add_subdirectory(openal)
endif()
