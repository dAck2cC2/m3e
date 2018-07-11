
project(EGL)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/ui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/EGL/include.cmake)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/opengl/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/opengl/libs )

include_directories(AFTER ${SOURCE_PATH})
include_directories(AFTER ${SOURCE_PATH}/EGL)

add_definitions(-DANDROID_IMPLEMENTATION=1)
add_definitions(-DEGL_EGLEXT_PROTOTYPES=1)
add_definitions(-DEGL_IMPLEMENTATION=1)

# dependency
set(EGL_DEPLIB
utils
log
ui
)

# header files
file(GLOB EGL_HEADER_FILES  
${HEADER_PATH}/KHR/*.h
${HEADER_PATH}/EGL/*.h
)

# libANGLE source code

set( ANGLE_HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/opengl/angle )
set( ANGLE_SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/opengl/angle )

add_definitions(-DANGLE_ENABLE_OPENGL=1)
include_directories(AFTER ${ANGLE_HEADER_PATH})

###############################################################################
#  EGL
###############################################################################
file(GLOB EGL_EGL_SOURCE_FILES 
${ANGLE_SOURCE_PATH}/*.h
${ANGLE_SOURCE_PATH}/*.cpp
${ANGLE_SOURCE_PATH}/libEGL/*.cpp
)
source_group(EGL FILES ${EGL_EGL_SOURCE_FILES})

list(APPEND EGL_SOURCE_FILES
${EGL_EGL_SOURCE_FILES}
)

###############################################################################
#  Common
###############################################################################
include_directories(AFTER ${ANGLE_SOURCE_PATH}/common/third_party/base)
set( EGL_COM_SOURCE_FILES
${ANGLE_SOURCE_PATH}/common/angleutils.h
${ANGLE_SOURCE_PATH}/common/angleutils.cpp
${ANGLE_SOURCE_PATH}/common/bitset_utils.h
${ANGLE_SOURCE_PATH}/common/Color.h
${ANGLE_SOURCE_PATH}/common/Color.inl
${ANGLE_SOURCE_PATH}/common/debug.h
${ANGLE_SOURCE_PATH}/common/debug.cpp
${ANGLE_SOURCE_PATH}/common/mathutil.h
#${ANGLE_SOURCE_PATH}/common/mathutil.cpp
${ANGLE_SOURCE_PATH}/common/Optional.h
${ANGLE_SOURCE_PATH}/common/platform.h
${ANGLE_SOURCE_PATH}/common/string_utils.h
${ANGLE_SOURCE_PATH}/common/string_utils.cpp
${ANGLE_SOURCE_PATH}/common/utilities.h
${ANGLE_SOURCE_PATH}/common/utilities.cpp
${ANGLE_SOURCE_PATH}/common/tls.h
${ANGLE_SOURCE_PATH}/common/tls.cpp
${ANGLE_SOURCE_PATH}/common/vector_utils.h
)
source_group(common FILES ${EGL_COM_SOURCE_FILES})

list(APPEND EGL_SOURCE_FILES
${EGL_COM_SOURCE_FILES}
)

###############################################################################
#  GLESv2
###############################################################################
set( EGL_GLESv2_SOURCE_FILES
${ANGLE_SOURCE_PATH}/libGLESv2/global_state.h
${ANGLE_SOURCE_PATH}/libGLESv2/global_state.cpp
${ANGLE_SOURCE_PATH}/libGLESv2/entry_points_egl.h
${ANGLE_SOURCE_PATH}/libGLESv2/entry_points_egl.cpp
${ANGLE_SOURCE_PATH}/libGLESv2/entry_points_egl_ext.h
${ANGLE_SOURCE_PATH}/libGLESv2/entry_points_egl_ext.cpp
)
source_group(GLESv2 FILES ${EGL_GLESv2_SOURCE_FILES})

list(APPEND EGL_SOURCE_FILES
${EGL_GLESv2_SOURCE_FILES}
)

###############################################################################
#  GL
###############################################################################
set(EGL_GL_SOURCE_FILES
${ANGLE_SOURCE_PATH}/libANGLE/renderer/gl/functionsgl_enums.h
${ANGLE_SOURCE_PATH}/libANGLE/renderer/gl/functionsgl_typedefs.h
${ANGLE_SOURCE_PATH}/libANGLE/renderer/gl/DispatchTableGL_autogen.h
${ANGLE_SOURCE_PATH}/libANGLE/renderer/gl/DispatchTableGL_autogen.cpp
${ANGLE_SOURCE_PATH}/libANGLE/renderer/gl/FunctionsGL.h
${ANGLE_SOURCE_PATH}/libANGLE/renderer/gl/FunctionsGL.cpp
${ANGLE_SOURCE_PATH}/libANGLE/renderer/gl/renderergl_utils.h
${ANGLE_SOURCE_PATH}/libANGLE/renderer/gl/renderergl_utils.cpp
${ANGLE_SOURCE_PATH}/libANGLE/renderer/gl/DisplayGL.h
${ANGLE_SOURCE_PATH}/libANGLE/renderer/gl/DisplayGL.cpp
${ANGLE_SOURCE_PATH}/libANGLE/renderer/gl/SurfaceGL.h
${ANGLE_SOURCE_PATH}/libANGLE/renderer/gl/SurfaceGL.cpp
)
source_group(GL FILES ${EGL_GL_SOURCE_FILES})

list(APPEND EGL_SOURCE_FILES
${EGL_GL_SOURCE_FILES}
)

###############################################################################
#  Renderer
###############################################################################
set(EGL_RENDERER_SOURCE_FILES
${ANGLE_SOURCE_PATH}/libANGLE/renderer/EGLImplFactory.h
${ANGLE_SOURCE_PATH}/libANGLE/renderer/DisplayImpl.h
${ANGLE_SOURCE_PATH}/libANGLE/renderer/DisplayImpl.cpp
${ANGLE_SOURCE_PATH}/libANGLE/renderer/driver_utils.h
${ANGLE_SOURCE_PATH}/libANGLE/renderer/driver_utils.cpp
${ANGLE_SOURCE_PATH}/libANGLE/renderer/SurfaceImpl.h
${ANGLE_SOURCE_PATH}/libANGLE/renderer/SurfaceImpl.cpp
)
source_group(renderer FILES ${EGL_RENDERER_SOURCE_FILES})

list(APPEND EGL_SOURCE_FILES
${EGL_RENDERER_SOURCE_FILES}
)

###############################################################################
#  ANGLE
###############################################################################
file(GLOB EGL_ANGLE_SOURCE_FILES
${ANGLE_SOURCE_PATH}/libANGLE/angletypes.h
${ANGLE_SOURCE_PATH}/libANGLE/angletypes.inl
#${ANGLE_SOURCE_PATH}/libANGLE/angletypes.cpp
${ANGLE_SOURCE_PATH}/libANGLE/Caps.h
${ANGLE_SOURCE_PATH}/libANGLE/Caps.cpp
${ANGLE_SOURCE_PATH}/libANGLE/Version.h
${ANGLE_SOURCE_PATH}/libANGLE/Display.h
${ANGLE_SOURCE_PATH}/libANGLE/Display.cpp
${ANGLE_SOURCE_PATH}/libANGLE/AttributeMap.h
${ANGLE_SOURCE_PATH}/libANGLE/AttributeMap.cpp
${ANGLE_SOURCE_PATH}/libANGLE/Error.h
${ANGLE_SOURCE_PATH}/libANGLE/Error.cpp
${ANGLE_SOURCE_PATH}/libANGLE/PackedGLEnums.h
#${ANGLE_SOURCE_PATH}/libANGLE/PackedGLEnums.cpp
${ANGLE_SOURCE_PATH}/libANGLE/PackedGLEnums_autogen.h
#${ANGLE_SOURCE_PATH}/libANGLE/PackedGLEnums_autogen.cpp
${ANGLE_SOURCE_PATH}/libANGLE/Debug.h
${ANGLE_SOURCE_PATH}/libANGLE/Debug.cpp
${ANGLE_SOURCE_PATH}/libANGLE/Observer.h
${ANGLE_SOURCE_PATH}/libANGLE/Observer.cpp
${ANGLE_SOURCE_PATH}/libANGLE/Config.h
${ANGLE_SOURCE_PATH}/libANGLE/Config.cpp
#${ANGLE_SOURCE_PATH}/libANGLE/Framebuffer.h
#${ANGLE_SOURCE_PATH}/libANGLE/Framebuffer.cpp
#${ANGLE_SOURCE_PATH}/libANGLE/FramebufferAttachment.h
#${ANGLE_SOURCE_PATH}/libANGLE/FramebufferAttachment.cpp
${ANGLE_SOURCE_PATH}/libANGLE/Thread.h
${ANGLE_SOURCE_PATH}/libANGLE/Thread.cpp
${ANGLE_SOURCE_PATH}/libANGLE/Platform.cpp
${ANGLE_SOURCE_PATH}/libANGLE/validationEGL.h
${ANGLE_SOURCE_PATH}/libANGLE/validationEGL.cpp
${ANGLE_SOURCE_PATH}/libANGLE/Surface.h
${ANGLE_SOURCE_PATH}/libANGLE/Surface.cpp
${ANGLE_SOURCE_PATH}/libANGLE/formatutils.h
${ANGLE_SOURCE_PATH}/libANGLE/formatutils.cpp
${ANGLE_SOURCE_PATH}/libANGLE/VertexAttribute.h
${ANGLE_SOURCE_PATH}/libANGLE/format_map_autogen.cpp
${ANGLE_SOURCE_PATH}/libANGLE/queryutils.h
${ANGLE_SOURCE_PATH}/libANGLE/queryutils.cpp
${ANGLE_SOURCE_PATH}/libANGLE/Context.h
${ANGLE_SOURCE_PATH}/libANGLE/Context.cpp
${ANGLE_SOURCE_PATH}/libANGLE/RefCountObject.h
)
source_group(ANGLE FILES ${EGL_ANGLE_SOURCE_FILES})

list(APPEND EGL_SOURCE_FILES
${EGL_ANGLE_SOURCE_FILES}
)

###############################################################################
#  WGL
###############################################################################
if(MSVC)
    include_directories(AFTER ${ANGLE_SOURCE_PATH}/third_party/khronos)

    add_definitions(-D_ALLOW_KEYWORD_MACROS=1)
    add_definitions(-DNOMINMAX=1)   
    add_definitions(-DANGLE_PLATFORM_WINDOWS=1)
    add_definitions(-D__STDC_CONSTANT_MACROS=1)
    #add_definitions(-Dstrcasecmp=strcmp)
    include_directories(AFTER ${MSVC_PATH})
    
    set(EGL_WGL_SOURCE_FILES
    ${ANGLE_SOURCE_PATH}/libANGLE/renderer/gl/wgl/DisplayWGL.h
    ${ANGLE_SOURCE_PATH}/libANGLE/renderer/gl/wgl/DisplayWGL.cpp
    ${ANGLE_SOURCE_PATH}/libANGLE/renderer/gl/wgl/FunctionsWGL.h
    ${ANGLE_SOURCE_PATH}/libANGLE/renderer/gl/wgl/FunctionsWGL.cpp
    ${ANGLE_SOURCE_PATH}/libANGLE/renderer/gl/wgl/functionswgl_typedefs.h
    ${ANGLE_SOURCE_PATH}/libANGLE/renderer/gl/wgl/wgl_utils.cpp      
    ${ANGLE_SOURCE_PATH}/libANGLE/renderer/gl/wgl/wgl_utils.h    
    ${ANGLE_SOURCE_PATH}/libANGLE/renderer/gl/wgl/SurfaceWGL.h     
    ${ANGLE_SOURCE_PATH}/libANGLE/renderer/gl/wgl/WindowSurfaceWGL.h   
    ${ANGLE_SOURCE_PATH}/libANGLE/renderer/gl/wgl/WindowSurfaceWGL.cpp 
    ${ANGLE_SOURCE_PATH}/libANGLE/renderer/gl/wgl/PbufferSurfaceWGL.h   
    ${ANGLE_SOURCE_PATH}/libANGLE/renderer/gl/wgl/PbufferSurfaceWGL.cpp 
    )
    source_group(WGL FILES ${EGL_WGL_SOURCE_FILES})

    list(APPEND EGL_SOURCE_FILES
    ${EGL_WGL_SOURCE_FILES}
    )

###############################################################################
#  CGL
###############################################################################
elseif(APPLE)    

endif()

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(EGL SHARED ${EGL_SOURCE_FILES} ${EGL_HEADER_FILES})
target_link_libraries(EGL ${EGL_DEPLIB})
