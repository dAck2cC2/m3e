project(ANGLE_GLESV1_CM)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

#add_definitions(-DNDEBUG=1)
#add_definitions(-DLIBANGLE_IMPLEMENTATION=1)
add_definitions(-DGL_GLES_PROTOTYPES=1)
add_definitions(-DGL_GLEXT_PROTOTYPES=1)
if(MSVC)
    add_definitions(-DGL_API=__declspec\(dllexport\))
    add_definitions(-DGL_APICALL=__declspec\(dllexport\))
elseif (APPLE)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14 -stdlib=libc++")
    set(CMAKE_C_FLAGS "-x objective-c")
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/src )

include_directories(AFTER ${HEADER_PATH})
include_directories(AFTER ${SOURCE_PATH})
include_directories(AFTER ${SOURCE_PATH}/id)

include(${M3E_SOURCE_DIR}/cmake/${EXT_PATH}/angle/angle/libGLESv2_gni.cmake)

###############################################################################
#  Public Header
###############################################################################
file(GLOB ANGLE_HEADER_KHR ${HEADER_PATH}/KHR/*.h)
source_group(public\\KHR FILES ${ANGLE_HEADER_KHR})

file(GLOB ANGLE_HEADER_GLES ${HEADER_PATH}/GLES/*.h)
source_group(public\\GLES FILES ${ANGLE_HEADER_GLES})


###############################################################################
#  GLESv1_CM
###############################################################################
# angle_shared_library("libGLESv1_CM") {
set(ANGLE_SOURCE_GLESv1_CM ${libglesv1_cm_sources})
source_group(GLESv1_CM FILES ${ANGLE_SOURCE_GLESv1_CM})

###############################################################################
#  Target file
###############################################################################
set(ANGLED_SOURCE_GLES1
${ANGLE_HEADER_KHR}
${ANGLE_HEADER_GLES}
${ANGLE_SOURCE_GLESv1_CM}
)

set(DEPLIB_GLESV1_CM
ANGLE
)

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(GLESv1_CM SHARED ${ANGLED_SOURCE_GLES1})
target_link_libraries(GLESv1_CM ${DEPLIB_GLESV1_CM})
