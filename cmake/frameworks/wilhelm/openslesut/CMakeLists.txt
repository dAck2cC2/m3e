project(OPENSLESUT)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/wilhelm/openslesut/include.cmake)

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

add_definitions(-DSL_API= )
add_definitions(-DXA_API= )
add_definitions(-DUNDEBUG)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/wilhelm/src/ut/ )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/wilhelm/src/ )

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES  
${HEADER_PATH}/*.h
)

set(${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/assert.cpp
${SOURCE_PATH}/ut/OpenSLESUT.c
${SOURCE_PATH}/ut/slesutResult.c
)

set(LIB_TYPE STATIC)
ADD_LIB(OpenSLESUT)
