project(HIDL)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/hidl/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/base/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)

set(${PROJECT_NAME}_DEPLIB
log
cutils
utils
base
)

if(MSVC)
    add_definitions(-DNOMINMAX)
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/system/libhidl/ )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/system/libhidl/ )
set( INTERMEDIATE_PATH ${M3E_SOURCE_DIR}/src/intermediate/system/libhidl/ )

include_directories(AFTER ${INTERMEDIATE_PATH}/transport/token/1.0/android.hidl.token@1.0_genc++_headers/gen)

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES
${HEADER_PATH}/base/include/hidl/*.h
${HEADER_PATH}/libhidlmemory/include/hidlmemory/*.h
${HEADER_PATH}/transport/include/hidl/*.h
${INTERMEDIATE_PATH}/transport/allocator/1.0/android.hidl.allocator@1.0_genc++_headers/gen/android/hidl/allocator/1.0/*.h
${INTERMEDIATE_PATH}/transport/base/1.0/android.hidl.base@1.0_genc++_headers/gen/android/hidl/base/1.0/*.h
${INTERMEDIATE_PATH}/transport/manager/1.0/android.hidl.manager@1.0_genc++_headers/gen/android/hidl/manager/1.0/*.h
${INTERMEDIATE_PATH}/transport/memory/1.0/android.hidl.memory@1.0_genc++_headers/gen/android/hidl/memory/1.0/*.h
${INTERMEDIATE_PATH}/transport/token/1.0/android.hidl.token@1.0_genc++_headers/gen/android/hidl/token/1.0/*.h
)

# source files
set(${PROJECT_NAME}_SOURCE_FILES 
${SOURCE_PATH}/base/HidlInternal.cpp 
${SOURCE_PATH}/base/HidlSupport.cpp 
${SOURCE_PATH}/base/Status.cpp 
#${SOURCE_PATH}/transport/ServiceManagement.cpp 
${SOURCE_PATH}/transport/token/1.0/utils/HybridInterface.cpp
${SOURCE_PATH}/libhidlmemory/mapping.cpp
${INTERMEDIATE_PATH}/transport/base/1.0/android.hidl.base@1.0_genc++/gen/android/hidl/base/1.0/BaseAll.cpp
)

ADD_LIB(hidl)
