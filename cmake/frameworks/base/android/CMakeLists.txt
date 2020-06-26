project(ANDROID)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/base/android/include.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/base/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/ziparchive/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/nativehelper/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/base/androidfw/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/base/jni/include.cmake)


set(${PROJECT_NAME}_DEPLIB
log
utils
androidfw
)

if (APPLE)
    add_definitions(-Doff64_t=off_t)
elseif(MSVC)
    add_definitions(-DNOMINMAX=1)
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/include/android )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/base/native/android )

file(GLOB ${PROJECT_NAME}_HEADER_FILES
${HEADER_PATH}/*.h
)

set(${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/asset_manager.cpp
#${SOURCE_PATH}/choreographer.cpp 
#${SOURCE_PATH}/configuration.cpp 
#${SOURCE_PATH}/hardware_buffer_jni.cpp 
#${SOURCE_PATH}/input.cpp 
#${SOURCE_PATH}/looper.cpp 
#${SOURCE_PATH}/native_activity.cpp 
#${SOURCE_PATH}/native_window_jni.cpp 
#${SOURCE_PATH}/net.c 
#${SOURCE_PATH}/obb.cpp 
#${SOURCE_PATH}/sensor.cpp 
#${SOURCE_PATH}/sharedmem.cpp 
#${SOURCE_PATH}/storage_manager.cpp 
#${SOURCE_PATH}/surface_texture.cpp 
#${SOURCE_PATH}/trace.cpp 
)

set(LIB_TYPE SHARED)
ADD_LIB(android)
