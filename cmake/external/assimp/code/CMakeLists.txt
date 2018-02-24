
SET( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/assimp/include/assimp )
SET( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/assimp/code/)

SET( COMPILER_HEADERS
  ${HEADER_PATH}/Compiler/pushpack1.h
  ${HEADER_PATH}/Compiler/poppack1.h
  ${HEADER_PATH}/Compiler/pstdint.h
)
SOURCE_GROUP( Compiler FILES ${COMPILER_HEADERS})

SET( PUBLIC_HEADERS
  ${HEADER_PATH}/anim.h
  ${HEADER_PATH}/ai_assert.h
  ${HEADER_PATH}/camera.h
  ${HEADER_PATH}/color4.h
  ${HEADER_PATH}/color4.inl
  ${CMAKE_BINARY_DIR}/assimp/include/assimp/config.h
  ${HEADER_PATH}/defs.h
  ${HEADER_PATH}/Defines.h
  ${HEADER_PATH}/cfileio.h
  ${HEADER_PATH}/light.h
  ${HEADER_PATH}/material.h
  ${HEADER_PATH}/material.inl
  ${HEADER_PATH}/matrix3x3.h
  ${HEADER_PATH}/matrix3x3.inl
  ${HEADER_PATH}/matrix4x4.h
  ${HEADER_PATH}/matrix4x4.inl
  ${HEADER_PATH}/mesh.h
  ${HEADER_PATH}/postprocess.h
  ${HEADER_PATH}/quaternion.h
  ${HEADER_PATH}/quaternion.inl
  ${HEADER_PATH}/scene.h
  ${HEADER_PATH}/metadata.h
  ${HEADER_PATH}/texture.h
  ${HEADER_PATH}/types.h
  ${HEADER_PATH}/vector2.h
  ${HEADER_PATH}/vector2.inl
  ${HEADER_PATH}/vector3.h
  ${HEADER_PATH}/vector3.inl
  ${HEADER_PATH}/version.h
  ${HEADER_PATH}/cimport.h
  ${HEADER_PATH}/importerdesc.h
  ${HEADER_PATH}/Importer.hpp
  ${HEADER_PATH}/DefaultLogger.hpp
  ${HEADER_PATH}/ProgressHandler.hpp
  ${HEADER_PATH}/IOStream.hpp
  ${HEADER_PATH}/IOSystem.hpp
  ${HEADER_PATH}/Logger.hpp
  ${HEADER_PATH}/LogStream.hpp
  ${HEADER_PATH}/NullLogger.hpp
  ${HEADER_PATH}/cexport.h
  ${HEADER_PATH}/Exporter.hpp
  ${HEADER_PATH}/DefaultIOStream.h
  ${HEADER_PATH}/DefaultIOSystem.h
  ${HEADER_PATH}/SceneCombiner.h
  ${HEADER_PATH}/fast_atof.h
  ${HEADER_PATH}/qnan.h
  ${HEADER_PATH}/BaseImporter.h
  ${HEADER_PATH}/Hash.h
  ${HEADER_PATH}/MemoryIOWrapper.h
  ${HEADER_PATH}/ParsingUtils.h
  ${HEADER_PATH}/StreamReader.h
  ${HEADER_PATH}/StreamWriter.h
  ${HEADER_PATH}/StringComparison.h
  ${HEADER_PATH}/StringUtils.h
  ${HEADER_PATH}/SGSpatialSort.h
  ${HEADER_PATH}/GenericProperty.h
  ${HEADER_PATH}/SpatialSort.h
  ${HEADER_PATH}/SkeletonMeshBuilder.h
  ${HEADER_PATH}/SmoothingGroups.h
  ${HEADER_PATH}/SmoothingGroups.inl
  ${HEADER_PATH}/StandardShapes.h
  ${HEADER_PATH}/RemoveComments.h
  ${HEADER_PATH}/Subdivision.h
  ${HEADER_PATH}/Vertex.h
  ${HEADER_PATH}/LineSplitter.h
  ${HEADER_PATH}/TinyFormatter.h
  ${HEADER_PATH}/Profiler.h
  ${HEADER_PATH}/LogAux.h
  ${HEADER_PATH}/Bitmap.h
  ${HEADER_PATH}/XMLTools.h
  ${HEADER_PATH}/IOStreamBuffer.h
  ${HEADER_PATH}/CreateAnimMesh.h
  ${HEADER_PATH}/irrXMLWrapper.h
  ${HEADER_PATH}/BlobIOSystem.h
  ${HEADER_PATH}/MathFunctions.h
  ${HEADER_PATH}/Macros.h
  ${HEADER_PATH}/Exceptional.h
  ${HEADER_PATH}/ByteSwapper.h
)

SET( Core_SRCS
${SOURCE_PATH}/Assimp.cpp
)

SET( Logging_SRCS
  ${HEADER_PATH}/DefaultLogger.hpp
  ${HEADER_PATH}/LogStream.hpp
  ${HEADER_PATH}/Logger.hpp
  ${HEADER_PATH}/NullLogger.hpp
  ${SOURCE_PATH}/Win32DebugLogStream.h
  ${SOURCE_PATH}/DefaultLogger.cpp
  ${SOURCE_PATH}/FileLogStream.h
  ${SOURCE_PATH}/StdOStreamLogStream.h
)
SOURCE_GROUP(Logging FILES ${Logging_SRCS})

SET( Common_SRCS
${SOURCE_PATH}/BaseImporter.cpp
${SOURCE_PATH}/BaseProcess.cpp
${SOURCE_PATH}/BaseProcess.h
${SOURCE_PATH}/Importer.h
${SOURCE_PATH}/ScenePrivate.h
${SOURCE_PATH}/PostStepRegistry.cpp
${SOURCE_PATH}/ImporterRegistry.cpp
${SOURCE_PATH}/DefaultProgressHandler.h
${SOURCE_PATH}/DefaultIOStream.cpp
${SOURCE_PATH}/DefaultIOSystem.cpp
${SOURCE_PATH}/CInterfaceIOWrapper.cpp
${SOURCE_PATH}/CInterfaceIOWrapper.h
${SOURCE_PATH}/Importer.cpp
${SOURCE_PATH}/IFF.h
${SOURCE_PATH}/SGSpatialSort.cpp
${SOURCE_PATH}/VertexTriangleAdjacency.cpp
${SOURCE_PATH}/VertexTriangleAdjacency.h
${SOURCE_PATH}/SpatialSort.cpp
${SOURCE_PATH}/SceneCombiner.cpp
${SOURCE_PATH}/ScenePreprocessor.cpp
${SOURCE_PATH}/ScenePreprocessor.h
${SOURCE_PATH}/SkeletonMeshBuilder.cpp
${SOURCE_PATH}/SplitByBoneCountProcess.cpp
${SOURCE_PATH}/SplitByBoneCountProcess.h
${SOURCE_PATH}/ScaleProcess.cpp
${SOURCE_PATH}/ScaleProcess.h
${SOURCE_PATH}/StandardShapes.cpp
${SOURCE_PATH}/TargetAnimation.cpp
${SOURCE_PATH}/TargetAnimation.h
${SOURCE_PATH}/RemoveComments.cpp
${SOURCE_PATH}/Subdivision.cpp
${SOURCE_PATH}/scene.cpp
${SOURCE_PATH}/Bitmap.cpp
${SOURCE_PATH}/Version.cpp
${SOURCE_PATH}/CreateAnimMesh.cpp
)
SOURCE_GROUP(Common FILES ${Common_SRCS})

IF ( ASSIMP_BUILD_NONFREE_C4D_IMPORTER )
  SET( C4D_SRCS
  ${SOURCE_PATH}/C4DImporter.cpp
  ${SOURCE_PATH}/C4DImporter.h
  )
  SOURCE_GROUP( C4D FILES ${C4D_SRCS})
ENDIF ( ASSIMP_BUILD_NONFREE_C4D_IMPORTER )

# if this variable is set to TRUE, the user can manually disable importers by setting
# ASSIMP_BUILD_XXX_IMPORTER to FALSE for each importer
# if this variable is set to FALSE, the user can manually enable importers by setting
# ASSIMP_BUILD_XXX_IMPORTER to TRUE for each importer
OPTION(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT "default value of all ASSIMP_BUILD_XXX_IMPORTER value" TRUE)


# macro to add the CMake Option ADD_ASSIMP_IMPORTER_<name> which enables compile of loader
# this way selective loaders can be compiled (reduces filesize + compile time)
MACRO(ADD_ASSIMP_IMPORTER name)
  OPTION(ASSIMP_BUILD_${name}_IMPORTER "build the ${name} importer" ${ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT})
  IF(ASSIMP_BUILD_${name}_IMPORTER)
    LIST(APPEND ASSIMP_LOADER_SRCS ${ARGN})
    SET(ASSIMP_IMPORTERS_ENABLED "${ASSIMP_IMPORTERS_ENABLED} ${name}")
    SET(${name}_SRCS ${ARGN})
    SOURCE_GROUP(${name} FILES ${ARGN})
  ELSE()
    SET(${name}_SRC "")
    SET(ASSIMP_IMPORTERS_DISABLED "${ASSIMP_IMPORTERS_DISABLED} ${name}")
    add_definitions(-DASSIMP_BUILD_NO_${name}_IMPORTER)
    add_definitions(-DASSIMP_BUILD_NO_${name}_EXPORTER)
  ENDIF()
ENDMACRO()

SET(ASSIMP_LOADER_SRCS "")
SET(ASSIMP_IMPORTERS_ENABLED "") # list of enabled importers
SET(ASSIMP_IMPORTERS_DISABLED "") # disabled list (used to print)


ADD_ASSIMP_IMPORTER( AMF
${SOURCE_PATH}/AMFImporter.hpp
${SOURCE_PATH}/AMFImporter_Macro.hpp
${SOURCE_PATH}/AMFImporter_Node.hpp
${SOURCE_PATH}/AMFImporter.cpp
${SOURCE_PATH}/AMFImporter_Geometry.cpp
${SOURCE_PATH}/AMFImporter_Material.cpp
${SOURCE_PATH}/AMFImporter_Postprocess.cpp
)

ADD_ASSIMP_IMPORTER( 3DS
${SOURCE_PATH}/3DSConverter.cpp
${SOURCE_PATH}/3DSHelper.h
${SOURCE_PATH}/3DSLoader.cpp
${SOURCE_PATH}/3DSLoader.h
${SOURCE_PATH}/3DSExporter.h
${SOURCE_PATH}/3DSExporter.cpp
)

ADD_ASSIMP_IMPORTER( AC
${SOURCE_PATH}/ACLoader.cpp
${SOURCE_PATH}/ACLoader.h
)

ADD_ASSIMP_IMPORTER( ASE
${SOURCE_PATH}/ASELoader.cpp
${SOURCE_PATH}/ASELoader.h
${SOURCE_PATH}/ASEParser.cpp
${SOURCE_PATH}/ASEParser.h
)

ADD_ASSIMP_IMPORTER( ASSBIN
${SOURCE_PATH}/AssbinExporter.h
${SOURCE_PATH}/AssbinExporter.cpp
${SOURCE_PATH}/AssbinLoader.h
${SOURCE_PATH}/AssbinLoader.cpp
)

ADD_ASSIMP_IMPORTER( ASSXML
${SOURCE_PATH}/AssxmlExporter.h
${SOURCE_PATH}/AssxmlExporter.cpp
)

ADD_ASSIMP_IMPORTER( B3D
${SOURCE_PATH}/B3DImporter.cpp
${SOURCE_PATH}/B3DImporter.h
)

ADD_ASSIMP_IMPORTER( BVH
${SOURCE_PATH}/BVHLoader.cpp
${SOURCE_PATH}/BVHLoader.h
)

ADD_ASSIMP_IMPORTER( COLLADA
${SOURCE_PATH}/ColladaHelper.h
${SOURCE_PATH}/ColladaLoader.cpp
${SOURCE_PATH}/ColladaLoader.h
${SOURCE_PATH}/ColladaParser.cpp
${SOURCE_PATH}/ColladaParser.h
${SOURCE_PATH}/ColladaExporter.h
${SOURCE_PATH}/ColladaExporter.cpp
)

ADD_ASSIMP_IMPORTER( DXF
${SOURCE_PATH}/DXFLoader.cpp
${SOURCE_PATH}/DXFLoader.h
${SOURCE_PATH}/DXFHelper.h
)

ADD_ASSIMP_IMPORTER( CSM
${SOURCE_PATH}/CSMLoader.cpp
${SOURCE_PATH}/CSMLoader.h
)

ADD_ASSIMP_IMPORTER( HMP
${SOURCE_PATH}/HMPFileData.h
${SOURCE_PATH}/HMPLoader.cpp
${SOURCE_PATH}/HMPLoader.h
${SOURCE_PATH}/HalfLifeFileData.h
)

ADD_ASSIMP_IMPORTER( IRRMESH
${SOURCE_PATH}/IRRMeshLoader.cpp
${SOURCE_PATH}/IRRMeshLoader.h
${SOURCE_PATH}/IRRShared.cpp
${SOURCE_PATH}/IRRShared.h
)

ADD_ASSIMP_IMPORTER( IRR
${SOURCE_PATH}/IRRLoader.cpp
${SOURCE_PATH}/IRRLoader.h
${SOURCE_PATH}/IRRShared.cpp
${SOURCE_PATH}/IRRShared.h
)

ADD_ASSIMP_IMPORTER( LWO
${SOURCE_PATH}/LWOAnimation.cpp
${SOURCE_PATH}/LWOAnimation.h
${SOURCE_PATH}/LWOBLoader.cpp
${SOURCE_PATH}/LWOFileData.h
${SOURCE_PATH}/LWOLoader.cpp
${SOURCE_PATH}/LWOLoader.h
${SOURCE_PATH}/LWOMaterial.cpp
)

ADD_ASSIMP_IMPORTER( LWS
${SOURCE_PATH}/LWSLoader.cpp
${SOURCE_PATH}/LWSLoader.h
)

ADD_ASSIMP_IMPORTER( MD2
${SOURCE_PATH}/MD2FileData.h
${SOURCE_PATH}/MD2Loader.cpp
${SOURCE_PATH}/MD2Loader.h
${SOURCE_PATH}/MD2NormalTable.h
)

ADD_ASSIMP_IMPORTER( MD3
${SOURCE_PATH}/MD3FileData.h
${SOURCE_PATH}/MD3Loader.cpp
${SOURCE_PATH}/MD3Loader.h
)

ADD_ASSIMP_IMPORTER( MD5
${SOURCE_PATH}/MD5Loader.cpp
${SOURCE_PATH}/MD5Loader.h
${SOURCE_PATH}/MD5Parser.cpp
${SOURCE_PATH}/MD5Parser.h
)

ADD_ASSIMP_IMPORTER( MDC
${SOURCE_PATH}/MDCFileData.h
${SOURCE_PATH}/MDCLoader.cpp
${SOURCE_PATH}/MDCLoader.h
${SOURCE_PATH}/MDCNormalTable.h
)

ADD_ASSIMP_IMPORTER( MDL
${SOURCE_PATH}/MDLDefaultColorMap.h
${SOURCE_PATH}/MDLFileData.h
${SOURCE_PATH}/MDLLoader.cpp
${SOURCE_PATH}/MDLLoader.h
${SOURCE_PATH}/MDLMaterialLoader.cpp
)

SET( MaterialSystem_SRCS
${SOURCE_PATH}/MaterialSystem.cpp
${SOURCE_PATH}/MaterialSystem.h
)
SOURCE_GROUP( MaterialSystem FILES ${MaterialSystem_SRCS})

ADD_ASSIMP_IMPORTER( NFF
${SOURCE_PATH}/NFFLoader.cpp
${SOURCE_PATH}/NFFLoader.h
)

ADD_ASSIMP_IMPORTER( NDO
${SOURCE_PATH}/NDOLoader.cpp
${SOURCE_PATH}/NDOLoader.h
)

ADD_ASSIMP_IMPORTER( OFF
${SOURCE_PATH}/OFFLoader.cpp
${SOURCE_PATH}/OFFLoader.h
)

ADD_ASSIMP_IMPORTER( OBJ
${SOURCE_PATH}/ObjFileData.h
${SOURCE_PATH}/ObjFileImporter.cpp
${SOURCE_PATH}/ObjFileImporter.h
${SOURCE_PATH}/ObjFileMtlImporter.cpp
${SOURCE_PATH}/ObjFileMtlImporter.h
${SOURCE_PATH}/ObjFileParser.cpp
${SOURCE_PATH}/ObjFileParser.h
${SOURCE_PATH}/ObjTools.h
${SOURCE_PATH}/ObjExporter.h
${SOURCE_PATH}/ObjExporter.cpp
)

ADD_ASSIMP_IMPORTER( OGRE
${SOURCE_PATH}/OgreImporter.h
${SOURCE_PATH}/OgreStructs.h
${SOURCE_PATH}/OgreParsingUtils.h
  ${SOURCE_PATH}/OgreBinarySerializer.h
  ${SOURCE_PATH}/OgreXmlSerializer.h
  ${SOURCE_PATH}/OgreImporter.cpp
  ${SOURCE_PATH}/OgreStructs.cpp
  ${SOURCE_PATH}/OgreBinarySerializer.cpp
  ${SOURCE_PATH}/OgreXmlSerializer.cpp
  ${SOURCE_PATH}/OgreMaterial.cpp
)

ADD_ASSIMP_IMPORTER( OPENGEX
${SOURCE_PATH}/OpenGEXExporter.cpp
  ${SOURCE_PATH}/OpenGEXExporter.h
  ${SOURCE_PATH}/OpenGEXImporter.cpp
  ${SOURCE_PATH}/OpenGEXImporter.h
  ${SOURCE_PATH}/OpenGEXStructs.h
)

ADD_ASSIMP_IMPORTER( PLY
${SOURCE_PATH}/PlyLoader.cpp
  ${SOURCE_PATH}/PlyLoader.h
  ${SOURCE_PATH}/PlyParser.cpp
  ${SOURCE_PATH}/PlyParser.h
  ${SOURCE_PATH}/PlyExporter.cpp
  ${SOURCE_PATH}/PlyExporter.h
)

ADD_ASSIMP_IMPORTER( MS3D
${SOURCE_PATH}/MS3DLoader.cpp
  ${SOURCE_PATH}/MS3DLoader.h
)

ADD_ASSIMP_IMPORTER( COB
${SOURCE_PATH}/COBLoader.cpp
  ${SOURCE_PATH}/COBLoader.h
  ${SOURCE_PATH}/COBScene.h
)

ADD_ASSIMP_IMPORTER( BLEND
${SOURCE_PATH}/BlenderLoader.cpp
  ${SOURCE_PATH}/BlenderLoader.h
  ${SOURCE_PATH}/BlenderDNA.cpp
  ${SOURCE_PATH}/BlenderDNA.h
  ${SOURCE_PATH}/BlenderDNA.inl
  ${SOURCE_PATH}/BlenderScene.cpp
  ${SOURCE_PATH}/BlenderScene.h
  ${SOURCE_PATH}/BlenderSceneGen.h
  ${SOURCE_PATH}/BlenderIntermediate.h
  ${SOURCE_PATH}/BlenderModifier.h
  ${SOURCE_PATH}/BlenderModifier.cpp
  ${SOURCE_PATH}/BlenderBMesh.h
  ${SOURCE_PATH}/BlenderBMesh.cpp
  ${SOURCE_PATH}/BlenderTessellator.h
  ${SOURCE_PATH}/BlenderTessellator.cpp
)


ADD_ASSIMP_IMPORTER( IFC
${SOURCE_PATH}/Importer/IFC/IFCLoader.cpp
${SOURCE_PATH}/Importer/IFC/IFCLoader.h
${SOURCE_PATH}/Importer/IFC/IFCReaderGen1_2x3.cpp
${SOURCE_PATH}/Importer/IFC/IFCReaderGen2_2x3.cpp
${SOURCE_PATH}/Importer/IFC/IFCReaderGen_2x3.h
${SOURCE_PATH}/Importer/IFC/IFCUtil.h
${SOURCE_PATH}/Importer/IFC/IFCUtil.cpp
${SOURCE_PATH}/Importer/IFC/IFCGeometry.cpp
${SOURCE_PATH}/Importer/IFC/IFCMaterial.cpp
${SOURCE_PATH}/Importer/IFC/IFCProfile.cpp
${SOURCE_PATH}/Importer/IFC/IFCCurve.cpp
${SOURCE_PATH}/Importer/IFC/IFCBoolean.cpp
${SOURCE_PATH}/Importer/IFC/IFCOpenings.cpp
${SOURCE_PATH}/Importer/IFC/STEPFileReader.h
${SOURCE_PATH}/Importer/IFC/STEPFileReader.cpp
${SOURCE_PATH}/Importer/IFC/STEPFileEncoding.cpp
${SOURCE_PATH}/Importer/IFC/STEPFileEncoding.h
)
if (ASSIMP_BUILD_IFC_IMPORTER)
  if (MSVC)
    set_source_files_properties(${SOURCE_PATH}/IFCReaderGen1.cpp ${SOURCE_PATH}/IFCReaderGen2.cpp PROPERTIES COMPILE_FLAGS "/bigobj")
  elseif(CMAKE_COMPILER_IS_MINGW)
    set_source_files_properties(${SOURCE_PATH}/IFCReaderGen1.cpp ${SOURCE_PATH}/IFCReaderGen2.cpp PROPERTIES COMPILE_FLAGS "-O2 -Wa,-mbig-obj")
  endif()
endif (ASSIMP_BUILD_IFC_IMPORTER)

ADD_ASSIMP_IMPORTER( XGL
${SOURCE_PATH}/XGLLoader.cpp
${SOURCE_PATH}/XGLLoader.h
)

ADD_ASSIMP_IMPORTER( FBX
${SOURCE_PATH}/FBXImporter.cpp
${SOURCE_PATH}/FBXCompileConfig.h
${SOURCE_PATH}/FBXImporter.h
  ${SOURCE_PATH}/FBXParser.cpp
  ${SOURCE_PATH}/FBXParser.h
  ${SOURCE_PATH}/FBXTokenizer.cpp
  ${SOURCE_PATH}/FBXTokenizer.h
  ${SOURCE_PATH}/FBXImportSettings.h
  ${SOURCE_PATH}/FBXConverter.h
  ${SOURCE_PATH}/FBXConverter.cpp
  ${SOURCE_PATH}/FBXUtil.h
  ${SOURCE_PATH}/FBXUtil.cpp
  ${SOURCE_PATH}/FBXDocument.h
  ${SOURCE_PATH}/FBXDocument.cpp
  ${SOURCE_PATH}/FBXProperties.h
  ${SOURCE_PATH}/FBXProperties.cpp
  ${SOURCE_PATH}/FBXMeshGeometry.h
  ${SOURCE_PATH}/FBXMeshGeometry.cpp
  ${SOURCE_PATH}/FBXMaterial.cpp
  ${SOURCE_PATH}/FBXModel.cpp
  ${SOURCE_PATH}/FBXAnimation.cpp
  ${SOURCE_PATH}/FBXNodeAttribute.cpp
  ${SOURCE_PATH}/FBXDeformer.cpp
  ${SOURCE_PATH}/FBXBinaryTokenizer.cpp
  ${SOURCE_PATH}/FBXDocumentUtil.cpp
  ${SOURCE_PATH}/FBXExporter.h
  ${SOURCE_PATH}/FBXExporter.cpp
  ${SOURCE_PATH}/FBXExportNode.h
  ${SOURCE_PATH}/FBXExportNode.cpp
  ${SOURCE_PATH}/FBXExportProperty.h
  ${SOURCE_PATH}/FBXExportProperty.cpp
  ${SOURCE_PATH}/FBXCommon.h
)


SET( PostProcessing_SRCS
${SOURCE_PATH}/CalcTangentsProcess.cpp
${SOURCE_PATH}/CalcTangentsProcess.h
${SOURCE_PATH}/ComputeUVMappingProcess.cpp
${SOURCE_PATH}/ComputeUVMappingProcess.h
${SOURCE_PATH}/ConvertToLHProcess.cpp
${SOURCE_PATH}/ConvertToLHProcess.h
${SOURCE_PATH}/EmbedTexturesProcess.cpp
${SOURCE_PATH}/EmbedTexturesProcess.h
${SOURCE_PATH}/FindDegenerates.cpp
${SOURCE_PATH}/FindDegenerates.h
${SOURCE_PATH}/FindInstancesProcess.cpp
${SOURCE_PATH}/FindInstancesProcess.h
${SOURCE_PATH}/FindInvalidDataProcess.cpp
${SOURCE_PATH}/FindInvalidDataProcess.h
${SOURCE_PATH}/FixNormalsStep.cpp
${SOURCE_PATH}/FixNormalsStep.h
${SOURCE_PATH}/GenFaceNormalsProcess.cpp
${SOURCE_PATH}/GenFaceNormalsProcess.h
${SOURCE_PATH}/GenVertexNormalsProcess.cpp
${SOURCE_PATH}/GenVertexNormalsProcess.h
${SOURCE_PATH}/PretransformVertices.cpp
${SOURCE_PATH}/PretransformVertices.h
${SOURCE_PATH}/ImproveCacheLocality.cpp
${SOURCE_PATH}/ImproveCacheLocality.h
${SOURCE_PATH}/JoinVerticesProcess.cpp
${SOURCE_PATH}/JoinVerticesProcess.h
${SOURCE_PATH}/LimitBoneWeightsProcess.cpp
${SOURCE_PATH}/LimitBoneWeightsProcess.h
${SOURCE_PATH}/RemoveRedundantMaterials.cpp
${SOURCE_PATH}/RemoveRedundantMaterials.h
${SOURCE_PATH}/RemoveVCProcess.cpp
${SOURCE_PATH}/RemoveVCProcess.h
${SOURCE_PATH}/SortByPTypeProcess.cpp
${SOURCE_PATH}/SortByPTypeProcess.h
${SOURCE_PATH}/SplitLargeMeshes.cpp
${SOURCE_PATH}/SplitLargeMeshes.h
${SOURCE_PATH}/TextureTransform.cpp
${SOURCE_PATH}/TextureTransform.h
${SOURCE_PATH}/TriangulateProcess.cpp
${SOURCE_PATH}/TriangulateProcess.h
${SOURCE_PATH}/ValidateDataStructure.cpp
${SOURCE_PATH}/ValidateDataStructure.h
${SOURCE_PATH}/OptimizeGraph.cpp
${SOURCE_PATH}/OptimizeGraph.h
${SOURCE_PATH}/OptimizeMeshes.cpp
${SOURCE_PATH}/OptimizeMeshes.h
${SOURCE_PATH}/DeboneProcess.cpp
${SOURCE_PATH}/DeboneProcess.h
${SOURCE_PATH}/ProcessHelper.h
${SOURCE_PATH}/ProcessHelper.cpp
${SOURCE_PATH}/PolyTools.h
${SOURCE_PATH}/MakeVerboseFormat.cpp
${SOURCE_PATH}/MakeVerboseFormat.h
)
SOURCE_GROUP( PostProcessing FILES ${PostProcessing_SRCS})

SET( IrrXML_SRCS ${HEADER_PATH}/irrXMLWrapper.h )
SOURCE_GROUP( IrrXML FILES ${IrrXML_SRCS})

ADD_ASSIMP_IMPORTER( Q3D
${SOURCE_PATH}/Q3DLoader.cpp
${SOURCE_PATH}/Q3DLoader.h
)

ADD_ASSIMP_IMPORTER( Q3BSP
${SOURCE_PATH}/Q3BSPFileData.h
${SOURCE_PATH}/Q3BSPFileParser.h
${SOURCE_PATH}/Q3BSPFileParser.cpp
${SOURCE_PATH}/Q3BSPFileImporter.h
${SOURCE_PATH}/Q3BSPFileImporter.cpp
${SOURCE_PATH}/Q3BSPZipArchive.h
${SOURCE_PATH}/Q3BSPZipArchive.cpp
)

ADD_ASSIMP_IMPORTER( RAW
${SOURCE_PATH}/RawLoader.cpp
${SOURCE_PATH}/RawLoader.h
)

ADD_ASSIMP_IMPORTER( SIB
${SOURCE_PATH}/SIBImporter.cpp
${SOURCE_PATH}/SIBImporter.h
)

ADD_ASSIMP_IMPORTER( SMD
${SOURCE_PATH}/SMDLoader.cpp
${SOURCE_PATH}/SMDLoader.h
)

ADD_ASSIMP_IMPORTER( STL
${SOURCE_PATH}/STLLoader.cpp
${SOURCE_PATH}/STLLoader.h
${SOURCE_PATH}/STLExporter.h
${SOURCE_PATH}/STLExporter.cpp
)

ADD_ASSIMP_IMPORTER( TERRAGEN
${SOURCE_PATH}/TerragenLoader.cpp
${SOURCE_PATH}/TerragenLoader.h
)

ADD_ASSIMP_IMPORTER( 3D
${SOURCE_PATH}/UnrealLoader.cpp
${SOURCE_PATH}/UnrealLoader.h
)

ADD_ASSIMP_IMPORTER( X
${SOURCE_PATH}/XFileHelper.h
${SOURCE_PATH}/XFileImporter.cpp
${SOURCE_PATH}/XFileImporter.h
${SOURCE_PATH}/XFileParser.cpp
${SOURCE_PATH}/XFileParser.h
${SOURCE_PATH}/XFileExporter.h
${SOURCE_PATH}/XFileExporter.cpp
)

ADD_ASSIMP_IMPORTER( X3D
${SOURCE_PATH}/X3DExporter.cpp
${SOURCE_PATH}/X3DExporter.hpp
${SOURCE_PATH}/X3DImporter.cpp
${SOURCE_PATH}/X3DImporter.hpp
${SOURCE_PATH}/X3DImporter_Geometry2D.cpp
${SOURCE_PATH}/X3DImporter_Geometry3D.cpp
${SOURCE_PATH}/X3DImporter_Group.cpp
${SOURCE_PATH}/X3DImporter_Light.cpp
  ${SOURCE_PATH}/X3DImporter_Macro.hpp
  ${SOURCE_PATH}/X3DImporter_Metadata.cpp
  ${SOURCE_PATH}/X3DImporter_Networking.cpp
  ${SOURCE_PATH}/X3DImporter_Node.hpp
  ${SOURCE_PATH}/X3DImporter_Postprocess.cpp
  ${SOURCE_PATH}/X3DImporter_Rendering.cpp
  ${SOURCE_PATH}/X3DImporter_Shape.cpp
  ${SOURCE_PATH}/X3DImporter_Texturing.cpp
  ${SOURCE_PATH}/FIReader.hpp
  ${SOURCE_PATH}/FIReader.cpp
  ${SOURCE_PATH}/X3DVocabulary.cpp
)

ADD_ASSIMP_IMPORTER( GLTF
${SOURCE_PATH}/glTFAsset.h
${SOURCE_PATH}/glTFAsset.inl
${SOURCE_PATH}/glTFAssetWriter.h
${SOURCE_PATH}/glTFAssetWriter.inl
${SOURCE_PATH}/glTFImporter.cpp
${SOURCE_PATH}/glTFImporter.h
${SOURCE_PATH}/glTFExporter.h
${SOURCE_PATH}/glTFExporter.cpp
${SOURCE_PATH}/glTF2Asset.h
${SOURCE_PATH}/glTF2Asset.inl
  ${SOURCE_PATH}/glTF2AssetWriter.h
  ${SOURCE_PATH}/glTF2AssetWriter.inl
  ${SOURCE_PATH}/glTF2Importer.cpp
  ${SOURCE_PATH}/glTF2Importer.h
  ${SOURCE_PATH}/glTF2Exporter.h
  ${SOURCE_PATH}/glTF2Exporter.cpp
)

ADD_ASSIMP_IMPORTER( 3MF
${SOURCE_PATH}/D3MFImporter.h
    ${SOURCE_PATH}/D3MFImporter.cpp
    ${SOURCE_PATH}/D3MFExporter.h
    ${SOURCE_PATH}/D3MFExporter.cpp
    ${SOURCE_PATH}/D3MFOpcPackage.h
    ${SOURCE_PATH}/D3MFOpcPackage.cpp
    ${SOURCE_PATH}/3MFXmlTags.h
)

ADD_ASSIMP_IMPORTER( MMD
${SOURCE_PATH}/MMDCpp14.h
  ${SOURCE_PATH}/MMDImporter.cpp
  ${SOURCE_PATH}/MMDImporter.h
  ${SOURCE_PATH}/MMDPmdParser.h
  ${SOURCE_PATH}/MMDPmxParser.h
  ${SOURCE_PATH}/MMDPmxParser.cpp
  ${SOURCE_PATH}/MMDVmdParser.h
)

SET( Step_SRCS
${SOURCE_PATH}/STEPFile.h
  ${SOURCE_PATH}/StepExporter.h
  ${SOURCE_PATH}/StepExporter.cpp
)
SOURCE_GROUP( Step FILES ${Step_SRCS})


SET( Exporter_SRCS
${SOURCE_PATH}/Exporter.cpp
${SOURCE_PATH}/AssimpCExport.cpp
  ${HEADER_PATH}/BlobIOSystem.h
)
SOURCE_GROUP( Exporter FILES ${Exporter_SRCS})

SET( Extra_SRCS
${SOURCE_PATH}/MD4FileData.h
)
SOURCE_GROUP( Extra FILES ${Extra_SRCS})


SET( Clipper_SRCS
${SOURCE_PATH}/../contrib/clipper/clipper.hpp
${SOURCE_PATH}/../contrib/clipper/clipper.cpp
)
SOURCE_GROUP( Clipper FILES ${Clipper_SRCS})

SET( Poly2Tri_SRCS
${SOURCE_PATH}/../contrib/poly2tri/poly2tri/common/shapes.cc
${SOURCE_PATH}/../contrib/poly2tri/poly2tri/common/shapes.h
${SOURCE_PATH}/../contrib/poly2tri/poly2tri/common/utils.h
${SOURCE_PATH}/../contrib/poly2tri/poly2tri/sweep/advancing_front.h
${SOURCE_PATH}/../contrib/poly2tri/poly2tri/sweep/advancing_front.cc
${SOURCE_PATH}/../contrib/poly2tri/poly2tri/sweep/cdt.cc
${SOURCE_PATH}/../contrib/poly2tri/poly2tri/sweep/cdt.h
${SOURCE_PATH}/../contrib/poly2tri/poly2tri/sweep/sweep.cc
${SOURCE_PATH}/../contrib/poly2tri/poly2tri/sweep/sweep.h
${SOURCE_PATH}/../contrib/poly2tri/poly2tri/sweep/sweep_context.cc
${SOURCE_PATH}/../contrib/poly2tri/poly2tri/sweep/sweep_context.h
)
SOURCE_GROUP( Poly2Tri FILES ${Poly2Tri_SRCS})

SET( unzip_SRCS
${SOURCE_PATH}/../contrib/unzip/crypt.h
${SOURCE_PATH}/../contrib/unzip/ioapi.c
${SOURCE_PATH}/../contrib/unzip/ioapi.h
${SOURCE_PATH}/../contrib/unzip/unzip.c
${SOURCE_PATH}/../contrib/unzip/unzip.h
)
SOURCE_GROUP( unzip FILES ${unzip_SRCS})

SET( ziplib_SRCS
${SOURCE_PATH}/../contrib/zip/src/miniz.h
${SOURCE_PATH}/../contrib/zip/src/zip.c
${SOURCE_PATH}/../contrib/zip/src/zip.h
)

SOURCE_GROUP( ziplib FILES ${ziplib_SRCS} )

SET ( openddl_parser_SRCS
${SOURCE_PATH}/../contrib/openddlparser/code/OpenDDLParser.cpp
${SOURCE_PATH}/../contrib/openddlparser/code/DDLNode.cpp
${SOURCE_PATH}/../contrib/openddlparser/code/OpenDDLCommon.cpp
${SOURCE_PATH}/../contrib/openddlparser/code/OpenDDLExport.cpp
${SOURCE_PATH}/../contrib/openddlparser/code/Value.cpp
${SOURCE_PATH}/../contrib/openddlparser/code/OpenDDLStream.cpp
${SOURCE_PATH}/../contrib/openddlparser/include/openddlparser/OpenDDLParser.h
${SOURCE_PATH}/../contrib/openddlparser/include/openddlparser/OpenDDLParserUtils.h
${SOURCE_PATH}/../contrib/openddlparser/include/openddlparser/OpenDDLCommon.h
${SOURCE_PATH}/../contrib/openddlparser/include/openddlparser/OpenDDLExport.h
${SOURCE_PATH}/../contrib/openddlparser/include/openddlparser/OpenDDLStream.h
${SOURCE_PATH}/../contrib/openddlparser/include/openddlparser/DDLNode.h
${SOURCE_PATH}/../contrib/openddlparser/include/openddlparser/Value.h
)
SOURCE_GROUP( openddl_parser FILES ${openddl_parser_SRCS})

SET ( open3dgc_SRCS
${SOURCE_PATH}/../contrib/Open3DGC/o3dgcAdjacencyInfo.h
${SOURCE_PATH}/../contrib/Open3DGC/o3dgcArithmeticCodec.cpp
${SOURCE_PATH}/../contrib/Open3DGC/o3dgcArithmeticCodec.h
${SOURCE_PATH}/../contrib/Open3DGC/o3dgcBinaryStream.h
${SOURCE_PATH}/../contrib/Open3DGC/o3dgcCommon.h
${SOURCE_PATH}/../contrib/Open3DGC/o3dgcDVEncodeParams.h
${SOURCE_PATH}/../contrib/Open3DGC/o3dgcDynamicVectorDecoder.cpp
${SOURCE_PATH}/../contrib/Open3DGC/o3dgcDynamicVectorDecoder.h
${SOURCE_PATH}/../contrib/Open3DGC/o3dgcDynamicVectorEncoder.cpp
${SOURCE_PATH}/../contrib/Open3DGC/o3dgcDynamicVectorEncoder.h
${SOURCE_PATH}/../contrib/Open3DGC/o3dgcDynamicVector.h
${SOURCE_PATH}/../contrib/Open3DGC/o3dgcFIFO.h
${SOURCE_PATH}/../contrib/Open3DGC/o3dgcIndexedFaceSet.h
${SOURCE_PATH}/../contrib/Open3DGC/o3dgcIndexedFaceSet.inl
${SOURCE_PATH}/../contrib/Open3DGC/o3dgcSC3DMCDecoder.h
${SOURCE_PATH}/../contrib/Open3DGC/o3dgcSC3DMCDecoder.inl
${SOURCE_PATH}/../contrib/Open3DGC/o3dgcSC3DMCEncodeParams.h
${SOURCE_PATH}/../contrib/Open3DGC/o3dgcSC3DMCEncoder.h
${SOURCE_PATH}/../contrib/Open3DGC/o3dgcSC3DMCEncoder.inl
${SOURCE_PATH}/../contrib/Open3DGC/o3dgcTimer.h
${SOURCE_PATH}/../contrib/Open3DGC/o3dgcTools.cpp
${SOURCE_PATH}/../contrib/Open3DGC/o3dgcTriangleFans.cpp
${SOURCE_PATH}/../contrib/Open3DGC/o3dgcTriangleFans.h
${SOURCE_PATH}/../contrib/Open3DGC/o3dgcTriangleListDecoder.h
${SOURCE_PATH}/../contrib/Open3DGC/o3dgcTriangleListDecoder.inl
${SOURCE_PATH}/../contrib/Open3DGC/o3dgcTriangleListEncoder.h
${SOURCE_PATH}/../contrib/Open3DGC/o3dgcTriangleListEncoder.inl
${SOURCE_PATH}/../contrib/Open3DGC/o3dgcVector.h
${SOURCE_PATH}/../contrib/Open3DGC/o3dgcVector.inl
)
SOURCE_GROUP( open3dgc FILES ${open3dgc_SRCS})

# Check dependencies for glTF importer with Open3DGC-compression.
# RT-extensions is used in "contrib/Open3DGC/o3dgcTimer.h" for collecting statistics. Pointed file
# has implementation for different platforms: WIN32, __MACH__ and other ("else" block).
FIND_PACKAGE(RT QUIET)
IF (RT_FOUND OR MSVC)
  SET( ASSIMP_IMPORTER_GLTF_USE_OPEN3DGC 1 )
  ADD_DEFINITIONS( -DASSIMP_IMPORTER_GLTF_USE_OPEN3DGC=1 )
ELSE ()
  SET (open3dgc_SRCS "")
  MESSAGE (INFO " RT-extension not found. glTF import/export will be built without Open3DGC-compression.")
  #!TODO: off course is better to remove statistics timers from o3dgc codec. Or propose to choose what to use.
ENDIF ()

INCLUDE_DIRECTORIES( "${SOURCE_PATH}/../contrib/rapidjson/include" )
INCLUDE_DIRECTORIES( "${SOURCE_PATH}/../contrib" )


# VC2010 fixes
if(MSVC10)
  option( VC10_STDINT_FIX "Fix for VC10 Compiler regarding pstdint.h redefinition errors" OFF )
  if( VC10_STDINT_FIX )
    ADD_DEFINITIONS( -D_STDINT )
  endif( VC10_STDINT_FIX )
endif(MSVC10)

ADD_DEFINITIONS( -DASSIMP_BUILD_DLL_EXPORT )

if ( MSVC )
  ADD_DEFINITIONS( -D_SCL_SECURE_NO_WARNINGS )
  ADD_DEFINITIONS( -D_CRT_SECURE_NO_WARNINGS )
endif ( MSVC )

if (UNZIP_FOUND)
  SET (unzip_compile_SRCS "")
else (UNZIP_FOUND)
  SET (unzip_compile_SRCS ${unzip_SRCS})
  INCLUDE_DIRECTORIES( "${SOURCE_PATH}/../contrib/unzip/" )
endif (UNZIP_FOUND)

MESSAGE(STATUS "Enabled formats:${ASSIMP_IMPORTERS_ENABLED}")
MESSAGE(STATUS "Disabled formats:${ASSIMP_IMPORTERS_DISABLED}")

SET( assimp_src
  # Assimp Files
  ${Core_SRCS}
  ${Common_SRCS}
  ${Logging_SRCS}
  ${Exporter_SRCS}
  ${PostProcessing_SRCS}
  ${MaterialSystem_SRCS}
  ${Step_SRCS}

  # Model Support
  ${ASSIMP_LOADER_SRCS}

  # Third-party libraries
  ${IrrXML_SRCS}
  ${unzip_compile_SRCS}
  ${Poly2Tri_SRCS}
  ${Clipper_SRCS}
  ${openddl_parser_SRCS}
  ${open3dgc_SRCS}
  ${ziplib_SRCS}
  # Necessary to show the headers in the project when using the VC++ generator:

  ${PUBLIC_HEADERS}
  ${COMPILER_HEADERS}

)
ADD_DEFINITIONS( -DOPENDDLPARSER_BUILD )

INCLUDE_DIRECTORIES(
    ${IRRXML_INCLUDE_DIR}
    ${SOURCE_PATH}/../contrib/openddlparser/include
)

IF (ASSIMP_BUILD_NONFREE_C4D_IMPORTER)
  SET( assimp_src ${assimp_src} ${C4D_SRCS})
  INCLUDE_DIRECTORIES(${C4D_INCLUDES})
ENDIF (ASSIMP_BUILD_NONFREE_C4D_IMPORTER)

SET(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
ADD_LIBRARY( assimp ${assimp_src} )
TARGET_LINK_LIBRARIES(assimp ${ZLIB_LIBRARIES} ${OPENDDL_PARSER_LIBRARIES} ${IRRXML_LIBRARY} )

if( MSVC )
  # in order to prevent DLL hell, each of the DLLs have to be suffixed with the major version and msvc prefix
  if( MSVC70 OR MSVC71 )
    set(MSVC_PREFIX "vc70")
  elseif( MSVC80 )
    set(MSVC_PREFIX "vc80")
  elseif( MSVC90 )
    set(MSVC_PREFIX "vc90")
  elseif( MSVC10 )
    set(MSVC_PREFIX "vc100")
  elseif( MSVC11 )
    set(MSVC_PREFIX "vc110")
  elseif( MSVC12 )
    set(MSVC_PREFIX "vc120")
  elseif( MSVC14 )
    set(MSVC_PREFIX "vc140")
  else()
    set(MSVC_PREFIX "vc150")
  endif()
  set(LIBRARY_SUFFIX "${ASSIMP_LIBRARY_SUFFIX}-${MSVC_PREFIX}-mt" CACHE STRING "the suffix for the assimp windows library")
endif()

SET_TARGET_PROPERTIES( assimp PROPERTIES
  VERSION ${ASSIMP_VERSION}
  SOVERSION ${ASSIMP_SOVERSION} # use full version
  OUTPUT_NAME assimp${LIBRARY_SUFFIX}
)

# Build against external unzip, or add ../contrib/unzip so
# assimp can #include "unzip.h"
if (UNZIP_FOUND)
  INCLUDE_DIRECTORIES(${UNZIP_INCLUDE_DIRS})
  TARGET_LINK_LIBRARIES(assimp ${UNZIP_LIBRARIES})
else (UNZIP_FOUND)
  INCLUDE_DIRECTORIES("${SOURCE_PATH}/../")
endif (UNZIP_FOUND)


# Add RT-extension library for glTF importer with Open3DGC-compression.
IF (RT_FOUND AND ASSIMP_IMPORTER_GLTF_USE_OPEN3DGC)
  TARGET_LINK_LIBRARIES(assimp ${RT_LIBRARY})
ENDIF (RT_FOUND AND ASSIMP_IMPORTER_GLTF_USE_OPEN3DGC)

INSTALL( TARGETS assimp
  LIBRARY DESTINATION ${ASSIMP_LIB_INSTALL_DIR}
  ARCHIVE DESTINATION ${ASSIMP_LIB_INSTALL_DIR}
  RUNTIME DESTINATION ${ASSIMP_BIN_INSTALL_DIR}
  FRAMEWORK DESTINATION ${ASSIMP_LIB_INSTALL_DIR}
  COMPONENT ${LIBASSIMP_COMPONENT})


if (ASSIMP_COVERALLS)
include(Coveralls)

set(COVERAGE_SRCS ${assimp_src} ${TEST_SRCS} )

# Create the coveralls target.
coveralls_setup(
    "${COVERAGE_SRCS}" # The source files.
    ON                 # If we should upload.
    "${PROJECT_SOURCE_DIR}/cmake-modules/") # (Optional) Alternate project cmake module path.
ENDIF()



