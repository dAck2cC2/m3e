
project(ANGLE_ANGLE)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

add_definitions(-DNDEBUG=1)
#add_definitions(-DLIBANGLE_IMPLEMENTATION=1)

set(gl_prototypes                 "true")
set(angle_64bit_current_cpu       "true")
set(angle_enable_trace            "false")
set(is_chromeos                   "false")
set(angle_disable_pool_alloc      "false")
set(debug_annotations_config      "false")
set(is_debug                      "false")
set(angle_release_asserts_config  "false")
set(dcheck_always_on              "false")
set(angle_common_config           "true")
set(angle_gl_visibility_config    "true")
set(angle_enable_swiftshader      "false")
set(angle_backend_config          "true")
set(libANGLE_config               "true")
set(angle_enable_overlay          "false")
set(angle_frame_capture_disabled  "true")
set(angle_frame_capture_enabled   "false")

if(MSVC)
    #add_definitions(-DGL_API=__declspec\(dllexport\))
    #add_definitions(-DGL_APICALL=__declspec\(dllexport\))
    add_definitions(-D__SCITECH_SNAP__)
    add_definitions(-D__STDC_CONSTANT_MACROS)
    add_definitions(-DNOMINMAX=1)
    add_definitions(-D_ALLOW_KEYWORD_MACROS=1)
    add_definitions(-D__STDC_LIMIT_MACROS=1)
    add_definitions(-DZLIB_WINAPI)

    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_flag_suppoted)
    if (_cpp_flag_suppoted)
        add_compile_options("/std:c++latest")
    endif()

    include(${M3E_SOURCE_DIR}/cmake/tool/FindWindowsSDK.cmake)
    get_windowssdk_library_dirs(${WINDOWSSDK_PREFERRED_DIR} DirectX_LIBRARY_PATHS)
    #message("DirectX_LIBRARY_PATHS=${DirectX_LIBRARY_PATHS}")

    set(is_win             "true")
    set(angle_enable_hlsl  "true")
    set(angle_enable_d3d9  "true")
    set(angle_enable_d3d11 "true")

elseif(APPLE)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14 -stdlib=libc++")
    set(CMAKE_C_FLAGS "-x objective-c")

    set(is_mac             "true")
    set(angle_enable_glsl  "true")
    set(angle_enable_gl    "true")

elseif(LINUX)
    set(is_linux       "true")
    set(angle_use_x11  "false")
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/src )

#include_directories(AFTER ${HEADER_PATH})
#include_directories(AFTER ${SOURCE_PATH})
#include_directories(AFTER ${SOURCE_PATH}/common/third_party/base)

###############################################################################
#  zlib portable
#  It doesn't contain this part in Android 9 zlib, 
#  use the one frome Android 10.
###############################################################################
include(${M3E_SOURCE_DIR}/cmake/${EXT_PATH}/zlib/include.cmake)
list(APPEND ANGLE_DEPLIB zlib)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/${EXT_PATH}/zlib/google)
set(ANGLE_SOURCE_ZLIB 
${M3E_SOURCE_DIR}/src/${EXT_PATH}/zlib/google/compression_utils_portable.h
${M3E_SOURCE_DIR}/src/${EXT_PATH}/zlib/google/compression_utils_portable.cc
)
source_group(zlib FILES ${ANGLE_SOURCE_ZLIB})

###############################################################################
#  BUILD.gn
###############################################################################

# declare_args() {
  # Use the PCI lib to collect GPU information on Linux.
  set(use_libpci false)

  # Link in system libGL, to work with apitrace.  See doc/DebuggingTips.md.
  set(angle_link_glx false)

  # Defaults to capture building to $root_out_dir/angle_libs/with_capture.
  # Switch on to build capture to $root_out_dir.
  set(angle_with_capture_by_default false)

  # Don't build extra (test, samples etc) for Windows UWP. We don't have
  # infrastructure (e.g. windowing helper functions) in place to run them.
  set(angle_build_all false)

  # Enable generating current commit information using git
  set(angle_enable_commit_id true)
#}

#import("src/compiler.gni")
include(compiler_gni.cmake)

#import("src/libGLESv2.gni")
include(libGLESv2_gni.cmake)

# This config is exported to dependent targets (and also applied to internal
# ones).
#include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/include)
# exported header path is defined in include.cmake

# Prevent the GL headers from redeclaring ANGLE entry points.
if (no_gl_prototypes)
    add_definitions(-DGL_GLES_PROTOTYPES=0)
    add_definitions(-DEGL_EGL_PROTOTYPES=0)
endif(no_gl_prototypes)

if (gl_prototypes)
    add_definitions(-DGL_GLES_PROTOTYPES=1)
    add_definitions(-DEGL_EGL_PROTOTYPES=1)
    add_definitions(-DGL_GLEXT_PROTOTYPES)
    add_definitions(-DEGL_EGLEXT_PROTOTYPES)
endif(gl_prototypes)

# This config is applied to internal Angle targets (not pushed to dependents).
include_directories(AFTER ${HEADER_PATH})
include_directories(AFTER ${SOURCE_PATH})

if (angle_64bit_current_cpu)
    add_definitions(-DANGLE_IS_64_BIT_CPU)
else(angle_64bit_current_cpu)
    add_definitions(-DANGLE_IS_32_BIT_CPU)
endif(angle_64bit_current_cpu)

if (angle_enable_trace)
    add_definitions(-DANGLE_ENABLE_DEBUG_TRACE=1)
endif(angle_enable_trace)

if (is_chromeos) 
    add_definitions(-DANGLE_PLATFORM_CHROMEOS)
endif(is_chromeos)

# ......

# angle_static_library("preprocessor") {
set(ANGLE_SOURCE_PREPROCESSOR ${angle_preprocessor_sources})
source_group(preprocessor FILES ${ANGLE_SOURCE_PREPROCESSOR})

if (angle_disable_pool_alloc)
    add_definitions(-DANGLE_DISABLE_POOL_ALLOC)
endif(angle_disable_pool_alloc)

if (debug_annotations_config)
    if (is_debug)
        add_definitions(-DANGLE_ENABLE_DEBUG_ANNOTATIONS)
    endif(is_debug)
endif(debug_annotations_config)

if (angle_release_asserts_config)
    if (dcheck_always_on)
        add_definitions(-DANGLE_ENABLE_RELEASE_ASSERTS)
    endif(dcheck_always_on)
endif(angle_release_asserts_config)

if (angle_common_config)
    include_directories(AFTER ${SOURCE_PATH}/common/third_party/base)
endif(angle_common_config)

# angle_source_set("angle_system_utils") {
set(ANGLE_SOURCE_SYSTEM_UTILS ${angle_system_utils_sources})
source_group(angle_system_utils FILES ${ANGLE_SOURCE_SYSTEM_UTILS})
    
# angle_source_set("xxhash") {
set(ANGLE_SOURCE_XXHASH ${xxhash_sources})
source_group(xxhash FILES ${ANGLE_SOURCE_XXHASH})
    
# ...

# angle_static_library("angle_common") {
set(ANGLE_SOURCE_COMMON ${libangle_common_sources})
source_group(angle_common FILES ${ANGLE_SOURCE_COMMON})
    
# ...

# angle_static_library("angle_image_util") {
set(ANGLE_SOURCE_IMAGE_UTILS
${libangle_image_util_headers}
${libangle_image_util_sources}
)
source_group(angle_image_util FILES ${ANGLE_SOURCE_IMAGE_UTILS})
    
if (angle_gl_visibility_config)
    if (is_win)
        add_definitions(-DGL_APICALL=__declspec\(dllexport\))
        add_definitions(-DGL_API=__declspec\(dllexport\))
    else(is_win)
        add_definitions(-DGL_APICALL=__attribute__\(\(visibility\(\"default\"\)\)\))
        add_definitions(-DGL_API=__attribute__\(\(visibility\(\"default\"\)\)\))
    endif(is_win)
endif(angle_gl_visibility_config)

# angle_static_library("angle_gpu_info_util") {
set(ANGLE_SOURCE_GPU_INFO_UTILS ${libangle_gpu_info_util_sources})
if (is_win)
    list(APPEND ANGLE_SOURCE_GPU_INFO_UTILS ${libangle_gpu_info_util_win_sources})
    list(APPEND ANGLE_DEPLIB dxgi)
endif(is_win)
if (is_linux)
    list(APPEND ANGLE_SOURCE_GPU_INFO_UTILS ${libangle_gpu_info_util_linux_sources})
    if (angle_use_x11)
        list(APPEND ANGLE_SOURCE_GPU_INFO_UTILS ${libangle_gpu_info_util_x11_sources})
        add_definitions(-DGPU_INFO_USE_X11)
        list(APPEND ANGLE_DEPLIB X11 Xi Xext)
    endif(angle_use_x11)
endif(is_linux)
if (is_mac)
    list(APPEND ANGLE_SOURCE_GPU_INFO_UTILS ${libangle_gpu_info_util_mac_sources})
    find_library(IOKIT_LIBRARY IOKit)
    list(APPEND ANGLE_DEPLIB ${IOKIT_LIBRARY})
    find_library(COREFUNDATION_LIBRARY CoreFoundation)
    list(APPEND ANGLE_DEPLIB ${COREFUNDATION_LIBRARY})
    find_library(COREGRAPHICS_LIBRARY CoreGraphics)
    list(APPEND ANGLE_DEPLIB ${COREGRAPHICS_LIBRARY})
    find_library(OPENGL_LIBRARY OpenGL)
    list(APPEND ANGLE_DEPLIB ${OPENGL_LIBRARY})
endif(is_mac)
source_group(angle_gpu_info_util FILES ${ANGLE_SOURCE_GPU_INFO_UTILS})

# angle_static_library("translator") {
set(ANGLE_SOURCE_TRANSLATOR 
${angle_translator_exported_headers}
${angle_translator_sources}
)
if (angle_enable_glsl)
    list(APPEND ANGLE_SOURCE_TRANSLATOR ${angle_translator_glsl_sources})
    add_definitions(-DANGLE_ENABLE_GLSL=1)
endif(angle_enable_glsl)
if (angle_enable_hlsl)
    list(APPEND ANGLE_SOURCE_TRANSLATOR ${angle_translator_hlsl_sources})
    add_definitions(-DANGLE_ENABLE_HLSL=1)
endif(angle_enable_hlsl)
source_group(translator FILES ${ANGLE_SOURCE_TRANSLATOR})

if (angle_enable_swiftshader)
    add_definitions(-DANGLE_ENABLE_SWIFTSHADER)
endif(angle_enable_swiftshader)

if (is_win)
    # Necessary to suppress some system header xtree warnigns in Release.
    # For some reason this warning doesn't get triggered in Chromium
    add_compile_options("/wd4718")
endif(is_win)

# angle_source_set("translator_fuzzer") {
set(ANGLE_SOURCE_TRANSLATOR_FUZZER  ${SOURCE_PATH}/compiler/fuzz/translator_fuzzer.cpp)
source_group(translator_fuzzer FILES ${ANGLE_SOURCE_TRANSLATOR_FUZZER})
    
# action("commit_id") {
set( ID_SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/src )
if(NOT EXISTS ${ID_SOURCE_PATH}/id)
    exec_program("cmake -E make_directory id" ${ID_SOURCE_PATH})
    exec_program("python commit_id.py gen ./id/commit.h" ${ID_SOURCE_PATH})
endif()
include_directories(AFTER ${ID_SOURCE_PATH}/id)

# angle_source_set("angle_version") {
set(ANGLE_SOURCE_VERSION  ${SOURCE_PATH}/common/version.h)
source_group(angle_version FILES ${ANGLE_SOURCE_VERSION})
    
if (angle_backend_config)
    if (angle_enable_d3d9) 
        add_definitions(-DANGLE_ENABLE_D3D9=1)
    endif(angle_enable_d3d9)
    if (angle_enable_d3d11)
        add_definitions(-DANGLE_ENABLE_D3D11=1)
    endif(angle_enable_d3d11)
    if (angle_enable_gl)
        add_definitions(-DANGLE_ENABLE_OPENGL=1)
    endif(angle_enable_gl)
    if (angle_enable_null)
        add_definitions(-DANGLE_ENABLE_NULL=1)
    endif(angle_enable_null)
endif(angle_backend_config)

if (libANGLE_config)
    if (angle_enable_d3d9)
        find_library(D3D9_LIBRARY d3d9 ${DirectX_LIBRARY_PATHS} NO_DEFAULT_PATH)
        list(APPEND ANGLE_DEPLIB ${D3D9_LIBRARY})
    endif(angle_enable_d3d9)

    add_definitions(-DLIBANGLE_IMPLEMENTATION=1)

    if (is_win)
        # C++ exception handler used, but unwind semantics
        # are not enabled.
        add_compile_options("/wd4718")
    endif(is_win)

    if (angle_use_x11)
        add_definitions(-DANGLE_USE_X11=1)
    endif(angle_use_x11)

    if (angle_enable_overlay)
        add_definitions(-DANGLE_ENABLE_OVERLAY=1)
    endif(angle_enable_overlay)
endif(libANGLE_config)

# angle_source_set("libANGLE_headers") {
set(ANGLE_SOURCE_LIBANGLE_HEADERS ${libangle_headers})
source_group(libANGLE_headers FILES ${ANGLE_SOURCE_LIBANGLE_HEADERS})
    
#angle_source_set("libANGLE_base") {
set(ANGLE_SOURCE_LIBANGLE_BASE ${libangle_sources})
if (is_win)
    if (angle_enable_d3d9)
        # cannot find this library.
        #find_library(DELAYIMP_LIBRARY delayimp ${DirectX_LIBRARY_PATHS} NO_DEFAULT_PATH)
        #list(APPEND ANGLE_DEPLIB ${DELAYIMP_LIBRARY})
    endif(angle_enable_d3d9)

    # it seems already included automatically
    #find_library(GDI32_LIBRARY gdi32 ${DirectX_LIBRARY_PATHS} NO_DEFAULT_PATH)
    #list(APPEND ANGLE_DEPLIB ${GDI32_LIBRARY})
    #find_library(USER32_LIBRARY user32 ${DirectX_LIBRARY_PATHS} NO_DEFAULT_PATH)
    #list(APPEND ANGLE_DEPLIB ${USER32_LIBRARY})
endif(is_win)
if (angle_enable_d3d9 OR angle_enable_d3d11)
    list(APPEND ANGLE_SOURCE_LIBANGLE_BASE ${libangle_d3d_shared_sources})
    #add_definitions(-DANGLE_PRELOADED_D3DCOMPILER_MODULE_NAMES=\{ \" + \"\"d3dcompiler_47.dll\", \"d3dcompiler_46.dll\", \"d3dcompiler_43.dll\" \}\")
endif()
if (angle_enable_d3d9)
    list(APPEND ANGLE_SOURCE_LIBANGLE_BASE ${libangle_d3d9_sources})
    find_library(D3D9_LIBRARY d3d9 ${DirectX_LIBRARY_PATHS} NO_DEFAULT_PATH)
    list(APPEND ANGLE_DEPLIB ${D3D9_LIBRARY})
endif(angle_enable_d3d9)
if (angle_enable_d3d11)
    list(APPEND ANGLE_SOURCE_LIBANGLE_BASE ${libangle_d3d11_sources})
    list(APPEND ANGLE_SOURCE_LIBANGLE_BASE ${libangle_d3d11_win32_sources})

    find_library(DXGUID_LIBRARY dxguid ${DirectX_LIBRARY_PATHS} NO_DEFAULT_PATH)
    list(APPEND ANGLE_DEPLIB ${DXGUID_LIBRARY}) 

    #import("src/libANGLE/renderer/d3d/d3d11/d3d11_blit_shaders_autogen.gni")
    include(d3d11_blit_shaders_autogen_gni.cmake)
    list(APPEND ANGLE_SOURCE_LIBANGLE_BASE ${libangle_d3d11_blit_shaders})
endif(angle_enable_d3d11)
if (angle_enable_gl)
    list(APPEND ANGLE_SOURCE_LIBANGLE_BASE ${libangle_gl_sources})
    if (angle_enable_gl_null) 
        list(APPEND ANGLE_SOURCE_LIBANGLE_BASE ${libangle_gl_null_sources})
    endif(angle_enable_gl_null)
    if (is_win)
        list(APPEND ANGLE_SOURCE_LIBANGLE_BASE ${libangle_gl_wgl_sources})
    endif(is_win)
    if (angle_use_x11)
        list(APPEND ANGLE_SOURCE_LIBANGLE_BASE ${libangle_gl_glx_sources})
        list(APPEND ANGLE_DEPLIB X11 Xi Xext) 
    endif(angle_use_x11)
    if (is_mac)
        list(APPEND ANGLE_SOURCE_LIBANGLE_BASE ${libangle_gl_cgl_sources}) 
        find_library(COCOA_LIBRARY Cocoa)
        list(APPEND ANGLE_DEPLIB ${COCOA_LIBRARY})
        find_library(IOSURFACE_LIBRARY IOSurface)
        list(APPEND ANGLE_DEPLIB ${IOSURFACE_LIBRARY})
        find_library(OPENGL_LIBRARY OpenGL)
        list(APPEND ANGLE_DEPLIB ${OPENGL_LIBRARY})
        find_library(QUARTYCORE_LIBRARY QuartzCore)
        list(APPEND ANGLE_DEPLIB ${QUARTYCORE_LIBRARY})
    endif(is_mac)
    if (is_linux)
        list(APPEND ANGLE_SOURCE_LIBANGLE_BASE ${libangle_gl_egl_sources}) 
        list(APPEND ANGLE_SOURCE_LIBANGLE_BASE ${libangle_gl_egl_dl_sources}) 
    endif(is_linux)
endif(angle_enable_gl)
if (angle_enable_null)
    list(APPEND ANGLE_SOURCE_LIBANGLE_BASE ${libangle_null_sources}) 
endif(angle_enable_null)
if (is_mac)
    list(APPEND ANGLE_SOURCE_LIBANGLE_BASE ${libangle_mac_sources}) 
endif(is_mac)
if (is_debug)
    add_definitions(-DANGLE_GENERATE_SHADER_DEBUG_INFO=1)
endif(is_debug)
source_group(libANGLE_base FILES ${ANGLE_SOURCE_LIBANGLE_BASE})
    
if (angle_frame_capture_disabled)
    add_definitions(-DANGLE_CAPTURE_ENABLED=0)
endif(angle_frame_capture_disabled)
if (angle_frame_capture_enabled)
    add_definitions(-DANGLE_CAPTURE_ENABLED=1)
endif(angle_frame_capture_enabled)

# angle_source_set("libANGLE") {
set(ANGLE_SOURCE_LIBANGLE ${SOURCE_PATH}/libANGLE/FrameCapture_mock.cpp)
list(APPEND ANGLE_SOURCE_LIBANGLE
${SOURCE_PATH}/libANGLE/gl_enum_utils.cpp
${SOURCE_PATH}/libANGLE/gl_enum_utils_autogen.cpp
)
source_group(libANGLE FILES ${ANGLE_SOURCE_LIBANGLE})

# template("angle_libGLESv2") {
set(ANGLE_SOURCE_LIBGLESV2 ${libglesv2_sources})
list(REMOVE_ITEM ANGLE_SOURCE_LIBGLESV2 ${SOURCE_PATH}/libGLESv2/libGLESv2_autogen.cpp)
source_group(angle_libGLESv2 FILES ${ANGLE_SOURCE_LIBGLESV2})

###############################################################################
#  Target file
###############################################################################
set(ANGLE_SOURCE
${ANGLE_SOURCE_ZLIB}
${ANGLE_SOURCE_PREPROCESSOR}
${ANGLE_SOURCE_SYSTEM_UTILS}
${ANGLE_SOURCE_XXHASH}
${ANGLE_SOURCE_COMMON}
${ANGLE_SOURCE_IMAGE_UTILS}
${ANGLE_SOURCE_GPU_INFO_UTILS}
${ANGLE_SOURCE_TRANSLATOR}
${ANGLE_SOURCE_TRANSLATOR_FUZZER}
${ANGLE_SOURCE_VERSION}
${ANGLE_SOURCE_LIBANGLE_HEADERS}
${ANGLE_SOURCE_LIBANGLE_BASE}
${ANGLE_SOURCE_LIBANGLE}
${ANGLE_SOURCE_LIBGLESV2}
)

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(ANGLE SHARED ${ANGLE_SOURCE})
target_link_libraries(ANGLE ${ANGLE_DEPLIB})
