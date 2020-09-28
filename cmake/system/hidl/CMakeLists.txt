project(HIDL)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/hidl/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/base/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/interfaces/include.cmake)

set(${PROJECT_NAME}_DEPLIB
log
cutils
utils
base
interfaces
)

if(MSVC)
    add_definitions(-DNOMINMAX)
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/system/libhidl/ )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/system/libhidl/ )

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES
${HEADER_PATH}/base/include/hidl/*.h
${HEADER_PATH}/libhidlmemory/include/hidlmemory/*.h
${HEADER_PATH}/transport/include/hidl/*.h
)

# source files
set(${PROJECT_NAME}_SOURCE_FILES 
${SOURCE_PATH}/base/HidlInternal.cpp 
${SOURCE_PATH}/base/HidlSupport.cpp 
${SOURCE_PATH}/base/Status.cpp 
#${SOURCE_PATH}/transport/ServiceManagement.cpp 
${SOURCE_PATH}/transport/token/1.0/utils/HybridInterface.cpp
${SOURCE_PATH}/libhidlmemory/mapping.cpp
)

ADD_LIB(hidl)
