
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

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/base/include/androidfw )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/base/androidfw )

file(GLOB ANDROIDFW_HEADER_FILES
${HEADER_PATH}/*.h
)

set(ANDROIDFW_SOURCE_FILES
${SOURCE_PATH}/Asset.cpp
${SOURCE_PATH}/AssetDir.cpp
${SOURCE_PATH}/AssetManager.cpp
${SOURCE_PATH}/LocaleData.cpp
${SOURCE_PATH}/misc.cpp
${SOURCE_PATH}/ObbFile.cpp
${SOURCE_PATH}/ResourceTypes.cpp
${SOURCE_PATH}/StreamingZipInflater.cpp
${SOURCE_PATH}/TypeWrappers.cpp
${SOURCE_PATH}/ZipFileRO.cpp
${SOURCE_PATH}/ZipUtils.cpp
)

if(MSVC)
    add_definitions(-DNOMINMAX=1)
    add_definitions(-Dstrcasecmp=strcmp)

    include_directories(AFTER ${MSVC_PATH})

    list(APPEND ANDROIDFW_HEADER_FILES
    ${MSVC_PATH}/dirent.h
    )
endif(MSVC)


set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(androidfw SHARED ${ANDROIDFW_SOURCE_FILES} ${ANDROIDFW_HEADER_FILES})
target_link_libraries(androidfw ${ANDROIDFW_DEPLIB})
