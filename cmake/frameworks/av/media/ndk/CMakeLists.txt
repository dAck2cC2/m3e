
project(MEDIANDK)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/ndk/include.cmake)

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
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/EGL/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright_foundation/include.cmake)

set( ${PROJECT_NAME}_DEPLIB
log
cutils
utils
binder
)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/ndk/include/media )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/ndk )

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES  
${HEADER_PATH}/*.h
)

set(${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/NdkMediaCodec.cpp
${SOURCE_PATH}/NdkMediaCrypto.cpp
${SOURCE_PATH}/NdkMediaExtractor.cpp
${SOURCE_PATH}/NdkMediaFormat.cpp
${SOURCE_PATH}/NdkMediaMuxer.cpp
${SOURCE_PATH}/NdkMediaDrm.cpp
${SOURCE_PATH}/NdkImage.cpp
${SOURCE_PATH}/NdkImageReader.cpp
)

set(LIB_TYPE SHARED)
ADD_LIB(mediandk)