
project(ANGLE_GLESV2)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

#add_definitions(-DNDEBUG=1)
add_definitions(-DLIBANGLE_IMPLEMENTATION=1)
add_definitions(-DGL_GLEXT_PROTOTYPES=1)
if(MSVC)
    add_definitions(-DGL_API=__declspec\(dllexport\))
    add_definitions(-DGL_APICALL=__declspec\(dllexport\))
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/src )

include_directories(AFTER ${HEADER_PATH})
include_directories(AFTER ${SOURCE_PATH})
include_directories(AFTER ${SOURCE_PATH}/common/third_party/base)

###############################################################################
#  Common
###############################################################################

set(ANGLE_SOURCE_COMMON
${SOURCE_PATH}/common/angleutils.h
${SOURCE_PATH}/common/angleutils.cpp
${SOURCE_PATH}/common/debug.h
${SOURCE_PATH}/common/debug.cpp
${SOURCE_PATH}/common/event_tracer.h
${SOURCE_PATH}/common/event_tracer.cpp
${SOURCE_PATH}/common/Float16ToFloat32.cpp
${SOURCE_PATH}/common/mathutil.h
${SOURCE_PATH}/common/mathutil.cpp
${SOURCE_PATH}/common/matrix_utils.h
${SOURCE_PATH}/common/matrix_utils.cpp
${SOURCE_PATH}/common/MemoryBuffer.h
${SOURCE_PATH}/common/MemoryBuffer.cpp
${SOURCE_PATH}/common/string_utils.h
${SOURCE_PATH}/common/string_utils.cpp
${SOURCE_PATH}/common/tls.h
${SOURCE_PATH}/common/tls.cpp
${SOURCE_PATH}/common/utilities.h
${SOURCE_PATH}/common/utilities.cpp
${SOURCE_PATH}/common/uniform_type_info_autogen.cpp
${SOURCE_PATH}/common/third_party/base/anglebase/sha1.h
${SOURCE_PATH}/common/third_party/base/anglebase/sha1.cc
${SOURCE_PATH}/common/PackedGLEnums_autogen.cpp
${SOURCE_PATH}/common/PackedEGLEnums_autogen.cpp
${SOURCE_PATH}/common/PackedEnums.cpp
)
source_group(common FILES ${ANGLE_SOURCE_COMMON})

###############################################################################
#  Compiler
###############################################################################
file(GLOB ANGLE_SOURCE_COMPILER_TRANSLATOR 
${SOURCE_PATH}/compiler/translator/*.h
${SOURCE_PATH}/compiler/translator/*.inl
)
list(APPEND ANGLE_SOURCE_COMPILER_TRANSLATOR
${SOURCE_PATH}/compiler/translator/tree_ops/AddAndTrueToLoopCondition.cpp
${SOURCE_PATH}/compiler/translator/BuiltInFunctionEmulator.cpp
${SOURCE_PATH}/compiler/translator/CallDAG.cpp
${SOURCE_PATH}/compiler/translator/tree_ops/ClampFragDepth.cpp
${SOURCE_PATH}/compiler/translator/tree_ops/ClampPointSize.cpp
${SOURCE_PATH}/compiler/translator/CodeGen.cpp
${SOURCE_PATH}/compiler/translator/CollectVariables.cpp
${SOURCE_PATH}/compiler/translator/ConstantUnion.cpp
${SOURCE_PATH}/compiler/translator/Compiler.cpp
${SOURCE_PATH}/compiler/translator/Declarator.cpp
${SOURCE_PATH}/compiler/translator/tree_ops/DeclareAndInitBuiltinsForInstancedMultiview.cpp
${SOURCE_PATH}/compiler/translator/tree_ops/DeferGlobalInitializers.cpp
${SOURCE_PATH}/compiler/translator/Diagnostics.cpp
${SOURCE_PATH}/compiler/translator/DirectiveHandler.cpp
${SOURCE_PATH}/compiler/translator/tree_ops/EmulatePrecision.cpp
${SOURCE_PATH}/compiler/translator/ExtensionBehavior.cpp
${SOURCE_PATH}/compiler/translator/tree_ops/FoldExpressions.cpp
${SOURCE_PATH}/compiler/translator/tree_util/FindMain.cpp
${SOURCE_PATH}/compiler/translator/tree_util/FindSymbolNode.cpp
${SOURCE_PATH}/compiler/translator/FunctionLookup.cpp
${SOURCE_PATH}/compiler/translator/glslang_lex.cpp
${SOURCE_PATH}/compiler/translator/glslang_tab.cpp
${SOURCE_PATH}/compiler/translator/HashNames.cpp
${SOURCE_PATH}/compiler/translator/Initialize.cpp
${SOURCE_PATH}/compiler/translator/InitializeDll.cpp
${SOURCE_PATH}/compiler/translator/tree_ops/InitializeVariables.cpp
${SOURCE_PATH}/compiler/translator/InfoSink.cpp
${SOURCE_PATH}/compiler/translator/IntermNode.cpp
${SOURCE_PATH}/compiler/translator/tree_util/IntermNodePatternMatcher.cpp
${SOURCE_PATH}/compiler/translator/tree_util/IntermNode_util.cpp
${SOURCE_PATH}/compiler/translator/tree_util/IntermTraverse.cpp
${SOURCE_PATH}/compiler/translator/ImmutableString.cpp
${SOURCE_PATH}/compiler/translator/ImmutableStringBuilder.cpp
${SOURCE_PATH}/compiler/translator/IsASTDepthBelowLimit.cpp
${SOURCE_PATH}/compiler/translator/Operator.cpp
${SOURCE_PATH}/compiler/translator/OutputTree.cpp
${SOURCE_PATH}/compiler/translator/ParseContext.cpp
${SOURCE_PATH}/compiler/translator/PoolAlloc.cpp
${SOURCE_PATH}/compiler/translator/tree_ops/PruneEmptyCases.cpp
${SOURCE_PATH}/compiler/translator/tree_ops/PruneNoOps.cpp
${SOURCE_PATH}/compiler/translator/QualifierTypes.cpp
${SOURCE_PATH}/compiler/translator/tree_ops/RemoveArrayLengthMethod.cpp
${SOURCE_PATH}/compiler/translator/tree_ops/RemoveInvariantDeclaration.cpp
${SOURCE_PATH}/compiler/translator/tree_ops/RemoveUnreferencedVariables.cpp
${SOURCE_PATH}/compiler/translator/tree_util/ReplaceVariable.cpp
${SOURCE_PATH}/compiler/translator/tree_ops/RegenerateStructNames.cpp
${SOURCE_PATH}/compiler/translator/tree_ops/RewriteDoWhile.cpp
${SOURCE_PATH}/compiler/translator/tree_ops/RewriteTexelFetchOffset.cpp
${SOURCE_PATH}/compiler/translator/tree_ops/RewriteUnaryMinusOperatorFloat.cpp
${SOURCE_PATH}/compiler/translator/tree_ops/RemovePow.cpp
${SOURCE_PATH}/compiler/translator/tree_util/RunAtTheEndOfShader.cpp
${SOURCE_PATH}/compiler/translator/tree_ops/ScalarizeVecAndMatConstructorArgs.cpp
${SOURCE_PATH}/compiler/translator/tree_ops/SeparateDeclarations.cpp
${SOURCE_PATH}/compiler/translator/tree_ops/SimplifyLoopConditions.cpp
${SOURCE_PATH}/compiler/translator/ShaderLang.cpp
${SOURCE_PATH}/compiler/translator/ShaderVars.cpp
${SOURCE_PATH}/compiler/translator/tree_ops/SplitSequenceOperator.cpp
${SOURCE_PATH}/compiler/translator/Symbol.cpp
${SOURCE_PATH}/compiler/translator/SymbolTable.cpp
${SOURCE_PATH}/compiler/translator/SymbolTable_autogen.cpp
${SOURCE_PATH}/compiler/translator/SymbolUniqueId.cpp
${SOURCE_PATH}/compiler/translator/Types.cpp
${SOURCE_PATH}/compiler/translator/tree_ops/UnfoldShortCircuitAST.cpp
${SOURCE_PATH}/compiler/translator/tree_ops/UseInterfaceBlockFields.cpp
${SOURCE_PATH}/compiler/translator/util.cpp
${SOURCE_PATH}/compiler/translator/ValidateGlobalInitializer.cpp
${SOURCE_PATH}/compiler/translator/ValidateLimitations.cpp
${SOURCE_PATH}/compiler/translator/ValidateMaxParameters.cpp
${SOURCE_PATH}/compiler/translator/ValidateOutputs.cpp
${SOURCE_PATH}/compiler/translator/ValidateVaryingLocations.cpp
${SOURCE_PATH}/compiler/translator/ValidateSwitch.cpp
${SOURCE_PATH}/compiler/translator/VariablePacker.cpp
${SOURCE_PATH}/compiler/translator/tree_ops/VectorizeVectorScalarArithmetic.cpp
${SOURCE_PATH}/compiler/translator/BuiltInFunctionEmulatorGLSL.cpp
${SOURCE_PATH}/compiler/translator/tree_ops/EmulateGLFragColorBroadcast.cpp
${SOURCE_PATH}/compiler/translator/ExtensionGLSL.cpp
${SOURCE_PATH}/compiler/translator/OutputGLSL.cpp
${SOURCE_PATH}/compiler/translator/OutputGLSLBase.cpp
${SOURCE_PATH}/compiler/translator/TranslatorGLSL.cpp
${SOURCE_PATH}/compiler/translator/VersionGLSL.cpp
${SOURCE_PATH}/compiler/translator/tree_ops/RewriteAtomicFunctionExpressions.cpp
${SOURCE_PATH}/compiler/translator/tree_ops/RewriteRepeatedAssignToSwizzled.cpp
)
source_group(compiler\\translator FILES ${ANGLE_SOURCE_COMPILER_TRANSLATOR})


file(GLOB ANGLE_SOURCE_COMPILER_PREPROCESSOR 
${SOURCE_PATH}/compiler/preprocessor/*.h
${SOURCE_PATH}/compiler/preprocessor/*.inl
)
list(APPEND ANGLE_SOURCE_COMPILER_PREPROCESSOR
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
source_group(compiler\\preprocessor FILES ${ANGLE_SOURCE_COMPILER_PREPROCESSOR})


list(APPEND ANGLE_SOURCE_COMPILER
${ANGLE_SOURCE_COMPILER_TRANSLATOR}
${ANGLE_SOURCE_COMPILER_PREPROCESSOR}
)

###############################################################################
#  Thrid Party
###############################################################################
file(GLOB ANGLEG_SOURCE_THIRD_COMPILER ${SOURCE_PATH}/third_party/compiler/*.*)
source_group(third_party\\compiler FILES ${ANGLEG_SOURCE_THIRD_COMPILER})

set(ANGLE_SOURCE_THIRD
${ANGLEG_SOURCE_THIRD_COMPILER}
)

###############################################################################
#  Image Util
###############################################################################
file(GLOB ANGLE_SOURCE_IMAGE_UTIL ${SOURCE_PATH}/image_util/*.*)
source_group(image_util FILES ${ANGLE_SOURCE_IMAGE_UTIL})

###############################################################################
#  ANGLE
###############################################################################
file(GLOB ANGLE_SOURCE_ANGLE 
${SOURCE_PATH}/libANGLE/*.h
${SOURCE_PATH}/libANGLE/*.inl
)
list(APPEND ANGLE_SOURCE_ANGLE
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
${SOURCE_PATH}/libANGLE/GLES1Renderer.cpp
${SOURCE_PATH}/libANGLE/HandleAllocator.cpp
${SOURCE_PATH}/libANGLE/HandleRangeAllocator.cpp
${SOURCE_PATH}/libANGLE/Image.cpp
${SOURCE_PATH}/libANGLE/ImageIndex.cpp
${SOURCE_PATH}/libANGLE/IndexRangeCache.cpp
${SOURCE_PATH}/libANGLE/LoggingAnnotator.cpp
${SOURCE_PATH}/libANGLE/MemoryProgramCache.cpp
${SOURCE_PATH}/libANGLE/Observer.cpp
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
source_group(angle FILES ${ANGLE_SOURCE_ANGLE})

file(GLOB ANGLED_SOURCE_RENDER 
${SOURCE_PATH}/libANGLE/renderer/*.h
${SOURCE_PATH}/libANGLE/renderer/*.inl
${SOURCE_PATH}/libANGLE/renderer/*.cpp 
)
source_group(angle\\renderer FILES ${ANGLED_SOURCE_RENDER})
list(APPEND ANGLE_SOURCE_ANGLE ${ANGLED_SOURCE_RENDER} )

if(MSVC)
    add_definitions(-DNOMINMAX=1)
    add_definitions(-D_ALLOW_KEYWORD_MACROS=1)
    add_definitions(-DANGLE_PLATFORM_WINDOWS=1)
    add_definitions(-DANGLE_ENABLE_HLSL=1)    

    add_definitions(-DANGLE_ENABLE_D3D9=1)
    add_definitions(-DANGLE_ENABLE_D3D11=1) 
    file(GLOB ANGLED_SOURCE_RENDER_D3D 
    ${SOURCE_PATH}/libANGLE/renderer/d3d/*.* 
    ${SOURCE_PATH}/libANGLE/renderer/d3d/d3d9/*.*
    ${SOURCE_PATH}/libANGLE/renderer/d3d/d3d11/*.h
    ${SOURCE_PATH}/libANGLE/renderer/d3d/d3d11/*.cpp
    ${SOURCE_PATH}/libANGLE/renderer/d3d/d3d11/win32/*.*
    )
    source_group(angle\\renderer\\d3d FILES ${ANGLED_SOURCE_RENDER_D3D})
    list(APPEND ANGLE_SOURCE_ANGLE ${ANGLED_SOURCE_RENDER_D3D} ) 

    set(ANGLE_SOURCE_ANGLE_D3D 
    ${SOURCE_PATH}/compiler/translator/blocklayout.cpp 
    ${SOURCE_PATH}/compiler/translator/blocklayoutHLSL.cpp 
    ${SOURCE_PATH}/compiler/translator/blocklayoutHLSL.cpp 
    ${SOURCE_PATH}/third_party/systeminfo/SystemInfo.h
    ${SOURCE_PATH}/third_party/systeminfo/SystemInfo.cpp
    ${SOURCE_PATH}/common/third_party/smhasher/src/PMurHash.h
    ${SOURCE_PATH}/common/third_party/smhasher/src/PMurHash.cpp
    ${SOURCE_PATH}/compiler/translator/emulated_builtin_functions_hlsl_autogen.cpp
    ${SOURCE_PATH}/compiler/translator/UtilsHLSL.cpp
    ${SOURCE_PATH}/compiler/translator/TranslatorHLSL.cpp
    ${SOURCE_PATH}/compiler/translator/OutputHLSL.cpp
    ${SOURCE_PATH}/compiler/translator/ASTMetadataHLSL.cpp
    ${SOURCE_PATH}/compiler/translator/BuiltInFunctionEmulatorHLSL.cpp
    ${SOURCE_PATH}/compiler/translator/ImageFunctionHLSL.cpp
    ${SOURCE_PATH}/compiler/translator/FlagStd140Structs.cpp
    ${SOURCE_PATH}/compiler/translator/StructureHLSL.cpp
    ${SOURCE_PATH}/compiler/translator/TextureFunctionHLSL.cpp
    ${SOURCE_PATH}/compiler/translator/UniformHLSL.cpp
    ${SOURCE_PATH}/compiler/translator/tree_ops/AddDefaultReturnStatements.cpp
    ${SOURCE_PATH}/compiler/translator/tree_ops/ArrayReturnValueToOutParameter.cpp
    ${SOURCE_PATH}/compiler/translator/tree_ops/BreakVariableAliasingInInnerLoops.cpp
    ${SOURCE_PATH}/compiler/translator/tree_ops/ExpandIntegerPowExpressions.cpp
    ${SOURCE_PATH}/compiler/translator/tree_ops/RemoveDynamicIndexing.cpp
    ${SOURCE_PATH}/compiler/translator/tree_ops/RewriteElseBlocks.cpp
    ${SOURCE_PATH}/compiler/translator/tree_ops/RewriteUnaryMinusOperatorInt.cpp
    ${SOURCE_PATH}/compiler/translator/tree_ops/SeparateArrayConstructorStatements.cpp
    ${SOURCE_PATH}/compiler/translator/tree_ops/SeparateArrayInitialization.cpp
    ${SOURCE_PATH}/compiler/translator/tree_ops/SeparateExpressionsReturningArrays.cpp
    ${SOURCE_PATH}/compiler/translator/tree_ops/UnfoldShortCircuitToIf.cpp
    ${SOURCE_PATH}/compiler/translator/tree_ops/WrapSwitchStatementsInBlocks.cpp
    ${SOURCE_PATH}/compiler/translator/tree_ops/RemoveSwitchFallThrough.cpp
    ) 
    source_group(angle\\d3d FILES ${ANGLE_SOURCE_ANGLE_D3D})
    list(APPEND ANGLE_SOURCE_ANGLE ${ANGLE_SOURCE_ANGLE_D3D} ) 

    include(${M3E_SOURCE_DIR}/cmake/tool/FindWindowsSDK.cmake)
    get_windowssdk_library_dirs(${WINDOWSSDK_PREFERRED_DIR} DirectX_LIBRARY_PATHS)

    #message("DirectX_LIBRARY_PATHS=${DirectX_LIBRARY_PATHS}")

    find_library(D3D9_LIBRARY d3d9 ${DirectX_LIBRARY_PATHS} NO_DEFAULT_PATH)
    list(APPEND ANGLE_DEPLIB ${D3D9_LIBRARY})

    find_library(DXGUID_LIBRARY dxguid ${DirectX_LIBRARY_PATHS} NO_DEFAULT_PATH)
    list(APPEND ANGLE_DEPLIB ${DXGUID_LIBRARY}) 


elseif(APPLE)
    add_definitions(-DANGLE_ENABLE_OPENGL=1)
    add_definitions(-DANGLE_PLATFORM_APPLE=1)
    add_definitions(-DANGLE_ENABLE_GLSL=1)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14 -stdlib=libc++")
    set(CMAKE_C_FLAGS "-x objective-c")

    file(GLOB ANGLED_SOURCE_RENDER_GL 
    ${SOURCE_PATH}/libANGLE/renderer/gl/*.h
    ${SOURCE_PATH}/libANGLE/renderer/gl/*.cpp 
    )
    source_group(angle\\renderer\\gl FILES ${ANGLED_SOURCE_RENDER_GL})
    list(APPEND ANGLE_SOURCE_ANGLE ${ANGLED_SOURCE_RENDER_GL} )

    find_package(OpenGL REQUIRED)
    list(APPEND ANGLE_DEPLIB ${OPENGL_LIBRARY})

    find_library(COREGRAPHICS_LIBRARY CoreGraphics)
    list(APPEND ANGLE_DEPLIB ${COREGRAPHICS_LIBRARY})
    find_library(QUARTZCORE_LIBRARY QuartzCore)
    list(APPEND ANGLE_DEPLIB ${QUARTZCORE_LIBRARY})
    find_library(IOSURFACE_LIBRARY IOSurface)
    list(APPEND ANGLE_DEPLIB ${IOSURFACE_LIBRARY})

    file(GLOB ANGLED_SOURCE_CGL ${SOURCE_PATH}/libANGLE/renderer/gl/cgl/*.h )
    list(APPEND ANGLED_SOURCE_CGL
    ${SOURCE_PATH}/libANGLE/renderer/gl/cgl/DisplayCGL.mm  
    ${SOURCE_PATH}/libANGLE/renderer/gl/cgl/IOSurfaceSurfaceCGL.mm   
    ${SOURCE_PATH}/libANGLE/renderer/gl/cgl/PbufferSurfaceCGL.mm   
    ${SOURCE_PATH}/libANGLE/renderer/gl/cgl/WindowSurfaceCGL.mm  
    ${SOURCE_PATH}/common/system_utils.h
    ${SOURCE_PATH}/common/system_utils_mac.cpp  
    )
    source_group(angle\\renderer\\cgl FILES ${ANGLED_SOURCE_CGL})
    list(APPEND ANGLE_SOURCE_ANGLE ${ANGLED_SOURCE_CGL} )

elseif(CYGWIN)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=gnu++11")
elseif(UNIX)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++0x")
endif()

###############################################################################
#  Public Header
###############################################################################
file(GLOB ANGLE_HEADER_KHR ${HEADER_PATH}/KHR/*.h)
source_group(public\\KHR FILES ${ANGLE_HEADER_KHR})

file(GLOB ANGLE_HEADER_GLES2 ${HEADER_PATH}/GLES2/*.h)
source_group(public\\GLES2 FILES ${ANGLE_HEADER_GLES2})

###############################################################################
#  GLESv2
###############################################################################
file(GLOB ANGLE_SOURCE_GLESv2 
${SOURCE_PATH}/libGLESv2/*.cpp
${SOURCE_PATH}/libGLESv2/*.h
${HEADER_PATH}/*.h
${HEADER_PATH}/platform/*.h
)
source_group(GLESv2 FILES ${ANGLE_SOURCE_GLESv2})

###############################################################################
#  Target file
###############################################################################
set(ANGLED_SOURCE_GLES2
${ANGLE_SOURCE_COMMON}
${ANGLE_SOURCE_COMPILER}
${ANGLE_SOURCE_THIRD}
${ANGLE_SOURCE_IMAGE_UTIL}
${ANGLE_SOURCE_ANGLE}
${ANGLE_HEADER_KHR}
${ANGLE_HEADER_GLES2}
${ANGLE_SOURCE_GLESv2}
)

set(DEPLIB_AGLESV2
${ANGLE_DEPLIB}
)

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(GLESv2 SHARED ${ANGLED_SOURCE_GLES2})
target_link_libraries(GLESv2 ${DEPLIB_AGLESV2})
