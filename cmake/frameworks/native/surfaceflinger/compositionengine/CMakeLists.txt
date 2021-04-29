project(COMPOSITIONENGINE)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/surfaceflinger/compositionengine/include.cmake)

# dependency
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/base/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/sync/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/hardware/interfaces/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/hidl/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/frameworks/native/ui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/gui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/math/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/renderengine/include.cmake)

include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/native/services/surfaceflinger/)


set( ${PROJECT_NAME}_DEPLIB
log
cutils
utils
gui
)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/services/surfaceflinger/CompositionEngine/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/services/surfaceflinger/CompositionEngine/src)

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES  
${HEADER_PATH}/compositionengine/*.h
${HEADER_PATH}/compositionengine/impl/*.h
)

# source files
set(${PROJECT_NAME}_SOURCE_FILES 
${SOURCE_PATH}/CompositionEngine.cpp 
${SOURCE_PATH}/Display.cpp 
${SOURCE_PATH}/DisplayColorProfile.cpp 
${SOURCE_PATH}/DisplaySurface.cpp 
${SOURCE_PATH}/DumpHelpers.cpp 
${SOURCE_PATH}/HwcBufferCache.cpp 
${SOURCE_PATH}/Layer.cpp 
${SOURCE_PATH}/LayerCompositionState.cpp 
${SOURCE_PATH}/Output.cpp 
${SOURCE_PATH}/OutputCompositionState.cpp 
${SOURCE_PATH}/OutputLayer.cpp 
${SOURCE_PATH}/OutputLayerCompositionState.cpp 
${SOURCE_PATH}/RenderSurface.cpp 
)

# target files
ADD_SHARED_LIB(compositionengine)
