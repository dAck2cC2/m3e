
project(SKIA)

if(NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH}/skia)
	message(STATUS "Download\tskia")
	exec_program("git clone https://skia.googlesource.com/skia.git" ${M3E_SOURCE_DIR}/${EXT_PATH})
	exec_program("git checkout chrome/m65" ${M3E_SOURCE_DIR}/${EXT_PATH}/skia)
	if (MSVC)
		exec_program("git apply ${M3E_SOURCE_DIR}/src/${EXT_PATH}/skia/skia.patch" ${M3E_SOURCE_DIR}/${EXT_PATH}/skia)
	endif(MSVC)
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/src )

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/skia/include.cmake)
#include(${M3E_SOURCE_DIR}/cmake/external/jsoncpp/include.cmake)
#include(${M3E_SOURCE_DIR}/cmake/external/imgui/include.cmake)

# All supported options ###############################################
OPTION( SKIA_ENABLE_SKSL
  "Set to ON to enable SKSL"
  ON
)

OPTION( SKIA_ENABLE_EFFECTS
  "Set to ON to enable effects"
  ON
)

OPTION( SKIA_ENABLE_GPU_GL
  "Set to ON to enable OpenGL for GPU"
  ON
)

OPTION( SKIA_ENABLE_VIEWS
  "Set to ON to enable views"
  ON
)

if (MSVC)
	add_definitions(-DSKIA_IMPLEMENTATION)
endif (MSVC)

# dependency

set(SKIA_DEPLIB
#jsoncpp
#imgui
)

#include_directories(AFTER ${HEADER_PATH}/config)
#include_directories(AFTER ${HEADER_PATH}/core)
include_directories(AFTER ${HEADER_PATH}/codec)
include_directories(AFTER ${HEADER_PATH}/effects)
#include_directories(AFTER ${HEADER_PATH}/utils)
#include_directories(AFTER ${HEADER_PATH}/gpu)
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

# core ###############################################
file(GLOB CORE_HEADER ${HEADER_PATH}/core/*.h)
file(GLOB CORE_SOURCE ${SOURCE_PATH}/core/*.*)
source_group(core FILES ${CORE_HEADER} ${CORE_SOURCE})

# port ###############################################
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
    #add_definitions(-DDWRITE_RENDERING_MODE_GDI_CLASSIC=DWRITE_RENDERING_MODE_CLEARTYPE_GDI_CLASSIC)
    #add_definitions(-DDWRITE_RENDERING_MODE_NATURAL=DWRITE_RENDERING_MODE_CLEARTYPE_NATURAL)
    #add_definitions(-DDWRITE_RENDERING_MODE_NATURAL_SYMMETRIC=DWRITE_RENDERING_MODE_CLEARTYPE_NATURAL_SYMMETRIC)
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

source_group(ports FILES ${PORTS_HEADER} ${PORTS_SOURCE})

# shaders ###############################################
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
${SOURCE_PATH}/shaders/gradients/SkGradientShader.cpp
${SOURCE_PATH}/shaders/gradients/SkTwoPointConicalGradient.cpp
${SOURCE_PATH}/shaders/gradients/SkSweepGradient.cpp
${SOURCE_PATH}/shaders/gradients/SkRadialGradient.cpp
${SOURCE_PATH}/shaders/gradients/SkGradientBitmapCache.cpp
${SOURCE_PATH}/shaders/gradients/SkLinearGradient.cpp
${SOURCE_PATH}/shaders/gradients/Sk4fLinearGradient.cpp
${SOURCE_PATH}/shaders/gradients/Sk4fGradientBase.cpp
)

if (SKIA_ENABLE_GPU_GL)
    set(SHADERS_SOURCE ${SHADERS_SOURCE}
    ${SOURCE_PATH}/shaders/gradients/SkTwoPointConicalGradient_gpu.cpp
    )
endif (SKIA_ENABLE_GPU_GL)

source_group(shaders FILES ${SHADERS_HEADER} ${SHADERS_SOURCE})

# utils ###############################################
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

if (SKIA_ENABLE_GPU_GL)
    set(UTILS_SOURCE ${UTILS_SOURCE}
    ${SOURCE_PATH}/utils/SkDashPath.cpp
    ${SOURCE_PATH}/utils/SkJSONWriter.cpp
    )
endif (SKIA_ENABLE_GPU_GL)

source_group(utils FILES ${UTILS_HEADER} ${UTILS_SOURCE})

# image ###############################################
file(GLOB IMAGE_HEADER ${SOURCE_PATH}/image/*.h)
set(IMAGE_SOURCE 
${SOURCE_PATH}/image/SkImage_Raster.cpp
${SOURCE_PATH}/image/SkSurface_Raster.cpp
${SOURCE_PATH}/image/SkImage.cpp
${SOURCE_PATH}/image/SkSurface.cpp
${SOURCE_PATH}/image/SkImage_Lazy.cpp
)

if (SKIA_ENABLE_GPU_GL)
    set(IMAGE_SOURCE ${IMAGE_SOURCE}
    ${SOURCE_PATH}/image/SkImage_Gpu.cpp
    ${SOURCE_PATH}/image/SkSurface_Gpu.cpp
    )
endif (SKIA_ENABLE_GPU_GL)

source_group(image FILES ${IMAGE_HEADER} ${IMAGE_SOURCE})

# images ###############################################
file(GLOB IMAGES_HEADER ${SOURCE_PATH}/images/*.h)
set(IMAGES_SOURCE 
${SOURCE_PATH}/images/SkImageEncoder.cpp
) 

source_group(images FILES ${IMAGES_HEADER} ${IMAGES_SOURCE})

# pathops ###############################################
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

if (SKIA_ENABLE_GPU_GL)
    set(PATHOPS_SOURCE ${PATHOPS_SOURCE}
    ${SOURCE_PATH}/pathops/SkPathOpsSimplify.cpp
    )
endif (SKIA_ENABLE_GPU_GL)

source_group(pathops FILES ${PATHOPS_HEADER} ${PATHOPS_SOURCE})

# opts ###############################################
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

source_group(opts FILES ${OPTS_HEADER} ${OPTS_SOURCE})

# jumper ###############################################
add_definitions(-DSK_JUMPER_USE_ASSEMBLY=0)
file(GLOB JUMPER_HEADER ${SOURCE_PATH}/jumper/*.h)
set(JUMPER_SOURCE 
${SOURCE_PATH}/jumper/SkJumper.cpp
${SOURCE_PATH}/jumper/SkJumper_stages.cpp
)

source_group(opts FILES ${JUMPER_HEADER} ${JUMPER_SOURCE})

# fonts ###############################################
file(GLOB FONTS_HEADER ${SOURCE_PATH}/fonts/*.h)
set(FONTS_SOURCE 
${SOURCE_PATH}/fonts/SkFontMgr_indirect.cpp 
)

source_group(fonts FILES ${FONTS_HEADER} ${FONTS_SOURCE})

# sfnt ###############################################
file(GLOB SFNT_HEADER ${SOURCE_PATH}/sfnt/*.h)
file(GLOB SFNT_SOURCE ${SOURCE_PATH}/sfnt/*.cpp)
#set(SFNT_SOURCE ${SOURCE_PATH}/sfnt/SkOTUtils.cpp ${SOURCE_PATH}/sfnt/SkOTTable_name.cpp)

source_group(sfnt FILES ${SFNT_HEADER} ${SFNT_SOURCE})

# gpu ###############################################
if (SKIA_ENABLE_GPU_GL)
    add_definitions(-DSK_SUPPORT_GPU=1)

    include_directories(AFTER ${SOURCE_PATH}/gpu)
    include_directories(AFTER ${SOURCE_PATH}/sksl)
    file(GLOB GPU_HEADER ${HEADER_PATH}/gpu/*.h)
    file(GLOB GPU_SOURCE ${SOURCE_PATH}/gpu/*.*)

    file(GLOB GPU_SRC_OPS ${SOURCE_PATH}/gpu/ops/*.*)
    list(APPEND GPU_SOURCE ${GPU_SRC_OPS})

    file(GLOB GPU_SRC_TEXT ${SOURCE_PATH}/gpu/text/*.*)
    list(APPEND GPU_SOURCE ${GPU_SRC_TEXT})

    file(GLOB GPU_SRC_EFFECTS ${SOURCE_PATH}/gpu/effects/*.cpp)
    list(APPEND GPU_SOURCE ${GPU_SRC_EFFECTS})

    file(GLOB GPU_SRC_CCPR ${SOURCE_PATH}/gpu/ccpr/*.*)
    list(APPEND GPU_SOURCE ${GPU_SRC_CCPR})

    file(GLOB GPU_SRC_DDL ${SOURCE_PATH}/gpu/ddl/*.*)
    list(APPEND GPU_SOURCE ${GPU_SRC_DDL})    

    file(GLOB GPU_SRC_MOCK ${SOURCE_PATH}/gpu/mock/*.*)
    list(APPEND GPU_SOURCE ${GPU_SRC_MOCK})    
    
    # OpenGL #############################
    include_directories(AFTER ${HEADER_PATH}/gpu/gl)

    find_package(OpenGL REQUIRED)
    list(APPEND SKIA_DEPLIB ${OPENGL_gl_LIBRARY})
    include_directories(${OPENGL_INCLUDE_DIR})

    file(GLOB GPU_SRC_GL ${SOURCE_PATH}/gpu/gl/*.*)
    list(APPEND GPU_SOURCE ${GPU_SRC_GL})

    file(GLOB GPU_SRC_GL_BUILDERS ${SOURCE_PATH}/gpu/gl/builders/*.*)
    list(APPEND GPU_SOURCE ${GPU_SRC_GL_BUILDERS})

    file(GLOB GPU_SRC_GLSL ${SOURCE_PATH}/gpu/glsl/*.*)
    list(APPEND GPU_SOURCE ${GPU_SRC_GLSL})
    
    if (APPLE)
        list(REMOVE_ITEM GPU_SOURCE ${SOURCE_PATH}/gpu/gl/GrGLMakeNativeInterface_none.cpp)
        set(GPU_SOURCE ${GPU_SOURCE}
        ${SOURCE_PATH}/gpu/gl/mac/GrGLMakeNativeInterface_mac.cpp
        )
    elseif (MSVC)
        list(REMOVE_ITEM GPU_SOURCE ${SOURCE_PATH}/gpu/gl/GrGLMakeNativeInterface_none.cpp)
        set(GPU_SOURCE ${GPU_SOURCE}
        ${SOURCE_PATH}/gpu/gl/win/GrGLMakeNativeInterface_win.cpp
        )
    endif ()
else (SKIA_ENABLE_GPU_GL)
    add_definitions(-DSK_SUPPORT_GPU=0)
    set(GPU_HEADER )
    set(GPU_SOURCE )
endif (SKIA_ENABLE_GPU_GL)

source_group(gpu FILES ${GPU_HEADER} ${GPU_SOURCE})

# sksl ###############################################
if (SKIA_ENABLE_SKSL)
    file(GLOB SKSL_HEADER ${SOURCE_PATH}/sksl/*.h)
    file(GLOB SKSL_SOURCE ${SOURCE_PATH}/sksl/*.cpp)

    file(GLOB SKSL_SRC_IR ${SOURCE_PATH}/sksl/ir/*.*)
    list(APPEND SKSL_SOURCE ${SKSL_SRC_IR})

else (SKIA_ENABLE_SKSL)
    set(SKSL_HEADER )
    set(SKSL_SOURCE )
endif (SKIA_ENABLE_SKSL)

source_group(sksl FILES ${SKSL_HEADER} ${SKSL_SOURCE})

# effects ###############################################
if (SKIA_ENABLE_EFFECTS)
    file(GLOB EFFECTS_HEADER ${HEADER_PATH}/effects/*.h)
    file(GLOB EFFECTS_SOURCE ${SOURCE_PATH}/effects/*.cpp)
else (SKIA_ENABLE_EFFECTS)
    set(EFFECTS_HEADER )
    set(EFFECTS_SOURCE )
endif (SKIA_ENABLE_EFFECTS)

source_group(effects FILES ${EFFECTS_HEADER} ${EFFECTS_SOURCE})

# views ###############################################
if (SKIA_ENABLE_VIEWS)
    include_directories(AFTER ${HEADER_PATH}/views)
    file(GLOB VIEWS_HEADER ${HEADER_PATH}/views/*.h)
    file(GLOB VIEWS_SOURCE ${SOURCE_PATH}/views/*.cpp)
else (SKIA_ENABLE_VIEWS)
    set(VIEWS_HEADER )
    set(VIEWS_SOURCE )
endif (SKIA_ENABLE_VIEWS)

source_group(views FILES ${VIEWS_HEADER} ${VIEWS_SOURCE})

# build library of skia ###############################################
set(SKIA_HEADER_FILES
# core
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

# optional
${SKSL_HEADER}
${GPU_HEADER}
${EFFECTS_HEADER}
${VIEWS_HEADER}
)

set(SKIA_SOURCE_FILES
# core
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

# optional
${SKSL_SOURCE}
${GPU_SOURCE}
${EFFECTS_SOURCE}
${VIEWS_SOURCE}
)

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(skia SHARED ${SKIA_SOURCE_FILES} ${SKIA_HEADER_FILES})
target_link_libraries(skia ${SKIA_DEPLIB})
