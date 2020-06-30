project(TEST_GLFW)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/glfw/include.cmake)

set(DEMO_DEPLIBS
glfw
)

set(ROOT_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/glfw)
set(SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/glfw/examples)

include_directories(AFTER ${ROOT_PATH}/deps)


if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

if (WIN32)
    set(ICON ${SOURCE_PATH}/glfw.rc)
elseif (APPLE)
    set(ICON ${SOURCE_PATH}/glfw.icns)
endif()

if (${CMAKE_VERSION} VERSION_EQUAL "3.1.0" OR
    ${CMAKE_VERSION} VERSION_GREATER "3.1.0")
    set(CMAKE_C_STANDARD 99)
else()
    # Remove this fallback when removing support for CMake version less than 3.1
    add_compile_options("$<$<C_COMPILER_ID:AppleClang>:-std=c99>"
                        "$<$<C_COMPILER_ID:Clang>:-std=c99>"
                        "$<$<C_COMPILER_ID:GNU>:-std=c99>")

endif()

set(GLAD_GL "${ROOT_PATH}/deps/glad/gl.h"
            "${ROOT_PATH}/deps/glad_gl.c")
set(GETOPT "${ROOT_PATH}/deps/getopt.h"
           "${ROOT_PATH}/deps/getopt.c")
set(TINYCTHREAD "${ROOT_PATH}/deps/tinycthread.h"
                "${ROOT_PATH}/deps/tinycthread.c")

ADD_DEMO(boing WIN32 MACOSX_BUNDLE ${SOURCE_PATH}/boing.c ${ICON} ${GLAD_GL})


set(GUI_ONLY_BINARIES 
test_boing 
#test_gears test_heightmap test_particles test_sharing test_simple test_splitview test_wave
)
set(CONSOLE_BINARIES 
#test_offscreen
)

if (MSVC)
    # Tell MSVC to use main instead of WinMain for Windows subsystem executables
    set_target_properties(${GUI_ONLY_BINARIES} PROPERTIES
                          LINK_FLAGS "/ENTRY:mainCRTStartup")
endif()


if (APPLE)
    set_target_properties(test_boing PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "Boing")
    #set_target_properties(test_gears PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "Gears")
    #set_target_properties(test_heightmap PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "Heightmap")
    #set_target_properties(test_particles PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "Particles")
    #set_target_properties(test_sharing PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "Sharing")
    #set_target_properties(test_simple PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "Simple")
    #set_target_properties(test_splitview PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "SplitView")
    #set_target_properties(test_wave PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "Wave")

    set_source_files_properties(${SOURCE_PATH}/glfw.icns PROPERTIES
                                MACOSX_PACKAGE_LOCATION "Resources")
    set_target_properties(${GUI_ONLY_BINARIES} PROPERTIES
                          MACOSX_BUNDLE_SHORT_VERSION_STRING ${GLFW_VERSION}
                          MACOSX_BUNDLE_LONG_VERSION_STRING ${GLFW_VERSION}
                          MACOSX_BUNDLE_ICON_FILE  ${SOURCE_PATH}/glfw.icns
                          MACOSX_BUNDLE_INFO_PLIST "${ROOT_PATH}/CMake/MacOSXBundleInfo.plist.in")
endif()
