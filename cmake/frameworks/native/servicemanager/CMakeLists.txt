
project(SERVICEMANAGER)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)

if (MSVC)
    add_definitions(-DANDROID_DLL)
    add_definitions(-DANDROID_IMPLEMENTATION=1)
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/servicemanager )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/servicemanager )

# dependency
set( SERVICEMANAGER_DEPLIB
log
cutils
utils
binder
)

set( SERVICEMANAGER_SOURCE_FILES  
${SOURCE_PATH}/ServiceManager_local.cpp
)

set(LIB_NAME servicemanager_local)

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${LIB_NAME} SHARED ${SERVICEMANAGER_SOURCE_FILES})
target_link_libraries(${LIB_NAME} ${SERVICEMANAGER_DEPLIB})

