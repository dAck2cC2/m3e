
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


if (ENABLE_LEGACY)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/include/views)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/include/gpu/gl)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/src/gpu)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/src/sksl)
endif(ENABLE_LEGACY)

# core
add_definitions(-DSK_SUPPORT_GPU=0)

file(GLOB CORE_HEADER
${HEADER_PATH}/core/*.h
)

file(GLOB CORE_SOURCE
${SOURCE_PATH}/core/*.*
)

# port
if (APPLE)
set(PORTS_HEADER
)

set(PORTS_SOURCE
${SOURCE_PATH}/ports/SkOSFile_posix.cpp
${SOURCE_PATH}/ports/SkOSFile_stdio.cpp
${SOURCE_PATH}/ports/SkDebug_stdio.cpp
)

else()
set(PORTS_HEADER )
set(PORTS_SOURCE )
endif()

set(PORTS_SOURCE ${PORTS_SOURCE}
${SOURCE_PATH}/ports/SkMemory_malloc.cpp
${SOURCE_PATH}/ports/SkGlobalInitialization_none.cpp
#${SOURCE_PATH}/ports/SkGlobalInitialization_default.cpp
)

# shaders
set(SHADERS_HEADER )
set(SHADERS_SOURCE 
${SOURCE_PATH}/shaders/SkImageShader.cpp
${SOURCE_PATH}/shaders/SkShader.cpp
${SOURCE_PATH}/shaders/SkColorShader.cpp
${SOURCE_PATH}/shaders/SkComposeShader.cpp
)

# utils
set(UTILS_HEADER )
set(UTILS_SOURCE 
${SOURCE_PATH}/utils/SkMatrix22.cpp
${SOURCE_PATH}/utils/SkShadowUtils.cpp
${SOURCE_PATH}/utils/SkNWayCanvas.cpp
${SOURCE_PATH}/utils/SkPatchUtils.cpp
${SOURCE_PATH}/utils/SkEventTracer.cpp
)

# image
set(IMAGE_HEADER )
set(IMAGE_SOURCE 
${SOURCE_PATH}/image/SkImage_Raster.cpp
${SOURCE_PATH}/image/SkSurface_Raster.cpp
${SOURCE_PATH}/image/SkImage.cpp
${SOURCE_PATH}/image/SkSurface.cpp
)

# images
set(IMAGES_HEADER )
set(IMAGES_SOURCE 
${SOURCE_PATH}/images/SkImageEncoder.cpp
) 


# pathops
set(PATHOPS_HEADER )
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
)

# opts
set(OPTS_HEADER )
set(OPTS_SOURCE 
${SOURCE_PATH}/opts/SkBlitMask_opts_none.cpp
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
)

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(skia SHARED ${SKIA_SOURCE_FILES} ${SKIA_HEADER_FILES})
target_link_libraries(skia ${SKIA_DEPLIB})
