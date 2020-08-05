project(FMQ)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/fmq/include.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/base/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/hidl/include.cmake)


set(${PROJECT_NAME}_DEPLIB
log
cutils
utils
base
)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/system/libfmq/include/fmq )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/system/libfmq )

file(GLOB ${PROJECT_NAME}_HEADER_FILES 
${HEADER_PATH}/*.h 
)

set(${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/EventFlag.cpp
${SOURCE_PATH}/FmqInternal.cpp
)

# target files
set(LIB_TYPE SHARED)
ADD_LIB(fmq)
