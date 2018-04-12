project(SURFACEFLINGER)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/gui/include.cmake)
#include(${M3E_SOURCE_DIR}/cmake/external/angle/include.cmake)

#add_definitions(-DANDROID_IMPLEMENTATION=1)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/surfaceflinger )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/surfaceflinger )

add_definitions(-D_LIBCPP_HAS_NO_ATOMIC_HEADER=1)

# dependency
set( SURFACEFLINGER_DEPLIB
log
cutils
utils
binder
gui
#angle
)

# source files
set( SURFACEFLINGER_HEADER_FILES  
${HEADER_PATH}/SurfaceFlinger.h
)

set( SURFACEFLINGER_SOURCE_FILES  
${SOURCE_PATH}/SurfaceFlinger.cpp
${SOURCE_PATH}/main_surfaceflinger.cpp
)

if (APPLE)
    set(LIB_NAME surfaceflinger.osx)
else ()
    set(LIB_NAME surfaceflinger.default)
endif()

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${LIB_NAME} SHARED ${SURFACEFLINGER_SOURCE_FILES} ${SURFACEFLINGER_HEADER_FILES})
target_link_libraries(${LIB_NAME} ${SURFACEFLINGER_DEPLIB})
