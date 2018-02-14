
project(SKIA)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/skia/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/jsoncpp/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/imgui/include.cmake)

# dependency

set(SKIA_DEPLIB
jsoncpp
imgui
)

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/include/config)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/include/utils)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/include/core)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/include/gpu)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/include/views)

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/include/private)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/include/gpu/gl)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/include/ports)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/include/pathops)

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/tools)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/tools/timer)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/tools/sk_app)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/tools/flags)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/tools/trace)

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/samplecode)

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/gm)

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/src/core)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/src/gpu)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/src/image)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/src/utils)

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/src/shaders)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/src/sksl)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/src/sfnt)

add_definitions(-DGR_TEST_UTILS)

file(GLOB SKIA_HEADER_FILES
${M3E_SOURCE_DIR}/${EXT_PATH}/skia/tools/sk_app/*.h
)

set(SKIA_SOURCE_FILES
${M3E_SOURCE_DIR}/${EXT_PATH}/skia/tools/sk_app/CommandSet.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/skia/tools/sk_app/GLWindowContext.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/skia/tools/sk_app/Window.cpp

${M3E_SOURCE_DIR}/${EXT_PATH}/skia/tools/viewer/Viewer.cpp

${M3E_SOURCE_DIR}/${EXT_PATH}/skia/src/ports/SkMemory_malloc.cpp

${M3E_SOURCE_DIR}/${EXT_PATH}/skia/src/core/SkString.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/skia/src/core/SkPaint.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/skia/src/core/SkCanvas.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/skia/src/core/SkUtils.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/skia/src/core/SkScalar.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/skia/src/core/SkRect.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/skia/src/core/SkMatrix.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/skia/src/core/SkPaintPriv.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/skia/src/core/SkColorFilter.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/skia/src/core/SkStrokeRec.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/skia/src/core/SkDraw.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/skia/src/core/SkStream.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/skia/src/core/SkTypeface.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/skia/src/core/SkFontDescriptor.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/skia/src/core/SkGraphics.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/skia/src/core/SkGlyphCache.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/skia/src/core/SkMaskGamma.cpp

${M3E_SOURCE_DIR}/${EXT_PATH}/skia/src/gpu/GrBackendSurface.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/skia/src/gpu/GrContext.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/skia/src/gpu/gl/GrGLUtil.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/skia/src/gpu/gl/GrGLExtensions.cpp

${M3E_SOURCE_DIR}/${EXT_PATH}/skia/src/image/SkSurface.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/skia/src/image/SkSurface_Gpu.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/skia/src/image/SkSurface_Raster.cpp
)

if(MSVC)

add_definitions(-DNOMINMAX)

set(SKIA_HEADER_FILES ${SKIA_HEADER_FILES}
${M3E_SOURCE_DIR}/${EXT_PATH}/skia/tools/sk_app/win/Window_win.h
${M3E_SOURCE_DIR}/${EXT_PATH}/skia/tools/sk_app/win/WindowContextFactory_win.h
)

set(SKIA_SOURCE_FILES ${SKIA_SOURCE_FILES}
${M3E_SOURCE_DIR}/${EXT_PATH}/skia/tools/sk_app/win/GLWindowContext_win.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/skia/tools/sk_app/win/main_win.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/skia/tools/sk_app/win/RasterWindowContext_win.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/skia/tools/sk_app/win/Window_win.cpp

${M3E_SOURCE_DIR}/${EXT_PATH}/skia/src/gpu/gl/win/GrGLMakeNativeInterface_win.cpp

${M3E_SOURCE_DIR}/${EXT_PATH}/skia/src/utils/win/SkWGL_win.cpp

${M3E_SOURCE_DIR}/${EXT_PATH}/skia/src/ports/SkDebug_win.cpp
)

elseif(APPLE)

include(${M3E_SOURCE_DIR}/cmake/external/sdl/include.cmake)
set(SKIA_DEPLIB ${SKIA_DEPLIB} sdl)

set(SKIA_HEADER_FILES ${SKIA_HEADER_FILES}
${M3E_SOURCE_DIR}/${EXT_PATH}/skia/tools/sk_app/mac/Window_mac.h
${M3E_SOURCE_DIR}/${EXT_PATH}/skia/tools/sk_app/mac/WindowContextFactory_mac.h
)

set(SKIA_SOURCE_FILES ${SKIA_SOURCE_FILES}
${M3E_SOURCE_DIR}/${EXT_PATH}/skia/tools/sk_app/mac/GLWindowContext_mac.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/skia/tools/sk_app/mac/main_mac.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/skia/tools/sk_app/mac/RasterWindowContext_mac.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/skia/tools/sk_app/mac/Window_mac.cpp

)
endif()

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(skia SHARED ${SKIA_SOURCE_FILES} ${SKIA_HEADER_FILES})
target_link_libraries(skia ${SKIA_DEPLIB})
