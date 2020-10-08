
set(HWC_VER_1    1)
set(HWC_VER_2    2)

# SurfaceFlinger of Android 9 is using HW composer 2
set(HWC_VERSION  2)

###############################################################################
# The HW composer2 works as unique so file
if(HWC_VERSION EQUAL HWC_VER_2)

    if (ENABLE_GLFW)
        add_subdirectory(glfw)
    else ()
        add_subdirectory(angle)
    endif()

###############################################################################
# The legacy HW composer uses separated cmake to generate so files
else()

    if(MSVC)
        add_subdirectory(win)
    elseif(APPLE)
        add_subdirectory(osx)
    endif()

endif()