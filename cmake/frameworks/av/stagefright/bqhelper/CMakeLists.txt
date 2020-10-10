project(STAGEFRIGHT_BUFFERQUEUE_HELPER)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright/bqhelper/include.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)

set(${PROJECT_NAME}_DEPLIB
log
utils
gui
stagefright_foundation
)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/bqhelper/include/media/stagefright/bqhelper )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/bqhelper )

file(GLOB ${PROJECT_NAME}_HEADER_FILES
${SOURCE_PATH}/*.h
)

# source files
set(${PROJECT_NAME}_SOURCE_FILES 
${SOURCE_PATH}/Conversion.cpp
${SOURCE_PATH}/FrameDropper.cpp
${SOURCE_PATH}/GraphicBufferSource.cpp
${SOURCE_PATH}/WProducerListener.cpp
)

ADD_LIB(stagefright_bufferqueue_helper)
