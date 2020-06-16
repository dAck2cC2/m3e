
project(MEDIANDK)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/ndk/include.cmake)

# dependency
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/grallocusage/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/hidl/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/interfaces/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/ui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/gui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/drm/drmframework/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/media/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/mediametrics/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright_foundation/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright/include.cmake)

include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/foundation/include/media/stagefright)

set( ${PROJECT_NAME}_DEPLIB
log
cutils
utils
binder
gui
stagefright_foundation
stagefright
grallocusage
media
)

if (MSVC)
    add_definitions(-DEXPORT=__declspec\(dllexport\))
    add_definitions(-DMEDIANDK_API=__declspec\(dllexport\))
else()
    add_definitions(-DEXPORT=__attribute__\(\(visibility\(\"default\"\)\)\))
endif()

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
#${SOURCE_PATH}/NdkMediaDrm.cpp
#${SOURCE_PATH}/NdkImage.cpp
#${SOURCE_PATH}/NdkImageReader.cpp
)

set(LIB_TYPE SHARED)
ADD_LIB(mediandk)

set(ENABLE_TEST "TRUE")
if (ENABLE_TEST)
    add_subdirectory(test)
endif(ENABLE_TEST)
