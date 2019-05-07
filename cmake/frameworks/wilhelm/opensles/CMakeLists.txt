project(OPENSLES)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/wilhelm/opensles/include.cmake)

# dependency
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/wilhelm/wilhelm/include.cmake)

set( ${PROJECT_NAME}_DEPLIB
log
wilhelm
)

if(MSVC)
    add_definitions(-DSL_API=__declspec\(dllexport\))
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/wilhelm/include/SLES/ )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/wilhelm/src/ )

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES  
${HEADER_PATH}/*.h
)

set(${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/sl_entry.cpp
${SOURCE_PATH}/sl_iid.cpp
${SOURCE_PATH}/assert.cpp
)

set(LIB_TYPE SHARED)
ADD_LIB(OpenSLES)
