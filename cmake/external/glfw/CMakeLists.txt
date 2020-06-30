cmake_minimum_required(VERSION 3.0)

project(GLFW VERSION 3.3.2 LANGUAGES C)

if(NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH}/glfw)
  message(STATUS "Download\tglfw")
  exec_program("git clone https://github.com/glfw/glfw.git" ${M3E_SOURCE_DIR}/${EXT_PATH})
  exec_program("git checkout tags/3.3.2" ${M3E_SOURCE_DIR}/${EXT_PATH}/glfw)
endif()

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

set(HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/glfw/include)
set(SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/glfw/src)

set(CMAKE_LEGACY_CYGWIN_WIN32 OFF)

if (POLICY CMP0054)
    cmake_policy(SET CMP0054 NEW)
endif()

if (POLICY CMP0077)
    cmake_policy(SET CMP0077 NEW)
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)
option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
option(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
option(GLFW_INSTALL "Generate installation target" OFF)
option(GLFW_VULKAN_STATIC "Assume the Vulkan loader is linked with the application" OFF)

include(GNUInstallDirs)
include(CMakeDependentOption)

cmake_dependent_option(GLFW_USE_OSMESA "Use OSMesa for offscreen context creation" OFF
                       "UNIX" OFF)
cmake_dependent_option(GLFW_USE_HYBRID_HPG "Force use of high-performance GPU on hybrid systems" OFF
                       "WIN32" OFF)
cmake_dependent_option(GLFW_USE_WAYLAND "Use Wayland for window creation" OFF
                       "UNIX;NOT APPLE" OFF)
cmake_dependent_option(USE_MSVC_RUNTIME_LIBRARY_DLL "Use MSVC runtime library DLL" ON
                       "MSVC" OFF)

if (BUILD_SHARED_LIBS)
    set(_GLFW_BUILD_DLL 1)
endif()

if (BUILD_SHARED_LIBS AND UNIX)
    # On Unix-like systems, shared libraries can use the soname system.
    set(GLFW_LIB_NAME glfw)
else()
    set(GLFW_LIB_NAME glfw3)
endif()

if (GLFW_VULKAN_STATIC)
    if (BUILD_SHARED_LIBS)
        # If you absolutely must do this, remove this line and add the Vulkan
        # loader static library via the CMAKE_SHARED_LINKER_FLAGS
        message(FATAL_ERROR "You are trying to link the Vulkan loader static library into the GLFW shared library")
    endif()
    set(_GLFW_VULKAN_STATIC 1)
endif()

list(APPEND CMAKE_MODULE_PATH "${M3E_SOURCE_DIR}/${EXT_PATH}/glfw/CMake/modules")

find_package(Threads REQUIRED)

if (GLFW_BUILD_DOCS)
    set(DOXYGEN_SKIP_DOT TRUE)
    find_package(Doxygen)
endif()

#--------------------------------------------------------------------
# Set compiler specific flags
#--------------------------------------------------------------------
if (MSVC)
    if (MSVC90)
        # Workaround for VS 2008 not shipping with the DirectX 9 SDK
        include(CheckIncludeFile)
        check_include_file(dinput.h DINPUT_H_FOUND)
        if (NOT DINPUT_H_FOUND)
            message(FATAL_ERROR "DirectX 9 headers not found; install DirectX 9 SDK")
        endif()
        # Workaround for VS 2008 not shipping with stdint.h
        list(APPEND glfw_INCLUDE_DIRS "${GLFW_SOURCE_DIR}/deps/vs2008")
    endif()

    if (NOT USE_MSVC_RUNTIME_LIBRARY_DLL)
        foreach (flag CMAKE_C_FLAGS
                      CMAKE_C_FLAGS_DEBUG
                      CMAKE_C_FLAGS_RELEASE
                      CMAKE_C_FLAGS_MINSIZEREL
                      CMAKE_C_FLAGS_RELWITHDEBINFO)

            if (${flag} MATCHES "/MD")
                string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
            endif()
            if (${flag} MATCHES "/MDd")
                string(REGEX REPLACE "/MDd" "/MTd" ${flag} "${${flag}}")
            endif()

        endforeach()
    endif()
endif()

if (MINGW)
    # Workaround for legacy MinGW not providing XInput and DirectInput
    include(CheckIncludeFile)

    check_include_file(dinput.h DINPUT_H_FOUND)
    check_include_file(xinput.h XINPUT_H_FOUND)
    if (NOT DINPUT_H_FOUND OR NOT XINPUT_H_FOUND)
        list(APPEND glfw_INCLUDE_DIRS "${GLFW_SOURCE_DIR}/deps/mingw")
    endif()

    # Enable link-time exploit mitigation features enabled by default on MSVC
    include(CheckCCompilerFlag)

    # Compatibility with data execution prevention (DEP)
    set(CMAKE_REQUIRED_FLAGS "-Wl,--nxcompat")
    check_c_compiler_flag("" _GLFW_HAS_DEP)
    if (_GLFW_HAS_DEP)
        set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--nxcompat ${CMAKE_SHARED_LINKER_FLAGS}")
    endif()

    # Compatibility with address space layout randomization (ASLR)
    set(CMAKE_REQUIRED_FLAGS "-Wl,--dynamicbase")
    check_c_compiler_flag("" _GLFW_HAS_ASLR)
    if (_GLFW_HAS_ASLR)
        set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--dynamicbase ${CMAKE_SHARED_LINKER_FLAGS}")
    endif()

    # Compatibility with 64-bit address space layout randomization (ASLR)
    set(CMAKE_REQUIRED_FLAGS "-Wl,--high-entropy-va")
    check_c_compiler_flag("" _GLFW_HAS_64ASLR)
    if (_GLFW_HAS_64ASLR)
        set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--high-entropy-va ${CMAKE_SHARED_LINKER_FLAGS}")
    endif()
endif()

#--------------------------------------------------------------------
# Detect and select backend APIs
#--------------------------------------------------------------------
if (GLFW_USE_WAYLAND)
    set(_GLFW_WAYLAND 1)
    message(STATUS "Using Wayland for window creation")
elseif (GLFW_USE_OSMESA)
    set(_GLFW_OSMESA 1)
    message(STATUS "Using OSMesa for headless context creation")
elseif (WIN32)
    set(_GLFW_WIN32 1)
    message(STATUS "Using Win32 for window creation")
elseif (APPLE)
    set(_GLFW_COCOA 1)
    message(STATUS "Using Cocoa for window creation")
elseif (UNIX)
    set(_GLFW_X11 1)
    message(STATUS "Using X11 for window creation")
else()
    message(FATAL_ERROR "No supported platform was detected")
endif()

#--------------------------------------------------------------------
# Find and add Unix math and time libraries
#--------------------------------------------------------------------
if (UNIX AND NOT APPLE)
    find_library(RT_LIBRARY rt)
    mark_as_advanced(RT_LIBRARY)
    if (RT_LIBRARY)
        list(APPEND glfw_LIBRARIES "${RT_LIBRARY}")
        list(APPEND glfw_PKG_LIBS "-lrt")
    endif()

    find_library(MATH_LIBRARY m)
    mark_as_advanced(MATH_LIBRARY)
    if (MATH_LIBRARY)
        list(APPEND glfw_LIBRARIES "${MATH_LIBRARY}")
        list(APPEND glfw_PKG_LIBS "-lm")
    endif()

    if (CMAKE_DL_LIBS)
        list(APPEND glfw_LIBRARIES "${CMAKE_DL_LIBS}")
        list(APPEND glfw_PKG_LIBS "-l${CMAKE_DL_LIBS}")
    endif()
endif()

#--------------------------------------------------------------------
# Use Win32 for window creation
#--------------------------------------------------------------------
if (_GLFW_WIN32)

    list(APPEND glfw_PKG_LIBS "-lgdi32")

    if (GLFW_USE_HYBRID_HPG)
        set(_GLFW_USE_HYBRID_HPG 1)
    endif()
endif()

#--------------------------------------------------------------------
# Use X11 for window creation
#--------------------------------------------------------------------
if (_GLFW_X11)

    find_package(X11 REQUIRED)

    list(APPEND glfw_PKG_DEPS "x11")

    # Set up library and include paths
    list(APPEND glfw_INCLUDE_DIRS "${X11_X11_INCLUDE_PATH}")
    list(APPEND glfw_LIBRARIES "${X11_X11_LIB}" "${CMAKE_THREAD_LIBS_INIT}")

    # Check for XRandR (modern resolution switching and gamma control)
    if (NOT X11_Xrandr_INCLUDE_PATH)
        message(FATAL_ERROR "RandR headers not found; install libxrandr development package")
    endif()

    # Check for Xinerama (legacy multi-monitor support)
    if (NOT X11_Xinerama_INCLUDE_PATH)
        message(FATAL_ERROR "Xinerama headers not found; install libxinerama development package")
    endif()

    # Check for Xkb (X keyboard extension)
    if (NOT X11_Xkb_INCLUDE_PATH)
        message(FATAL_ERROR "XKB headers not found; install X11 development package")
    endif()

    # Check for Xcursor (cursor creation from RGBA images)
    if (NOT X11_Xcursor_INCLUDE_PATH)
        message(FATAL_ERROR "Xcursor headers not found; install libxcursor development package")
    endif()

    # Check for XInput (modern HID input)
    if (NOT X11_Xi_INCLUDE_PATH)
        message(FATAL_ERROR "XInput headers not found; install libxi development package")
    endif()

    list(APPEND glfw_INCLUDE_DIRS "${X11_Xrandr_INCLUDE_PATH}"
                                  "${X11_Xinerama_INCLUDE_PATH}"
                                  "${X11_Xkb_INCLUDE_PATH}"
                                  "${X11_Xcursor_INCLUDE_PATH}"
                                  "${X11_Xi_INCLUDE_PATH}")
endif()

#--------------------------------------------------------------------
# Use Wayland for window creation
#--------------------------------------------------------------------
if (_GLFW_WAYLAND)
    find_package(ECM REQUIRED NO_MODULE)
    list(APPEND CMAKE_MODULE_PATH "${ECM_MODULE_PATH}")

    find_package(Wayland REQUIRED Client Cursor Egl)
    find_package(WaylandScanner REQUIRED)
    find_package(WaylandProtocols 1.15 REQUIRED)

    list(APPEND glfw_PKG_DEPS "wayland-egl")

    list(APPEND glfw_INCLUDE_DIRS "${Wayland_INCLUDE_DIRS}")
    list(APPEND glfw_LIBRARIES "${Wayland_LIBRARIES}" "${CMAKE_THREAD_LIBS_INIT}")

    find_package(XKBCommon REQUIRED)
    list(APPEND glfw_INCLUDE_DIRS "${XKBCOMMON_INCLUDE_DIRS}")

    include(CheckIncludeFiles)
    include(CheckFunctionExists)
    check_include_files(xkbcommon/xkbcommon-compose.h HAVE_XKBCOMMON_COMPOSE_H)
    check_function_exists(memfd_create HAVE_MEMFD_CREATE)

    if (NOT ("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux"))
        find_package(EpollShim)
        if (EPOLLSHIM_FOUND)
            list(APPEND glfw_INCLUDE_DIRS "${EPOLLSHIM_INCLUDE_DIRS}")
            list(APPEND glfw_LIBRARIES "${EPOLLSHIM_LIBRARIES}")
        endif()
    endif()
endif()

#--------------------------------------------------------------------
# Use OSMesa for offscreen context creation
#--------------------------------------------------------------------
if (_GLFW_OSMESA)
    find_package(OSMesa REQUIRED)
    list(APPEND glfw_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}")
endif()

#--------------------------------------------------------------------
# Use Cocoa for window creation and NSOpenGL for context creation
#--------------------------------------------------------------------
if (_GLFW_COCOA)

    list(APPEND glfw_LIBRARIES
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreFoundation")

    set(glfw_PKG_DEPS "")
    set(glfw_PKG_LIBS "-framework Cocoa -framework IOKit -framework CoreFoundation")
endif()

#--------------------------------------------------------------------
# Add the Vulkan loader as a dependency if necessary
#--------------------------------------------------------------------
if (GLFW_VULKAN_STATIC)
    list(APPEND glfw_PKG_DEPS "vulkan")
endif()

#--------------------------------------------------------------------
# Export GLFW library dependencies
#--------------------------------------------------------------------
foreach(arg ${glfw_PKG_DEPS})
    set(GLFW_PKG_DEPS "${GLFW_PKG_DEPS} ${arg}")
endforeach()
foreach(arg ${glfw_PKG_LIBS})
    set(GLFW_PKG_LIBS "${GLFW_PKG_LIBS} ${arg}")
endforeach()

#--------------------------------------------------------------------
# Create generated files
#--------------------------------------------------------------------
include(CMakePackageConfigHelpers)

set(GLFW_CONFIG_PATH "${BUILD_PATH}/cmake/glfw3")

configure_package_config_file(${SOURCE_PATH}/glfw3Config.cmake.in
                              ${SOURCE_PATH}/glfw3Config.cmake
                              INSTALL_DESTINATION "${GLFW_CONFIG_PATH}"
                              NO_CHECK_REQUIRED_COMPONENTS_MACRO)

write_basic_package_version_file(${SOURCE_PATH}/glfw3ConfigVersion.cmake
                                 VERSION ${GLFW_VERSION}
                                 COMPATIBILITY SameMajorVersion)

configure_file(${SOURCE_PATH}/glfw_config.h.in ${SOURCE_PATH}/glfw_config.h @ONLY)

configure_file(${SOURCE_PATH}/glfw3.pc.in ${SOURCE_PATH}/glfw3.pc @ONLY)

#--------------------------------------------------------------------
# Add subdirectories
#--------------------------------------------------------------------
#add_subdirectory(src)

set(common_HEADERS ${SOURCE_PATH}/internal.h ${SOURCE_PATH}/mappings.h
                   "${SOURCE_PATH}/glfw_config.h"
                   "${HEADER_PATH}/GLFW/glfw3.h"
                   "${HEADER_PATH}/GLFW/glfw3native.h")
set(common_SOURCES ${SOURCE_PATH}/context.c ${SOURCE_PATH}/init.c ${SOURCE_PATH}/input.c ${SOURCE_PATH}/monitor.c ${SOURCE_PATH}/vulkan.c ${SOURCE_PATH}/window.c)

if (_GLFW_COCOA)
    set(glfw_HEADERS ${common_HEADERS} ${SOURCE_PATH}/cocoa_platform.h ${SOURCE_PATH}/cocoa_joystick.h
    ${SOURCE_PATH}/posix_thread.h ${SOURCE_PATH}/nsgl_context.h ${SOURCE_PATH}/egl_context.h ${SOURCE_PATH}/osmesa_context.h)
    set(glfw_SOURCES ${common_SOURCES} ${SOURCE_PATH}/cocoa_init.m ${SOURCE_PATH}/cocoa_joystick.m
    ${SOURCE_PATH}/cocoa_monitor.m ${SOURCE_PATH}/cocoa_window.m ${SOURCE_PATH}/cocoa_time.c ${SOURCE_PATH}/posix_thread.c
    ${SOURCE_PATH}/nsgl_context.m ${SOURCE_PATH}/egl_context.c ${SOURCE_PATH}/osmesa_context.c)
elseif (_GLFW_WIN32)
    set(glfw_HEADERS ${common_HEADERS} ${SOURCE_PATH}/win32_platform.h ${SOURCE_PATH}/win32_joystick.h
    ${SOURCE_PATH}/wgl_context.h ${SOURCE_PATH}/egl_context.h ${SOURCE_PATH}/osmesa_context.h)
    set(glfw_SOURCES ${common_SOURCES} ${SOURCE_PATH}/win32_init.c ${SOURCE_PATH}/win32_joystick.c
    ${SOURCE_PATH}/win32_monitor.c ${SOURCE_PATH}/win32_time.c ${SOURCE_PATH}/win32_thread.c ${SOURCE_PATH}/win32_window.c
    ${SOURCE_PATH}/wgl_context.c ${SOURCE_PATH}/egl_context.c ${SOURCE_PATH}/osmesa_context.c)
elseif (_GLFW_X11)
    set(glfw_HEADERS ${common_HEADERS} ${SOURCE_PATH}/x11_platform.h ${SOURCE_PATH}/xkb_unicode.h ${SOURCE_PATH}/posix_time.h
    ${SOURCE_PATH}/posix_thread.h ${SOURCE_PATH}/glx_context.h ${SOURCE_PATH}/egl_context.h ${SOURCE_PATH}/osmesa_context.h)
    set(glfw_SOURCES ${common_SOURCES} ${SOURCE_PATH}/x11_init.c ${SOURCE_PATH}/x11_monitor.c ${SOURCE_PATH}/x11_window.c
    ${SOURCE_PATH}/xkb_unicode.c ${SOURCE_PATH}/posix_time.c ${SOURCE_PATH}/posix_thread.c ${SOURCE_PATH}/glx_context.c
    ${SOURCE_PATH}/egl_context.c ${SOURCE_PATH}/osmesa_context.c)
elseif (_GLFW_WAYLAND)
    set(glfw_HEADERS ${common_HEADERS}  ${SOURCE_PATH}/wl_platform.h
    ${SOURCE_PATH}/posix_time.h  ${SOURCE_PATH}/posix_thread.h  ${SOURCE_PATH}/xkb_unicode.h  ${SOURCE_PATH}/egl_context.h
    ${SOURCE_PATH}/osmesa_context.h)
    set(glfw_SOURCES ${common_SOURCES}  ${SOURCE_PATH}/wl_init.c  ${SOURCE_PATH}/wl_monitor.c  ${SOURCE_PATH}/wl_window.c
    ${SOURCE_PATH}/posix_time.c  ${SOURCE_PATH}/posix_thread.c  ${SOURCE_PATH}/xkb_unicode.c
    ${SOURCE_PATH}/egl_context.c  ${SOURCE_PATH}/osmesa_context.c)

    ecm_add_wayland_client_protocol(glfw_SOURCES
        PROTOCOL
        "${WAYLAND_PROTOCOLS_PKGDATADIR}/stable/xdg-shell/xdg-shell.xml"
        BASENAME xdg-shell)
    ecm_add_wayland_client_protocol(glfw_SOURCES
        PROTOCOL
        "${WAYLAND_PROTOCOLS_PKGDATADIR}/unstable/xdg-decoration/xdg-decoration-unstable-v1.xml"
        BASENAME xdg-decoration)
    ecm_add_wayland_client_protocol(glfw_SOURCES
        PROTOCOL
        "${WAYLAND_PROTOCOLS_PKGDATADIR}/stable/viewporter/viewporter.xml"
        BASENAME viewporter)
    ecm_add_wayland_client_protocol(glfw_SOURCES
        PROTOCOL
        "${WAYLAND_PROTOCOLS_PKGDATADIR}/unstable/relative-pointer/relative-pointer-unstable-v1.xml"
        BASENAME relative-pointer-unstable-v1)
    ecm_add_wayland_client_protocol(glfw_SOURCES
        PROTOCOL
        "${WAYLAND_PROTOCOLS_PKGDATADIR}/unstable/pointer-constraints/pointer-constraints-unstable-v1.xml"
        BASENAME pointer-constraints-unstable-v1)
    ecm_add_wayland_client_protocol(glfw_SOURCES
        PROTOCOL
        "${WAYLAND_PROTOCOLS_PKGDATADIR}/unstable/idle-inhibit/idle-inhibit-unstable-v1.xml"
        BASENAME idle-inhibit-unstable-v1)
elseif (_GLFW_OSMESA)
    set(glfw_HEADERS ${common_HEADERS} ${SOURCE_PATH}/pnull_platform.h ${SOURCE_PATH}/pnull_joystick.h
    ${SOURCE_PATH}/pposix_time.h ${SOURCE_PATH}/pposix_thread.h ${SOURCE_PATH}/posmesa_context.h)
    set(glfw_SOURCES ${common_SOURCES} ${SOURCE_PATH}/pnull_init.c ${SOURCE_PATH}/pnull_monitor.c ${SOURCE_PATH}/pnull_window.c
    ${SOURCE_PATH}/pnull_joystick.c ${SOURCE_PATH}/pposix_time.c ${SOURCE_PATH}/pposix_thread.c ${SOURCE_PATH}/posmesa_context.c)
endif()

if (_GLFW_X11 OR _GLFW_WAYLAND)
    if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
        set(glfw_HEADERS ${glfw_HEADERS} ${SOURCE_PATH}/linux_joystick.h)
        set(glfw_SOURCES ${glfw_SOURCES} ${SOURCE_PATH}/linux_joystick.c)
    else()
        set(glfw_HEADERS ${glfw_HEADERS} ${SOURCE_PATH}/null_joystick.h)
        set(glfw_SOURCES ${glfw_SOURCES} ${SOURCE_PATH}/null_joystick.c)
    endif()
endif()

if (APPLE)
    # For some reason CMake didn't know about .m until version 3.16
    set_source_files_properties(${SOURCE_PATH}/cocoa_init.m ${SOURCE_PATH}/cocoa_joystick.m ${SOURCE_PATH}/cocoa_monitor.m
    ${SOURCE_PATH}/cocoa_window.m ${SOURCE_PATH}/nsgl_context.m PROPERTIES
                                LANGUAGE C)
endif()

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(glfw SHARED ${glfw_SOURCES} ${glfw_HEADERS})

if (${CMAKE_VERSION} VERSION_EQUAL "3.1.0" OR
    ${CMAKE_VERSION} VERSION_GREATER "3.1.0")

    set_target_properties(glfw PROPERTIES C_STANDARD 99)
else()
    # Remove this fallback when removing support for CMake version less than 3.1
    target_compile_options(glfw PRIVATE
                           "$<$<C_COMPILER_ID:AppleClang>:-std=c99>"
                           "$<$<C_COMPILER_ID:Clang>:-std=c99>"
                           "$<$<C_COMPILER_ID:GNU>:-std=c99>")
endif()

target_compile_definitions(glfw PRIVATE _GLFW_USE_CONFIG_H)


target_link_libraries(glfw PRIVATE ${glfw_LIBRARIES})

if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_C_COMPILER_ID}" STREQUAL "Clang" OR
    "${CMAKE_C_COMPILER_ID}" STREQUAL "AppleClang")

    # Make GCC and Clang warn about declarations that VS 2010 and 2012 won't
    # accept for all source files that VS will build
    set_source_files_properties(${SOURCE_PATH}/context.c ${SOURCE_PATH}/init.c ${SOURCE_PATH}/input.c ${SOURCE_PATH}/monitor.c ${SOURCE_PATH}/vulkan.c
    ${SOURCE_PATH}/window.c ${SOURCE_PATH}/win32_init.c ${SOURCE_PATH}/win32_joystick.c
    ${SOURCE_PATH}/win32_monitor.c ${SOURCE_PATH}/win32_time.c ${SOURCE_PATH}/win32_thread.c
    ${SOURCE_PATH}/win32_window.c ${SOURCE_PATH}/wgl_context.c ${SOURCE_PATH}/egl_context.c
    ${SOURCE_PATH}/osmesa_context.c PROPERTIES
                                COMPILE_FLAGS -Wdeclaration-after-statement)

    # Enable a reasonable set of warnings (no, -Wextra is not reasonable)
    target_compile_options(glfw PRIVATE "-Wall")
endif()


if (WIN32)
    target_compile_definitions(glfw PRIVATE _UNICODE)
endif()

# HACK: When building on MinGW, WINVER and UNICODE need to be defined before
# the inclusion of stddef.h (by glfw3.h), which is itself included before
# win32_platform.h.  We define them here until a saner solution can be found
# NOTE: MinGW-w64 and Visual C++ do /not/ need this hack.
if (MINGW)
    target_compile_definitions(glfw PRIVATE UNICODE WINVER=0x0501)
endif()

if (BUILD_SHARED_LIBS)
    if (WIN32)
        if (MINGW)
            # Remove the dependency on the shared version of libgcc
            # NOTE: MinGW-w64 has the correct default but MinGW needs this
            target_link_libraries(glfw PRIVATE "-static-libgcc")

            # Remove the lib prefix on the DLL (but not the import library)
            set_target_properties(glfw PROPERTIES PREFIX "")

            # Add a suffix to the import library to avoid naming conflicts
            set_target_properties(glfw PROPERTIES IMPORT_SUFFIX "dll.a")
        else()
            # Add a suffix to the import library to avoid naming conflicts
            set_target_properties(glfw PROPERTIES IMPORT_SUFFIX "dll.lib")
        endif()

        target_compile_definitions(glfw INTERFACE GLFW_DLL)
    elseif (APPLE)
        # Add -fno-common to work around a bug in Apple's GCC
        target_compile_options(glfw PRIVATE "-fno-common")

        set_target_properties(glfw PROPERTIES
                              INSTALL_NAME_DIR "${CMAKE_INSTALL_LIBDIR}")
    endif()

    if (UNIX)
        # Hide symbols not explicitly tagged for export from the shared library
        target_compile_options(glfw PRIVATE "-fvisibility=hidden")
    endif()
endif()

if (MSVC)
    target_compile_definitions(glfw PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()



#set(ENABLE_TEST  TRUE)
if(ENABLE_TEST)
  add_subdirectory(test)
endif(ENABLE_TEST)
