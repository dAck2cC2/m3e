
project(STAGEFRIGHT)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/utils.cmake)
include(${M3E_SOURCE_DIR}/cmake/misc.cmake)
include(${M3E_SOURCE_DIR}/cmake/media.cmake)

set(STAGEFRIGHT_DEPLIB
utils
misc
media
stagefright_foundation
)

# dependency
set(STAGEFRIGHT_DEP 
${STAGEFRIGHT_DEPLIB}
)

# define
if(APPLE)
add_definitions(-DO_LARGEFILE=0)
add_definitions(-Dlseek64=lseek)
endif()

# include files
include_directories(AFTER ${M3E_SOURCE_DIR}/src/av/media/libstagefright)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/av/media/libstagefright/include)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/av/include)

# header files
file(GLOB STAGEFRIGHT_HEADER_FILES 
${M3E_SOURCE_DIR}/src/av/include/media/stagefright/*.h 
${M3E_SOURCE_DIR}/src/av/media/libstagefright/include/*.h 
)

# source files
#file(GLOB STAGEFRIGHT_SOURCE_FILES 
#${M3E_SOURCE_DIR}/src/av/media/libstagefright/*.cpp
#)
set(STAGEFRIGHT_SOURCE_FILES
${M3E_SOURCE_DIR}/src/av/media/libstagefright/avc_utils.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/CallbackDataSource.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/DataSource.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/DataURISource.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/DRMExtractor.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/ESDS.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/FileSource.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/HevcUtils.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/http/MediaHTTP.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/HTTPBase.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/MediaDefs.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/NuCachedSource2.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/Utils.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/WAVExtractor.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/MediaSource.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/MediaExtractor_legacy.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/AudioPlayer.cpp
)

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(stagefright SHARED ${STAGEFRIGHT_SOURCE_FILES} ${STAGEFRIGHT_HEADER_FILES})
target_link_libraries(stagefright ${STAGEFRIGHT_DEPLIB})
