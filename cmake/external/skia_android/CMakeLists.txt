
# skia frome Android
project(SKIA_ANDROID)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

if(NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH}/skia_android)
    GET_ANDROID_MODULE(skia)
    exec_program("mv skia skia_android" ${M3E_SOURCE_DIR}/${EXT_PATH})
    exec_program("git apply ${M3E_SOURCE_DIR}/src/${EXT_PATH}/skia_android/skia.patch" ${M3E_SOURCE_DIR}/${EXT_PATH}/skia_android)
endif()

include(${M3E_SOURCE_DIR}/cmake/external/png/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/jpeg-turbo/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/gif/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/dng_sdk/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/webp/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/piex/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/zlib/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/expat/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/EGL/include.cmake)

set(SKIA_DEPLIB
${PNG_LIBRARIES}
${JPEG_LIBRARIES}
${GIF_LIBRARIES}
dng_sdk
${WEBP_DEC}
${WEBP_ENC}
piex
zlib
expat
${OPENGL_DEPLIB}
)

add_definitions(-D_FORTIFY_SOURCE=1)
add_definitions(-DSKIA_IMPLEMENTATION=1)
add_definitions(-D__BIG_ENDIAN=4321)
add_definitions(-DATRACE_TAG=ATRACE_TAG_VIEW)

add_definitions(-D__LITTLE_ENDIAN=1234)

if(MSVC)
    add_definitions(-DSKIA_DLL)
    add_definitions(-D__BYTE_ORDER=1234)
    add_definitions(-D__STDC_LIMIT_MACROS=1)

    list(APPEND SKIA_DEPLIB FontSub)
elseif(APPLE)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -stdlib=libc++")
    add_definitions(-D__BYTE_ORDER=1234)    
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/skia_android/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/skia_android/src )

###############################################
# public include
###############################################

macro(SKIA_ADD_HEADER name)
    include_directories(AFTER ${HEADER_PATH}/${name})
    file(GLOB ${name}_HEADER ${HEADER_PATH}/${name}/*.h)
    source_group(public\\${name} FILES ${${name}_HEADER})
    list(APPEND SKIA_HEADER_FILES ${${name}_HEADER})
endmacro()

SKIA_ADD_HEADER(android)
SKIA_ADD_HEADER(c)
SKIA_ADD_HEADER(codec)
SKIA_ADD_HEADER(config)
SKIA_ADD_HEADER(core)
SKIA_ADD_HEADER(effects)
SKIA_ADD_HEADER(encode)
SKIA_ADD_HEADER(gpu)

include_directories(AFTER ${HEADER_PATH}/gpu/gl)
file(GLOB GPU_GL_HEADER ${HEADER_PATH}/gpu/gl/*.h)
source_group(public\\gpu\\gl FILES ${GPU_GL_HEADER})
list(APPEND SKIA_HEADER_FILES ${GPU_GL_HEADER})

SKIA_ADD_HEADER(pathops)
SKIA_ADD_HEADER(ports)
SKIA_ADD_HEADER(private)
SKIA_ADD_HEADER(svg)

include_directories(AFTER ${HEADER_PATH}/utils)
file(GLOB UTILS_HEADER ${HEADER_PATH}/utils/*.h)
if (MSVC)
    include_directories(AFTER ${HEADER_PATH}/utils/win)
    file(GLOB UTILS_WIN_HEADER ${HEADER_PATH}/utils/win/*.h)
    list(APPEND UTILS_HEADER ${UTILS_WIN_HEADER})
elseif(APPLE)
    include_directories(AFTER ${HEADER_PATH}/utils/mac)
    file(GLOB UTILS_MAC_HEADER ${HEADER_PATH}/utils/mac/*.h)
    list(APPEND UTILS_HEADER ${UTILS_MAC_HEADER})
endif() 
source_group(public\\utils FILES ${UTILS_HEADER})
list(APPEND SKIA_HEADER_FILES ${UTILS_HEADER})

SKIA_ADD_HEADER(views)


###############################################
# source code
###############################################

macro(SKIA_ADD_SOURCE name)
    file(GLOB ${name}_SOURCE_H ${SOURCE_PATH}/${name}/*.h)
    list(APPEND ${name}_SOURCE ${${name}_SOURCE_H})
    source_group(${name} FILES ${${name}_SOURCE})
    include_directories(AFTER ${SOURCE_PATH}/${name})
    list(APPEND SKIA_SOURCE_FILES ${${name}_SOURCE})
endmacro()


###############################################
# android
###############################################
list(APPEND android_SOURCE
${SOURCE_PATH}/android/SkBitmapRegionCodec.cpp
${SOURCE_PATH}/android/SkBitmapRegionDecoder.cpp
)
SKIA_ADD_SOURCE(android)

###############################################
# c
###############################################
list(APPEND c_SOURCE
${SOURCE_PATH}/c/sk_effects.cpp
${SOURCE_PATH}/c/sk_paint.cpp
${SOURCE_PATH}/c/sk_surface.cpp
)
SKIA_ADD_SOURCE(c)

###############################################
# codec 
###############################################
list(APPEND codec_SOURCE
${SOURCE_PATH}/codec/SkAndroidCodec.cpp 
${SOURCE_PATH}/codec/SkBmpBaseCodec.cpp 
${SOURCE_PATH}/codec/SkBmpCodec.cpp 
${SOURCE_PATH}/codec/SkBmpMaskCodec.cpp 
${SOURCE_PATH}/codec/SkBmpRLECodec.cpp 
${SOURCE_PATH}/codec/SkBmpStandardCodec.cpp 
${SOURCE_PATH}/codec/SkCodec.cpp 
${SOURCE_PATH}/codec/SkCodecImageGenerator.cpp 
${SOURCE_PATH}/codec/SkGifCodec.cpp 
${SOURCE_PATH}/codec/SkHeifCodec.cpp 
${SOURCE_PATH}/codec/SkIcoCodec.cpp 
${SOURCE_PATH}/codec/SkJpegCodec.cpp 
${SOURCE_PATH}/codec/SkJpegDecoderMgr.cpp 
${SOURCE_PATH}/codec/SkJpegUtility.cpp 
${SOURCE_PATH}/codec/SkMaskSwizzler.cpp 
${SOURCE_PATH}/codec/SkMasks.cpp 
${SOURCE_PATH}/codec/SkPngCodec.cpp 
${SOURCE_PATH}/codec/SkRawAdapterCodec.cpp 
${SOURCE_PATH}/codec/SkRawCodec.cpp 
${SOURCE_PATH}/codec/SkSampledCodec.cpp 
${SOURCE_PATH}/codec/SkSampler.cpp 
${SOURCE_PATH}/codec/SkStreamBuffer.cpp 
${SOURCE_PATH}/codec/SkSwizzler.cpp 
${SOURCE_PATH}/codec/SkWbmpCodec.cpp 
${SOURCE_PATH}/codec/SkWebpAdapterCodec.cpp 
${SOURCE_PATH}/codec/SkWebpCodec.cpp 
)
SKIA_ADD_SOURCE(codec)

###############################################
# core
###############################################
list(APPEND core_SOURCE
${SOURCE_PATH}/core/SkAAClip.cpp 
${SOURCE_PATH}/core/SkATrace.cpp 
${SOURCE_PATH}/core/SkAlphaRuns.cpp 
${SOURCE_PATH}/core/SkAnalyticEdge.cpp 
${SOURCE_PATH}/core/SkAnnotation.cpp 
${SOURCE_PATH}/core/SkArenaAlloc.cpp 
${SOURCE_PATH}/core/SkAutoPixmapStorage.cpp 
${SOURCE_PATH}/core/SkBBHFactory.cpp 
${SOURCE_PATH}/core/SkBigPicture.cpp 
${SOURCE_PATH}/core/SkBitmap.cpp 
${SOURCE_PATH}/core/SkBitmapCache.cpp 
${SOURCE_PATH}/core/SkBitmapController.cpp 
${SOURCE_PATH}/core/SkBitmapDevice.cpp 
${SOURCE_PATH}/core/SkBitmapProcState.cpp 
${SOURCE_PATH}/core/SkBitmapProcState_matrixProcs.cpp 
${SOURCE_PATH}/core/SkBitmapProvider.cpp 
${SOURCE_PATH}/core/SkBitmapScaler.cpp 
${SOURCE_PATH}/core/SkBlendMode.cpp 
${SOURCE_PATH}/core/SkBlitMask_D32.cpp 
${SOURCE_PATH}/core/SkBlitRow_D32.cpp 
${SOURCE_PATH}/core/SkBlitter.cpp 
${SOURCE_PATH}/core/SkBlitter_A8.cpp 
${SOURCE_PATH}/core/SkBlitter_ARGB32.cpp 
${SOURCE_PATH}/core/SkBlitter_RGB565.cpp 
${SOURCE_PATH}/core/SkBlitter_Sprite.cpp 
${SOURCE_PATH}/core/SkBlurImageFilter.cpp 
${SOURCE_PATH}/core/SkBuffer.cpp 
${SOURCE_PATH}/core/SkCachedData.cpp 
${SOURCE_PATH}/core/SkCanvas.cpp 
${SOURCE_PATH}/core/SkClipStack.cpp 
${SOURCE_PATH}/core/SkClipStackDevice.cpp 
${SOURCE_PATH}/core/SkColor.cpp 
${SOURCE_PATH}/core/SkColorFilter.cpp 
${SOURCE_PATH}/core/SkColorLookUpTable.cpp 
${SOURCE_PATH}/core/SkColorMatrixFilterRowMajor255.cpp 
${SOURCE_PATH}/core/SkColorSpace.cpp 
${SOURCE_PATH}/core/SkColorSpaceXform.cpp 
${SOURCE_PATH}/core/SkColorSpaceXformCanvas.cpp 
${SOURCE_PATH}/core/SkColorSpaceXformImageGenerator.cpp 
${SOURCE_PATH}/core/SkColorSpaceXform_A2B.cpp 
${SOURCE_PATH}/core/SkColorSpaceXformer.cpp 
${SOURCE_PATH}/core/SkColorSpace_A2B.cpp 
${SOURCE_PATH}/core/SkColorSpace_ICC.cpp 
${SOURCE_PATH}/core/SkColorSpace_XYZ.cpp 
${SOURCE_PATH}/core/SkColorTable.cpp 
${SOURCE_PATH}/core/SkConvertPixels.cpp 
${SOURCE_PATH}/core/SkConvolver.cpp 
${SOURCE_PATH}/core/SkCpu.cpp 
${SOURCE_PATH}/core/SkCubicClipper.cpp 
${SOURCE_PATH}/core/SkData.cpp 
${SOURCE_PATH}/core/SkDataTable.cpp 
${SOURCE_PATH}/core/SkDebug.cpp 
${SOURCE_PATH}/core/SkDeque.cpp 
${SOURCE_PATH}/core/SkDevice.cpp 
${SOURCE_PATH}/core/SkDeviceLooper.cpp 
${SOURCE_PATH}/core/SkDeviceProfile.cpp 
${SOURCE_PATH}/core/SkDistanceFieldGen.cpp 
${SOURCE_PATH}/core/SkDither.cpp 
${SOURCE_PATH}/core/SkDocument.cpp 
${SOURCE_PATH}/core/SkDraw.cpp 
${SOURCE_PATH}/core/SkDrawLooper.cpp 
${SOURCE_PATH}/core/SkDraw_vertices.cpp 
${SOURCE_PATH}/core/SkDrawable.cpp 
${SOURCE_PATH}/core/SkEdge.cpp 
${SOURCE_PATH}/core/SkEdgeBuilder.cpp 
${SOURCE_PATH}/core/SkEdgeClipper.cpp 
${SOURCE_PATH}/core/SkExecutor.cpp 
${SOURCE_PATH}/core/SkFlattenable.cpp 
${SOURCE_PATH}/core/SkFlattenableSerialization.cpp 
${SOURCE_PATH}/core/SkFont.cpp 
${SOURCE_PATH}/core/SkFontDescriptor.cpp 
${SOURCE_PATH}/core/SkFontLCDConfig.cpp 
${SOURCE_PATH}/core/SkFontMgr.cpp 
${SOURCE_PATH}/core/SkFontStream.cpp 
${SOURCE_PATH}/core/SkFontStyle.cpp 
${SOURCE_PATH}/core/SkGeometry.cpp 
${SOURCE_PATH}/core/SkGlobalInitialization_core.cpp 
${SOURCE_PATH}/core/SkGlyphCache.cpp 
${SOURCE_PATH}/core/SkGpuBlurUtils.cpp 
${SOURCE_PATH}/core/SkGraphics.cpp 
${SOURCE_PATH}/core/SkHalf.cpp 
${SOURCE_PATH}/core/SkICC.cpp 
${SOURCE_PATH}/core/SkImageFilter.cpp 
${SOURCE_PATH}/core/SkImageFilterCache.cpp 
${SOURCE_PATH}/core/SkImageGenerator.cpp 
${SOURCE_PATH}/core/SkImageInfo.cpp 
${SOURCE_PATH}/core/SkLatticeIter.cpp 
${SOURCE_PATH}/core/SkLights.cpp 
${SOURCE_PATH}/core/SkLineClipper.cpp 
${SOURCE_PATH}/core/SkLinearBitmapPipeline.cpp 
${SOURCE_PATH}/core/SkLiteDL.cpp 
${SOURCE_PATH}/core/SkLiteRecorder.cpp 
${SOURCE_PATH}/core/SkLocalMatrixImageFilter.cpp 
${SOURCE_PATH}/core/SkMD5.cpp 
${SOURCE_PATH}/core/SkMallocPixelRef.cpp 
${SOURCE_PATH}/core/SkMask.cpp 
${SOURCE_PATH}/core/SkMaskBlurFilter.cpp 
${SOURCE_PATH}/core/SkMaskCache.cpp 
${SOURCE_PATH}/core/SkMaskFilter.cpp 
${SOURCE_PATH}/core/SkMaskGamma.cpp 
${SOURCE_PATH}/core/SkMath.cpp 
${SOURCE_PATH}/core/SkMatrix.cpp 
${SOURCE_PATH}/core/SkMatrix44.cpp 
${SOURCE_PATH}/core/SkMatrixImageFilter.cpp 
${SOURCE_PATH}/core/SkMetaData.cpp 
${SOURCE_PATH}/core/SkMiniRecorder.cpp 
${SOURCE_PATH}/core/SkMipMap.cpp 
${SOURCE_PATH}/core/SkModeColorFilter.cpp 
${SOURCE_PATH}/core/SkMultiPictureDraw.cpp 
${SOURCE_PATH}/core/SkNormalFlatSource.cpp 
${SOURCE_PATH}/core/SkNormalMapSource.cpp 
${SOURCE_PATH}/core/SkNormalSource.cpp 
${SOURCE_PATH}/core/SkOpts.cpp 
${SOURCE_PATH}/core/SkOverdrawCanvas.cpp 
${SOURCE_PATH}/core/SkPaint.cpp 
${SOURCE_PATH}/core/SkPaintPriv.cpp 
${SOURCE_PATH}/core/SkPath.cpp 
${SOURCE_PATH}/core/SkPathEffect.cpp 
${SOURCE_PATH}/core/SkPathMeasure.cpp 
${SOURCE_PATH}/core/SkPathRef.cpp 
${SOURCE_PATH}/core/SkPicture.cpp 
${SOURCE_PATH}/core/SkPictureAnalyzer.cpp 
${SOURCE_PATH}/core/SkPictureContentInfo.cpp 
${SOURCE_PATH}/core/SkPictureData.cpp 
${SOURCE_PATH}/core/SkPictureFlat.cpp 
${SOURCE_PATH}/core/SkPictureImageGenerator.cpp 
${SOURCE_PATH}/core/SkPicturePlayback.cpp 
${SOURCE_PATH}/core/SkPictureRecord.cpp 
${SOURCE_PATH}/core/SkPictureRecorder.cpp 
${SOURCE_PATH}/core/SkPixelRef.cpp 
${SOURCE_PATH}/core/SkPixmap.cpp 
${SOURCE_PATH}/core/SkPoint.cpp 
${SOURCE_PATH}/core/SkPoint3.cpp 
${SOURCE_PATH}/core/SkPtrRecorder.cpp 
${SOURCE_PATH}/core/SkQuadClipper.cpp 
${SOURCE_PATH}/core/SkRRect.cpp 
${SOURCE_PATH}/core/SkRTree.cpp 
${SOURCE_PATH}/core/SkRWBuffer.cpp 
${SOURCE_PATH}/core/SkRasterClip.cpp 
${SOURCE_PATH}/core/SkRasterPipeline.cpp 
${SOURCE_PATH}/core/SkRasterPipelineBlitter.cpp 
${SOURCE_PATH}/core/SkRasterizer.cpp 
${SOURCE_PATH}/core/SkReadBuffer.cpp 
${SOURCE_PATH}/core/SkRecord.cpp 
${SOURCE_PATH}/core/SkRecordDraw.cpp 
${SOURCE_PATH}/core/SkRecordOpts.cpp 
${SOURCE_PATH}/core/SkRecordedDrawable.cpp 
${SOURCE_PATH}/core/SkRecorder.cpp 
${SOURCE_PATH}/core/SkRecords.cpp 
${SOURCE_PATH}/core/SkRect.cpp 
${SOURCE_PATH}/core/SkRefDict.cpp 
${SOURCE_PATH}/core/SkRegion.cpp 
${SOURCE_PATH}/core/SkRegion_path.cpp 
${SOURCE_PATH}/core/SkResourceCache.cpp 
${SOURCE_PATH}/core/SkSRGB.cpp 
${SOURCE_PATH}/core/SkScalar.cpp 
${SOURCE_PATH}/core/SkScalerContext.cpp 
${SOURCE_PATH}/core/SkScan.cpp 
${SOURCE_PATH}/core/SkScan_AAAPath.cpp 
${SOURCE_PATH}/core/SkScan_AntiPath.cpp 
${SOURCE_PATH}/core/SkScan_Antihair.cpp 
${SOURCE_PATH}/core/SkScan_Hairline.cpp 
${SOURCE_PATH}/core/SkScan_Path.cpp 
${SOURCE_PATH}/core/SkSemaphore.cpp 
${SOURCE_PATH}/core/SkSharedMutex.cpp 
${SOURCE_PATH}/core/SkSpecialImage.cpp 
${SOURCE_PATH}/core/SkSpecialSurface.cpp 
${SOURCE_PATH}/core/SkSpinlock.cpp 
${SOURCE_PATH}/core/SkSpriteBlitter_ARGB32.cpp 
${SOURCE_PATH}/core/SkSpriteBlitter_RGB565.cpp 
${SOURCE_PATH}/core/SkStream.cpp 
${SOURCE_PATH}/core/SkString.cpp 
${SOURCE_PATH}/core/SkStringUtils.cpp 
${SOURCE_PATH}/core/SkStroke.cpp 
${SOURCE_PATH}/core/SkStrokeRec.cpp 
${SOURCE_PATH}/core/SkStrokerPriv.cpp 
${SOURCE_PATH}/core/SkSwizzle.cpp 
${SOURCE_PATH}/core/SkTLS.cpp 
${SOURCE_PATH}/core/SkTSearch.cpp 
${SOURCE_PATH}/core/SkTaskGroup.cpp 
${SOURCE_PATH}/core/SkTextBlob.cpp 
${SOURCE_PATH}/core/SkThreadID.cpp 
${SOURCE_PATH}/core/SkTime.cpp 
${SOURCE_PATH}/core/SkTypeface.cpp 
${SOURCE_PATH}/core/SkTypefaceCache.cpp 
${SOURCE_PATH}/core/SkUnPreMultiply.cpp 
${SOURCE_PATH}/core/SkUtils.cpp 
${SOURCE_PATH}/core/SkValidatingReadBuffer.cpp 
${SOURCE_PATH}/core/SkVertState.cpp 
${SOURCE_PATH}/core/SkVertices.cpp 
${SOURCE_PATH}/core/SkWriteBuffer.cpp 
${SOURCE_PATH}/core/SkWriter32.cpp 
${SOURCE_PATH}/core/SkXfermode.cpp 
${SOURCE_PATH}/core/SkXfermodeInterpretation.cpp 
${SOURCE_PATH}/core/SkYUVPlanesCache.cpp 
)
SKIA_ADD_SOURCE(core)

###############################################
# effects
###############################################
list(APPEND effects_SOURCE
${SOURCE_PATH}/effects/GrAlphaThresholdFragmentProcessor.cpp 
${SOURCE_PATH}/effects/GrCircleBlurFragmentProcessor.cpp 
${SOURCE_PATH}/effects/Sk1DPathEffect.cpp 
${SOURCE_PATH}/effects/Sk2DPathEffect.cpp 
${SOURCE_PATH}/effects/SkAlphaThresholdFilter.cpp 
${SOURCE_PATH}/effects/SkArcToPathEffect.cpp 
${SOURCE_PATH}/effects/SkArithmeticImageFilter.cpp 
${SOURCE_PATH}/effects/SkBlurMask.cpp 
${SOURCE_PATH}/effects/SkBlurMaskFilter.cpp 
${SOURCE_PATH}/effects/SkColorFilterImageFilter.cpp 
${SOURCE_PATH}/effects/SkColorMatrix.cpp 
${SOURCE_PATH}/effects/SkColorMatrixFilter.cpp 
${SOURCE_PATH}/effects/SkComposeImageFilter.cpp 
${SOURCE_PATH}/effects/SkCornerPathEffect.cpp 
${SOURCE_PATH}/effects/SkDashPathEffect.cpp 
${SOURCE_PATH}/effects/SkDiscretePathEffect.cpp 
${SOURCE_PATH}/effects/SkDisplacementMapEffect.cpp 
${SOURCE_PATH}/effects/SkDropShadowImageFilter.cpp 
${SOURCE_PATH}/effects/SkEmbossMask.cpp 
${SOURCE_PATH}/effects/SkEmbossMaskFilter.cpp 
${SOURCE_PATH}/effects/SkHighContrastFilter.cpp 
${SOURCE_PATH}/effects/SkImageSource.cpp 
${SOURCE_PATH}/effects/SkLayerDrawLooper.cpp 
${SOURCE_PATH}/effects/SkLayerRasterizer.cpp 
${SOURCE_PATH}/effects/SkLightingImageFilter.cpp 
${SOURCE_PATH}/effects/SkLumaColorFilter.cpp 
${SOURCE_PATH}/effects/SkMagnifierImageFilter.cpp 
${SOURCE_PATH}/effects/SkMatrixConvolutionImageFilter.cpp 
${SOURCE_PATH}/effects/SkMergeImageFilter.cpp 
${SOURCE_PATH}/effects/SkMorphologyImageFilter.cpp 
${SOURCE_PATH}/effects/SkOffsetImageFilter.cpp 
${SOURCE_PATH}/effects/SkOverdrawColorFilter.cpp 
${SOURCE_PATH}/effects/SkPackBits.cpp 
${SOURCE_PATH}/effects/SkPaintFlagsDrawFilter.cpp 
${SOURCE_PATH}/effects/SkPaintImageFilter.cpp 
${SOURCE_PATH}/effects/SkPictureImageFilter.cpp 
${SOURCE_PATH}/effects/SkRRectsGaussianEdgeMaskFilter.cpp 
${SOURCE_PATH}/effects/SkTableColorFilter.cpp 
${SOURCE_PATH}/effects/SkTableMaskFilter.cpp 
${SOURCE_PATH}/effects/SkTileImageFilter.cpp 
${SOURCE_PATH}/effects/SkXfermodeImageFilter.cpp 
)
SKIA_ADD_SOURCE(effects)

###############################################
# fonts
###############################################
list(APPEND fonts_SOURCE
${SOURCE_PATH}/fonts/SkRandomScalerContext.cpp 
${SOURCE_PATH}/fonts/SkTestScalerContext.cpp 
${SOURCE_PATH}/fonts/SkFontMgr_indirect.cpp 
${SOURCE_PATH}/fonts/SkRemotableFontMgr.cpp 
)
SKIA_ADD_SOURCE(fonts)

###############################################
# gpu 
###############################################
list(APPEND gpu_SOURCE 
${SOURCE_PATH}/gpu/GrAHardwareBufferImageGenerator.cpp 
${SOURCE_PATH}/gpu/GrAuditTrail.cpp 
${SOURCE_PATH}/gpu/GrBackendSurface.cpp 
${SOURCE_PATH}/gpu/GrBackendTextureImageGenerator.cpp 
${SOURCE_PATH}/gpu/GrBitmapTextureMaker.cpp 
${SOURCE_PATH}/gpu/GrBlend.cpp 
${SOURCE_PATH}/gpu/GrBlurUtils.cpp 
${SOURCE_PATH}/gpu/GrBuffer.cpp 
${SOURCE_PATH}/gpu/GrBufferAllocPool.cpp 
${SOURCE_PATH}/gpu/GrCaps.cpp 
${SOURCE_PATH}/gpu/GrClipStackClip.cpp 
${SOURCE_PATH}/gpu/GrColorSpaceXform.cpp 
${SOURCE_PATH}/gpu/GrContext.cpp 
${SOURCE_PATH}/gpu/GrDefaultGeoProcFactory.cpp 
${SOURCE_PATH}/gpu/GrDistanceFieldGenFromVector.cpp 
${SOURCE_PATH}/gpu/GrDrawOpAtlas.cpp 
${SOURCE_PATH}/gpu/GrDrawOpTest.cpp 
${SOURCE_PATH}/gpu/GrDrawingManager.cpp 
${SOURCE_PATH}/gpu/GrFixedClip.cpp 
${SOURCE_PATH}/gpu/GrFragmentProcessor.cpp 
${SOURCE_PATH}/gpu/GrGpu.cpp 
${SOURCE_PATH}/gpu/GrGpuCommandBuffer.cpp 
${SOURCE_PATH}/gpu/GrGpuFactory.cpp 
${SOURCE_PATH}/gpu/GrGpuResource.cpp 
${SOURCE_PATH}/gpu/GrGpuResourceRef.cpp 
${SOURCE_PATH}/gpu/GrImageTextureMaker.cpp 
${SOURCE_PATH}/gpu/GrMemoryPool.cpp 
${SOURCE_PATH}/gpu/GrOnFlushResourceProvider.cpp 
${SOURCE_PATH}/gpu/GrOpFlushState.cpp 
${SOURCE_PATH}/gpu/GrOpList.cpp 
${SOURCE_PATH}/gpu/GrPaint.cpp 
${SOURCE_PATH}/gpu/GrPath.cpp 
${SOURCE_PATH}/gpu/GrPathProcessor.cpp 
${SOURCE_PATH}/gpu/GrPathRange.cpp 
${SOURCE_PATH}/gpu/GrPathRenderer.cpp 
${SOURCE_PATH}/gpu/GrPathRendererChain.cpp 
${SOURCE_PATH}/gpu/GrPathRendering.cpp 
${SOURCE_PATH}/gpu/GrPathRenderingRenderTargetContext.cpp 
${SOURCE_PATH}/gpu/GrPathUtils.cpp 
${SOURCE_PATH}/gpu/GrPipeline.cpp 
${SOURCE_PATH}/gpu/GrPrimitiveProcessor.cpp 
${SOURCE_PATH}/gpu/GrProcessor.cpp 
${SOURCE_PATH}/gpu/GrProcessorAnalysis.cpp 
${SOURCE_PATH}/gpu/GrProcessorSet.cpp 
${SOURCE_PATH}/gpu/GrProcessorUnitTest.cpp 
${SOURCE_PATH}/gpu/GrProgramDesc.cpp 
${SOURCE_PATH}/gpu/GrRectanizer_pow2.cpp 
${SOURCE_PATH}/gpu/GrRectanizer_skyline.cpp 
${SOURCE_PATH}/gpu/GrReducedClip.cpp 
${SOURCE_PATH}/gpu/GrRenderTarget.cpp 
${SOURCE_PATH}/gpu/GrRenderTargetContext.cpp 
${SOURCE_PATH}/gpu/GrRenderTargetOpList.cpp 
${SOURCE_PATH}/gpu/GrRenderTargetProxy.cpp 
${SOURCE_PATH}/gpu/GrResourceAllocator.cpp 
${SOURCE_PATH}/gpu/GrResourceCache.cpp 
${SOURCE_PATH}/gpu/GrResourceProvider.cpp 
${SOURCE_PATH}/gpu/GrSKSLPrettyPrint.cpp 
${SOURCE_PATH}/gpu/GrSWMaskHelper.cpp 
${SOURCE_PATH}/gpu/GrShaderCaps.cpp 
${SOURCE_PATH}/gpu/GrShaderVar.cpp 
${SOURCE_PATH}/gpu/GrShape.cpp 
${SOURCE_PATH}/gpu/GrSoftwarePathRenderer.cpp 
${SOURCE_PATH}/gpu/GrStencilAttachment.cpp 
${SOURCE_PATH}/gpu/GrStencilSettings.cpp 
${SOURCE_PATH}/gpu/GrStyle.cpp 
${SOURCE_PATH}/gpu/GrSurface.cpp 
${SOURCE_PATH}/gpu/GrSurfaceContext.cpp 
${SOURCE_PATH}/gpu/GrSurfaceProxy.cpp 
${SOURCE_PATH}/gpu/GrTessellator.cpp 
${SOURCE_PATH}/gpu/GrTestUtils.cpp 
${SOURCE_PATH}/gpu/GrTexture.cpp 
${SOURCE_PATH}/gpu/GrTextureAdjuster.cpp 
${SOURCE_PATH}/gpu/GrTextureContext.cpp 
${SOURCE_PATH}/gpu/GrTextureMaker.cpp 
${SOURCE_PATH}/gpu/GrTextureOpList.cpp 
${SOURCE_PATH}/gpu/GrTextureProducer.cpp 
${SOURCE_PATH}/gpu/GrTextureProxy.cpp 
${SOURCE_PATH}/gpu/GrTextureRenderTargetProxy.cpp 
${SOURCE_PATH}/gpu/GrTraceMarker.cpp 
${SOURCE_PATH}/gpu/GrXferProcessor.cpp 
${SOURCE_PATH}/gpu/GrYUVProvider.cpp 
${SOURCE_PATH}/gpu/SkGpuDevice.cpp 
${SOURCE_PATH}/gpu/SkGpuDevice_drawTexture.cpp 
${SOURCE_PATH}/gpu/SkGr.cpp 
)
SKIA_ADD_SOURCE(gpu)

###############################################
# gpu ccpr
###############################################
file(GLOB GPU_CCPR_SOURCE ${SOURCE_PATH}/gpu/ccpr/*.h)
list(APPEND GPU_CCPR_SOURCE
${SOURCE_PATH}/gpu/ccpr/GrCCPRAtlas.cpp 
${SOURCE_PATH}/gpu/ccpr/GrCCPRCoverageOpsBuilder.cpp 
${SOURCE_PATH}/gpu/ccpr/GrCCPRCoverageProcessor.cpp 
${SOURCE_PATH}/gpu/ccpr/GrCCPRCubicProcessor.cpp 
${SOURCE_PATH}/gpu/ccpr/GrCCPRPathProcessor.cpp 
${SOURCE_PATH}/gpu/ccpr/GrCCPRQuadraticProcessor.cpp 
${SOURCE_PATH}/gpu/ccpr/GrCCPRTriangleProcessor.cpp 
${SOURCE_PATH}/gpu/ccpr/GrCoverageCountingPathRenderer.cpp 
)

source_group(gpu\\ccpr FILES ${GPU_CCPR_SOURCE})
include_directories(AFTER ${SOURCE_PATH}/gpu/ccpr)
list(APPEND SKIA_SOURCE_FILES ${GPU_CCPR_SOURCE})

###############################################
# gpu effects 
###############################################
file(GLOB GPU_EFFECT_SOURCE ${SOURCE_PATH}/gpu/effects/*.h)
list(APPEND GPU_EFFECT_SOURCE
${SOURCE_PATH}/gpu/effects/GrBezierEffect.cpp 
${SOURCE_PATH}/gpu/effects/GrBicubicEffect.cpp 
${SOURCE_PATH}/gpu/effects/GrBitmapTextGeoProc.cpp 
${SOURCE_PATH}/gpu/effects/GrBlurredEdgeFragmentProcessor.cpp 
${SOURCE_PATH}/gpu/effects/GrCircleEffect.cpp 
${SOURCE_PATH}/gpu/effects/GrConfigConversionEffect.cpp 
${SOURCE_PATH}/gpu/effects/GrConstColorProcessor.cpp 
${SOURCE_PATH}/gpu/effects/GrConvexPolyEffect.cpp 
${SOURCE_PATH}/gpu/effects/GrCoverageSetOpXP.cpp 
${SOURCE_PATH}/gpu/effects/GrCustomXfermode.cpp 
${SOURCE_PATH}/gpu/effects/GrDisableColorXP.cpp 
${SOURCE_PATH}/gpu/effects/GrDistanceFieldGeoProc.cpp 
${SOURCE_PATH}/gpu/effects/GrDitherEffect.cpp 
${SOURCE_PATH}/gpu/effects/GrEllipseEffect.cpp 
${SOURCE_PATH}/gpu/effects/GrGaussianConvolutionFragmentProcessor.cpp 
${SOURCE_PATH}/gpu/effects/GrMatrixConvolutionEffect.cpp 
${SOURCE_PATH}/gpu/effects/GrNonlinearColorSpaceXformEffect.cpp 
${SOURCE_PATH}/gpu/effects/GrOvalEffect.cpp 
${SOURCE_PATH}/gpu/effects/GrPorterDuffXferProcessor.cpp 
${SOURCE_PATH}/gpu/effects/GrRRectEffect.cpp 
${SOURCE_PATH}/gpu/effects/GrSRGBEffect.cpp 
${SOURCE_PATH}/gpu/effects/GrShadowGeoProc.cpp 
${SOURCE_PATH}/gpu/effects/GrSimpleTextureEffect.cpp 
${SOURCE_PATH}/gpu/effects/GrSingleTextureEffect.cpp 
${SOURCE_PATH}/gpu/effects/GrTextureDomain.cpp 
${SOURCE_PATH}/gpu/effects/GrTextureStripAtlas.cpp 
${SOURCE_PATH}/gpu/effects/GrXfermodeFragmentProcessor.cpp 
${SOURCE_PATH}/gpu/effects/GrYUVEffect.cpp 
)

source_group(gpu\\effects FILES ${GPU_EFFECT_SOURCE})
include_directories(AFTER ${SOURCE_PATH}/gpu/effects)
list(APPEND SKIA_SOURCE_FILES ${GPU_EFFECT_SOURCE})

###############################################
# gpu gl
###############################################
file(GLOB GPU_GL_SOURCE ${SOURCE_PATH}/gpu/gl/*.h)
list(APPEND GPU_GL_SOURCE
${SOURCE_PATH}/gpu/gl/GrGLAssembleInterface.cpp 
${SOURCE_PATH}/gpu/gl/GrGLBuffer.cpp 
${SOURCE_PATH}/gpu/gl/GrGLCaps.cpp 
${SOURCE_PATH}/gpu/gl/GrGLContext.cpp 
${SOURCE_PATH}/gpu/gl/GrGLCreateNullInterface.cpp 
${SOURCE_PATH}/gpu/gl/GrGLDefaultInterface_native.cpp 
${SOURCE_PATH}/gpu/gl/GrGLExtensions.cpp 
${SOURCE_PATH}/gpu/gl/GrGLGLSL.cpp 
${SOURCE_PATH}/gpu/gl/GrGLGpu.cpp 
${SOURCE_PATH}/gpu/gl/GrGLGpuProgramCache.cpp 
${SOURCE_PATH}/gpu/gl/GrGLInterface.cpp 
${SOURCE_PATH}/gpu/gl/GrGLPath.cpp 
${SOURCE_PATH}/gpu/gl/GrGLPathRange.cpp 
${SOURCE_PATH}/gpu/gl/GrGLPathRendering.cpp 
${SOURCE_PATH}/gpu/gl/GrGLProgram.cpp 
${SOURCE_PATH}/gpu/gl/GrGLProgramDataManager.cpp 
${SOURCE_PATH}/gpu/gl/GrGLRenderTarget.cpp 
${SOURCE_PATH}/gpu/gl/GrGLSemaphore.cpp 
${SOURCE_PATH}/gpu/gl/GrGLStencilAttachment.cpp 
${SOURCE_PATH}/gpu/gl/GrGLTestInterface.cpp 
${SOURCE_PATH}/gpu/gl/GrGLTexture.cpp 
${SOURCE_PATH}/gpu/gl/GrGLTextureRenderTarget.cpp 
${SOURCE_PATH}/gpu/gl/GrGLUniformHandler.cpp 
${SOURCE_PATH}/gpu/gl/GrGLUtil.cpp 
${SOURCE_PATH}/gpu/gl/GrGLVaryingHandler.cpp 
${SOURCE_PATH}/gpu/gl/GrGLVertexArray.cpp 
${SOURCE_PATH}/gpu/gl/android/GrGLCreateNativeInterface_android.cpp 
${SOURCE_PATH}/gpu/gl/builders/GrGLProgramBuilder.cpp 
${SOURCE_PATH}/gpu/gl/builders/GrGLShaderStringBuilder.cpp 
${SOURCE_PATH}/gpu/gl/egl/GrGLCreateNativeInterface_egl.cpp 
)

source_group(gpu\\gl FILES ${GPU_GL_SOURCE})
include_directories(AFTER ${SOURCE_PATH}/gpu/gl)
list(APPEND SKIA_SOURCE_FILES ${GPU_GL_SOURCE})

###############################################
# gpu glsl
###############################################
file(GLOB GPU_GLSL_SOURCE ${SOURCE_PATH}/gpu/glsl/*.h)
list(APPEND GPU_GLSL_SOURCE
${SOURCE_PATH}/gpu/glsl/GrGLSL.cpp 
${SOURCE_PATH}/gpu/glsl/GrGLSLBlend.cpp 
${SOURCE_PATH}/gpu/glsl/GrGLSLFragmentProcessor.cpp 
${SOURCE_PATH}/gpu/glsl/GrGLSLFragmentShaderBuilder.cpp 
${SOURCE_PATH}/gpu/glsl/GrGLSLGeometryProcessor.cpp 
${SOURCE_PATH}/gpu/glsl/GrGLSLGeometryShaderBuilder.cpp 
${SOURCE_PATH}/gpu/glsl/GrGLSLPrimitiveProcessor.cpp 
${SOURCE_PATH}/gpu/glsl/GrGLSLProgramBuilder.cpp 
${SOURCE_PATH}/gpu/glsl/GrGLSLProgramDataManager.cpp 
${SOURCE_PATH}/gpu/glsl/GrGLSLShaderBuilder.cpp 
${SOURCE_PATH}/gpu/glsl/GrGLSLUtil.cpp 
${SOURCE_PATH}/gpu/glsl/GrGLSLVarying.cpp 
${SOURCE_PATH}/gpu/glsl/GrGLSLVertexShaderBuilder.cpp 
${SOURCE_PATH}/gpu/glsl/GrGLSLXferProcessor.cpp 
)

source_group(gpu\\glsl FILES ${GPU_GLSL_SOURCE})
include_directories(AFTER ${SOURCE_PATH}/gpu/glsl)
list(APPEND SKIA_SOURCE_FILES ${GPU_GLSL_SOURCE})

###############################################
# gpu instanced
###############################################
file(GLOB GPU_INSTANCED_SOURCE ${SOURCE_PATH}/gpu/instanced/*.h)
list(APPEND GPU_INSTANCED_SOURCE
${SOURCE_PATH}/gpu/instanced/GLInstancedRendering.cpp
${SOURCE_PATH}/gpu/instanced/InstanceProcessor.cpp
${SOURCE_PATH}/gpu/instanced/InstancedOp.cpp
${SOURCE_PATH}/gpu/instanced/InstancedRendering.cpp
)

source_group(gpu\\instanced FILES ${GPU_INSTANCED_SOURCE})
include_directories(AFTER ${SOURCE_PATH}/gpu/instanced)
list(APPEND SKIA_SOURCE_FILES ${GPU_INSTANCED_SOURCE})

###############################################
# gpu mock
###############################################
file(GLOB GPU_MOCK_SOURCE ${SOURCE_PATH}/gpu/mock/*.h)
list(APPEND GPU_MOCK_SOURCE
${SOURCE_PATH}/gpu/mock/GrMockGpu.cpp
)

source_group(gpu\\mock FILES ${GPU_MOCK_SOURCE})
include_directories(AFTER ${SOURCE_PATH}/gpu/mock)
list(APPEND SKIA_SOURCE_FILES ${GPU_MOCK_SOURCE})

###############################################
# gpu ops
###############################################
file(GLOB GPU_OPS_SOURCE ${SOURCE_PATH}/gpu/ops/*.h)
list(APPEND GPU_OPS_SOURCE
${SOURCE_PATH}/gpu/ops/GrAAConvexPathRenderer.cpp 
${SOURCE_PATH}/gpu/ops/GrAAConvexTessellator.cpp 
${SOURCE_PATH}/gpu/ops/GrAAFillRectOp.cpp 
${SOURCE_PATH}/gpu/ops/GrAAHairLinePathRenderer.cpp 
${SOURCE_PATH}/gpu/ops/GrAALinearizingConvexPathRenderer.cpp 
${SOURCE_PATH}/gpu/ops/GrAAStrokeRectOp.cpp 
${SOURCE_PATH}/gpu/ops/GrAtlasTextOp.cpp 
${SOURCE_PATH}/gpu/ops/GrClearOp.cpp 
${SOURCE_PATH}/gpu/ops/GrCopySurfaceOp.cpp 
${SOURCE_PATH}/gpu/ops/GrDashLinePathRenderer.cpp 
${SOURCE_PATH}/gpu/ops/GrDashOp.cpp 
${SOURCE_PATH}/gpu/ops/GrDefaultPathRenderer.cpp 
${SOURCE_PATH}/gpu/ops/GrDrawAtlasOp.cpp 
${SOURCE_PATH}/gpu/ops/GrDrawOp.cpp 
${SOURCE_PATH}/gpu/ops/GrDrawPathOp.cpp 
${SOURCE_PATH}/gpu/ops/GrDrawVerticesOp.cpp 
${SOURCE_PATH}/gpu/ops/GrLatticeOp.cpp 
${SOURCE_PATH}/gpu/ops/GrMSAAPathRenderer.cpp 
${SOURCE_PATH}/gpu/ops/GrMeshDrawOp.cpp 
${SOURCE_PATH}/gpu/ops/GrNonAAFillRectOp.cpp 
${SOURCE_PATH}/gpu/ops/GrNonAAStrokeRectOp.cpp 
${SOURCE_PATH}/gpu/ops/GrOp.cpp 
${SOURCE_PATH}/gpu/ops/GrOvalOpFactory.cpp 
${SOURCE_PATH}/gpu/ops/GrRegionOp.cpp 
${SOURCE_PATH}/gpu/ops/GrSemaphoreOp.cpp 
${SOURCE_PATH}/gpu/ops/GrShadowRRectOp.cpp 
${SOURCE_PATH}/gpu/ops/GrSimpleMeshDrawOpHelper.cpp 
${SOURCE_PATH}/gpu/ops/GrSmallPathRenderer.cpp 
${SOURCE_PATH}/gpu/ops/GrStencilAndCoverPathRenderer.cpp 
${SOURCE_PATH}/gpu/ops/GrStencilPathOp.cpp 
${SOURCE_PATH}/gpu/ops/GrTessellatingPathRenderer.cpp 
)

source_group(gpu\\ops FILES ${GPU_OPS_SOURCE})
include_directories(AFTER ${SOURCE_PATH}/gpu/ops)
list(APPEND SKIA_SOURCE_FILES ${GPU_OPS_SOURCE})

###############################################
# gpu text
###############################################
file(GLOB GPU_TEXT_SOURCE ${SOURCE_PATH}/gpu/text/*.h)
list(APPEND GPU_TEXT_SOURCE
${SOURCE_PATH}/gpu/text/GrAtlasGlyphCache.cpp 
${SOURCE_PATH}/gpu/text/GrAtlasTextBlob.cpp 
${SOURCE_PATH}/gpu/text/GrAtlasTextBlob_regenInOp.cpp 
${SOURCE_PATH}/gpu/text/GrAtlasTextContext.cpp 
${SOURCE_PATH}/gpu/text/GrDistanceFieldAdjustTable.cpp 
${SOURCE_PATH}/gpu/text/GrStencilAndCoverTextContext.cpp 
${SOURCE_PATH}/gpu/text/GrTextBlobCache.cpp 
${SOURCE_PATH}/gpu/text/GrTextUtils.cpp 
)

source_group(gpu\\text FILES ${GPU_TEXT_SOURCE})
include_directories(AFTER ${SOURCE_PATH}/gpu/text)
list(APPEND SKIA_SOURCE_FILES ${GPU_TEXT_SOURCE})

###############################################
# image
###############################################
list(APPEND image_SOURCE
${SOURCE_PATH}/image/SkImage.cpp 
${SOURCE_PATH}/image/SkImage_Gpu.cpp 
${SOURCE_PATH}/image/SkImage_Lazy.cpp 
${SOURCE_PATH}/image/SkImage_Raster.cpp 
${SOURCE_PATH}/image/SkSurface.cpp 
${SOURCE_PATH}/image/SkSurface_Gpu.cpp 
${SOURCE_PATH}/image/SkSurface_Raster.cpp 
)
SKIA_ADD_SOURCE(image)

###############################################
# images
###############################################
list(APPEND images_SOURCE
${SOURCE_PATH}/images/SkImageEncoder.cpp
${SOURCE_PATH}/images/SkJPEGWriteUtility.cpp
${SOURCE_PATH}/images/SkJpegEncoder.cpp
${SOURCE_PATH}/images/SkPngEncoder.cpp
${SOURCE_PATH}/images/SkWebpEncoder.cpp
)
SKIA_ADD_SOURCE(images)

###############################################
# jumper
###############################################
list(APPEND jumper_SOURCE
${SOURCE_PATH}/jumper/SkJumper.cpp
${SOURCE_PATH}/jumper/SkJumper_stages.cpp
)
if (MSVC)
    enable_language(ASM_MASM)
    list(APPEND jumper_SOURCE_ASM
    ${SOURCE_PATH}/jumper/SkJumper_generated_win.S
    )
    set_property(SOURCE ${jumper_SOURCE_ASM} PROPERTY LANGUAGE ASM_MASM)
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /SAFESEH:NO")
    list(APPEND jumper_SOURCE ${jumper_SOURCE_ASM})
else()
    enable_language(ASM)
    list(APPEND jumper_SOURCE
    ${SOURCE_PATH}/jumper/SkJumper_generated.S
    )
endif()
SKIA_ADD_SOURCE(jumper)

###############################################
# lazy 
###############################################
list(APPEND lazy_SOURCE
${SOURCE_PATH}/lazy/SkDiscardableMemoryPool.cpp
)
SKIA_ADD_SOURCE(lazy)

###############################################
# pathops 
###############################################
list(APPEND pathops_SOURCE
${SOURCE_PATH}/pathops/SkAddIntersections.cpp 
${SOURCE_PATH}/pathops/SkDConicLineIntersection.cpp 
${SOURCE_PATH}/pathops/SkDCubicLineIntersection.cpp 
${SOURCE_PATH}/pathops/SkDCubicToQuads.cpp 
${SOURCE_PATH}/pathops/SkDLineIntersection.cpp 
${SOURCE_PATH}/pathops/SkDQuadLineIntersection.cpp 
${SOURCE_PATH}/pathops/SkIntersections.cpp 
${SOURCE_PATH}/pathops/SkOpAngle.cpp 
${SOURCE_PATH}/pathops/SkOpBuilder.cpp 
${SOURCE_PATH}/pathops/SkOpCoincidence.cpp 
${SOURCE_PATH}/pathops/SkOpContour.cpp 
${SOURCE_PATH}/pathops/SkOpCubicHull.cpp 
${SOURCE_PATH}/pathops/SkOpEdgeBuilder.cpp 
${SOURCE_PATH}/pathops/SkOpSegment.cpp 
${SOURCE_PATH}/pathops/SkOpSpan.cpp 
${SOURCE_PATH}/pathops/SkPathOpsCommon.cpp 
${SOURCE_PATH}/pathops/SkPathOpsConic.cpp 
${SOURCE_PATH}/pathops/SkPathOpsCubic.cpp 
${SOURCE_PATH}/pathops/SkPathOpsCurve.cpp 
${SOURCE_PATH}/pathops/SkPathOpsDebug.cpp 
${SOURCE_PATH}/pathops/SkPathOpsLine.cpp 
${SOURCE_PATH}/pathops/SkPathOpsOp.cpp 
${SOURCE_PATH}/pathops/SkPathOpsPoint.cpp 
${SOURCE_PATH}/pathops/SkPathOpsQuad.cpp 
${SOURCE_PATH}/pathops/SkPathOpsRect.cpp 
${SOURCE_PATH}/pathops/SkPathOpsSimplify.cpp 
${SOURCE_PATH}/pathops/SkPathOpsTSect.cpp 
${SOURCE_PATH}/pathops/SkPathOpsTightBounds.cpp 
${SOURCE_PATH}/pathops/SkPathOpsTypes.cpp 
${SOURCE_PATH}/pathops/SkPathOpsWinding.cpp 
${SOURCE_PATH}/pathops/SkPathWriter.cpp 
${SOURCE_PATH}/pathops/SkReduceOrder.cpp 
)
SKIA_ADD_SOURCE(pathops)

###############################################
# pdf 
###############################################
list(APPEND pdf_SOURCE
${SOURCE_PATH}/pdf/SkDeflate.cpp 
${SOURCE_PATH}/pdf/SkJpegInfo.cpp 
${SOURCE_PATH}/pdf/SkKeyedImage.cpp 
${SOURCE_PATH}/pdf/SkPDFBitmap.cpp 
${SOURCE_PATH}/pdf/SkPDFCanon.cpp 
${SOURCE_PATH}/pdf/SkPDFConvertType1FontStream.cpp 
${SOURCE_PATH}/pdf/SkPDFDevice.cpp 
${SOURCE_PATH}/pdf/SkPDFDocument.cpp 
${SOURCE_PATH}/pdf/SkPDFFont.cpp 
${SOURCE_PATH}/pdf/SkPDFFormXObject.cpp 
${SOURCE_PATH}/pdf/SkPDFGradientShader.cpp 
${SOURCE_PATH}/pdf/SkPDFGraphicState.cpp 
${SOURCE_PATH}/pdf/SkPDFMakeCIDGlyphWidthsArray.cpp 
${SOURCE_PATH}/pdf/SkPDFMakeToUnicodeCmap.cpp 
${SOURCE_PATH}/pdf/SkPDFMetadata.cpp 
${SOURCE_PATH}/pdf/SkPDFResourceDict.cpp 
${SOURCE_PATH}/pdf/SkPDFShader.cpp 
${SOURCE_PATH}/pdf/SkPDFTypes.cpp 
${SOURCE_PATH}/pdf/SkPDFUtils.cpp 
)
SKIA_ADD_SOURCE(pdf)

###############################################
# pipe 
###############################################
list(APPEND pipe_SOURCE
${SOURCE_PATH}/pipe/SkPipeCanvas.cpp
${SOURCE_PATH}/pipe/SkPipeReader.cpp
)
SKIA_ADD_SOURCE(pipe)

###############################################
# ports 
###############################################
list(APPEND ports_SOURCE
${SOURCE_PATH}/ports/SkDiscardableMemory_none.cpp
${SOURCE_PATH}/ports/SkGlobalInitialization_default.cpp 
${SOURCE_PATH}/ports/SkImageGenerator_skia.cpp 
${SOURCE_PATH}/ports/SkMemory_malloc.cpp 
${SOURCE_PATH}/ports/SkOSFile_stdio.cpp  
)
if (MSVC)
    list(APPEND ports_SOURCE
    ${SOURCE_PATH}/ports/SkDebug_win.cpp 
    ${SOURCE_PATH}/ports/SkOSFile_win.cpp 
    ${SOURCE_PATH}/ports/SkFontMgr_win_dw.cpp
    ${SOURCE_PATH}/ports/SkFontMgr_win_dw_factory.cpp
    ${SOURCE_PATH}/ports/SkTypeface_win_dw.cpp
    ${SOURCE_PATH}/ports/SkTypeface_win_dw.h
    ${SOURCE_PATH}/ports/SkScalerContext_win_dw.cpp 
    ${SOURCE_PATH}/ports/SkScalerContext_win_dw.h
    ${SOURCE_PATH}/ports/SkTLS_win.cpp
    )
else(MSVC)
    list(APPEND ports_SOURCE
    ${SOURCE_PATH}/ports/SkDebug_stdio.cpp 
    ${SOURCE_PATH}/ports/SkTLS_pthread.cpp 
    ${SOURCE_PATH}/ports/SkOSFile_posix.cpp     
    )

    if (APPLE)
        list(APPEND ports_SOURCE
        ${SOURCE_PATH}/ports/SkFontHost_mac.cpp   
        )   
    endif(APPLE) 
endif(MSVC)
SKIA_ADD_SOURCE(ports)

###############################################
# sfnt 
###############################################
list(APPEND sfnt_SOURCE
${SOURCE_PATH}/sfnt/SkOTTable_name.cpp 
${SOURCE_PATH}/sfnt/SkOTUtils.cpp 
)
SKIA_ADD_SOURCE(sfnt)

###############################################
# shaders 
###############################################
list(APPEND shaders_SOURCE
${SOURCE_PATH}/shaders/SkBitmapProcShader.cpp 
${SOURCE_PATH}/shaders/SkColorFilterShader.cpp 
${SOURCE_PATH}/shaders/SkColorShader.cpp 
${SOURCE_PATH}/shaders/SkComposeShader.cpp 
${SOURCE_PATH}/shaders/SkImageShader.cpp 
${SOURCE_PATH}/shaders/SkLightingShader.cpp 
${SOURCE_PATH}/shaders/SkLocalMatrixShader.cpp 
${SOURCE_PATH}/shaders/SkPerlinNoiseShader.cpp 
${SOURCE_PATH}/shaders/SkPictureShader.cpp 
${SOURCE_PATH}/shaders/SkShader.cpp 
${SOURCE_PATH}/shaders/gradients/Sk4fGradientBase.cpp 
${SOURCE_PATH}/shaders/gradients/Sk4fLinearGradient.cpp 
${SOURCE_PATH}/shaders/gradients/SkClampRange.cpp 
${SOURCE_PATH}/shaders/gradients/SkGradientBitmapCache.cpp 
${SOURCE_PATH}/shaders/gradients/SkGradientShader.cpp 
${SOURCE_PATH}/shaders/gradients/SkLinearGradient.cpp 
${SOURCE_PATH}/shaders/gradients/SkRadialGradient.cpp 
${SOURCE_PATH}/shaders/gradients/SkSweepGradient.cpp 
${SOURCE_PATH}/shaders/gradients/SkTwoPointConicalGradient.cpp 
${SOURCE_PATH}/shaders/gradients/SkTwoPointConicalGradient_gpu.cpp 
)
SKIA_ADD_SOURCE(shaders)

###############################################
# sksl
###############################################
list(APPEND sksl_SOURCE
${SOURCE_PATH}/sksl/SkSLCFGGenerator.cpp 
${SOURCE_PATH}/sksl/SkSLCPPCodeGenerator.cpp 
${SOURCE_PATH}/sksl/SkSLCompiler.cpp 
${SOURCE_PATH}/sksl/SkSLGLSLCodeGenerator.cpp 
${SOURCE_PATH}/sksl/SkSLHCodeGenerator.cpp 
${SOURCE_PATH}/sksl/SkSLIRGenerator.cpp 
${SOURCE_PATH}/sksl/SkSLParser.cpp 
${SOURCE_PATH}/sksl/SkSLSPIRVCodeGenerator.cpp 
${SOURCE_PATH}/sksl/SkSLString.cpp 
${SOURCE_PATH}/sksl/SkSLUtil.cpp 
${SOURCE_PATH}/sksl/ir/SkSLSetting.cpp 
${SOURCE_PATH}/sksl/ir/SkSLSymbolTable.cpp 
${SOURCE_PATH}/sksl/ir/SkSLType.cpp 
${SOURCE_PATH}/sksl/lex.layout.cpp 
)
SKIA_ADD_SOURCE(sksl)

###############################################
# svg
###############################################
list(APPEND svg_SOURCE
${SOURCE_PATH}/svg/SkSVGCanvas.cpp
${SOURCE_PATH}/svg/SkSVGDevice.cpp
)
SKIA_ADD_SOURCE(svg)

###############################################
# utils
###############################################
list(APPEND utils_SOURCE
${SOURCE_PATH}/utils/SkBase64.cpp 
${SOURCE_PATH}/utils/SkBitmapSourceDeserializer.cpp 
${SOURCE_PATH}/utils/SkCamera.cpp 
${SOURCE_PATH}/utils/SkCanvasStack.cpp 
${SOURCE_PATH}/utils/SkCanvasStateUtils.cpp 
${SOURCE_PATH}/utils/SkCurveMeasure.cpp 
${SOURCE_PATH}/utils/SkDashPath.cpp 
${SOURCE_PATH}/utils/SkDeferredCanvas.cpp 
${SOURCE_PATH}/utils/SkDumpCanvas.cpp 
${SOURCE_PATH}/utils/SkEventTracer.cpp 
${SOURCE_PATH}/utils/SkFrontBufferedStream.cpp 
${SOURCE_PATH}/utils/SkInsetConvexPolygon.cpp 
${SOURCE_PATH}/utils/SkInterpolator.cpp 
${SOURCE_PATH}/utils/SkMatrix22.cpp 
${SOURCE_PATH}/utils/SkMultiPictureDocument.cpp 
${SOURCE_PATH}/utils/SkNWayCanvas.cpp 
${SOURCE_PATH}/utils/SkNullCanvas.cpp 
${SOURCE_PATH}/utils/SkOSPath.cpp 
${SOURCE_PATH}/utils/SkPaintFilterCanvas.cpp 
${SOURCE_PATH}/utils/SkParse.cpp 
${SOURCE_PATH}/utils/SkParseColor.cpp 
${SOURCE_PATH}/utils/SkParsePath.cpp 
${SOURCE_PATH}/utils/SkPatchUtils.cpp 
${SOURCE_PATH}/utils/SkShadowTessellator.cpp
${SOURCE_PATH}/utils/SkShadowUtils.cpp 
${SOURCE_PATH}/utils/SkTextBox.cpp 
${SOURCE_PATH}/utils/SkWhitelistTypefaces.cpp 
)
if (MSVC)
    include_directories(AFTER ${SOURCE_PATH}/utils/win)

    list(APPEND utils_SOURCE
    ${SOURCE_PATH}/utils/SkThreadUtils_win.cpp 
    ${SOURCE_PATH}/utils/win/SkDWrite.cpp 
    ${SOURCE_PATH}/utils/win/SkDWrite.h
    ${SOURCE_PATH}/utils/win/SkDWriteFontFileStream.cpp 
    ${SOURCE_PATH}/utils/win/SkDWriteFontFileStream.h
    ${SOURCE_PATH}/utils/win/SkDWriteGeometrySink.cpp 
    ${SOURCE_PATH}/utils/win/SkDWriteGeometrySink.h    
    ${SOURCE_PATH}/utils/win/SkHRESULT.cpp
    ${SOURCE_PATH}/utils/win/SkIStream.cpp
    )
else()
    if (APPLE)
        list(APPEND utils_SOURCE
        ${SOURCE_PATH}/utils/mac/SkCreateCGImageRef.cpp
        ${SOURCE_PATH}/utils/mac/SkStream_mac.cpp
        )   
    endif() 

    list(APPEND utils_SOURCE
    ${SOURCE_PATH}/utils/SkThreadUtils_pthread.cpp 
    )
endif()
SKIA_ADD_SOURCE(utils)

###############################################
# xml
###############################################
list(APPEND xml_SOURCE
${SOURCE_PATH}/xml/SkDOM.cpp
${SOURCE_PATH}/xml/SkXMLParser.cpp
${SOURCE_PATH}/xml/SkXMLWriter.cpp
)
SKIA_ADD_SOURCE(xml)

###############################################
# xps
###############################################
list(APPEND xps_SOURCE
${SOURCE_PATH}/xps/SkXPSDevice.cpp
${SOURCE_PATH}/xps/SkXPSDocument.cpp
)
SKIA_ADD_SOURCE(xps)

###############################################
# third_party/gif 
###############################################
list(APPEND third_party_gif_SOURCE
${SOURCE_PATH}/../third_party/gif/SkGifImageReader.cpp
)

source_group(third_party\\gif FILES ${third_party_gif_SOURCE})
include_directories(AFTER ${SOURCE_PATH}/../third_party/gif)
list(APPEND SKIA_SOURCE_FILES ${third_party_gif_SOURCE})

###############################################
# opts 
###############################################
if (MSVC OR APPLE)
    list(APPEND opts_SOURCE
    ${SOURCE_PATH}/opts/SkBitmapProcState_opts_SSE2.cpp 
    ${SOURCE_PATH}/opts/SkBitmapProcState_opts_SSSE3.cpp 
    ${SOURCE_PATH}/opts/SkBlitRow_opts_SSE2.cpp 
    ${SOURCE_PATH}/opts/SkOpts_avx.cpp 
    ${SOURCE_PATH}/opts/SkOpts_hsw.cpp 
    ${SOURCE_PATH}/opts/SkOpts_sse41.cpp
    ${SOURCE_PATH}/opts/SkOpts_sse42.cpp
    ${SOURCE_PATH}/opts/SkOpts_ssse3.cpp 
    ${SOURCE_PATH}/opts/opts_check_x86.cpp 
    )
endif() 
SKIA_ADD_SOURCE(opts)


###############################################
# build library of skia 
###############################################
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(skia_android SHARED ${SKIA_SOURCE_FILES} ${SKIA_HEADER_FILES})
target_link_libraries(skia_android ${SKIA_DEPLIB})
