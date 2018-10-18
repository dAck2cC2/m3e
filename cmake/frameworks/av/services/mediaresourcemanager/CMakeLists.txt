project(MEDIARESOURCEMANAGER)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/ui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/gui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/EGL/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright/include.cmake)

set( ${PROJECT_NAME}_DEPLIB
log
cutils
utils
binder
media
stagefright
)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/services/mediaresourcemanager )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/services/mediaresourcemanager )

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES  
${HEADER_PATH}/*.h
)

set(${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/ResourceManagerService.cpp
${SOURCE_PATH}/ServiceLog.cpp
${SOURCE_PATH}/main_mediaresourcemanager.cpp
)

# target files
set(LIB_TYPE SHARED)
set(LIB_NAME mediaresourcemanager_default)
ADD_LIB(mediaresourcemanager_default)
