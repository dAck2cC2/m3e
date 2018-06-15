
project(BOOTANIMATION)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/ui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/gui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/base/androidfw/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/angle/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/skia/include.cmake)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/base/cmds/bootanimation )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/base/cmds/bootanimation )

# dependency
set(BOOTANIMATION_DEPLIB
cutils
utils
binder
log
ui
gui
androidfw
angle
skia
)

# source files
set( BOOTANIMATION_HEADER_FILES 
${HEADER_PATH}/BootAnimation.h
)

set( BOOTANIMATION_SOURCE_FILES 
${SOURCE_PATH}/BootAnimation.cpp
)

if(MSVC)
    #add_definitions(-DNOMINMAX=1)
    add_definitions(-Dstrcasecmp=strcmp)

    include_directories(AFTER ${MSVC_PATH})

    list(APPEND BOOTANIMATION_HEADER_FILES
    ${MSVC_PATH}/sys/time.h
    )
    list(APPEND BOOTANIMATION_SOURCE_FILES
    ${MSVC_PATH}/sys/time.c
    )    
endif(MSVC)

set(LIB_NAME bootanimation_default)

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${LIB_NAME} SHARED ${BOOTANIMATION_SOURCE_FILES} ${BOOTANIMATION_HEADER_FILES})
target_link_libraries(${LIB_NAME} ${BOOTANIMATION_DEPLIB})

