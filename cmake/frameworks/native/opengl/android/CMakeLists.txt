
project(OPENGLES)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/include.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/vndksupport/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/hidl/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/interfaces/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/ui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/graphicsenv/include.cmake)

include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/native/libs/nativewindow/include-private)


set(${PROJECT_NAME}_DEPLIB
utils
log
ui
vndksupport
)

add_definitions(-DEGL_IMPLEMENTATION=1)

if(APPLE)
    add_definitions(-Doff64_t=off_t)
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/opengl/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/opengl/libs )

include_directories(AFTER ${HEADER_PATH})
include_directories(AFTER ${SOURCE_PATH})

file(GLOB EGL_HEADER_FILES ${HEADER_PATH}/EGL/*.h)
source_group(public\\EGL FILES ${EGL_HEADER_FILES})

file(GLOB GLES_HEADER_FILES ${HEADER_PATH}/GLES/*.h)
source_group(public\\GLES FILES ${GLES_HEADER_FILES})

file(GLOB GLES2_HEADER_FILES ${HEADER_PATH}/GLES2/*.h)
source_group(public\\GLES2 FILES ${GLES2_HEADER_FILES})

file(GLOB GLES3_HEADER_FILES ${HEADER_PATH}/GLES3/*.h)
source_group(public\\GLES3 FILES ${GLES3_HEADER_FILES})

file(GLOB KHR_HEADER_FILES ${HEADER_PATH}/KHR/*.h)
source_group(public\\KHR FILES ${KHR_HEADER_FILES})

###############################################################################
#  libETC1
###############################################################################
set(libETC1_SOURCE_FILES 
${SOURCE_PATH}/ETC1/etc1.cpp
)
source_group(libETC1 FILES ${libETC1_SOURCE_FILES})

###############################################################################
#  libEGL
###############################################################################
add_definitions(-D__ANDROID_VNDK__=1)

include_directories(AFTER ${HEADER_PATH}/EGL)
include_directories(AFTER ${SOURCE_PATH}/EGL/include)

set(libEGL_SOURCE_FILES 
${SOURCE_PATH}/EGL/getProcAddress.cpp
${SOURCE_PATH}/EGL/BlobCache.cpp
${SOURCE_PATH}/EGL/FileBlobCache.cpp
${SOURCE_PATH}/EGL/egl_tls.cpp
${SOURCE_PATH}/EGL/egl_cache.cpp
${SOURCE_PATH}/EGL/egl_display.cpp
${SOURCE_PATH}/EGL/egl_object.cpp
${SOURCE_PATH}/EGL/egl.cpp
${SOURCE_PATH}/EGL/eglApi.cpp
${SOURCE_PATH}/EGL/Loader.cpp
)
source_group(libEGL FILES ${libEGL_SOURCE_FILES})

###############################################################################
#  libGLESv1_CM
###############################################################################
set(libGLESv1_CM_SOURCE_FILES 
${SOURCE_PATH}/GLES_CM/gl.cpp
)
source_group(libGLESv1_CM FILES ${libGLESv1_CM_SOURCE_FILES})

###############################################################################
#  libGLESv2
###############################################################################
set(llibGLESv2_SOURCE_FILES 
${SOURCE_PATH}/GLES2/gl2.cpp
)
source_group(libGLESv2 FILES ${llibGLESv2_SOURCE_FILES})

###############################################################################
#  Source
###############################################################################
set(${PROJECT_NAME}_SOURCE
${EGL_HEADER_FILES}
${GLES_HEADER_FILES}
${GLES2_HEADER_FILES}
${GLES3_HEADER_FILES}
${KHR_HEADER_FILES}
${libETC1_SOURCE_FILES}
${libEGL_SOURCE_FILES}
${libGLESv1_CM_SOURCE_FILES}
${llibGLESv2_SOURCE_FILES}
#${llibGLESv3_SOURCE_FILES}
)

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})

#add_library(OpenGLES SHARED ${${PROJECT_NAME}_SOURCE})
#target_link_libraries(OpenGLES ${${PROJECT_NAME}_DEPLIB})

# libEGL
set(${PROJECT_NAME}_SOURCE
${GLES_HEADER_FILES}
${KHR_HEADER_FILES}
${libETC1_SOURCE_FILES}
${libEGL_SOURCE_FILES}
)
add_library(EGL SHARED ${${PROJECT_NAME}_SOURCE})
target_link_libraries(EGL ${${PROJECT_NAME}_DEPLIB})

# libGLESv1_CM
list(APPEND ${PROJECT_NAME}_DEPLIB EGL)

set(${PROJECT_NAME}_SOURCE
${EGL_HEADER_FILES}
${KHR_HEADER_FILES}
${libGLESv1_CM_SOURCE_FILES}
)
add_library(GLESv1_CM SHARED ${${PROJECT_NAME}_SOURCE})
target_link_libraries(GLESv1_CM ${${PROJECT_NAME}_DEPLIB})

# libGLESv2
set(${PROJECT_NAME}_SOURCE
${EGL_HEADER_FILES}
${KHR_HEADER_FILES}
${llibGLESv2_SOURCE_FILES}
)
add_library(GLESv2 SHARED ${${PROJECT_NAME}_SOURCE})
target_link_libraries(GLESv2 ${${PROJECT_NAME}_DEPLIB})
