project(MEDIACODEC)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/hidl/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/interfaces/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/ui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/gui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/media_plugin/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/EGL/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright_omx/include.cmake)


set( ${PROJECT_NAME}_DEPLIB
log
cutils
utils
binder
media
stagefright_omx
)

include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/native/include/media/openmax)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/services/mediacodec )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/services/mediacodec )

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES  
${HEADER_PATH}/*.h
)

set(${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/MediaCodecService.cpp
${SOURCE_PATH}/main_mediacodecservice.cpp
)

# target files
set(LIB_TYPE SHARED)
set(LIB_NAME mediacodecservice_default)
ADD_LIB(mediacodecservice_default)
