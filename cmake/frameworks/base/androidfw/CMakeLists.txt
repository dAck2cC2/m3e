
project(ANDROIDFW)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/base/androidfw/include.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/base/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/ziparchive/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/gui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/zlib/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/base/android/include.cmake)

set(ANDROIDFW_DEPLIB
cutils
utils
base
binder
log
gui
zlib
ziparchive
)

if(MSVC)
    add_definitions(-DNOMINMAX=1)
    add_definitions(-Dstrcasecmp=strcmp)

    include(${MSVC_INCLUDE})
    list(APPEND ANDROIDFW_DEPLIB ${LIB_MSVC_WRAP})
endif(MSVC)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/base/libs/androidfw/include/androidfw )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/base/libs/androidfw )

file(GLOB ANDROIDFW_HEADER_FILES
${HEADER_PATH}/*.h
)

set(ANDROIDFW_SOURCE_FILES
${SOURCE_PATH}/ApkAssets.cpp
${SOURCE_PATH}/Asset.cpp
${SOURCE_PATH}/AssetDir.cpp
${SOURCE_PATH}/AssetManager.cpp
${SOURCE_PATH}/AssetManager2.cpp
${SOURCE_PATH}/ChunkIterator.cpp
${SOURCE_PATH}/Idmap.cpp
${SOURCE_PATH}/LocaleData.cpp
${SOURCE_PATH}/LoadedArsc.cpp
${SOURCE_PATH}/misc.cpp
${SOURCE_PATH}/ObbFile.cpp
${SOURCE_PATH}/ResourceTypes.cpp
${SOURCE_PATH}/ResourceUtils.cpp
${SOURCE_PATH}/StreamingZipInflater.cpp
${SOURCE_PATH}/TypeWrappers.cpp
${SOURCE_PATH}/Util.cpp
${SOURCE_PATH}/ZipFileRO.cpp
${SOURCE_PATH}/ZipUtils.cpp
)


set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(androidfw SHARED ${ANDROIDFW_SOURCE_FILES} ${ANDROIDFW_HEADER_FILES})
target_link_libraries(androidfw ${ANDROIDFW_DEPLIB})
