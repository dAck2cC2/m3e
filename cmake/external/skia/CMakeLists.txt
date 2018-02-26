
project(SKIA)

if(NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH}/skia)
message(STATUS "Download\tskia")
exec_program("git clone https://skia.googlesource.com/skia.git" ${M3E_SOURCE_DIR}/${EXT_PATH})
exec_program("git checkout chrome/m65" ${M3E_SOURCE_DIR}/${EXT_PATH}/skia)
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/src )

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/skia/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/jsoncpp/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/imgui/include.cmake)

# dependency

set(SKIA_DEPLIB
#jsoncpp
#imgui
)

include_directories(AFTER ${HEADER_PATH}/config)
include_directories(AFTER ${HEADER_PATH}/core)
include_directories(AFTER ${HEADER_PATH}/codec)
include_directories(AFTER ${HEADER_PATH}/effects)
include_directories(AFTER ${HEADER_PATH}/utils)
include_directories(AFTER ${HEADER_PATH}/gpu)
include_directories(AFTER ${HEADER_PATH}/pathops)
include_directories(AFTER ${HEADER_PATH}/ports)
include_directories(AFTER ${HEADER_PATH}/encode)
include_directories(AFTER ${HEADER_PATH}/private)

include_directories(AFTER ${SOURCE_PATH}/opts)
include_directories(AFTER ${SOURCE_PATH}/shaders)
include_directories(AFTER ${SOURCE_PATH}/core)
include_directories(AFTER ${SOURCE_PATH}/image)
include_directories(AFTER ${SOURCE_PATH}/utils)
include_directories(AFTER ${SOURCE_PATH}/sfnt)

# core
add_definitions(-DSK_SUPPORT_GPU=0)
file(GLOB CORE_HEADER
${HEADER_PATH}/core/*.h
)
file(GLOB CORE_SOURCE
${SOURCE_PATH}/core/*.*
)

# port
file(GLOB PORTS_HEADER ${SOURCE_PATH}/ports/*.h)

if (APPLE)
include_directories(AFTER ${HEADER_PATH}/utils/mac)
find_library(CORE_FOUNDATION_LIBRARY CoreFoundation)
list(APPEND SKIA_DEPLIB ${CORE_FOUNDATION_LIBRARY})
find_library(CORE_GRAPHICS_LIBRARY CoreGraphics)
list(APPEND SKIA_DEPLIB ${CORE_GRAPHICS_LIBRARY})
find_library(CORE_TEXT_LIBRARY CoreText)
list(APPEND SKIA_DEPLIB ${CORE_TEXT_LIBRARY})

set(PORTS_SOURCE
${SOURCE_PATH}/ports/SkOSFile_posix.cpp
${SOURCE_PATH}/ports/SkOSFile_stdio.cpp
${SOURCE_PATH}/ports/SkDebug_stdio.cpp
${SOURCE_PATH}/ports/SkTLS_pthread.cpp
${SOURCE_PATH}/ports/SkFontHost_mac.cpp
)

elseif (MSVC)
add_definitions(-DNOMINMAX)
add_definitions(-DDWRITE_RENDERING_MODE_GDI_CLASSIC=DWRITE_RENDERING_MODE_CLEARTYPE_GDI_CLASSIC)
add_definitions(-DDWRITE_RENDERING_MODE_NATURAL=DWRITE_RENDERING_MODE_CLEARTYPE_NATURAL)
add_definitions(-DDWRITE_RENDERING_MODE_NATURAL_SYMMETRIC=DWRITE_RENDERING_MODE_CLEARTYPE_NATURAL_SYMMETRIC)
include_directories(AFTER ${SOURCE_PATH}/utils/win)

set(PORTS_SOURCE
${SOURCE_PATH}/ports/SkOSFile_win.cpp
${SOURCE_PATH}/ports/SkOSFile_stdio.cpp
${SOURCE_PATH}/ports/SkDebug_win.cpp
${SOURCE_PATH}/ports/SkTLS_win.cpp
${SOURCE_PATH}/ports/SkFontMgr_win_dw_factory.cpp
${SOURCE_PATH}/ports/SkFontMgr_win_dw.cpp
${SOURCE_PATH}/ports/SkTypeface_win_dw.cpp
${SOURCE_PATH}/ports/SkScalerContext_win_dw.cpp
)

else()
set(PORTS_SOURCE 
${SOURCE_PATH}/ports/SkTLS_pthread.cpp
${SOURCE_PATH}/ports/SkFontMgr_empty_factory.cpp
)
endif()

set(PORTS_SOURCE ${PORTS_SOURCE}
${SOURCE_PATH}/ports/SkMemory_malloc.cpp
${SOURCE_PATH}/ports/SkGlobalInitialization_none.cpp
#${SOURCE_PATH}/ports/SkGlobalInitialization_default.cpp
${SOURCE_PATH}/ports/SkImageGenerator_none.cpp
#${SOURCE_PATH}/ports/SkImageGenerator_skia.cpp
)

# shaders
file(GLOB SHADERS_HEADER ${SOURCE_PATH}/shaders/*.h)
set(SHADERS_SOURCE 
${SOURCE_PATH}/shaders/SkImageShader.cpp
${SOURCE_PATH}/shaders/SkShader.cpp
${SOURCE_PATH}/shaders/SkColorShader.cpp
${SOURCE_PATH}/shaders/SkComposeShader.cpp
${SOURCE_PATH}/shaders/SkColorFilterShader.cpp
${SOURCE_PATH}/shaders/SkPictureShader.cpp
${SOURCE_PATH}/shaders/SkBitmapProcShader.cpp
${SOURCE_PATH}/shaders/SkLocalMatrixShader.cpp
)

# utils
file(GLOB UTILS_HEADER ${SOURCE_PATH}/utils/*.h)
set(UTILS_SOURCE 
${SOURCE_PATH}/utils/SkMatrix22.cpp
${SOURCE_PATH}/utils/SkShadowUtils.cpp
${SOURCE_PATH}/utils/SkNWayCanvas.cpp
${SOURCE_PATH}/utils/SkPatchUtils.cpp
${SOURCE_PATH}/utils/SkEventTracer.cpp
${SOURCE_PATH}/utils/SkShadowTessellator.cpp
${SOURCE_PATH}/utils/SkInsetConvexPolygon.cpp
)

if (APPLE)
set(UTILS_SOURCE ${UTILS_SOURCE}
${SOURCE_PATH}/utils/mac/SkStream_mac.cpp
)
elseif (MSVC)
set(UTILS_SOURCE ${UTILS_SOURCE}
${SOURCE_PATH}/utils/win/SkDWriteGeometrySink.cpp
${SOURCE_PATH}/utils/win/SkDWriteFontFileStream.cpp
${SOURCE_PATH}/utils/win/SkDWrite.cpp
${SOURCE_PATH}/utils/win/SkHRESULT.cpp
)
endif ()

# image
file(GLOB IMAGE_HEADER ${SOURCE_PATH}/image/*.h)
set(IMAGE_SOURCE 
${SOURCE_PATH}/image/SkImage_Raster.cpp
${SOURCE_PATH}/image/SkSurface_Raster.cpp
${SOURCE_PATH}/image/SkImage.cpp
${SOURCE_PATH}/image/SkSurface.cpp
${SOURCE_PATH}/image/SkImage_Lazy.cpp
)

# images
file(GLOB IMAGES_HEADER ${SOURCE_PATH}/images/*.h)
set(IMAGES_SOURCE 
${SOURCE_PATH}/images/SkImageEncoder.cpp
) 


# pathops
file(GLOB PATHOPS_HEADER ${SOURCE_PATH}/pathops/*.h)
set(PATHOPS_SOURCE 
${SOURCE_PATH}/pathops/SkPathOpsOp.cpp
${SOURCE_PATH}/pathops/SkPathOpsCommon.cpp
${SOURCE_PATH}/pathops/SkAddIntersections.cpp
${SOURCE_PATH}/pathops/SkPathOpsTypes.cpp
${SOURCE_PATH}/pathops/SkPathOpsWinding.cpp
${SOURCE_PATH}/pathops/SkOpContour.cpp
${SOURCE_PATH}/pathops/SkOpSegment.cpp
${SOURCE_PATH}/pathops/SkOpSpan.cpp
${SOURCE_PATH}/pathops/SkPathWriter.cpp
${SOURCE_PATH}/pathops/SkPathOpsCurve.cpp
${SOURCE_PATH}/pathops/SkPathOpsDebug.cpp
${SOURCE_PATH}/pathops/SkIntersections.cpp
${SOURCE_PATH}/pathops/SkDLineIntersection.cpp
${SOURCE_PATH}/pathops/SkDQuadLineIntersection.cpp
${SOURCE_PATH}/pathops/SkDCubicLineIntersection.cpp
${SOURCE_PATH}/pathops/SkDConicLineIntersection.cpp
${SOURCE_PATH}/pathops/SkPathOpsCubic.cpp
${SOURCE_PATH}/pathops/SkPathOpsQuad.cpp
${SOURCE_PATH}/pathops/SkOpCubicHull.cpp
${SOURCE_PATH}/pathops/SkPathOpsLine.cpp
${SOURCE_PATH}/pathops/SkOpCoincidence.cpp
${SOURCE_PATH}/pathops/SkPathOpsRect.cpp
${SOURCE_PATH}/pathops/SkOpAngle.cpp
${SOURCE_PATH}/pathops/SkPathOpsConic.cpp
${SOURCE_PATH}/pathops/SkPathOpsTSect.cpp
${SOURCE_PATH}/pathops/SkOpEdgeBuilder.cpp
${SOURCE_PATH}/pathops/SkReduceOrder.cpp
${SOURCE_PATH}/pathops/SkPathOpsPoint.cpp
)

# opts
file(GLOB OPTS_HEADER ${SOURCE_PATH}/opts/*.h)
set(OPTS_SOURCE 
${SOURCE_PATH}/opts/SkBlitMask_opts_none.cpp
${SOURCE_PATH}/opts/SkBitmapProcState_opts_none.cpp
${SOURCE_PATH}/opts/SkBlitRow_opts_none.cpp
${SOURCE_PATH}/opts/SkOpts_ssse3.cpp
${SOURCE_PATH}/opts/SkOpts_sse41.cpp
${SOURCE_PATH}/opts/SkOpts_sse42.cpp
${SOURCE_PATH}/opts/SkOpts_avx.cpp
)

# jumper
add_definitions(-DSK_JUMPER_USE_ASSEMBLY=0)
file(GLOB JUMPER_HEADER ${SOURCE_PATH}/jumper/*.h)
set(JUMPER_SOURCE 
${SOURCE_PATH}/jumper/SkJumper.cpp
${SOURCE_PATH}/jumper/SkJumper_stages.cpp
)

# fonts
file(GLOB FONTS_HEADER ${SOURCE_PATH}/fonts/*.h)
set(FONTS_SOURCE 
${SOURCE_PATH}/fonts/SkFontMgr_indirect.cpp 
)

#sfnt
file(GLOB SFNT_HEADER ${SOURCE_PATH}/sfnt/*.h)
set(SFNT_SOURCE 
${SOURCE_PATH}/sfnt/SkOTUtils.cpp
${SOURCE_PATH}/sfnt/SkOTTable_name.cpp
)


set(SKIA_HEADER_FILES
${CORE_HEADER}
${PORTS_HEADER}
${SHADERS_HEADER}
${UTILS_HEADER}
${IMAGE_HEADER}
${IMAGES_HEADER}
${PATHOPS_HEADER}
${OPTS_HEADER}
${JUMPER_HEADER}
${FONTS_HEADER}
${SFNT_HEADER}
)

set(SKIA_SOURCE_FILES
${CORE_SOURCE}
${PORTS_SOURCE}
${SHADERS_SOURCE}
${UTILS_SOURCE}
${IMAGE_SOURCE}
${IMAGES_SOURCE}
${PATHOPS_SOURCE}
${OPTS_SOURCE}
${JUMPER_SOURCE}
${FONTS_SOURCE}
${SFNT_SOURCE}
)

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(skia SHARED ${SKIA_SOURCE_FILES} ${SKIA_HEADER_FILES})
target_link_libraries(skia ${SKIA_DEPLIB})
