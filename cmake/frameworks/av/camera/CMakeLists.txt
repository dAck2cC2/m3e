project(CAMERA_CLIENT)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/camera/include.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/hidl/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/interfaces/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/ui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/gui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/media_plugin/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/EGL/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright_omx/include.cmake)

set(${PROJECT_NAME}_DEPLIB
log
cutils
utils
binder
gui
)

include_directories(AFTER ${M3E_SOURCE_DIR}/src/system/media/camera/include)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/native/include/media/openmax)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/include/camera )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/camera )

include_directories(AFTER ${HEADER_PATH})

file(GLOB ${PROJECT_NAME}_HEADER_FILES  
${HEADER_PATH}/*.h
${HEADER_PATH}/android/hardware/*.h
${SOURCE_PATH}/*.h
)

set(${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/ICamera.cpp
${SOURCE_PATH}/ICameraClient.cpp
${SOURCE_PATH}/ICameraRecordingProxy.cpp
${SOURCE_PATH}/ICameraRecordingProxyListener.cpp
)

# target files
set(LIB_NAME camera_client)
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${LIB_NAME} SHARED ${${PROJECT_NAME}_SOURCE_FILES} ${${PROJECT_NAME}_HEADER_FILES})
target_link_libraries(${LIB_NAME} ${${PROJECT_NAME}_DEPLIB})
