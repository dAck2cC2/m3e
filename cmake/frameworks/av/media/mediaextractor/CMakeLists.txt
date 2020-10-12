project(MEDIAEXTRACTOR)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/mediaextractor/include.cmake)

# dependency
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright_foundation/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/media/include.cmake)

if(MSVC)
    add_definitions(-D__unused= )
    add_definitions(-Dstrncasecmp=_strnicmp)
    add_definitions(-Dstrcasecmp=_stricmp)
endif()

set( ${PROJECT_NAME}_DEPLIB
log
cutils
utils
binder
stagefright_foundation
)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libmediaextractor/include/media )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libmediaextractor )

file(GLOB ${PROJECT_NAME}_HEADER_FILES  
${HEADER_PATH}/*.h
${HEADER_PATH}/stagefright/*.h
)

set(${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/DataSourceBase.cpp 
${SOURCE_PATH}/MediaBuffer.cpp 
${SOURCE_PATH}/MediaBufferBase.cpp 
${SOURCE_PATH}/MediaBufferGroup.cpp 
${SOURCE_PATH}/MediaSource.cpp 
${SOURCE_PATH}/MediaTrack.cpp 
${SOURCE_PATH}/MediaExtractor.cpp 
${SOURCE_PATH}/MetaData.cpp 
${SOURCE_PATH}/MetaDataBase.cpp 
${SOURCE_PATH}/VorbisComment.cpp 
)

# target files
set(LIB_TYPE SHARED)
ADD_LIB(mediaextractor)