###############################################################################
#  src/compiler.gni
###############################################################################

#  angle_translator_exported_headers
set(angle_translator_exported_headers
${HEADER_PATH}/GLSLANG/ShaderLang.h 
${HEADER_PATH}/GLSLANG/ShaderVars.h 
${SOURCE_PATH}/compiler/translator/blocklayout.h 
${SOURCE_PATH}/compiler/translator/blocklayoutHLSL.h 
)

# angle_translator_sources
set(angle_translator_sources
${HEADER_PATH}/EGL/egl.h 
${HEADER_PATH}/EGL/eglext.h 
${HEADER_PATH}/EGL/eglplatform.h 
${HEADER_PATH}/GLES2/gl2.h 
${HEADER_PATH}/GLES2/gl2ext.h 
${HEADER_PATH}/GLES2/gl2platform.h 
${HEADER_PATH}/GLES3/gl3.h 
${HEADER_PATH}/GLES3/gl31.h 
${HEADER_PATH}/GLES3/gl32.h 
${HEADER_PATH}/GLES3/gl3platform.h 
${HEADER_PATH}/KHR/khrplatform.h 
${HEADER_PATH}/angle_gl.h 
${SOURCE_PATH}/compiler/translator/BaseTypes.h 
${SOURCE_PATH}/compiler/translator/BuiltInFunctionEmulator.cpp 
${SOURCE_PATH}/compiler/translator/BuiltInFunctionEmulator.h 
${SOURCE_PATH}/compiler/translator/CallDAG.cpp 
${SOURCE_PATH}/compiler/translator/CallDAG.h 
${SOURCE_PATH}/compiler/translator/CodeGen.cpp 
${SOURCE_PATH}/compiler/translator/CollectVariables.cpp 
${SOURCE_PATH}/compiler/translator/CollectVariables.h 
${SOURCE_PATH}/compiler/translator/Common.h 
${SOURCE_PATH}/compiler/translator/Compiler.cpp 
${SOURCE_PATH}/compiler/translator/Compiler.h 
${SOURCE_PATH}/compiler/translator/ConstantUnion.cpp 
${SOURCE_PATH}/compiler/translator/ConstantUnion.h 
${SOURCE_PATH}/compiler/translator/Declarator.cpp 
${SOURCE_PATH}/compiler/translator/Declarator.h 
${SOURCE_PATH}/compiler/translator/Diagnostics.cpp 
${SOURCE_PATH}/compiler/translator/Diagnostics.h 
${SOURCE_PATH}/compiler/translator/DirectiveHandler.cpp 
${SOURCE_PATH}/compiler/translator/DirectiveHandler.h 
${SOURCE_PATH}/compiler/translator/ExtensionBehavior.cpp 
${SOURCE_PATH}/compiler/translator/ExtensionBehavior.h 
${SOURCE_PATH}/compiler/translator/FlagStd140Structs.cpp 
${SOURCE_PATH}/compiler/translator/FlagStd140Structs.h 
${SOURCE_PATH}/compiler/translator/FunctionLookup.cpp 
${SOURCE_PATH}/compiler/translator/FunctionLookup.h 
${SOURCE_PATH}/compiler/translator/HashNames.cpp 
${SOURCE_PATH}/compiler/translator/HashNames.h 
${SOURCE_PATH}/compiler/translator/ImmutableString.h 
${SOURCE_PATH}/compiler/translator/ImmutableStringBuilder.cpp 
${SOURCE_PATH}/compiler/translator/ImmutableStringBuilder.h 
${SOURCE_PATH}/compiler/translator/InfoSink.cpp 
${SOURCE_PATH}/compiler/translator/InfoSink.h 
${SOURCE_PATH}/compiler/translator/Initialize.cpp 
${SOURCE_PATH}/compiler/translator/Initialize.h 
${SOURCE_PATH}/compiler/translator/InitializeDll.cpp 
${SOURCE_PATH}/compiler/translator/InitializeDll.h 
${SOURCE_PATH}/compiler/translator/InitializeGlobals.h 
${SOURCE_PATH}/compiler/translator/IntermNode.cpp 
${SOURCE_PATH}/compiler/translator/IntermNode.h 
${SOURCE_PATH}/compiler/translator/IsASTDepthBelowLimit.cpp 
${SOURCE_PATH}/compiler/translator/IsASTDepthBelowLimit.h 
${SOURCE_PATH}/compiler/translator/Operator.cpp 
${SOURCE_PATH}/compiler/translator/Operator.h 
${SOURCE_PATH}/compiler/translator/OutputTree.cpp 
${SOURCE_PATH}/compiler/translator/OutputTree.h 
${SOURCE_PATH}/compiler/translator/ParseContext.cpp 
${SOURCE_PATH}/compiler/translator/ParseContext.h 
${SOURCE_PATH}/compiler/translator/ParseContext_ESSL_autogen.h 
${SOURCE_PATH}/compiler/translator/ParseContext_complete_autogen.h 
${SOURCE_PATH}/compiler/translator/ParseContext_interm.h 
${SOURCE_PATH}/compiler/translator/PoolAlloc.cpp 
${SOURCE_PATH}/compiler/translator/PoolAlloc.h 
${SOURCE_PATH}/compiler/translator/Pragma.h 
${SOURCE_PATH}/compiler/translator/QualifierTypes.cpp 
${SOURCE_PATH}/compiler/translator/QualifierTypes.h 
${SOURCE_PATH}/compiler/translator/Severity.h 
${SOURCE_PATH}/compiler/translator/ShaderLang.cpp 
${SOURCE_PATH}/compiler/translator/ShaderVars.cpp 
${SOURCE_PATH}/compiler/translator/StaticType.h 
${SOURCE_PATH}/compiler/translator/Symbol.cpp 
${SOURCE_PATH}/compiler/translator/Symbol.h 
${SOURCE_PATH}/compiler/translator/SymbolTable.cpp 
${SOURCE_PATH}/compiler/translator/SymbolTable.h 
${SOURCE_PATH}/compiler/translator/SymbolTable_autogen.h 
${SOURCE_PATH}/compiler/translator/SymbolUniqueId.cpp 
${SOURCE_PATH}/compiler/translator/SymbolUniqueId.h 
${SOURCE_PATH}/compiler/translator/Types.cpp 
${SOURCE_PATH}/compiler/translator/Types.h 
${SOURCE_PATH}/compiler/translator/ValidateAST.cpp 
${SOURCE_PATH}/compiler/translator/ValidateAST.h 
${SOURCE_PATH}/compiler/translator/ValidateGlobalInitializer.cpp 
${SOURCE_PATH}/compiler/translator/ValidateGlobalInitializer.h 
${SOURCE_PATH}/compiler/translator/ValidateLimitations.cpp 
${SOURCE_PATH}/compiler/translator/ValidateLimitations.h 
${SOURCE_PATH}/compiler/translator/ValidateMaxParameters.cpp 
${SOURCE_PATH}/compiler/translator/ValidateMaxParameters.h 
${SOURCE_PATH}/compiler/translator/ValidateOutputs.cpp 
${SOURCE_PATH}/compiler/translator/ValidateOutputs.h 
${SOURCE_PATH}/compiler/translator/ValidateSwitch.cpp 
${SOURCE_PATH}/compiler/translator/ValidateSwitch.h 
${SOURCE_PATH}/compiler/translator/ValidateVaryingLocations.cpp 
${SOURCE_PATH}/compiler/translator/ValidateVaryingLocations.h 
${SOURCE_PATH}/compiler/translator/VariablePacker.cpp 
${SOURCE_PATH}/compiler/translator/VariablePacker.h 
${SOURCE_PATH}/compiler/translator/blocklayout.cpp 
${SOURCE_PATH}/compiler/translator/glslang.h 
${SOURCE_PATH}/compiler/translator/glslang_lex_autogen.cpp 
${SOURCE_PATH}/compiler/translator/glslang_tab_autogen.cpp 
${SOURCE_PATH}/compiler/translator/glslang_tab_autogen.h 
${SOURCE_PATH}/compiler/translator/length_limits.h 
${SOURCE_PATH}/compiler/translator/tree_ops/AddAndTrueToLoopCondition.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/AddAndTrueToLoopCondition.h 
${SOURCE_PATH}/compiler/translator/tree_ops/BreakVariableAliasingInInnerLoops.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/BreakVariableAliasingInInnerLoops.h 
${SOURCE_PATH}/compiler/translator/tree_ops/ClampFragDepth.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/ClampFragDepth.h 
${SOURCE_PATH}/compiler/translator/tree_ops/ClampPointSize.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/ClampPointSize.h 
${SOURCE_PATH}/compiler/translator/tree_ops/DeclareAndInitBuiltinsForInstancedMultiview.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/DeclareAndInitBuiltinsForInstancedMultiview.h 
${SOURCE_PATH}/compiler/translator/tree_ops/DeferGlobalInitializers.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/DeferGlobalInitializers.h 
${SOURCE_PATH}/compiler/translator/tree_ops/EarlyFragmentTestsOptimization.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/EarlyFragmentTestsOptimization.h 
${SOURCE_PATH}/compiler/translator/tree_ops/EmulateGLFragColorBroadcast.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/EmulateGLFragColorBroadcast.h 
${SOURCE_PATH}/compiler/translator/tree_ops/EmulateMultiDrawShaderBuiltins.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/EmulateMultiDrawShaderBuiltins.h 
${SOURCE_PATH}/compiler/translator/tree_ops/EmulatePrecision.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/EmulatePrecision.h 
${SOURCE_PATH}/compiler/translator/tree_ops/ExpandIntegerPowExpressions.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/ExpandIntegerPowExpressions.h 
${SOURCE_PATH}/compiler/translator/tree_ops/FoldExpressions.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/FoldExpressions.h 
${SOURCE_PATH}/compiler/translator/tree_ops/InitializeVariables.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/InitializeVariables.h 
${SOURCE_PATH}/compiler/translator/tree_ops/NameEmbeddedUniformStructs.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/NameEmbeddedUniformStructs.h 
${SOURCE_PATH}/compiler/translator/tree_ops/PruneEmptyCases.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/PruneEmptyCases.h 
${SOURCE_PATH}/compiler/translator/tree_ops/PruneNoOps.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/PruneNoOps.h 
${SOURCE_PATH}/compiler/translator/tree_ops/RecordConstantPrecision.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/RecordConstantPrecision.h 
${SOURCE_PATH}/compiler/translator/tree_ops/RegenerateStructNames.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/RegenerateStructNames.h 
${SOURCE_PATH}/compiler/translator/tree_ops/RemoveArrayLengthMethod.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/RemoveArrayLengthMethod.h 
${SOURCE_PATH}/compiler/translator/tree_ops/RemoveAtomicCounterBuiltins.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/RemoveAtomicCounterBuiltins.h 
${SOURCE_PATH}/compiler/translator/tree_ops/RemoveDynamicIndexing.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/RemoveDynamicIndexing.h 
${SOURCE_PATH}/compiler/translator/tree_ops/RemoveInactiveInterfaceVariables.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/RemoveInactiveInterfaceVariables.h 
${SOURCE_PATH}/compiler/translator/tree_ops/RemoveInvariantDeclaration.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/RemoveInvariantDeclaration.h 
${SOURCE_PATH}/compiler/translator/tree_ops/RemovePow.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/RemovePow.h 
${SOURCE_PATH}/compiler/translator/tree_ops/RemoveUnreferencedVariables.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/RemoveUnreferencedVariables.h 
${SOURCE_PATH}/compiler/translator/tree_ops/RewriteAtomicCounters.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/RewriteAtomicCounters.h 
${SOURCE_PATH}/compiler/translator/tree_ops/RewriteAtomicFunctionExpressions.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/RewriteAtomicFunctionExpressions.h 
${SOURCE_PATH}/compiler/translator/tree_ops/RewriteCubeMapSamplersAs2DArray.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/RewriteCubeMapSamplersAs2DArray.h 
${SOURCE_PATH}/compiler/translator/tree_ops/RewriteDfdy.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/RewriteDfdy.h 
${SOURCE_PATH}/compiler/translator/tree_ops/RewriteDoWhile.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/RewriteDoWhile.h 
${SOURCE_PATH}/compiler/translator/tree_ops/RewriteExpressionsWithShaderStorageBlock.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/RewriteExpressionsWithShaderStorageBlock.h 
${SOURCE_PATH}/compiler/translator/tree_ops/RewriteRepeatedAssignToSwizzled.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/RewriteRepeatedAssignToSwizzled.h 
${SOURCE_PATH}/compiler/translator/tree_ops/RewriteRowMajorMatrices.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/RewriteRowMajorMatrices.h 
${SOURCE_PATH}/compiler/translator/tree_ops/RewriteStructSamplers.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/RewriteStructSamplers.h 
${SOURCE_PATH}/compiler/translator/tree_ops/RewriteStructSamplersOld.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/RewriteTexelFetchOffset.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/RewriteTexelFetchOffset.h 
${SOURCE_PATH}/compiler/translator/tree_ops/RewriteUnaryMinusOperatorFloat.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/RewriteUnaryMinusOperatorFloat.h 
${SOURCE_PATH}/compiler/translator/tree_ops/RewriteUnaryMinusOperatorInt.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/RewriteUnaryMinusOperatorInt.h 
${SOURCE_PATH}/compiler/translator/tree_ops/ScalarizeVecAndMatConstructorArgs.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/ScalarizeVecAndMatConstructorArgs.h 
${SOURCE_PATH}/compiler/translator/tree_ops/SeparateDeclarations.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/SeparateDeclarations.h 
${SOURCE_PATH}/compiler/translator/tree_ops/SimplifyLoopConditions.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/SimplifyLoopConditions.h 
${SOURCE_PATH}/compiler/translator/tree_ops/SplitSequenceOperator.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/SplitSequenceOperator.h 
${SOURCE_PATH}/compiler/translator/tree_ops/UnfoldShortCircuitAST.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/UnfoldShortCircuitAST.h 
${SOURCE_PATH}/compiler/translator/tree_ops/UseInterfaceBlockFields.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/UseInterfaceBlockFields.h 
${SOURCE_PATH}/compiler/translator/tree_ops/VectorizeVectorScalarArithmetic.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/VectorizeVectorScalarArithmetic.h 
${SOURCE_PATH}/compiler/translator/tree_util/BuiltIn.h 
${SOURCE_PATH}/compiler/translator/tree_util/BuiltIn_ESSL_autogen.h 
${SOURCE_PATH}/compiler/translator/tree_util/BuiltIn_complete_autogen.h 
${SOURCE_PATH}/compiler/translator/tree_util/FindFunction.cpp 
${SOURCE_PATH}/compiler/translator/tree_util/FindFunction.h 
${SOURCE_PATH}/compiler/translator/tree_util/FindMain.cpp 
${SOURCE_PATH}/compiler/translator/tree_util/FindMain.h 
${SOURCE_PATH}/compiler/translator/tree_util/FindSymbolNode.cpp 
${SOURCE_PATH}/compiler/translator/tree_util/FindSymbolNode.h 
${SOURCE_PATH}/compiler/translator/tree_util/IntermNodePatternMatcher.cpp 
${SOURCE_PATH}/compiler/translator/tree_util/IntermNodePatternMatcher.h 
${SOURCE_PATH}/compiler/translator/tree_util/IntermNode_util.cpp 
${SOURCE_PATH}/compiler/translator/tree_util/IntermNode_util.h 
${SOURCE_PATH}/compiler/translator/tree_util/IntermTraverse.cpp 
${SOURCE_PATH}/compiler/translator/tree_util/IntermTraverse.h 
${SOURCE_PATH}/compiler/translator/tree_util/NodeSearch.h 
${SOURCE_PATH}/compiler/translator/tree_util/ReplaceClipDistanceVariable.cpp 
${SOURCE_PATH}/compiler/translator/tree_util/ReplaceClipDistanceVariable.h 
${SOURCE_PATH}/compiler/translator/tree_util/ReplaceShadowingVariables.cpp 
${SOURCE_PATH}/compiler/translator/tree_util/ReplaceShadowingVariables.h 
${SOURCE_PATH}/compiler/translator/tree_util/ReplaceVariable.cpp 
${SOURCE_PATH}/compiler/translator/tree_util/ReplaceVariable.h 
${SOURCE_PATH}/compiler/translator/tree_util/RunAtTheEndOfShader.cpp 
${SOURCE_PATH}/compiler/translator/tree_util/RunAtTheEndOfShader.h 
${SOURCE_PATH}/compiler/translator/tree_util/Visit.h 
${SOURCE_PATH}/compiler/translator/util.cpp 
${SOURCE_PATH}/compiler/translator/util.h 
${SOURCE_PATH}/third_party/compiler/ArrayBoundsClamper.cpp 
${SOURCE_PATH}/third_party/compiler/ArrayBoundsClamper.h 
)

# angle_translator_essl_sources

# EMPTY
# No use in current platforms

# angle_translator_glsl_sources
set(angle_translator_glsl_sources
${SOURCE_PATH}/compiler/translator/BuiltInFunctionEmulatorGLSL.cpp 
${SOURCE_PATH}/compiler/translator/BuiltInFunctionEmulatorGLSL.h 
${SOURCE_PATH}/compiler/translator/BuiltinsWorkaroundGLSL.cpp 
${SOURCE_PATH}/compiler/translator/BuiltinsWorkaroundGLSL.h 
${SOURCE_PATH}/compiler/translator/ExtensionGLSL.cpp 
${SOURCE_PATH}/compiler/translator/ExtensionGLSL.h 
${SOURCE_PATH}/compiler/translator/OutputGLSL.cpp 
${SOURCE_PATH}/compiler/translator/OutputGLSL.h 
${SOURCE_PATH}/compiler/translator/OutputGLSLBase.cpp 
${SOURCE_PATH}/compiler/translator/OutputGLSLBase.h 
${SOURCE_PATH}/compiler/translator/TranslatorGLSL.cpp 
${SOURCE_PATH}/compiler/translator/TranslatorGLSL.h 
${SOURCE_PATH}/compiler/translator/VersionGLSL.cpp 
${SOURCE_PATH}/compiler/translator/VersionGLSL.h 
)

# angle_translator_hlsl_sources
set(angle_translator_hlsl_sources
${SOURCE_PATH}/compiler/translator/ASTMetadataHLSL.cpp 
${SOURCE_PATH}/compiler/translator/ASTMetadataHLSL.h 
${SOURCE_PATH}/compiler/translator/AtomicCounterFunctionHLSL.cpp 
${SOURCE_PATH}/compiler/translator/AtomicCounterFunctionHLSL.h 
${SOURCE_PATH}/compiler/translator/BuiltInFunctionEmulatorHLSL.cpp 
${SOURCE_PATH}/compiler/translator/BuiltInFunctionEmulatorHLSL.h 
${SOURCE_PATH}/compiler/translator/ImageFunctionHLSL.cpp 
${SOURCE_PATH}/compiler/translator/ImageFunctionHLSL.h 
${SOURCE_PATH}/compiler/translator/OutputHLSL.cpp 
${SOURCE_PATH}/compiler/translator/OutputHLSL.h 
${SOURCE_PATH}/compiler/translator/ResourcesHLSL.cpp 
${SOURCE_PATH}/compiler/translator/ResourcesHLSL.h 
${SOURCE_PATH}/compiler/translator/ShaderStorageBlockFunctionHLSL.cpp 
${SOURCE_PATH}/compiler/translator/ShaderStorageBlockFunctionHLSL.h 
${SOURCE_PATH}/compiler/translator/ShaderStorageBlockOutputHLSL.cpp 
${SOURCE_PATH}/compiler/translator/ShaderStorageBlockOutputHLSL.h 
${SOURCE_PATH}/compiler/translator/StructureHLSL.cpp 
${SOURCE_PATH}/compiler/translator/StructureHLSL.h 
${SOURCE_PATH}/compiler/translator/TextureFunctionHLSL.cpp 
${SOURCE_PATH}/compiler/translator/TextureFunctionHLSL.h 
${SOURCE_PATH}/compiler/translator/TranslatorHLSL.cpp 
${SOURCE_PATH}/compiler/translator/TranslatorHLSL.h 
${SOURCE_PATH}/compiler/translator/UtilsHLSL.cpp 
${SOURCE_PATH}/compiler/translator/UtilsHLSL.h 
${SOURCE_PATH}/compiler/translator/blocklayoutHLSL.cpp 
${SOURCE_PATH}/compiler/translator/emulated_builtin_functions_hlsl_autogen.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/AddDefaultReturnStatements.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/AddDefaultReturnStatements.h 
${SOURCE_PATH}/compiler/translator/tree_ops/ArrayReturnValueToOutParameter.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/ArrayReturnValueToOutParameter.h 
${SOURCE_PATH}/compiler/translator/tree_ops/RemoveSwitchFallThrough.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/RemoveSwitchFallThrough.h 
${SOURCE_PATH}/compiler/translator/tree_ops/RewriteElseBlocks.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/RewriteElseBlocks.h 
${SOURCE_PATH}/compiler/translator/tree_ops/SeparateArrayConstructorStatements.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/SeparateArrayConstructorStatements.h 
${SOURCE_PATH}/compiler/translator/tree_ops/SeparateArrayInitialization.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/SeparateArrayInitialization.h 
${SOURCE_PATH}/compiler/translator/tree_ops/SeparateExpressionsReturningArrays.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/SeparateExpressionsReturningArrays.h 
${SOURCE_PATH}/compiler/translator/tree_ops/UnfoldShortCircuitToIf.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/UnfoldShortCircuitToIf.h 
${SOURCE_PATH}/compiler/translator/tree_ops/WrapSwitchStatementsInBlocks.cpp 
${SOURCE_PATH}/compiler/translator/tree_ops/WrapSwitchStatementsInBlocks.h 
)

# angle_translator_lib_vulkan_sources
set(angle_translator_lib_vulkan_sources
${SOURCE_PATH}/compiler/translator/OutputVulkanGLSL.cpp 
${SOURCE_PATH}/compiler/translator/OutputVulkanGLSL.h 
${SOURCE_PATH}/compiler/translator/TranslatorVulkan.cpp 
${SOURCE_PATH}/compiler/translator/TranslatorVulkan.h 
)

if (is_android)
list(APPEND angle_translator_sources
${SOURCE_PATH}/compiler/translator/ImmutableString_ESSL_autogen.cpp 
${SOURCE_PATH}/compiler/translator/SymbolTable_ESSL_autogen.cpp 
)
else()
list(APPEND angle_translator_sources
${SOURCE_PATH}/compiler/translator/ImmutableString_autogen.cpp 
${SOURCE_PATH}/compiler/translator/SymbolTable_autogen.cpp 
)
endif()

# angle_translator_lib_metal_sources
set(angle_translator_lib_metal_sources
${SOURCE_PATH}/compiler/translator/OutputVulkanGLSLForMetal.h 
${SOURCE_PATH}/compiler/translator/OutputVulkanGLSLForMetal.mm 
${SOURCE_PATH}/compiler/translator/TranslatorMetal.cpp 
${SOURCE_PATH}/compiler/translator/TranslatorMetal.h 
)

# angle_preprocessor_sources
set(angle_preprocessor_sources
${SOURCE_PATH}/compiler/preprocessor/DiagnosticsBase.cpp 
${SOURCE_PATH}/compiler/preprocessor/DiagnosticsBase.h 
${SOURCE_PATH}/compiler/preprocessor/DirectiveHandlerBase.cpp 
${SOURCE_PATH}/compiler/preprocessor/DirectiveHandlerBase.h 
${SOURCE_PATH}/compiler/preprocessor/DirectiveParser.cpp 
${SOURCE_PATH}/compiler/preprocessor/DirectiveParser.h 
${SOURCE_PATH}/compiler/preprocessor/ExpressionParser.h 
${SOURCE_PATH}/compiler/preprocessor/Input.cpp 
${SOURCE_PATH}/compiler/preprocessor/Input.h 
${SOURCE_PATH}/compiler/preprocessor/Lexer.cpp 
${SOURCE_PATH}/compiler/preprocessor/Lexer.h 
${SOURCE_PATH}/compiler/preprocessor/Macro.cpp 
${SOURCE_PATH}/compiler/preprocessor/Macro.h 
${SOURCE_PATH}/compiler/preprocessor/MacroExpander.cpp 
${SOURCE_PATH}/compiler/preprocessor/MacroExpander.h 
${SOURCE_PATH}/compiler/preprocessor/Preprocessor.cpp 
${SOURCE_PATH}/compiler/preprocessor/Preprocessor.h 
${SOURCE_PATH}/compiler/preprocessor/SourceLocation.h 
${SOURCE_PATH}/compiler/preprocessor/Token.cpp 
${SOURCE_PATH}/compiler/preprocessor/Token.h 
${SOURCE_PATH}/compiler/preprocessor/Tokenizer.h 
${SOURCE_PATH}/compiler/preprocessor/numeric_lex.h 
${SOURCE_PATH}/compiler/preprocessor/preprocessor_lex_autogen.cpp 
${SOURCE_PATH}/compiler/preprocessor/preprocessor_tab_autogen.cpp 
)
