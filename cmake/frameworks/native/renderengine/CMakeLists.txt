project(RENDERENGINE)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/renderengine/include.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/base/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/sync/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/interfaces/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/hidl/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/frameworks/native/ui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/gui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/math/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/include.cmake)


set(${PROJECT_NAME}_DEPLIB
log
cutils
utils
ui
gui
${OPENGL_DEPLIB}
)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/libs/renderengine/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/libs/renderengine )

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES  
${HEADER_PATH}/renderengine/*.h
${HEADER_PATH}/renderengine/private/*.h
)

# source files
set(${PROJECT_NAME}_SOURCE_FILES 
${SOURCE_PATH}/Description.cpp
${SOURCE_PATH}/Mesh.cpp
${SOURCE_PATH}/RenderEngine.cpp
${SOURCE_PATH}/Texture.cpp

${SOURCE_PATH}/gl/GLESRenderEngine.cpp 
${SOURCE_PATH}/gl/GLExtensions.cpp 
${SOURCE_PATH}/gl/GLFramebuffer.cpp 
${SOURCE_PATH}/gl/GLImage.cpp 
${SOURCE_PATH}/gl/ImageManager.cpp 
${SOURCE_PATH}/gl/Program.cpp 
${SOURCE_PATH}/gl/ProgramCache.cpp 
)

# target files
ADD_SHARED_LIB(renderengine)
