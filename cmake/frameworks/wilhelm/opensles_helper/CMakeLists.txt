project(OPENSLES_HELPER)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

# dependency
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/frameworks/wilhelm/opensles/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/wilhelm/openmaxal/include.cmake)

set( ${PROJECT_NAME}_DEPLIB
log
cutils
utils
)

include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/wilhelm/src/autogen/)
#add_definitions(-DUSE_DESIGNATED_INITIALIZERS)

add_definitions(-DANDROID)
add_definitions(-UNDEBUG)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/wilhelm/src/ )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/wilhelm/src/ )

set(${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/assert.cpp
${SOURCE_PATH}/MPH_to.c
${SOURCE_PATH}/handlers.c
)

if (APPLE)
    set(LIB_TYPE STATIC)
endif()
ADD_LIB(opensles_helper)
