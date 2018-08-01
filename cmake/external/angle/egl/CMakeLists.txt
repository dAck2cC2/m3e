
project(ANGLE_EGL)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

#add_definitions(-DNDEBUG=1)
#add_definitions(-DLIBANGLE_IMPLEMENTATION=1)
add_definitions(-DEGL_EGLEXT_PROTOTYPES=1)
if(MSVC)
    add_definitions(-DEGLAPI=__declspec\(dllexport\))
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/src )

include_directories(AFTER ${HEADER_PATH})
include_directories(AFTER ${SOURCE_PATH})

###############################################################################
#  Public Header
###############################################################################
file(GLOB ANGLE_HEADER_KHR ${HEADER_PATH}/KHR/*.h)
source_group(public\\KHR FILES ${ANGLE_HEADER_KHR})

file(GLOB ANGLE_HEADER_EGL ${HEADER_PATH}/EGL/*.h)
source_group(public\\EGL FILES ${ANGLE_HEADER_EGL})

###############################################################################
#  GLESv1_CM
###############################################################################
file(GLOB ANGLE_SOURCE_EGL 
${SOURCE_PATH}/libEGL/*.cpp
${SOURCE_PATH}/libEGL/*.h
)
list(APPEND ANGLE_SOURCE_EGL
${M3E_SOURCE_DIR}/src/external/angle/eglext.cpp
)
source_group(EGL FILES ${ANGLE_SOURCE_EGL})

###############################################################################
#  Target file
###############################################################################
set(DEPLIB_ANGLE_EGL
GLESv2
)

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(EGL SHARED ${ANGLE_SOURCE_EGL} ${ANGLE_HEADER_EGL} ${ANGLE_HEADER_KHR})
target_link_libraries(EGL ${DEPLIB_ANGLE_EGL})
