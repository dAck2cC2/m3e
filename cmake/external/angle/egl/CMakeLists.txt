
project(ANGLE_EGL)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

#add_definitions(-DNDEBUG=1)
#add_definitions(-DLIBANGLE_IMPLEMENTATION=1)
add_definitions(-DEGL_EGL_PROTOTYPES=1)
add_definitions(-DEGL_EGLEXT_PROTOTYPES=1)

if (APPLE)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14 -stdlib=libc++")
    set(CMAKE_C_FLAGS "-x objective-c")
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/src )

include_directories(AFTER ${HEADER_PATH})
include_directories(AFTER ${SOURCE_PATH})
include_directories(AFTER ${SOURCE_PATH}/id)
include_directories(AFTER ${SOURCE_PATH}/common/third_party/base)

include(${M3E_SOURCE_DIR}/cmake/${EXT_PATH}/angle/angle/libGLESv2_gni.cmake)

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
# angle_shared_library("libEGL") {
set(ANGLE_SOURCE_EGL ${libegl_sources})
add_definitions(-DLIBEGL_IMPLEMENTATION)
if(MSVC)
    add_definitions(-DEGLAPI=__declspec\(dllexport\))

    # It will lead to link libEGL.dll, 
    # which cases error 126 when LoadLibrary call.
    #list(APPEND ANGLE_SOURCE_EGL ${SOURCE_PATH}/libEGL/libEGL.def)
endif()
source_group(EGL FILES ${ANGLE_SOURCE_EGL})

###############################################################################
#  Target file
###############################################################################
set(DEPLIB_ANGLE_EGL
ANGLE
)

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(EGL SHARED ${ANGLE_SOURCE_EGL} ${ANGLE_HEADER_EGL} ${ANGLE_HEADER_KHR})
target_link_libraries(EGL ${DEPLIB_ANGLE_EGL})
