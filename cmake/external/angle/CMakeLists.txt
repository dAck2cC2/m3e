
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

if(NOT EXISTS ${SOURCE_PATH}/id)
    exec_program("mkdir id" ${SOURCE_PATH})
    exec_program("cp ../commit.h ./" ${SOURCE_PATH}/id)
endif()

include_directories(AFTER ${SOURCE_PATH})
include_directories(AFTER ${SOURCE_PATH}/common/third_party/base)

# header files
file(GLOB ANGLE_HEADER_KHR ${HEADER_PATH}/KHR/*.h)
file(GLOB ANGLE_HEADER_EGL ${HEADER_PATH}/EGL/*.h)
file(GLOB ANGLE_HEADER_GLES ${HEADER_PATH}/GLES/*.h)
file(GLOB ANGLE_HEADER_GLES2 ${HEADER_PATH}/GLES2/*.h)
file(GLOB ANGLE_HEADER_GLES3 ${HEADER_PATH}/GLES3/*.h)
list(APPEND ANGLE_HEADER_FILES  
${ANGLE_HEADER_KHR}
${ANGLE_HEADER_EGL}
${ANGLE_HEADER_GLES}
${ANGLE_HEADER_GLES2}
${ANGLE_HEADER_GLES3}
)

# source files
set(ANGLE_SOURCE_COMMON
${SOURCE_PATH}/common/angleutils.cpp
${SOURCE_PATH}/common/debug.cpp
${SOURCE_PATH}/common/event_tracer.cpp
${SOURCE_PATH}/common/Float16ToFloat32.cpp
${SOURCE_PATH}/common/mathutil.cpp
${SOURCE_PATH}/common/matrix_utils.cpp
${SOURCE_PATH}/common/MemoryBuffer.cpp
${SOURCE_PATH}/common/string_utils.cpp
${SOURCE_PATH}/common/tls.cpp
${SOURCE_PATH}/common/utilities.cpp
${SOURCE_PATH}/common/uniform_type_info_autogen.cpp
${SOURCE_PATH}/common/third_party/base/anglebase/sha1.cc
)

set(ANGLE_SOURCE_COMPILER_TRANSLATOR
${SOURCE_PATH}/compiler/translator/AddAndTrueToLoopCondition.cpp
${SOURCE_PATH}/compiler/translator/BuiltInFunctionEmulator.cpp
${SOURCE_PATH}/compiler/translator/CallDAG.cpp
${SOURCE_PATH}/compiler/translator/ClampFragDepth.cpp
${SOURCE_PATH}/compiler/translator/ClampPointSize.cpp
${SOURCE_PATH}/compiler/translator/CodeGen.cpp
${SOURCE_PATH}/compiler/translator/CollectVariables.cpp
${SOURCE_PATH}/compiler/translator/ConstantUnion.cpp
${SOURCE_PATH}/compiler/translator/Compiler.cpp
${SOURCE_PATH}/compiler/translator/Declarator.cpp
${SOURCE_PATH}/compiler/translator/DeclareAndInitBuiltinsForInstancedMultiview.cpp
${SOURCE_PATH}/compiler/translator/DeferGlobalInitializers.cpp
${SOURCE_PATH}/compiler/translator/Diagnostics.cpp
${SOURCE_PATH}/compiler/translator/DirectiveHandler.cpp
${SOURCE_PATH}/compiler/translator/EmulatePrecision.cpp
${SOURCE_PATH}/compiler/translator/ExtensionBehavior.cpp
${SOURCE_PATH}/compiler/translator/FoldExpressions.cpp
${SOURCE_PATH}/compiler/translator/FindMain.cpp
${SOURCE_PATH}/compiler/translator/FindSymbolNode.cpp
${SOURCE_PATH}/compiler/translator/FunctionLookup.cpp
${SOURCE_PATH}/compiler/translator/glslang_lex.cpp
${SOURCE_PATH}/compiler/translator/glslang_tab.cpp
${SOURCE_PATH}/compiler/translator/HashNames.cpp
${SOURCE_PATH}/compiler/translator/Initialize.cpp
${SOURCE_PATH}/compiler/translator/InitializeDll.cpp
${SOURCE_PATH}/compiler/translator/InitializeVariables.cpp
${SOURCE_PATH}/compiler/translator/InfoSink.cpp
${SOURCE_PATH}/compiler/translator/IntermNode.cpp
${SOURCE_PATH}/compiler/translator/IntermNodePatternMatcher.cpp
${SOURCE_PATH}/compiler/translator/IntermNode_util.cpp
${SOURCE_PATH}/compiler/translator/IntermTraverse.cpp
${SOURCE_PATH}/compiler/translator/ImmutableString.cpp
${SOURCE_PATH}/compiler/translator/ImmutableStringBuilder.cpp
${SOURCE_PATH}/compiler/translator/IsASTDepthBelowLimit.cpp
${SOURCE_PATH}/compiler/translator/Operator.cpp
${SOURCE_PATH}/compiler/translator/OutputTree.cpp
${SOURCE_PATH}/compiler/translator/ParseContext.cpp
${SOURCE_PATH}/compiler/translator/PoolAlloc.cpp
${SOURCE_PATH}/compiler/translator/PruneEmptyCases.cpp
${SOURCE_PATH}/compiler/translator/PruneNoOps.cpp
${SOURCE_PATH}/compiler/translator/QualifierTypes.cpp
${SOURCE_PATH}/compiler/translator/RemoveArrayLengthMethod.cpp
${SOURCE_PATH}/compiler/translator/RemoveInvariantDeclaration.cpp
${SOURCE_PATH}/compiler/translator/RemoveUnreferencedVariables.cpp
${SOURCE_PATH}/compiler/translator/ReplaceVariable.cpp
${SOURCE_PATH}/compiler/translator/RegenerateStructNames.cpp
${SOURCE_PATH}/compiler/translator/RewriteDoWhile.cpp
${SOURCE_PATH}/compiler/translator/RewriteTexelFetchOffset.cpp
${SOURCE_PATH}/compiler/translator/RewriteUnaryMinusOperatorFloat.cpp
${SOURCE_PATH}/compiler/translator/RemovePow.cpp
${SOURCE_PATH}/compiler/translator/RunAtTheEndOfShader.cpp
${SOURCE_PATH}/compiler/translator/ScalarizeVecAndMatConstructorArgs.cpp
${SOURCE_PATH}/compiler/translator/SeparateDeclarations.cpp
${SOURCE_PATH}/compiler/translator/SimplifyLoopConditions.cpp
${SOURCE_PATH}/compiler/translator/ShaderLang.cpp
${SOURCE_PATH}/compiler/translator/ShaderVars.cpp
${SOURCE_PATH}/compiler/translator/SplitSequenceOperator.cpp
${SOURCE_PATH}/compiler/translator/Symbol.cpp
${SOURCE_PATH}/compiler/translator/SymbolTable.cpp
${SOURCE_PATH}/compiler/translator/SymbolTable_autogen.cpp
${SOURCE_PATH}/compiler/translator/SymbolUniqueId.cpp
${SOURCE_PATH}/compiler/translator/Types.cpp
${SOURCE_PATH}/compiler/translator/UnfoldShortCircuitAST.cpp
${SOURCE_PATH}/compiler/translator/UseInterfaceBlockFields.cpp
${SOURCE_PATH}/compiler/translator/util.cpp
${SOURCE_PATH}/compiler/translator/ValidateGlobalInitializer.cpp
${SOURCE_PATH}/compiler/translator/ValidateLimitations.cpp
${SOURCE_PATH}/compiler/translator/ValidateMaxParameters.cpp
${SOURCE_PATH}/compiler/translator/ValidateOutputs.cpp
${SOURCE_PATH}/compiler/translator/ValidateVaryingLocations.cpp
${SOURCE_PATH}/compiler/translator/ValidateSwitch.cpp
${SOURCE_PATH}/compiler/translator/VariablePacker.cpp
${SOURCE_PATH}/compiler/translator/VectorizeVectorScalarArithmetic.cpp
${SOURCE_PATH}/compiler/translator/BuiltInFunctionEmulatorGLSL.cpp
${SOURCE_PATH}/compiler/translator/EmulateGLFragColorBroadcast.cpp
${SOURCE_PATH}/compiler/translator/ExtensionGLSL.cpp
${SOURCE_PATH}/compiler/translator/OutputGLSL.cpp
${SOURCE_PATH}/compiler/translator/OutputGLSLBase.cpp
${SOURCE_PATH}/compiler/translator/TranslatorGLSL.cpp
${SOURCE_PATH}/compiler/translator/VersionGLSL.cpp
)
set(ANGLE_SOURCE_COMPILER_PREPROCESSOR
${SOURCE_PATH}/compiler/preprocessor/DiagnosticsBase.cpp
${SOURCE_PATH}/compiler/preprocessor/DirectiveHandlerBase.cpp
${SOURCE_PATH}/compiler/preprocessor/DirectiveParser.cpp
${SOURCE_PATH}/compiler/preprocessor/ExpressionParser.cpp
${SOURCE_PATH}/compiler/preprocessor/Input.cpp
${SOURCE_PATH}/compiler/preprocessor/Lexer.cpp
${SOURCE_PATH}/compiler/preprocessor/Macro.cpp
${SOURCE_PATH}/compiler/preprocessor/MacroExpander.cpp
${SOURCE_PATH}/compiler/preprocessor/Preprocessor.cpp
${SOURCE_PATH}/compiler/preprocessor/Token.cpp
${SOURCE_PATH}/compiler/preprocessor/Tokenizer.cpp
)
set(ANGLE_SOURCE_COMPILER
${ANGLE_SOURCE_COMPILER_TRANSLATOR}
${ANGLE_SOURCE_COMPILER_PREPROCESSOR}
)

file(GLOB ANGLE_SOURCE_THIRD_COMPILER ${SOURCE_PATH}/third_party/compiler/*.cpp)
set(ANGLE_SOURCE_THIRD
${ANGLE_SOURCE_THIRD_COMPILER}
)

file(GLOB ANGLE_SOURCE_IMAGE_UTIL ${SOURCE_PATH}/image_util/*.cpp)

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

if(MSVC)
    add_definitions(-DANGLE_PLATFORM_WINDOWS)
    add_definitions(-DANGLE_ENABLE_D3D9)
    add_definitions(-DNOMINMAX)
    add_definitions(-D_ALLOW_KEYWORD_MACROS=1)

    list(REMOVE_ITEM ANGLE_SOURCE_ANGLE ${SOURCE_PATH}/libANGLE/renderer/Format_table_autogen.cpp)
    list(APPEND ANGLE_SOURCE_ANGLE ${M3E_SOURCE_DIR}/src/${EXT_PATH}/angle/Format_table_autogen_msvc.cpp)
    
elseif(APPLE)
    add_definitions(-DANGLE_ENABLE_OPENGL=1)
    add_definitions(-DANGLE_PLATFORM_APPLE=1)
    add_definitions(-DANGLE_ENABLE_GLSL=1)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14 -stdlib=libc++")
    set(CMAKE_C_FLAGS "-x objective-c")

    file(GLOB ANGLE_SOURCE_RENDER_GL ${SOURCE_PATH}/libANGLE/renderer/gl/*.cpp )
    list(APPEND ANGLE_SOURCE_ANGLE ${ANGLE_SOURCE_RENDER_GL} )

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
    list(APPEND ANGLE_SOURCE_COMMON
    ${SOURCE_PATH}/common/system_utils_mac.cpp   
    ) 
elseif(CYGWIN)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=gnu++11")
elseif(UNIX)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++0x")
endif()


file(GLOB ANGLE_SOURCE_EGL ${SOURCE_PATH}/libEGL/*.cpp)
file(GLOB ANGLE_SOURCE_GLESv2 ${SOURCE_PATH}/libGLESv2/*.cpp)
list(APPEND ANGLE_SOURCE_FILES  
${ANGLE_SOURCE_COMPILER}
${ANGLE_SOURCE_COMMON}
${ANGLE_SOURCE_ANGLE}
${ANGLE_SOURCE_EGL}
${ANGLE_SOURCE_GLESv2}
${ANGLE_SOURCE_THIRD}
${ANGLE_SOURCE_IMAGE_UTIL}
)


# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(angle SHARED ${ANGLE_SOURCE_FILES} ${ANGLE_HEADER_FILES})
target_link_libraries(angle ${ANGLE_DEPLIB})
