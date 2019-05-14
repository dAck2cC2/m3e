
project(HWCOMPOSER_DEFAULT)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/EGL/include.cmake)

set( ${PROJECT_NAME}_DEPLIB
log
cutils
${OPENGL_DEPLIB}
)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/hardware/libhardware/modules/hwcomposer )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/hardware/libhardware/modules/hwcomposer )

list(APPEND ${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/hwcomposer.cpp
)

# target files
set(LIB_TYPE SHARED)
ADD_LIB(hwcomposer_default)
