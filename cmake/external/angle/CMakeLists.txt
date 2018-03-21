
project(ANGLE)

if(NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH}/angle)
message(STATUS "Download\t angel")
exec_program("git clone https://github.com/google/angle.git" ${M3E_SOURCE_DIR}/${EXT_PATH})
exec_program("git reset --hard b2c60b1a195049ede3f3d28a81cb1ff35929f88b" ${M3E_SOURCE_DIR}/${EXT_PATH}/angle)
endif()

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/angle/include.cmake)

add_definitions(-DLIBANGLE_IMPLEMENTATION)

set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/src )

include_directories(AFTER ${SOURCE_PATH})
include_directories(AFTER ${SOURCE_PATH}/common/third_party/base)


if(APPLE)
    add_definitions(-DANGLE_ENABLE_OPENGL=1)
    add_definitions(-DANGLE_PLATFORM_APPLE=1)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14 -stdlib=libc++")
elseif(CYGWIN)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=gnu++11")
elseif(UNIX)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++0x")
endif()

# header files
file(GLOB ANGLE_HEADER_EGL ${HEADER_PATH}/EGL/*.h)
list(APPEND ANGLE_HEADER_FILES  
${ANGLE_HEADER_EGL})

# source files
set(ANGLE_SOURCE_COMMON
${SOURCE_PATH}/common/angleutils.cpp
${SOURCE_PATH}/common/debug.cpp
${SOURCE_PATH}/common/tls.cpp
${SOURCE_PATH}/common/utilities.cpp
${SOURCE_PATH}/common/uniform_type_info_autogen.cpp
)
file(GLOB ANGLE_SOURCE_COMPILER_TRANSLATOR
#${SOURCE_PATH}/compiler/translator/*.cpp
)
set(ANGLE_SOURCE_COMPILER
${ANGLE_SOURCE_COMPILER_TRANSLATOR}
)
set(ANGLE_SOURCE_ANGLE
${SOURCE_PATH}/libANGLE/angletypes.cpp 
${SOURCE_PATH}/libANGLE/AttributeMap.cpp
${SOURCE_PATH}/libANGLE/Buffer.cpp
${SOURCE_PATH}/libANGLE/Caps.cpp
${SOURCE_PATH}/libANGLE/Compiler.cpp
${SOURCE_PATH}/libANGLE/Config.cpp
${SOURCE_PATH}/libANGLE/Context_gles_1_0.cpp
${SOURCE_PATH}/libANGLE/Context.cpp
${SOURCE_PATH}/libANGLE/ContextState.cpp
${SOURCE_PATH}/libANGLE/Debug.cpp
${SOURCE_PATH}/libANGLE/Device.cpp
${SOURCE_PATH}/libANGLE/Display.cpp
${SOURCE_PATH}/libANGLE/Error.cpp
${SOURCE_PATH}/libANGLE/es3_copy_conversion_table_autogen.cpp
${SOURCE_PATH}/libANGLE/Fence.cpp
${SOURCE_PATH}/libANGLE/format_map_autogen.cpp
${SOURCE_PATH}/libANGLE/formatutils.cpp
${SOURCE_PATH}/libANGLE/Framebuffer.cpp
${SOURCE_PATH}/libANGLE/FramebufferAttachment.cpp
${SOURCE_PATH}/libANGLE/GLES1State.cpp
${SOURCE_PATH}/libANGLE/HandleAllocator.cpp
${SOURCE_PATH}/libANGLE/HandleRangeAllocator.cpp
${SOURCE_PATH}/libANGLE/Image.cpp
${SOURCE_PATH}/libANGLE/ImageIndex.cpp
${SOURCE_PATH}/libANGLE/IndexRangeCache.cpp
${SOURCE_PATH}/libANGLE/LoggingAnnotator.cpp
${SOURCE_PATH}/libANGLE/MemoryProgramCache.cpp
${SOURCE_PATH}/libANGLE/Observer.cpp
${SOURCE_PATH}/libANGLE/PackedGLEnums.cpp
${SOURCE_PATH}/libANGLE/PackedGLEnums_autogen.cpp
${SOURCE_PATH}/libANGLE/params.cpp
${SOURCE_PATH}/libANGLE/Path.cpp
${SOURCE_PATH}/libANGLE/Platform.cpp
${SOURCE_PATH}/libANGLE/Program.cpp
${SOURCE_PATH}/libANGLE/ProgramLinkedResources.cpp
${SOURCE_PATH}/libANGLE/ProgramPipeline.cpp
${SOURCE_PATH}/libANGLE/queryconversions.cpp
${SOURCE_PATH}/libANGLE/queryutils.cpp
${SOURCE_PATH}/libANGLE/Query.cpp
${SOURCE_PATH}/libANGLE/Renderbuffer.cpp
${SOURCE_PATH}/libANGLE/ResourceManager.cpp
${SOURCE_PATH}/libANGLE/Sampler.cpp
${SOURCE_PATH}/libANGLE/Shader.cpp
${SOURCE_PATH}/libANGLE/State.cpp
${SOURCE_PATH}/libANGLE/Stream.cpp
${SOURCE_PATH}/libANGLE/Surface.cpp
${SOURCE_PATH}/libANGLE/Texture.cpp
${SOURCE_PATH}/libANGLE/Thread.cpp
${SOURCE_PATH}/libANGLE/TransformFeedback.cpp
${SOURCE_PATH}/libANGLE/Uniform.cpp
${SOURCE_PATH}/libANGLE/validationEGL.cpp
${SOURCE_PATH}/libANGLE/validationES.cpp
${SOURCE_PATH}/libANGLE/validationES1.cpp
${SOURCE_PATH}/libANGLE/validationES2.cpp
${SOURCE_PATH}/libANGLE/validationES3.cpp
${SOURCE_PATH}/libANGLE/validationES31.cpp
${SOURCE_PATH}/libANGLE/VaryingPacking.cpp
${SOURCE_PATH}/libANGLE/VertexArray.cpp
${SOURCE_PATH}/libANGLE/VertexAttribute.cpp
${SOURCE_PATH}/libANGLE/WorkerThread.cpp
)

file(GLOB ANGLE_SOURCE_RENDER ${SOURCE_PATH}/libANGLE/renderer/*.cpp )
list(APPEND ANGLE_SOURCE_ANGLE ${ANGLE_SOURCE_RENDER} )

file(GLOB ANGLE_SOURCE_RENDER_GL ${SOURCE_PATH}/libANGLE/renderer/gl/*.cpp )
list(APPEND ANGLE_SOURCE_ANGLE ${ANGLE_SOURCE_RENDER_GL} )

if(APPLE)
    set(CMAKE_C_FLAGS "-x objective-c")

    find_package(OpenGL REQUIRED)
    list(APPEND ANGLE_DEPLIB ${OPENGL_gl_LIBRARY})

    find_library(COREGRAPHICS_LIBRARY CoreGraphics)
    list(APPEND ANGLE_DEPLIB ${COREGRAPHICS_LIBRARY})
    find_library(QUARTZCORE_LIBRARY QuartzCore)
    list(APPEND ANGLE_DEPLIB ${QUARTZCORE_LIBRARY})
    find_library(IOSURFACE_LIBRARY IOSurface)
    list(APPEND ANGLE_DEPLIB ${IOSURFACE_LIBRARY})

    list(APPEND ANGLE_SOURCE_ANGLE
    ${SOURCE_PATH}/libANGLE/renderer/gl/cgl/DisplayCGL.mm  
    ${SOURCE_PATH}/libANGLE/renderer/gl/cgl/IOSurfaceSurfaceCGL.mm   
    ${SOURCE_PATH}/libANGLE/renderer/gl/cgl/PbufferSurfaceCGL.mm   
    ${SOURCE_PATH}/libANGLE/renderer/gl/cgl/WindowSurfaceCGL.mm  
    )
endif()
file(GLOB ANGLE_SOURCE_EGL ${SOURCE_PATH}/libEGL/*.cpp)
file(GLOB ANGLE_SOURCE_GLESv2 ${SOURCE_PATH}/libGLESv2/*.cpp)
list(APPEND ANGLE_SOURCE_FILES  
${ANGLE_SOURCE_COMPILER}
${ANGLE_SOURCE_COMMON}
${ANGLE_SOURCE_ANGLE}
${ANGLE_SOURCE_EGL}
${ANGLE_SOURCE_GLESv2}
)


# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(angle SHARED ${ANGLE_SOURCE_FILES} ${ANGLE_HEADER_FILES})
target_link_libraries(angle ${ANGLE_DEPLIB})
