project(HIDL)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/hidl/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/base/include.cmake)

set(${PROJECT_NAME}_DEPLIB
log
)

if(MSVC)
    add_definitions(-DNOMINMAX)
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/system/libhidl/ )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/system/libhidl/ )

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES
${HEADER_PATH}/base/include/*.h
${HEADER_PATH}/transport/include/*.h
${HEADER_PATH}/transport/base/android/hidl/base/1.0/*.h
${HEADER_PATH}/transport/manager/android/hidl/manager/1.0/*.h
)

# source files
set(${PROJECT_NAME}_SOURCE_FILES 
${SOURCE_PATH}/base/HidlSupport.cpp 
${SOURCE_PATH}/base/Status.cpp 
#${SOURCE_PATH}/transport/ServiceManagement.cpp 
)

ADD_LIB(hidl)
