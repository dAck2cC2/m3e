project(STAGEFRIGHT_WEBM)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright/include.cmake)

add_definitions(-D__STDINT_LIMITS)

set(${PROJECT_NAME}_DEPLIB
log
utils
media
stagefright_foundation
)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/webm )

file(GLOB ${PROJECT_NAME}_HEADER_FILES
${SOURCE_PATH}/*.h
)

# source files
set(${PROJECT_NAME}_SOURCE_FILES 
${SOURCE_PATH}/EbmlUtil.cpp
${SOURCE_PATH}/WebmElement.cpp
${SOURCE_PATH}/WebmFrame.cpp
${SOURCE_PATH}/WebmFrameThread.cpp
${SOURCE_PATH}/WebmWriter.cpp
)

# target files
ADD_LIB(stagefright_webm)
