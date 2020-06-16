
project(ANGLE_GLESV2)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

#add_definitions(-DNDEBUG=1)
#add_definitions(-DLIBANGLE_IMPLEMENTATION=1)
add_definitions(-DGL_GLES_PROTOTYPES=1)
add_definitions(-DGL_GLEXT_PROTOTYPES=1)
if(MSVC)
    add_definitions(-DGL_API=__declspec\(dllexport\))
    add_definitions(-DGL_APICALL=__declspec\(dllexport\))
elseif(APPLE)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14 -stdlib=libc++")
    set(CMAKE_C_FLAGS "-x objective-c")
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/src )

include_directories(AFTER ${HEADER_PATH})
include_directories(AFTER ${SOURCE_PATH})
include_directories(AFTER ${SOURCE_PATH}/id)

###############################################################################
#  Public Header
###############################################################################
file(GLOB ANGLE_HEADER_KHR ${HEADER_PATH}/KHR/*.h)
source_group(public\\KHR FILES ${ANGLE_HEADER_KHR})

file(GLOB ANGLE_HEADER_GLES2 ${HEADER_PATH}/GLES2/*.h)
source_group(public\\GLES2 FILES ${ANGLE_HEADER_GLES2})

###############################################################################
#  GLESv2
###############################################################################
file(GLOB ANGLE_SOURCE_GLESv2 
${SOURCE_PATH}/libGLESv2/libGLESv2.rc 
${SOURCE_PATH}/libGLESv2/libGLESv2_autogen.cpp 
${SOURCE_PATH}/libGLESv2/resource.h
)
source_group(GLESv2 FILES ${ANGLE_SOURCE_GLESv2})

set(ANGLED_SOURCE_GLES2
${ANGLE_HEADER_KHR}
${ANGLE_HEADER_GLES2}
${ANGLE_SOURCE_GLESv2}
)

set(DEPLIB_AGLESV2
ANGLE
)

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(GLESv2 SHARED ${ANGLED_SOURCE_GLES2})
target_link_libraries(GLESv2 ${DEPLIB_AGLESV2})
