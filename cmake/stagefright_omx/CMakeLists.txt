
project(STAGEFRIGHT_OMX)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/misc/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/stagefright/include.cmake)

# dependency
set(STAGEFRIGHT_OMX_DEPLIB
utils
misc
media
stagefright_foundation
)

# include
include_directories(AFTER ${M3E_SOURCE_DIR}/src/av/media/libstagefright)

# header files
file(GLOB STAGEFRIGHT_OMX_HEADER_FILES 
${M3E_SOURCE_DIR}/src/av/media/libstagefright/omx/*.h 
)

# source files
#file(GLOB STAGEFRIGHT_OMX_SOURCE_FILES 
#${M3E_SOURCE_DIR}/src/av/media/libstagefright/omx/*.cpp
#)
set(STAGEFRIGHT_OMX_SOURCE_FILES
${M3E_SOURCE_DIR}/src/av/media/libstagefright/omx/OMX.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/omx/OMXNodeInstance.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/omx/GraphicBufferSource.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/omx/FrameDropper.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/omx/OMXUtils.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/omx/OMXMaster.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/omx/SoftOMXPlugin.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/omx/SoftOMXComponent.cpp
)

# target files
set(STAGEFRIGHT_OMX_DEP ${STAGEFRIGHT_OMX_DEPLIB})
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(stagefright_omx SHARED ${STAGEFRIGHT_OMX_SOURCE_FILES} ${STAGEFRIGHT_OMX_HEADER_FILES})
target_link_libraries(stagefright_omx ${STAGEFRIGHT_OMX_DEPLIB})
