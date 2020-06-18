project(VNDKSUPPORT)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/vndksupport/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)

set(${PROJECT_NAME}_DEPLIB log)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/system/core/libvndksupport/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/system/core/libvndksupport/ )

include_directories(AFTER ${M3E_SOURCE_DIR}/src/system/core/libvndksupport/include/vndksupport)

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES ${HEADER_PATH}/vndksupport/*.h)

# source files
file(GLOB ${PROJECT_NAME}_SOURCE_FILES ${SOURCE_PATH}/linker.c)

ADD_LIB(vndksupport)
