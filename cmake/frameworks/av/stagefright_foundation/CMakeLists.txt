
project(STAGEFRIGHT_FOUNDATION)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/ui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/gui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright_foundation/include.cmake)

add_definitions(-DANDROID_IMPLEMENTATION=1)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/include/media/stagefright/foundation )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/foundation )

# dependency
set(STAGEFRIGHT_FOUNDATION_DEPLIB
utils
binder
)

# define
if(CYGWIN)
    add_definitions(-D_GNU_SOURCE)
elseif(MSVC)
    add_definitions(-Dstrcasestr=strstr)
    add_definitions(-Dstrncasecmp=_strnicmp)
    add_definitions(-Dstrcasecmp=_stricmp)
endif()

# include files
include_directories(AFTER ${M3E_SOURCE_DIR}/src/av/include)
include_directories(AFTER ${HEADER_PATH})

# header files
file(GLOB STAGEFRIGHT_FOUNDATION_HEADER_FILES ${HEADER_PATH}/*.h)

# source files
#file(GLOB STAGEFRIGHT_FOUNDATION_SOURCE_FILES 
#${M3E_SOURCE_DIR}/src/av/media/libstagefright/foundation/*.cpp
#)
set(STAGEFRIGHT_FOUNDATION_SOURCE_FILES
${SOURCE_PATH}/AAtomizer.cpp
${SOURCE_PATH}/ABitReader.cpp
${SOURCE_PATH}/ABuffer.cpp
${SOURCE_PATH}/ADebug.cpp
${SOURCE_PATH}/AHandler.cpp
${SOURCE_PATH}/AHierarchicalStateMachine.cpp
${SOURCE_PATH}/ALooper.cpp
${SOURCE_PATH}/ALooperRoster.cpp
${SOURCE_PATH}/AMessage.cpp
${SOURCE_PATH}/AString.cpp
${SOURCE_PATH}/AStringUtils.cpp
${SOURCE_PATH}/ColorUtils.cpp
${SOURCE_PATH}/MediaBuffer.cpp
${SOURCE_PATH}/MediaBufferGroup.cpp
${SOURCE_PATH}/MetaData.cpp
${SOURCE_PATH}/ParsedMessage.cpp
${SOURCE_PATH}/base64.cpp
${SOURCE_PATH}/hexdump.cpp
)

if(MSVC)
    set(STAGEFRIGHT_FOUNDATION_SOURCE_FILES ${STAGEFRIGHT_FOUNDATION_SOURCE_FILES}
    ${MSVC_PATH}/vasprintf.c
    )
endif(MSVC)

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(stagefright_foundation SHARED ${STAGEFRIGHT_FOUNDATION_SOURCE_FILES} ${STAGEFRIGHT_FOUNDATION_HEADER_FILES})
target_link_libraries(stagefright_foundation ${STAGEFRIGHT_FOUNDATION_DEPLIB})
