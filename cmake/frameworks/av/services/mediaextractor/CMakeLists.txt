project(MEDIAEXTRACTOR)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/media/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/mediametrics/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright_foundation/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/drm/drmframework/include.cmake)

set( ${PROJECT_NAME}_DEPLIB
log
utils
binder
media
stagefright
)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/services/mediaextractor )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/services/mediaextractor )

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES  
${HEADER_PATH}/*.h
)

set(${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/MediaExtractorService.cpp
${SOURCE_PATH}/main_mediaextractorservice.cpp
)

# target files
set(LIB_TYPE SHARED)
set(LIB_NAME mediaextractor_default)
ADD_LIB(mediaextractor_default)
