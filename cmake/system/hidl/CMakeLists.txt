project(HIDL)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/hidl/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/base/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/hwbinder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)

if (NOT EXISTS ${HIDL_ROOT_PATH}/hardware/interfaces)
    message( FATAL_ERROR "Please firstly execute cmake of ${M3E_SOURCE_DIR}/tool which will download the source code")
endif()

include_directories(AFTER ${TMP_PATH}/${HIDL_HEADER_PATH})

set(${PROJECT_NAME}_DEPLIB
log
cutils
utils
base
)

if(MSVC)
    add_definitions(-DNOMINMAX)
endif()

#set( HEADER_PATH ${M3E_SOURCE_DIR}/src/system/libhidl/ )
#set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/system/libhidl/ )

set( HEADER_PATH ${HIDL_ROOT_PATH}/system/libhidl/ )
set( SOURCE_PATH ${HIDL_ROOT_PATH}/system/libhidl/ )

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES
${HEADER_PATH}/base/include/hidl/*.h
${HEADER_PATH}/libhidlmemory/include/hidlmemory/*.h
${HEADER_PATH}/transport/include/hidl/*.h
${HEADER_PATH}/transport/token/1.0/utils/include/hidlmemory/*.h
)

# source files
set(${PROJECT_NAME}_SOURCE_FILES 
${SOURCE_PATH}/base/HidlInternal.cpp 
${SOURCE_PATH}/base/HidlSupport.cpp 
${SOURCE_PATH}/base/Status.cpp 
#${SOURCE_PATH}/transport/ServiceManagement.cpp 
${SOURCE_PATH}/transport/token/1.0/utils/HybridInterface.cpp
${SOURCE_PATH}/transport/allocator/1.0/utils/FrameworkUtils.cpp 
${SOURCE_PATH}/libhidlmemory/mapping.cpp
)

###############################################################################
# generate android.hidl.memory@1.0
if (NOT EXISTS ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hidl/memory/1.0)
    exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_HEADER_PATH} -L c++-headers android.hidl.memory@1.0")
endif()
if (NOT EXISTS ${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hidl/memory/1.0)
    #exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_SOURCE_PATH} -L c++-sources android.hidl.memory@1.0")
endif()

file(GLOB ANDROID_HIDL_MEMORY_10_SOURCES
${TMP_PATH}/${HIDL_HEADER_PATH}/android/hidl/memory/1.0/*.h
)
list(APPEND ANDROID_HIDL_MEMORY_10_SOURCES
)
source_group(android.hidl.memory@1.0 FILES ${ANDROID_HIDL_MEMORY_10_SOURCES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${ANDROID_HIDL_MEMORY_10_SOURCES})

###############################################################################
# generate android.hidl.manager@1.0
if (NOT EXISTS ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hidl/manager/1.0)
    exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_HEADER_PATH} -L c++-headers android.hidl.manager@1.0")
endif()
if (NOT EXISTS ${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hidl/manager/1.0)
    #exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_SOURCE_PATH} -L c++-sources android.hidl.manager@1.0")
endif()

file(GLOB ANDROID_HIDL_MANAGER_10_SOURCES
${TMP_PATH}/${HIDL_HEADER_PATH}/android/hidl/manager/1.0/*.h
)
list(APPEND ANDROID_HIDL_MANAGER_10_SOURCES
)
source_group(android.hidl.manager@1.0 FILES ${ANDROID_HIDL_MANAGER_10_SOURCES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${ANDROID_HIDL_MANAGER_10_SOURCES})

###############################################################################
# generate android.hidl.allocator@1.0
if (NOT EXISTS ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hidl/allocator/1.0)
    exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_HEADER_PATH} -L c++-headers android.hidl.allocator@1.0")
endif()
if (NOT EXISTS ${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hidl/allocator/1.0)
    #exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_SOURCE_PATH} -L c++-sources android.hidl.allocator@1.0")
endif()

file(GLOB ANDROID_HIDL_ALLOCATOR_10_SOURCES
${TMP_PATH}/${HIDL_HEADER_PATH}/android/hidl/allocator/1.0/*.h
)
list(APPEND ANDROID_HIDL_ALLOCATOR_10_SOURCES
)
source_group(android.hidl.allocator@1.0 FILES ${ANDROID_HIDL_ALLOCATOR_10_SOURCES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${ANDROID_HIDL_ALLOCATOR_10_SOURCES})

###############################################################################
# generate android.hidl.token@1.0
if (NOT EXISTS ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hidl/token/1.0)
    exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_HEADER_PATH} -L c++-headers android.hidl.token@1.0")
endif()
if (NOT EXISTS ${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hidl/token/1.0)
    #exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_SOURCE_PATH} -L c++-sources android.hidl.token@1.0")
endif()

file(GLOB ANDROID_HIDL_TOKEN_10_SOURCES
${TMP_PATH}/${HIDL_HEADER_PATH}/android/hidl/token/1.0/*.h
)
list(APPEND ANDROID_HIDL_TOKEN_10_SOURCES
)
source_group(android.hidl.token@1.0 FILES ${ANDROID_HIDL_TOKEN_10_SOURCES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${ANDROID_HIDL_TOKEN_10_SOURCES})

###############################################################################
# generate android.hidl.base@1.0
if (NOT EXISTS ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hidl/base/1.0)
    exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_HEADER_PATH} -L c++-headers android.hidl.base@1.0")
endif()
if (NOT EXISTS ${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hidl/base/1.0)
    exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_SOURCE_PATH} -L c++-sources android.hidl.base@1.0")
endif()

file(GLOB ANDROID_HIDL_BASE_10_SOURCES
    ${TMP_PATH}/${HIDL_HEADER_PATH}/android/hidl/base/1.0/*.h
)
list(APPEND ANDROID_HIDL_BASE_10_SOURCES
${TMP_PATH}/${HIDL_SOURCE_PATH}/android/hidl/base/1.0/BaseAll.cpp
)
source_group(android.hidl.base@1.0 FILES ${ANDROID_HIDL_BASE_10_SOURCES})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${ANDROID_HIDL_BASE_10_SOURCES})



ADD_LIB(hidl)
