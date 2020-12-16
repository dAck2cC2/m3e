project(HIDL)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

if (NOT EXISTS ${HIDL_ROOT_PATH}/hardware/interfaces)
    message( FATAL_ERROR "Please firstly execute cmake of ${M3E_SOURCE_DIR}/tool which will download the source code")
endif()


include(${M3E_SOURCE_DIR}/cmake/system/hidl/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/base/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/vndksupport/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/hwbinder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)

include_directories(AFTER ${M3E_SOURCE_DIR}/src/${EXT_PATH}/libhidl/)
include_directories(AFTER ${TMP_PATH}/${HIDL_HEADER_PATH})

set(${PROJECT_NAME}_DEPLIB
log
cutils
utils
base
)

if(MSVC)
    add_definitions(-DNOMINMAX)
    add_definitions(-DRTLD_LAZY=0)

    add_definitions(-FI"predefine/__attribute__")
elseif(APPLE)
    add_definitions(-Denable_if_t=enable_if)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14 -stdlib=libc++")
endif()

set( HEADER_PATH ${HIDL_ROOT_PATH}/system/libhidl/ )
set( SOURCE_PATH ${HIDL_ROOT_PATH}/system/libhidl/ )

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES
${HEADER_PATH}/base/include/hidl/*.h
${HEADER_PATH}/libhidlmemory/include/hidlmemory/*.h
${HEADER_PATH}/transport/include/hidl/*.h
${HEADER_PATH}/transport/token/1.0/utils/include/hidlmemory/*.h
${M3E_SOURCE_DIR}/src/${EXT_PATH}/libhidl/*.h
)

# source files
set(${PROJECT_NAME}_SOURCE_FILES 
${SOURCE_PATH}/base/HidlInternal.cpp 
${SOURCE_PATH}/base/HidlSupport.cpp 
${SOURCE_PATH}/base/Status.cpp 

# Local hidl service management
#${SOURCE_PATH}/transport/ServiceManagement.cpp
${M3E_SOURCE_DIR}/src/${EXT_PATH}/libhidl/ServiceManagement.cpp 

${SOURCE_PATH}/transport/HidlTransportUtils.cpp
${SOURCE_PATH}/transport/token/1.0/utils/HybridInterface.cpp
${SOURCE_PATH}/transport/allocator/1.0/utils/FrameworkUtils.cpp 
${SOURCE_PATH}/libhidlmemory/mapping.cpp
)

###############################################################################
# generate hidl interfaces
if(MSVC)
    add_definitions(-DEXPORT_HIDL=__declspec\(dllexport\))
endif()

set(HIDL_MODULES
android.hidl.memory@1.0
android.hidl.manager@1.0
android.hidl.manager@1.1
#android.hidl.manager@1.2
android.hidl.allocator@1.0
android.hidl.token@1.0
android.hidl.base@1.0
)

foreach(module ${HIDL_MODULES})
    ADD_HIDL_SOURCE(${module})
endforeach()

###############################################################################
# target files
set(LIB_TYPE SHARED)
ADD_LIB(hidl)
