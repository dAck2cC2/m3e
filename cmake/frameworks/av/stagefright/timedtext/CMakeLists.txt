project(STAGEFRIGHT_TIMEDTEXT)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright/include.cmake)

set(${PROJECT_NAME}_DEPLIB
binder
stagefright
)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/timedtext )

file(GLOB ${PROJECT_NAME}_HEADER_FILES
${SOURCE_PATH}/*.h
)

# source files
set(${PROJECT_NAME}_SOURCE_FILES 
${SOURCE_PATH}/TextDescriptions.cpp
)

# target files
ADD_LIB(stagefright_timedtext)
