
project(FREEGLUT)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/freeglut/include.cmake)

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src)

# setup version numbers
# TODO: Update these for each release!
set(VERSION_MAJOR 3)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)
set(VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})


# option to also copy .pdb files to install directory when executing
# INSTALL target
IF(MSVC)
    OPTION(INSTALL_PDB "Also install .pdb files" ON)
ELSE()
    SET(INSTALL_PDB OFF)
ENDIF()

# OpenGL ES support
OPTION(FREEGLUT_GLES "Use OpenGL ES (requires EGL)" OFF)

# option to build either as "glut" (ON) or "freeglut" (OFF)
IF(WIN32)
    OPTION(FREEGLUT_REPLACE_GLUT "Be a replacement for GLUT" ON)
ELSE()
    OPTION(FREEGLUT_REPLACE_GLUT "Be a replacement for GLUT" ON)
ENDIF()

IF(NOT WIN32)
    # Wayland support
    OPTION(FREEGLUT_WAYLAND "Use Wayland (no X11)" OFF)
ENDIF()

FILE(GLOB FREEGLUT_HEADERS
${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/include/GL/*.h
)

SET(FREEGLUT_SRCS 
${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/fg_callbacks.c
${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/fg_cursor.c
${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/fg_display.c
${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/fg_ext.c
${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/fg_font_data.c
${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/fg_gamemode.c
${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/fg_geometry.c
${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/fg_gl2.c
${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/fg_gl2.h
${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/fg_init.c
${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/fg_init.h
${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/fg_internal.h
${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/fg_callback_macros.h
${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/fg_input_devices.c
${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/fg_joystick.c
${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/fg_main.c
${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/fg_misc.c
${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/fg_overlay.c
${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/fg_spaceball.c
${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/fg_state.c
${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/fg_stroke_mono_roman.c
${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/fg_stroke_roman.c
${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/fg_structure.c
${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/fg_teapot.c
${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/fg_teapot_data.h
${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/fg_videoresize.c
${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/fg_window.c
)

# TODO: OpenGL ES requires a compatible version of these files:
IF(NOT FREEGLUT_GLES)
    LIST(APPEND FREEGLUT_SRCS
        ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/fg_font.c
        ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/fg_menu.c
    )
ELSE()
    LIST(APPEND FREEGLUT_SRCS
        ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/gles_stubs.c
    )
ENDIF()

IF(WIN32)
    LIST(APPEND FREEGLUT_SRCS
        ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/mswin/fg_cursor_mswin.c
        ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/mswin/fg_display_mswin.c
        ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/mswin/fg_ext_mswin.c
        ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/mswin/fg_gamemode_mswin.c
        ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/mswin/fg_init_mswin.c
        ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/mswin/fg_internal_mswin.h
        ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/mswin/fg_input_devices_mswin.c
        ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/mswin/fg_joystick_mswin.c
        ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/mswin/fg_main_mswin.c
        ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/mswin/fg_menu_mswin.c
        ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/mswin/fg_spaceball_mswin.c
        ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/mswin/fg_state_mswin.c
        ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/mswin/fg_structure_mswin.c
        ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/mswin/fg_window_mswin.c
        ${CMAKE_BINARY_DIR}/freeglut.rc # generated below from freeglut.rc.in
    )
    IF (MSVC AND NOT CMAKE_CL_64)
        # .def file only for 32bit Windows builds (TODO: MSVC only right
        # now, needed for any other Windows platform?)
        LIST(APPEND FREEGLUT_SRCS
            ${CMAKE_BINARY_DIR}/freeglutdll.def # generated below from src/freeglutdll.def.in
        )
    ENDIF()

ELSE()
    # UNIX (Wayland)
    IF(FREEGLUT_WAYLAND)
        LIST(APPEND FREEGLUT_SRCS
            ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/wayland/fg_cursor_wl.c
            ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/wayland/fg_ext_wl.c
            ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/wayland/fg_gamemode_wl.c
            ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/wayland/fg_init_wl.c
            ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/wayland/fg_internal_wl.h
            ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/wayland/fg_input_devices_wl.c
            ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/wayland/fg_main_wl.c
            ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/wayland/fg_state_wl.c
            ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/wayland/fg_structure_wl.c
            ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/wayland/fg_window_wl.c
            # font, serial port & joystick code are agnostic
            ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/x11/fg_glutfont_definitions_x11.c
            ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/x11/fg_input_devices_x11.c
            ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/x11/fg_joystick_x11.c
        )
    # Mac OSX
    ELSEIF(APPLE)
        SET(CMAKE_C_FLAGS "-x objective-c")
        FIND_LIBRARY(COCOA_LIBRARY Cocoa)
        LIST(APPEND LIBS ${COCOA_LIBRARY})
        FIND_LIBRARY(COREVIDEO_LIBRARY CoreVideo)
        LIST(APPEND LIBS ${COREVIDEO_LIBRARY})
        FIND_LIBRARY(IOKIT_LIBRARY IOKit)
        LIST(APPEND LIBS ${IOKIT_LIBRARY})   
        INCLUDE_DIRECTORIES(AFTER ${M3E_SOURCE_DIR}/src/${EXT_PATH}/freeglut)
        LIST(APPEND FREEGLUT_SRCS
            ${M3E_SOURCE_DIR}/src/${EXT_PATH}/freeglut/fg_empty.c
            ${M3E_SOURCE_DIR}/src/${EXT_PATH}/freeglut/cocoa/fg_internal_cocoa.h
            ${M3E_SOURCE_DIR}/src/${EXT_PATH}/freeglut/cocoa/fg_init_cocoa.m
            ${M3E_SOURCE_DIR}/src/${EXT_PATH}/freeglut/cocoa/fg_main_cocoa.m
            ${M3E_SOURCE_DIR}/src/${EXT_PATH}/freeglut/cocoa/fg_window_cocoa.m
            ${M3E_SOURCE_DIR}/src/${EXT_PATH}/freeglut/cocoa/fg_window_cocoa_gl.m
            ${M3E_SOURCE_DIR}/src/${EXT_PATH}/freeglut/cocoa/fg_keyboard_cocoa.m
            ${M3E_SOURCE_DIR}/src/${EXT_PATH}/freeglut/cocoa/fg_cursor_cocoa.m  
            ${M3E_SOURCE_DIR}/src/${EXT_PATH}/freeglut/cocoa/fg_state_cocoa.m           
            ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/x11/fg_glutfont_definitions_x11.c
            ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/x11/fg_input_devices_x11.c              
        )
    # UNIX (X11)
    ELSE()
        LIST(APPEND FREEGLUT_SRCS
            ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/x11/fg_cursor_x11.c
            ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/x11/fg_ext_x11.c
            ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/x11/fg_gamemode_x11.c
            ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/x11/fg_glutfont_definitions_x11.c
            ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/x11/fg_init_x11.c
            ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/x11/fg_internal_x11.h
            ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/x11/fg_input_devices_x11.c
            ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/x11/fg_joystick_x11.c
            ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/x11/fg_main_x11.c
            ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/x11/fg_menu_x11.c
            ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/x11/fg_spaceball_x11.c
            ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/x11/fg_state_x11.c
            ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/x11/fg_structure_x11.c
            ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/x11/fg_window_x11.c
            ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/x11/fg_xinput_x11.c
        )
        IF(NOT(FREEGLUT_GLES))
            LIST(APPEND FREEGLUT_SRCS
                ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/x11/fg_internal_x11_glx.h
                ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/x11/fg_display_x11_glx.c
                ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/x11/fg_state_x11_glx.c
                ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/x11/fg_state_x11_glx.h
                ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/x11/fg_window_x11_glx.c
                ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/x11/fg_window_x11_glx.h
            )
        ENDIF()
    ENDIF()	
ENDIF()

# For OpenGL ES (GLES): compile with -DFREEGLUT_GLES to cleanly
# bootstrap headers inclusion in freeglut_std.h; this constant also
# need to be defined in client applications (e.g. through pkg-config),
# but do use GLES constants directly for all other needs
# GLES1 and GLES2 libraries are compatible and can be co-linked.
IF(FREEGLUT_GLES)
    LIST(APPEND PUBLIC_DEFINITIONS -DFREEGLUT_GLES)
    LIST(APPEND LIBS GLESv2 GLESv1_CM EGL)
ELSE()
  FIND_PACKAGE(OpenGL REQUIRED)
  LIST(APPEND LIBS ${OPENGL_gl_LIBRARY})
  INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
ENDIF()

# For Wayland: compile with -DFREEGLUT_WAYLAND and pull EGL
IF(FREEGLUT_WAYLAND)
  ADD_DEFINITIONS(-DFREEGLUT_WAYLAND)
  LIST(APPEND LIBS wayland-client wayland-cursor wayland-egl EGL xkbcommon)
ENDIF()

# lib m for math, not needed on windows
IF (NOT WIN32)
    # For compilation:
    LIST(APPEND LIBS m)
    # For CHECK_FUNCTION_EXISTS:
    LIST(APPEND CMAKE_REQUIRED_LIBRARIES m)
ENDIF()

IF(WIN32)
    # hide insecure CRT warnings, common practice
    ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
    IF(MSVC)
        SET( CMAKE_DEBUG_POSTFIX "d" )
    ENDIF(MSVC)
    
    IF(NOT(MSVC_VERSION LESS "1600"))
    # minimum requirement for WM_TOUCH device
        ADD_DEFINITIONS(-D_WIN32_WINNT=0x0601)
        ADD_DEFINITIONS(-DWINVER=0x0601)
    ELSEIF(NOT(MSVC_VERSION LESS "1300"))
    # minimum requirement for spaceball device
        ADD_DEFINITIONS(-D_WIN32_WINNT=0x0501)
        ADD_DEFINITIONS(-DWINVER=0x0501)
    ELSE()
    # enable the use of Win2000 APIs (needed for really old compilers like MSVC6)
        ADD_DEFINITIONS(-D_WIN32_WINNT=0x0500)
        ADD_DEFINITIONS(-DWINVER=0x0500)
    ENDIF()

ENDIF()

IF(CMAKE_COMPILER_IS_GNUCC)
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
  IF(NOT(ANDROID OR BLACKBERRY OR FREEGLUT_WAYLAND))
    # not setting -ansi as EGL/KHR headers doesn't support it
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic")
  ENDIF()
ENDIF(CMAKE_COMPILER_IS_GNUCC)

INCLUDE(CheckIncludeFiles)
IF(UNIX AND NOT(ANDROID OR BLACKBERRY OR FREEGLUT_WAYLAND OR APPLE))
    FIND_PACKAGE(X11 REQUIRED)
    INCLUDE_DIRECTORIES(${X11_INCLUDE_DIR})
    LIST(APPEND LIBS ${X11_LIBRARIES})
    IF(X11_Xrandr_FOUND)
        SET(HAVE_X11_EXTENSIONS_XRANDR_H TRUE)
        LIST(APPEND LIBS ${X11_Xrandr_LIB})
    ENDIF()
    IF(X11_xf86vmode_FOUND)
        SET(HAVE_X11_EXTENSIONS_XF86VMODE_H TRUE)
        LIST(APPEND LIBS ${X11_Xxf86vm_LIB})
    ENDIF()
    IF(X11_Xinput_FOUND)
        # Needed for multi-touch:
        CHECK_INCLUDE_FILES("${X11_Xinput_INCLUDE_PATH}/X11/extensions/XInput2.h" HAVE_X11_EXTENSIONS_XINPUT2_H)
        LIST(APPEND LIBS ${X11_Xinput_LIB})
    ELSE()
        MESSAGE(FATAL_ERROR "Missing X11's XInput.h (X11/extensions/XInput.h)")
    ENDIF()
ENDIF()
IF(ANDROID)
    # -landroid for ANativeWindow
    # -llog for native Android logging
    LIST(APPEND LIBS android log)
ELSEIF(BLACKBERRY)
    # -lbps for event loop
    # -screen for native screen
    LIST(APPEND LIBS bps screen)

    IF(NOT PLAYBOOK)
        # -lslog2 for logging
        # -pps for low-level screen manipulation
        LIST(APPEND LIBS slog2 pps)
    ENDIF()
ENDIF()

INCLUDE(CheckFunctionExists)
INCLUDE(CheckTypeSize)
IF (NOT APPLE)
CHECK_INCLUDE_FILES(unistd.h 	HAVE_UNISTD_H)
ENDIF()
CHECK_INCLUDE_FILES(sys/types.h HAVE_SYS_TYPES_H)
CHECK_INCLUDE_FILES(sys/time.h 	HAVE_SYS_TIME_H)
CHECK_INCLUDE_FILES(stdbool.h 	HAVE_STDBOOL_H)
CHECK_INCLUDE_FILES(sys/param.h HAVE_SYS_PARAM_H)
CHECK_INCLUDE_FILES(sys/ioctl.h HAVE_SYS_IOCTL_H)
CHECK_INCLUDE_FILES(fcntl.h 	HAVE_FCNTL_H)
CHECK_INCLUDE_FILES(usbhid.h 	HAVE_USBHID_H)
CHECK_FUNCTION_EXISTS(gettimeofday HAVE_GETTIMEOFDAY)
CHECK_FUNCTION_EXISTS(XParseGeometry   HAVE_XPARSEGEOMETRY)
IF (NOT HAVE_XPARSEGEOMETRY)
   LIST(APPEND FREEGLUT_SRCS
        ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/util/xparsegeometry_repl.c
        ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/util/xparsegeometry_repl.h)
   SET(NEED_XPARSEGEOMETRY_IMPL TRUE)
ENDIF()
# decide on suitable type for internal time keeping, 64-bit if possible
CHECK_INCLUDE_FILES(stdint.h    HAVE_STDINT_H)
CHECK_INCLUDE_FILES(inttypes.h  HAVE_INTTYPES_H)
IF (NOT (HAVE_STDINT_H OR HAVE_INTTYPES_H))
    IF (MSVC)
        # Some old Microsoft VC releases don't support unsigned long
        # long, but all we care about is support for unsigned __int64 on
        # MSVC, so test for presence of that type
        CHECK_TYPE_SIZE("unsigned __int64" U__INT64 BUILTIN_TYPES_ONLY)
    ELSEIF()
        CHECK_TYPE_SIZE("unsigned long long" ULONG_LONG BUILTIN_TYPES_ONLY)
    ENDIF()
ENDIF()

# The generated config.h is placed in the project's build directory, just to
# ensure that all CMake-generated files are kept away from the main source tree.
# As a result, the build directory must to be added to the include path list.
CONFIGURE_FILE(${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/config.h.in ${CMAKE_BINARY_DIR}/config.h)
INCLUDE_DIRECTORIES(BEFORE ${CMAKE_BINARY_DIR})
ADD_DEFINITIONS(-DHAVE_CONFIG_H)
IF(WIN32)
    # we also have to generate freeglut.rc, which contains the version
    # number
    CONFIGURE_FILE(${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/freeglut.rc.in ${CMAKE_BINARY_DIR}/freeglut.rc)
    IF (MSVC AND NOT CMAKE_CL_64)
        # .def file only for 32bit Windows builds with Visual Studio
        CONFIGURE_FILE(${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/src/freeglutdll.def.in ${CMAKE_BINARY_DIR}/freeglutdll.def)
    ENDIF()
ENDIF()

IF(WIN32)
    LIST(APPEND LIBS winmm)
	ADD_DEFINITIONS(-DFREEGLUT_EXPORTS)
	#TARGET_COMPILE_DEFINITIONS(freeglut PRIVATE FREEGLUT_EXPORTS)
ELSE()
ENDIF()	
	
SET(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
ADD_LIBRARY(freeglut SHARED ${FREEGLUT_SRCS} ${FREEGLUT_HEADERS})
TARGET_LINK_LIBRARIES(freeglut ${LIBS})
TARGET_COMPILE_DEFINITIONS(freeglut PUBLIC ${PUBLIC_DEFINITIONS})
	