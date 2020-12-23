project(BINDERTHREADSTATE)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binderthreadstate/include.cmake)

# dependency
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/base/include.cmake)

set(${PROJECT_NAME}_DEPLIB
log
utils
)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/libs/binderthreadstate/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/libs/binderthreadstate )

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES  
${HEADER_PATH}/binderthreadstate/*.h
)

# source files
file(GLOB ${PROJECT_NAME}_SOURCE_FILES 
${SOURCE_PATH}/IPCThreadStateBase.cpp
)

# target files
ADD_SHARED_LIB(binderthreadstate)
