project(INTERFACES)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/interfaces/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/base/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/hidl/include.cmake)

set(${PROJECT_NAME}_DEPLIB
log
)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/hardware/interfaces/ )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/hardware/interfaces/ )


# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES
${HEADER_PATH}/configstore/include/android/hardware/configstore/1.0/*.h
${HEADER_PATH}/graphics/allocator/include/android/hardware/graphics/allocator/2.0/*.h
${HEADER_PATH}/graphics/bufferqueue/include/android/hardware/graphics/bufferqueue/1.0/*.h
${HEADER_PATH}/graphics/common/include/android/hardware/graphics/common/1.0/*.h
${HEADER_PATH}/graphics/mapper/include/android/hardware/graphics/mapper/2.0/*.h
)

# source files
set(${PROJECT_NAME}_SOURCE_FILES 
${HEADER_PATH}/configstore/utils/ConfigStoreUtils.cpp
)

ADD_LIB(interfaces)
