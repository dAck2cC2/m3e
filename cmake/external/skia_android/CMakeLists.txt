
# skia frome Android
project(SKIA_ANDROID)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
#include(${M3E_SOURCE_DIR}/cmake/external/skia_android/include.cmake)

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
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/EGL/include.cmake)

set(SKIA_DEPLIB
${PNG_LIBRARIES}
${JPEG_LIBRARIES}
${GIF_LIBRARIES}
dng_sdk
${WEBP_DEC}
${WEBP_ENC}
piex
${OPENGL_DEPLIB}
)

add_definitions(-D_FORTIFY_SOURCE=1)
add_definitions(-DSKIA_IMPLEMENTATION=1)

if(MSVC)
    add_definitions(-DSKIA_DLL=1)
    add_definitions(-D__BIG_ENDIAN=4321)
    add_definitions(-D__LITTLE_ENDIAN=1234)
    add_definitions(-D__BYTE_ORDER=1234)
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/skia_android/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/skia_android/src )

###############################################
# include
###############################################

include_directories(AFTER ${HEADER_PATH}/core)
file(GLOB CORE_HEADER ${HEADER_PATH}/core/*.h)
source_group(public\\core FILES ${CORE_HEADER})

include_directories(AFTER ${HEADER_PATH}/codec)
file(GLOB CODEC_HEADER ${HEADER_PATH}/codec/*.h)
source_group(public\\codec FILES ${CODEC_HEADER})

include_directories(AFTER ${HEADER_PATH}/pathops)
file(GLOB PATHOPS_HEADER ${HEADER_PATH}/pathops/*.h)
source_group(public\\pathops FILES ${PATHOPS_HEADER})

include_directories(AFTER ${HEADER_PATH}/ports)
file(GLOB PORTS_HEADER ${HEADER_PATH}/ports/*.h)
source_group(public\\ports FILES ${PORTS_HEADER})

include_directories(AFTER ${HEADER_PATH}/private)
file(GLOB PRIVATE_HEADER ${HEADER_PATH}/private/*.h)
source_group(public\\private FILES ${PRIVATE_HEADER})

include_directories(AFTER ${HEADER_PATH}/utils)
file(GLOB UTILS_HEADER ${HEADER_PATH}/utils/*.h)
if (MSVC)
    include_directories(AFTER ${HEADER_PATH}/utils/win)
    file(GLOB UTILS_WIN_HEADER ${HEADER_PATH}/utils/win/*.h)
    list(APPEND UTILS_HEADER ${UTILS_WIN_HEADER})
endif() 
source_group(public\\utils FILES ${UTILS_HEADER})

include_directories(AFTER ${HEADER_PATH}/gpu)
file(GLOB GPU_HEADER ${HEADER_PATH}/gpu/*.h)
source_group(public\\gpu FILES ${GPU_HEADER})

include_directories(AFTER ${HEADER_PATH}/effects)
file(GLOB EFFECTS_HEADER ${HEADER_PATH}/effects/*.h)
source_group(public\\effects FILES ${EFFECTS_HEADER})

include_directories(AFTER ${HEADER_PATH}/images)
file(GLOB IMAGES_HEADER ${HEADER_PATH}/images/*.h)
source_group(public\\images FILES ${IMAGES_HEADER})

include_directories(AFTER ${HEADER_PATH}/client/android)
file(GLOB CLIENT_ANDROID_HEADER ${HEADER_PATH}/client/android/*.h)
source_group(public\\client\\android FILES ${CLIENT_ANDROID_HEADER})

set(SKIA_HEADER_FILES
${CORE_HEADER}
${CODEC_HEADER}
${PATHOPS_HEADER}
${PRIVATE_HEADER}
${PORTS_HEADER}
${UTILS_HEADER}
${GPU_HEADER}
${EFFECTS_HEADER}
${IMAGES_HEADER}
${CLIENT_ANDROID_HEADER}
)

###############################################
# core
###############################################
file(GLOB CORE_SOURCE ${SOURCE_PATH}/core/*.h)
list(APPEND CORE_SOURCE
${SOURCE_PATH}/core/SkAAClip.cpp 
${SOURCE_PATH}/core/SkAnnotation.cpp 
${SOURCE_PATH}/core/SkAdvancedTypefaceMetrics.cpp 
${SOURCE_PATH}/core/SkAlphaRuns.cpp 
${SOURCE_PATH}/core/SkBBHFactory.cpp 
${SOURCE_PATH}/core/SkBigPicture.cpp 
${SOURCE_PATH}/core/SkBitmap.cpp 
${SOURCE_PATH}/core/SkBitmapCache.cpp 
${SOURCE_PATH}/core/SkBitmapController.cpp 
${SOURCE_PATH}/core/SkBitmapDevice.cpp 
${SOURCE_PATH}/core/SkBitmapHeap.cpp 
${SOURCE_PATH}/core/SkBitmapProcShader.cpp 
${SOURCE_PATH}/core/SkBitmapProcState.cpp 
${SOURCE_PATH}/core/SkBitmapProcState_matrixProcs.cpp 
${SOURCE_PATH}/core/SkBitmapProvider.cpp 
${SOURCE_PATH}/core/SkBitmapScaler.cpp 
${SOURCE_PATH}/core/SkBlitMask_D32.cpp 
${SOURCE_PATH}/core/SkBlitRow_D16.cpp 
${SOURCE_PATH}/core/SkBlitRow_D32.cpp 
${SOURCE_PATH}/core/SkBlitter.cpp 
${SOURCE_PATH}/core/SkBlitter_A8.cpp 
${SOURCE_PATH}/core/SkBlitter_ARGB32.cpp 
${SOURCE_PATH}/core/SkBlitter_PM4f.cpp 
${SOURCE_PATH}/core/SkBlitter_RGB16.cpp 
${SOURCE_PATH}/core/SkBlitter_Sprite.cpp 
${SOURCE_PATH}/core/SkBuffer.cpp 
${SOURCE_PATH}/core/SkCachedData.cpp 
${SOURCE_PATH}/core/SkCanvas.cpp 
${SOURCE_PATH}/core/SkChecksum.cpp 
${SOURCE_PATH}/core/SkChunkAlloc.cpp 
${SOURCE_PATH}/core/SkClipStack.cpp 
${SOURCE_PATH}/core/SkColor.cpp 
${SOURCE_PATH}/core/SkColorFilter.cpp 
${SOURCE_PATH}/core/SkColorFilterShader.cpp 
${SOURCE_PATH}/core/SkColorMatrixFilterRowMajor255.cpp 
${SOURCE_PATH}/core/SkColorSpace.cpp 
${SOURCE_PATH}/core/SkColorTable.cpp 
${SOURCE_PATH}/core/SkComposeShader.cpp 
${SOURCE_PATH}/core/SkConfig8888.cpp 
${SOURCE_PATH}/core/SkConvolver.cpp 
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
${SOURCE_PATH}/core/SkDraw.cpp 
${SOURCE_PATH}/core/SkDrawable.cpp 
${SOURCE_PATH}/core/SkDrawLooper.cpp 
${SOURCE_PATH}/core/SkEdgeBuilder.cpp 
${SOURCE_PATH}/core/SkEdgeClipper.cpp 
${SOURCE_PATH}/core/SkEdge.cpp 
${SOURCE_PATH}/core/SkError.cpp 
${SOURCE_PATH}/core/SkFilterProc.cpp 
${SOURCE_PATH}/core/SkFlattenable.cpp 
${SOURCE_PATH}/core/SkFlattenableSerialization.cpp 
${SOURCE_PATH}/core/SkFloatBits.cpp 
${SOURCE_PATH}/core/SkFont.cpp 
${SOURCE_PATH}/core/SkFontHost.cpp 
${SOURCE_PATH}/core/SkFontMgr.cpp 
${SOURCE_PATH}/core/SkFontStyle.cpp 
${SOURCE_PATH}/core/SkFontDescriptor.cpp 
${SOURCE_PATH}/core/SkFontStream.cpp 
${SOURCE_PATH}/core/SkGeometry.cpp 
${SOURCE_PATH}/core/SkGlobalInitialization_core.cpp 
${SOURCE_PATH}/core/SkGlyphCache.cpp 
${SOURCE_PATH}/core/SkGraphics.cpp 
${SOURCE_PATH}/core/SkHalf.cpp 
${SOURCE_PATH}/core/SkImageFilter.cpp 
${SOURCE_PATH}/core/SkImageInfo.cpp 
${SOURCE_PATH}/core/SkImageCacherator.cpp 
${SOURCE_PATH}/core/SkImageGenerator.cpp 
${SOURCE_PATH}/core/SkLightingShader.cpp 
${SOURCE_PATH}/core/SkLinearBitmapPipeline.cpp 
${SOURCE_PATH}/core/SkLineClipper.cpp 
${SOURCE_PATH}/core/SkLocalMatrixImageFilter.cpp 
${SOURCE_PATH}/core/SkLocalMatrixShader.cpp 
${SOURCE_PATH}/core/SkMallocPixelRef.cpp 
${SOURCE_PATH}/core/SkMask.cpp 
${SOURCE_PATH}/core/SkMaskCache.cpp 
${SOURCE_PATH}/core/SkMaskFilter.cpp 
${SOURCE_PATH}/core/SkMaskGamma.cpp 
${SOURCE_PATH}/core/SkMath.cpp 
${SOURCE_PATH}/core/SkMatrix.cpp 
${SOURCE_PATH}/core/SkMatrixImageFilter.cpp 
${SOURCE_PATH}/core/SkMetaData.cpp 
${SOURCE_PATH}/core/SkMipMap.cpp 
${SOURCE_PATH}/core/SkMiniRecorder.cpp 
${SOURCE_PATH}/core/SkModeColorFilter.cpp 
${SOURCE_PATH}/core/SkMultiPictureDraw.cpp 
${SOURCE_PATH}/core/SkNinePatchIter.cpp 
${SOURCE_PATH}/core/SkOpts.cpp 
${SOURCE_PATH}/core/SkPaint.cpp 
${SOURCE_PATH}/core/SkPaintPriv.cpp 
${SOURCE_PATH}/core/SkPath.cpp 
${SOURCE_PATH}/core/SkPathEffect.cpp 
${SOURCE_PATH}/core/SkPathMeasure.cpp 
${SOURCE_PATH}/core/SkPathRef.cpp 
${SOURCE_PATH}/core/SkPicture.cpp 
${SOURCE_PATH}/core/SkPictureContentInfo.cpp 
${SOURCE_PATH}/core/SkPictureData.cpp 
${SOURCE_PATH}/core/SkPictureFlat.cpp 
${SOURCE_PATH}/core/SkPictureImageGenerator.cpp 
${SOURCE_PATH}/core/SkPicturePlayback.cpp 
${SOURCE_PATH}/core/SkPictureRecord.cpp 
${SOURCE_PATH}/core/SkPictureRecorder.cpp 
${SOURCE_PATH}/core/SkPictureShader.cpp 
${SOURCE_PATH}/core/SkPixelRef.cpp 
${SOURCE_PATH}/core/SkPixmap.cpp 
${SOURCE_PATH}/core/SkPoint.cpp 
${SOURCE_PATH}/core/SkPoint3.cpp 
${SOURCE_PATH}/core/SkPtrRecorder.cpp 
${SOURCE_PATH}/core/SkQuadClipper.cpp 
${SOURCE_PATH}/core/SkRasterClip.cpp 
${SOURCE_PATH}/core/SkRasterizer.cpp 
${SOURCE_PATH}/core/SkReadBuffer.cpp 
${SOURCE_PATH}/core/SkRecord.cpp 
${SOURCE_PATH}/core/SkRecords.cpp 
${SOURCE_PATH}/core/SkRecordDraw.cpp 
${SOURCE_PATH}/core/SkRecordOpts.cpp 
${SOURCE_PATH}/core/SkRecorder.cpp 
${SOURCE_PATH}/core/SkRect.cpp 
${SOURCE_PATH}/core/SkRefDict.cpp 
${SOURCE_PATH}/core/SkRegion.cpp 
${SOURCE_PATH}/core/SkRegion_path.cpp 
${SOURCE_PATH}/core/SkRemote.cpp 
${SOURCE_PATH}/core/SkResourceCache.cpp 
${SOURCE_PATH}/core/SkRRect.cpp 
${SOURCE_PATH}/core/SkRTree.cpp 
${SOURCE_PATH}/core/SkRWBuffer.cpp 
${SOURCE_PATH}/core/SkScalar.cpp 
${SOURCE_PATH}/core/SkScalerContext.cpp 
${SOURCE_PATH}/core/SkScan.cpp 
${SOURCE_PATH}/core/SkScan_AntiPath.cpp 
${SOURCE_PATH}/core/SkScan_Antihair.cpp 
${SOURCE_PATH}/core/SkScan_Hairline.cpp 
${SOURCE_PATH}/core/SkScan_Path.cpp 
${SOURCE_PATH}/core/SkSemaphore.cpp 
${SOURCE_PATH}/core/SkShader.cpp 
${SOURCE_PATH}/core/SkSharedMutex.cpp 
${SOURCE_PATH}/core/SkSpanProcs.cpp 
${SOURCE_PATH}/core/SkSpecialImage.cpp 
${SOURCE_PATH}/core/SkSpecialSurface.cpp 
${SOURCE_PATH}/core/SkSpinlock.cpp 
${SOURCE_PATH}/core/SkSpriteBlitter_ARGB32.cpp 
${SOURCE_PATH}/core/SkSpriteBlitter_RGB16.cpp 
${SOURCE_PATH}/core/SkSpriteBlitter4f.cpp 
${SOURCE_PATH}/core/SkStream.cpp 
${SOURCE_PATH}/core/SkString.cpp 
${SOURCE_PATH}/core/SkStringUtils.cpp 
${SOURCE_PATH}/core/SkStroke.cpp 
${SOURCE_PATH}/core/SkStrokeRec.cpp 
${SOURCE_PATH}/core/SkStrokerPriv.cpp 
${SOURCE_PATH}/core/SkTaskGroup.cpp 
${SOURCE_PATH}/core/SkTextBlob.cpp 
${SOURCE_PATH}/core/SkTime.cpp 
${SOURCE_PATH}/core/SkThreadID.cpp 
${SOURCE_PATH}/core/SkTLS.cpp 
${SOURCE_PATH}/core/SkTSearch.cpp 
${SOURCE_PATH}/core/SkTypeface.cpp 
${SOURCE_PATH}/core/SkTypefaceCache.cpp 
${SOURCE_PATH}/core/SkUnPreMultiply.cpp 
${SOURCE_PATH}/core/SkUtils.cpp 
${SOURCE_PATH}/core/SkValidatingReadBuffer.cpp 
${SOURCE_PATH}/core/SkVarAlloc.cpp 
${SOURCE_PATH}/core/SkVertState.cpp 
${SOURCE_PATH}/core/SkWriteBuffer.cpp 
${SOURCE_PATH}/core/SkWriter32.cpp 
${SOURCE_PATH}/core/SkXfermode.cpp 
${SOURCE_PATH}/core/SkXfermode4f.cpp 
${SOURCE_PATH}/core/SkXfermodeU64.cpp 
${SOURCE_PATH}/core/SkXfermodeInterpretation.cpp 
${SOURCE_PATH}/core/SkYUVPlanesCache.cpp
)

source_group(core FILES ${CORE_SOURCE})
include_directories(AFTER ${SOURCE_PATH}/core)

###############################################
# codec 
###############################################
file(GLOB CODEC_SOURCE ${SOURCE_PATH}/codec/*.h)
list(APPEND CODEC_SOURCE
${SOURCE_PATH}/codec/SkAndroidCodec.cpp 
${SOURCE_PATH}/codec/SkBmpCodec.cpp 
${SOURCE_PATH}/codec/SkBmpMaskCodec.cpp 
${SOURCE_PATH}/codec/SkBmpRLECodec.cpp 
${SOURCE_PATH}/codec/SkBmpStandardCodec.cpp 
${SOURCE_PATH}/codec/SkCodec.cpp 
${SOURCE_PATH}/codec/SkGifCodec.cpp 
${SOURCE_PATH}/codec/SkIcoCodec.cpp 
${SOURCE_PATH}/codec/SkJpegCodec.cpp
${SOURCE_PATH}/codec/SkJpegDecoderMgr.cpp 
${SOURCE_PATH}/codec/SkJpegUtility_codec.cpp 
${SOURCE_PATH}/codec/SkMaskSwizzler.cpp 
${SOURCE_PATH}/codec/SkMasks.cpp 
${SOURCE_PATH}/codec/SkPngCodec.cpp 
${SOURCE_PATH}/codec/SkSampler.cpp 
${SOURCE_PATH}/codec/SkSampledCodec.cpp 
${SOURCE_PATH}/codec/SkSwizzler.cpp 
${SOURCE_PATH}/codec/SkWbmpCodec.cpp 
${SOURCE_PATH}/codec/SkWebpAdapterCodec.cpp 
${SOURCE_PATH}/codec/SkWebpCodec.cpp 
${SOURCE_PATH}/codec/SkCodecImageGenerator.cpp 
${SOURCE_PATH}/codec/SkRawAdapterCodec.cpp 
${SOURCE_PATH}/codec/SkRawCodec.cpp 
)

source_group(codec FILES ${CODEC_SOURCE})
include_directories(AFTER ${SOURCE_PATH}/codec)

###############################################
# image
###############################################
file(GLOB IMAGE_SOURCE ${SOURCE_PATH}/image/*.h)
list(APPEND IMAGE_SOURCE
${SOURCE_PATH}/image/SkImage.cpp 
${SOURCE_PATH}/image/SkImage_Generator.cpp 
${SOURCE_PATH}/image/SkImage_Raster.cpp 
${SOURCE_PATH}/image/SkImageShader.cpp 
${SOURCE_PATH}/image/SkSurface.cpp 
${SOURCE_PATH}/image/SkSurface_Raster.cpp 
${SOURCE_PATH}/image/SkImage_Gpu.cpp 
${SOURCE_PATH}/image/SkSurface_Gpu.cpp 
)

source_group(image FILES ${IMAGE_SOURCE})
include_directories(AFTER ${SOURCE_PATH}/image)

###############################################
# fonts
###############################################
file(GLOB FONTS_SOURCE ${SOURCE_PATH}/fonts/*.h)
list(APPEND FONTS_SOURCE
${SOURCE_PATH}/fonts/SkFontMgr_indirect.cpp 
${SOURCE_PATH}/fonts/SkRemotableFontMgr.cpp 
${SOURCE_PATH}/fonts/SkGScalerContext.cpp 
${SOURCE_PATH}/fonts/SkRandomScalerContext.cpp 
${SOURCE_PATH}/fonts/SkTestScalerContext.cpp 
)

source_group(fonts FILES ${FONTS_SOURCE})
include_directories(AFTER ${SOURCE_PATH}/fonts)

###############################################
# images
###############################################
file(GLOB IMAGES_SOURCE ${SOURCE_PATH}/images/*.h)
list(APPEND IMAGES_SOURCE
${SOURCE_PATH}/images/bmpdecoderhelper.cpp 
${SOURCE_PATH}/images/SkForceLinking.cpp 
${SOURCE_PATH}/images/SkImageDecoder.cpp 
${SOURCE_PATH}/images/SkImageDecoder_FactoryDefault.cpp 
${SOURCE_PATH}/images/SkImageDecoder_FactoryRegistrar.cpp 
${SOURCE_PATH}/images/SkImageDecoder_wbmp.cpp 
${SOURCE_PATH}/images/SkImageDecoder_libbmp.cpp 
${SOURCE_PATH}/images/SkImageDecoder_libgif.cpp 
${SOURCE_PATH}/images/SkImageDecoder_libico.cpp 
${SOURCE_PATH}/images/SkImageDecoder_libwebp.cpp 
${SOURCE_PATH}/images/SkImageDecoder_libjpeg.cpp 
${SOURCE_PATH}/images/SkImageDecoder_libpng.cpp 
${SOURCE_PATH}/images/SkImageEncoder.cpp 
${SOURCE_PATH}/images/SkImageEncoder_Factory.cpp 
${SOURCE_PATH}/images/SkImageEncoder_argb.cpp 
${SOURCE_PATH}/images/SkJpegUtility.cpp 
${SOURCE_PATH}/images/SkMovie.cpp 
${SOURCE_PATH}/images/SkMovie_gif.cpp 
${SOURCE_PATH}/images/SkPageFlipper.cpp 
${SOURCE_PATH}/images/SkScaledBitmapSampler.cpp 
)

source_group(images FILES ${IMAGES_SOURCE})
include_directories(AFTER ${SOURCE_PATH}/images)

###############################################
# effects
###############################################
file(GLOB EFFECTS_SOURCE ${SOURCE_PATH}/effects/*.h)
list(APPEND EFFECTS_SOURCE
${SOURCE_PATH}/effects/GrCircleBlurFragmentProcessor.cpp 
${SOURCE_PATH}/effects/Sk1DPathEffect.cpp 
${SOURCE_PATH}/effects/Sk2DPathEffect.cpp 
${SOURCE_PATH}/effects/SkAlphaThresholdFilter.cpp 
${SOURCE_PATH}/effects/SkArcToPathEffect.cpp 
${SOURCE_PATH}/effects/SkArithmeticMode.cpp 
${SOURCE_PATH}/effects/SkArithmeticMode_gpu.cpp 
${SOURCE_PATH}/effects/SkAvoidXfermode.cpp 
${SOURCE_PATH}/effects/SkBlurDrawLooper.cpp 
${SOURCE_PATH}/effects/SkBlurMask.cpp 
${SOURCE_PATH}/effects/SkBlurImageFilter.cpp 
${SOURCE_PATH}/effects/SkBlurMaskFilter.cpp 
${SOURCE_PATH}/effects/SkColorCubeFilter.cpp 
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
${SOURCE_PATH}/effects/SkImageSource.cpp 
${SOURCE_PATH}/effects/SkGpuBlurUtils.cpp 
${SOURCE_PATH}/effects/SkLayerDrawLooper.cpp 
${SOURCE_PATH}/effects/SkLayerRasterizer.cpp 
${SOURCE_PATH}/effects/SkLightingImageFilter.cpp 
${SOURCE_PATH}/effects/SkLumaColorFilter.cpp 
${SOURCE_PATH}/effects/SkMagnifierImageFilter.cpp 
${SOURCE_PATH}/effects/SkMatrixConvolutionImageFilter.cpp 
${SOURCE_PATH}/effects/SkMergeImageFilter.cpp 
${SOURCE_PATH}/effects/SkMorphologyImageFilter.cpp 
${SOURCE_PATH}/effects/SkOffsetImageFilter.cpp 
${SOURCE_PATH}/effects/SkPackBits.cpp 
${SOURCE_PATH}/effects/SkPaintFlagsDrawFilter.cpp 
${SOURCE_PATH}/effects/SkPaintImageFilter.cpp 
${SOURCE_PATH}/effects/SkPerlinNoiseShader.cpp 
${SOURCE_PATH}/effects/SkPictureImageFilter.cpp 
${SOURCE_PATH}/effects/SkPixelXorXfermode.cpp 
${SOURCE_PATH}/effects/SkTableColorFilter.cpp 
${SOURCE_PATH}/effects/SkTableMaskFilter.cpp 
${SOURCE_PATH}/effects/SkTestImageFilters.cpp 
${SOURCE_PATH}/effects/SkTileImageFilter.cpp 
${SOURCE_PATH}/effects/SkXfermodeImageFilter.cpp 
${SOURCE_PATH}/effects/gradients/Sk4fGradientBase.cpp 
${SOURCE_PATH}/effects/gradients/Sk4fLinearGradient.cpp 
${SOURCE_PATH}/effects/gradients/SkClampRange.cpp 
${SOURCE_PATH}/effects/gradients/SkGradientBitmapCache.cpp 
${SOURCE_PATH}/effects/gradients/SkGradientShader.cpp 
${SOURCE_PATH}/effects/gradients/SkLinearGradient.cpp 
${SOURCE_PATH}/effects/gradients/SkRadialGradient.cpp 
${SOURCE_PATH}/effects/gradients/SkTwoPointConicalGradient.cpp 
${SOURCE_PATH}/effects/gradients/SkTwoPointConicalGradient_gpu.cpp 
${SOURCE_PATH}/effects/gradients/SkSweepGradient.cpp 
)

source_group(effects FILES ${EFFECTS_SOURCE})
include_directories(AFTER ${SOURCE_PATH}/effects)

###############################################
# utils
###############################################
file(GLOB UTILS_SOURCE ${SOURCE_PATH}/utils/*.h)
list(APPEND UTILS_SOURCE
${SOURCE_PATH}/utils/SkBase64.cpp 
${SOURCE_PATH}/utils/SkBitmapSourceDeserializer.cpp 
${SOURCE_PATH}/utils/SkBitSet.cpp 
${SOURCE_PATH}/utils/SkBoundaryPatch.cpp 
${SOURCE_PATH}/utils/SkFrontBufferedStream.cpp 
${SOURCE_PATH}/utils/SkCamera.cpp 
${SOURCE_PATH}/utils/SkCanvasStack.cpp 
${SOURCE_PATH}/utils/SkCanvasStateUtils.cpp 
${SOURCE_PATH}/utils/SkDashPath.cpp 
${SOURCE_PATH}/utils/SkDumpCanvas.cpp 
${SOURCE_PATH}/utils/SkEventTracer.cpp 
${SOURCE_PATH}/utils/SkImageGeneratorUtils.cpp 
${SOURCE_PATH}/utils/SkInterpolator.cpp 
${SOURCE_PATH}/utils/SkLayer.cpp 
${SOURCE_PATH}/utils/SkMatrix22.cpp 
${SOURCE_PATH}/utils/SkMatrix44.cpp 
${SOURCE_PATH}/utils/SkMD5.cpp 
${SOURCE_PATH}/utils/SkMeshUtils.cpp 
${SOURCE_PATH}/utils/SkNinePatch.cpp 
${SOURCE_PATH}/utils/SkNWayCanvas.cpp 
${SOURCE_PATH}/utils/SkNullCanvas.cpp 
${SOURCE_PATH}/utils/SkOSFile.cpp 
${SOURCE_PATH}/utils/SkPaintFilterCanvas.cpp 
${SOURCE_PATH}/utils/SkParse.cpp 
${SOURCE_PATH}/utils/SkParseColor.cpp 
${SOURCE_PATH}/utils/SkParsePath.cpp 
${SOURCE_PATH}/utils/SkPatchGrid.cpp 
${SOURCE_PATH}/utils/SkPatchUtils.cpp 
${SOURCE_PATH}/utils/SkRGBAToYUV.cpp 
${SOURCE_PATH}/utils/SkRTConf.cpp 
${SOURCE_PATH}/utils/SkTextBox.cpp 
${SOURCE_PATH}/utils/SkTextureCompressor.cpp 
${SOURCE_PATH}/utils/SkTextureCompressor_ASTC.cpp 
${SOURCE_PATH}/utils/SkTextureCompressor_R11EAC.cpp 
${SOURCE_PATH}/utils/SkTextureCompressor_LATC.cpp 
${SOURCE_PATH}/utils/SkWhitelistTypefaces.cpp 
)

if (MSVC)
    include_directories(AFTER ${SOURCE_PATH}/utils/win)

    list(APPEND UTILS_SOURCE
    ${SOURCE_PATH}/utils/SkThreadUtils_win.cpp 
    ${SOURCE_PATH}/utils/win/SkDWrite.cpp 
    ${SOURCE_PATH}/utils/win/SkDWrite.h
    ${SOURCE_PATH}/utils/win/SkDWriteFontFileStream.cpp 
    ${SOURCE_PATH}/utils/win/SkDWriteFontFileStream.h
    ${SOURCE_PATH}/utils/win/SkDWriteGeometrySink.cpp 
    ${SOURCE_PATH}/utils/win/SkDWriteGeometrySink.h    
    ${SOURCE_PATH}/utils/win/SkHRESULT.cpp
    )
else()
    if (APPLE)
        list(APPEND UTILS_SOURCE
        ${SOURCE_PATH}/utils/mac/SkCreateCGImageRef.cpp
        ${SOURCE_PATH}/utils/mac/SkStream_mac.cpp
        )   
    endif() 

    list(APPEND UTILS_SOURCE
    ${SOURCE_PATH}/utils/SkThreadUtils_pthread.cpp 
    )
endif()

source_group(utils FILES ${UTILS_SOURCE})
include_directories(AFTER ${SOURCE_PATH}/utils)

###############################################
# gpu 
###############################################
file(GLOB GPU_SOURCE ${SOURCE_PATH}/gpu/*.h)
list(APPEND GPU_SOURCE 
${SOURCE_PATH}/gpu/GrAuditTrail.cpp 
${SOURCE_PATH}/gpu/GrBatchAtlas.cpp 
${SOURCE_PATH}/gpu/GrBatchFlushState.cpp 
${SOURCE_PATH}/gpu/GrBatchTest.cpp 
${SOURCE_PATH}/gpu/GrBlend.cpp 
${SOURCE_PATH}/gpu/GrBlurUtils.cpp 
${SOURCE_PATH}/gpu/GrBufferAllocPool.cpp 
${SOURCE_PATH}/gpu/GrCaps.cpp 
${SOURCE_PATH}/gpu/GrClip.cpp 
${SOURCE_PATH}/gpu/GrClipMaskManager.cpp 
${SOURCE_PATH}/gpu/GrContext.cpp 
${SOURCE_PATH}/gpu/GrCoordTransform.cpp 
${SOURCE_PATH}/gpu/GrDefaultGeoProcFactory.cpp 
${SOURCE_PATH}/gpu/GrDrawContext.cpp 
${SOURCE_PATH}/gpu/GrPathRenderingDrawContext.cpp 
${SOURCE_PATH}/gpu/GrDrawingManager.cpp 
${SOURCE_PATH}/gpu/GrDrawTarget.cpp 
${SOURCE_PATH}/gpu/GrFragmentProcessor.cpp 
${SOURCE_PATH}/gpu/GrGpu.cpp 
${SOURCE_PATH}/gpu/GrGpuResource.cpp 
${SOURCE_PATH}/gpu/GrGpuFactory.cpp 
${SOURCE_PATH}/gpu/GrImageIDTextureAdjuster.cpp 
${SOURCE_PATH}/gpu/GrInvariantOutput.cpp 
${SOURCE_PATH}/gpu/GrLayerAtlas.cpp 
${SOURCE_PATH}/gpu/GrLayerCache.cpp 
${SOURCE_PATH}/gpu/GrLayerHoister.cpp 
${SOURCE_PATH}/gpu/GrMemoryPool.cpp 
${SOURCE_PATH}/gpu/GrOvalRenderer.cpp 
${SOURCE_PATH}/gpu/GrPaint.cpp 
${SOURCE_PATH}/gpu/GrPath.cpp 
${SOURCE_PATH}/gpu/GrPathProcessor.cpp 
${SOURCE_PATH}/gpu/GrPathRange.cpp 
${SOURCE_PATH}/gpu/GrPathRendererChain.cpp 
${SOURCE_PATH}/gpu/GrPathRenderer.cpp 
${SOURCE_PATH}/gpu/GrPathRendering.cpp 
${SOURCE_PATH}/gpu/GrPathUtils.cpp 
${SOURCE_PATH}/gpu/GrPipeline.cpp 
${SOURCE_PATH}/gpu/GrPipelineBuilder.cpp 
${SOURCE_PATH}/gpu/GrPrimitiveProcessor.cpp 
${SOURCE_PATH}/gpu/GrProgramElement.cpp 
${SOURCE_PATH}/gpu/GrProcessor.cpp 
${SOURCE_PATH}/gpu/GrProcessorUnitTest.cpp 
${SOURCE_PATH}/gpu/GrProcOptInfo.cpp 
${SOURCE_PATH}/gpu/GrGpuResourceRef.cpp 
${SOURCE_PATH}/gpu/GrRecordReplaceDraw.cpp 
${SOURCE_PATH}/gpu/GrRectanizer_pow2.cpp 
${SOURCE_PATH}/gpu/GrRectanizer_skyline.cpp 
${SOURCE_PATH}/gpu/GrRenderTarget.cpp 
${SOURCE_PATH}/gpu/GrReducedClip.cpp 
${SOURCE_PATH}/gpu/GrResourceCache.cpp 
${SOURCE_PATH}/gpu/GrResourceProvider.cpp 
${SOURCE_PATH}/gpu/GrStencil.cpp 
${SOURCE_PATH}/gpu/GrStencilAttachment.cpp 
${SOURCE_PATH}/gpu/GrStrokeInfo.cpp 
${SOURCE_PATH}/gpu/GrTessellator.cpp 
${SOURCE_PATH}/gpu/GrTraceMarker.cpp 
${SOURCE_PATH}/gpu/GrTestUtils.cpp 
${SOURCE_PATH}/gpu/GrSWMaskHelper.cpp 
${SOURCE_PATH}/gpu/GrSoftwarePathRenderer.cpp 
${SOURCE_PATH}/gpu/GrSurface.cpp 
${SOURCE_PATH}/gpu/GrTexture.cpp 
${SOURCE_PATH}/gpu/GrTextureParamsAdjuster.cpp 
${SOURCE_PATH}/gpu/GrTextureProvider.cpp 
${SOURCE_PATH}/gpu/GrTextureToYUVPlanes.cpp 
${SOURCE_PATH}/gpu/GrTextureAccess.cpp 
${SOURCE_PATH}/gpu/GrXferProcessor.cpp 
${SOURCE_PATH}/gpu/GrYUVProvider.cpp 
${SOURCE_PATH}/gpu/SkGpuDevice.cpp 
${SOURCE_PATH}/gpu/SkGpuDevice_drawTexture.cpp 
${SOURCE_PATH}/gpu/SkGr.cpp 
${SOURCE_PATH}/gpu/SkGrPixelRef.cpp 
${SOURCE_PATH}/gpu/SkGrTexturePixelRef.cpp 
)

source_group(gpu FILES ${GPU_SOURCE})
include_directories(AFTER ${SOURCE_PATH}/gpu)

###############################################
# gpu gl
###############################################
file(GLOB GPU_GL_SOURCE ${SOURCE_PATH}/gpu/gl/*.h)
list(APPEND GPU_GL_SOURCE
${SOURCE_PATH}/gpu/gl/GrGLAssembleInterface.cpp 
${SOURCE_PATH}/gpu/gl/GrGLBufferImpl.cpp 
${SOURCE_PATH}/gpu/gl/GrGLCaps.cpp 
${SOURCE_PATH}/gpu/gl/GrGLContext.cpp 
${SOURCE_PATH}/gpu/gl/GrGLGLSL.cpp 
${SOURCE_PATH}/gpu/gl/GrGLGpu.cpp 
${SOURCE_PATH}/gpu/gl/GrGLGpuProgramCache.cpp 
${SOURCE_PATH}/gpu/gl/GrGLExtensions.cpp 
${SOURCE_PATH}/gpu/gl/GrGLIndexBuffer.cpp 
${SOURCE_PATH}/gpu/gl/GrGLInterface.cpp 
${SOURCE_PATH}/gpu/gl/GrGLNoOpInterface.cpp 
${SOURCE_PATH}/gpu/gl/GrGLPath.cpp 
${SOURCE_PATH}/gpu/gl/GrGLPathRange.cpp 
${SOURCE_PATH}/gpu/gl/GrGLPathRendering.cpp 
${SOURCE_PATH}/gpu/gl/GrGLProgram.cpp 
${SOURCE_PATH}/gpu/gl/GrGLProgramDesc.cpp 
${SOURCE_PATH}/gpu/gl/GrGLProgramDataManager.cpp 
${SOURCE_PATH}/gpu/gl/GrGLRenderTarget.cpp 
${SOURCE_PATH}/gpu/gl/GrGLStencilAttachment.cpp 
${SOURCE_PATH}/gpu/gl/GrGLTexture.cpp 
${SOURCE_PATH}/gpu/gl/GrGLTextureRenderTarget.cpp 
${SOURCE_PATH}/gpu/gl/GrGLTransferBuffer.cpp 
${SOURCE_PATH}/gpu/gl/GrGLUtil.cpp 
${SOURCE_PATH}/gpu/gl/GrGLUniformHandler.cpp 
${SOURCE_PATH}/gpu/gl/GrGLVaryingHandler.cpp 
${SOURCE_PATH}/gpu/gl/GrGLVertexArray.cpp 
${SOURCE_PATH}/gpu/gl/GrGLVertexBuffer.cpp 
${SOURCE_PATH}/gpu/gl/builders/GrGLProgramBuilder.cpp 
${SOURCE_PATH}/gpu/gl/builders/GrGLShaderStringBuilder.cpp 
${SOURCE_PATH}/gpu/gl/builders/GrGLSLPrettyPrint.cpp 
${SOURCE_PATH}/gpu/gl/SkGLContext.cpp 
${SOURCE_PATH}/gpu/gl/GrGLDefaultInterface_native.cpp 
${SOURCE_PATH}/gpu/gl/egl/GrGLCreateNativeInterface_egl.cpp 
${SOURCE_PATH}/gpu/gl/egl/SkCreatePlatformGLContext_egl.cpp 
${SOURCE_PATH}/gpu/gl/debug/GrGLCreateDebugInterface.cpp 
${SOURCE_PATH}/gpu/gl/debug/GrBufferObj.cpp 
${SOURCE_PATH}/gpu/gl/debug/GrTextureObj.cpp 
${SOURCE_PATH}/gpu/gl/debug/GrTextureUnitObj.cpp 
${SOURCE_PATH}/gpu/gl/debug/GrFrameBufferObj.cpp 
${SOURCE_PATH}/gpu/gl/debug/GrShaderObj.cpp 
${SOURCE_PATH}/gpu/gl/debug/GrProgramObj.cpp 
${SOURCE_PATH}/gpu/gl/debug/GrDebugGL.cpp 
${SOURCE_PATH}/gpu/gl/debug/SkDebugGLContext.cpp 
${SOURCE_PATH}/gpu/gl/GrGLCreateNullInterface.cpp 
${SOURCE_PATH}/gpu/gl/SkNullGLContext.cpp 
)

source_group(gpu\\gl FILES ${GPU_GL_SOURCE})
include_directories(AFTER ${SOURCE_PATH}/gpu/gl)

###############################################
# gpu batches
###############################################
file(GLOB GPU_BATCHES_SOURCE ${SOURCE_PATH}/gpu/batches/*.h)
list(APPEND GPU_BATCHES_SOURCE
${SOURCE_PATH}/gpu/batches/GrAAHairLinePathRenderer.cpp 
${SOURCE_PATH}/gpu/batches/GrAALinearizingConvexPathRenderer.cpp 
${SOURCE_PATH}/gpu/batches/GrAAConvexTessellator.cpp 
${SOURCE_PATH}/gpu/batches/GrAADistanceFieldPathRenderer.cpp 
${SOURCE_PATH}/gpu/batches/GrAAConvexPathRenderer.cpp 
${SOURCE_PATH}/gpu/batches/GrAAFillRectBatch.cpp 
${SOURCE_PATH}/gpu/batches/GrAAStrokeRectBatch.cpp 
${SOURCE_PATH}/gpu/batches/GrAtlasTextBatch.cpp 
${SOURCE_PATH}/gpu/batches/GrBatch.cpp 
${SOURCE_PATH}/gpu/batches/GrCopySurfaceBatch.cpp 
${SOURCE_PATH}/gpu/batches/GrDashLinePathRenderer.cpp 
${SOURCE_PATH}/gpu/batches/GrDefaultPathRenderer.cpp 
${SOURCE_PATH}/gpu/batches/GrDrawBatch.cpp 
${SOURCE_PATH}/gpu/batches/GrDrawAtlasBatch.cpp 
${SOURCE_PATH}/gpu/batches/GrDrawPathBatch.cpp 
${SOURCE_PATH}/gpu/batches/GrDrawVerticesBatch.cpp 
${SOURCE_PATH}/gpu/batches/GrNonAAFillRectBatch.cpp 
${SOURCE_PATH}/gpu/batches/GrNonAAStrokeRectBatch.cpp 
${SOURCE_PATH}/gpu/batches/GrNinePatch.cpp 
${SOURCE_PATH}/gpu/batches/GrPLSPathRenderer.cpp 
${SOURCE_PATH}/gpu/batches/GrRectBatchFactory.cpp 
${SOURCE_PATH}/gpu/batches/GrStencilAndCoverPathRenderer.cpp 
${SOURCE_PATH}/gpu/batches/GrTessellatingPathRenderer.cpp 
${SOURCE_PATH}/gpu/batches/GrVertexBatch.cpp 
)

source_group(gpu\\batches FILES ${GPU_BATCHES_SOURCE})
include_directories(AFTER ${SOURCE_PATH}/gpu/batches)

###############################################
# gpu effects 
###############################################
file(GLOB GPU_EFFECT_SOURCE ${SOURCE_PATH}/gpu/effects/*.h)
list(APPEND GPU_EFFECT_SOURCE
${SOURCE_PATH}/gpu/effects/GrConfigConversionEffect.cpp 
${SOURCE_PATH}/gpu/effects/GrConstColorProcessor.cpp 
${SOURCE_PATH}/gpu/effects/GrCoverageSetOpXP.cpp 
${SOURCE_PATH}/gpu/effects/GrCustomXfermode.cpp 
${SOURCE_PATH}/gpu/effects/GrBezierEffect.cpp 
${SOURCE_PATH}/gpu/effects/GrConvolutionEffect.cpp 
${SOURCE_PATH}/gpu/effects/GrConvexPolyEffect.cpp 
${SOURCE_PATH}/gpu/effects/GrBicubicEffect.cpp 
${SOURCE_PATH}/gpu/effects/GrBitmapTextGeoProc.cpp 
${SOURCE_PATH}/gpu/effects/GrDashingEffect.cpp 
${SOURCE_PATH}/gpu/effects/GrDisableColorXP.cpp 
${SOURCE_PATH}/gpu/effects/GrDistanceFieldGeoProc.cpp 
${SOURCE_PATH}/gpu/effects/GrDitherEffect.cpp 
${SOURCE_PATH}/gpu/effects/GrMatrixConvolutionEffect.cpp 
${SOURCE_PATH}/gpu/effects/GrOvalEffect.cpp 
${SOURCE_PATH}/gpu/effects/GrPorterDuffXferProcessor.cpp 
${SOURCE_PATH}/gpu/effects/GrRRectEffect.cpp 
${SOURCE_PATH}/gpu/effects/GrSimpleTextureEffect.cpp 
${SOURCE_PATH}/gpu/effects/GrSingleTextureEffect.cpp 
${SOURCE_PATH}/gpu/effects/GrTextureDomain.cpp 
${SOURCE_PATH}/gpu/effects/GrTextureStripAtlas.cpp 
${SOURCE_PATH}/gpu/effects/GrXfermodeFragmentProcessor.cpp 
${SOURCE_PATH}/gpu/effects/GrYUVEffect.cpp 
)

source_group(gpu\\effects FILES ${GPU_EFFECT_SOURCE})
include_directories(AFTER ${SOURCE_PATH}/gpu/effects)

###############################################
# gpu glsl
###############################################

file(GLOB GPU_GLSL_SOURCE ${SOURCE_PATH}/gpu/glsl/*.h)
list(APPEND GPU_GLSL_SOURCE
${SOURCE_PATH}/gpu/glsl/GrGLSL.cpp 
${SOURCE_PATH}/gpu/glsl/GrGLSLBlend.cpp 
${SOURCE_PATH}/gpu/glsl/GrGLSLCaps.cpp 
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

###############################################
# gpu text
###############################################
file(GLOB GPU_TEXT_SOURCE ${SOURCE_PATH}/gpu/text/*.h)
list(APPEND GPU_TEXT_SOURCE
${SOURCE_PATH}/gpu/text/GrAtlasTextBlob.cpp 
${SOURCE_PATH}/gpu/text/GrAtlasTextBlob_regenInBatch.cpp 
${SOURCE_PATH}/gpu/text/GrAtlasTextContext.cpp 
${SOURCE_PATH}/gpu/text/GrBatchFontCache.cpp 
${SOURCE_PATH}/gpu/text/GrDistanceFieldAdjustTable.cpp 
${SOURCE_PATH}/gpu/text/GrFontScaler.cpp 
${SOURCE_PATH}/gpu/text/GrStencilAndCoverTextContext.cpp 
${SOURCE_PATH}/gpu/text/GrTextBlobCache.cpp 
${SOURCE_PATH}/gpu/text/GrTextUtils.cpp 
)

source_group(gpu\\text FILES ${GPU_TEXT_SOURCE})
include_directories(AFTER ${SOURCE_PATH}/gpu/text)

###############################################
# port 
###############################################
set(PORTS_SOURCE ${PORTS_SOURCE}
${SOURCE_PATH}/ports/SkImageGenerator_skia.cpp 
${SOURCE_PATH}/ports/SkMemory_malloc.cpp 
${SOURCE_PATH}/ports/SkOSFile_stdio.cpp  
${SOURCE_PATH}/ports/SkGlobalInitialization_default.cpp
${SOURCE_PATH}/ports/SkDiscardableMemory_none.cpp 
)

if (MSVC)
    list(APPEND PORTS_SOURCE
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
else()
    list(APPEND PORTS_SOURCE
    ${SOURCE_PATH}/ports/SkDebug_stdio.cpp 
    ${SOURCE_PATH}/ports/SkTLS_pthread.cpp 
    )
endif()

source_group(ports FILES ${PORTS_SOURCE})

###############################################
# sfnt 
###############################################
file(GLOB SFNT_SOURCE ${SOURCE_PATH}/sfnt/*.h)
list(APPEND SFNT_SOURCE
${SOURCE_PATH}/sfnt/SkOTTable_name.cpp 
${SOURCE_PATH}/sfnt/SkOTUtils.cpp 
)

source_group(sfnt FILES ${SFNT_SOURCE})
include_directories(AFTER ${SOURCE_PATH}/sfnt)

###############################################
# lazy 
###############################################
file(GLOB LAZY_SOURCE ${SOURCE_PATH}/lazy/*.h)
list(APPEND LAZY_SOURCE
${SOURCE_PATH}/lazy/SkDiscardableMemoryPool.cpp
${SOURCE_PATH}/lazy/SkDiscardablePixelRef.cpp
)

source_group(lazy FILES ${LAZY_SOURCE})
include_directories(AFTER ${SOURCE_PATH}/lazy)

###############################################
# opts 
###############################################
file(GLOB OPTS_SOURCE ${SOURCE_PATH}/opts/*.h)
if (MSVC OR APPLE)
    list(APPEND OPTS_SOURCE
    ${SOURCE_PATH}/opts/SkBitmapFilter_opts_SSE2.cpp 
    ${SOURCE_PATH}/opts/SkBitmapProcState_opts_SSE2.cpp 
    ${SOURCE_PATH}/opts/SkBlitRow_opts_SSE2.cpp 
    ${SOURCE_PATH}/opts/opts_check_x86.cpp 
    ${SOURCE_PATH}/opts/SkBitmapProcState_opts_SSSE3.cpp 
    ${SOURCE_PATH}/opts/SkOpts_ssse3.cpp 
    ${SOURCE_PATH}/opts/SkBlitRow_opts_SSE4.cpp 
    ${SOURCE_PATH}/opts/SkOpts_sse41.cpp
    )
endif() 

source_group(opts FILES ${OPTS_SOURCE})
include_directories(AFTER ${SOURCE_PATH}/opts)

###############################################
# pathops 
###############################################
file(GLOB PATHOPS_SOURCE ${SOURCE_PATH}/pathops/*.h)
list(APPEND PATHOPS_SOURCE
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

source_group(pathops FILES ${PATHOPS_SOURCE})
include_directories(AFTER ${SOURCE_PATH}/pathops)

###############################################
# build library of skia 
###############################################
set(SKIA_SOURCE_FILES
${CORE_SOURCE}
${CODEC_SOURCE}
${PORTS_SOURCE}
${IMAGE_SOURCE}
${FONTS_SOURCE}
${UTILS_SOURCE}
${IMAGES_SOURCE}
${EFFECTS_SOURCE}
${GPU_SOURCE}
${GPU_GL_SOURCE}
${GPU_BATCHES_SOURCE}
${GPU_EFFECT_SOURCE}
${GPU_GLSL_SOURCE}
${GPU_TEXT_SOURCE}
${OPTS_SOURCE}
${SFNT_SOURCE}
${LAZY_SOURCE}
${PATHOPS_SOURCE}
)

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(skia_android SHARED ${SKIA_SOURCE_FILES} ${SKIA_HEADER_FILES})
target_link_libraries(skia_android ${SKIA_DEPLIB})
