project(RAYLIB)

if(NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH}/raylib)
  message(STATUS "Download\traylib")
  exec_program("git clone https://github.com/raysan5/raylib.git" ${M3E_SOURCE_DIR}/${EXT_PATH})
  exec_program("git checkout tags/3.0.0" ${M3E_SOURCE_DIR}/${EXT_PATH}/raylib)
  #exec_program("git reset --hard 03846342bbb0a8b6b99025467bc6038119cf71ee" ${M3E_SOURCE_DIR}/${EXT_PATH}/raylib)
  exec_program("git apply ${M3E_SOURCE_DIR}/src/${EXT_PATH}/raylib/raylib.patch" ${M3E_SOURCE_DIR}/${EXT_PATH}/raylib)
endif()

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/nativehelper/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/base/android/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/nativewindow/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/arect/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/wilhelm/openmaxal/include.cmake)

# for native window
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/nativebase/include.cmake)

# for gui
#include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
#include(${M3E_SOURCE_DIR}/cmake/system/hidl/include.cmake)
#include(${M3E_SOURCE_DIR}/cmake/hardware/interfaces/include.cmake)
#include(${M3E_SOURCE_DIR}/cmake/frameworks/native/ui/include.cmake)
#include(${M3E_SOURCE_DIR}/cmake/frameworks/native/gui/include.cmake)
#include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
#include(${M3E_SOURCE_DIR}/cmake/frameworks/native/math/include.cmake)


set(SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/raylib/src)

include_directories(AFTER ${SOURCE_PATH})
include_directories(AFTER ${SOURCE_PATH}/external/android/native_app_glue)

add_definitions(-DPLATFORM_ANDROID)
add_definitions(-DGRAPHICS_API_OPENGL_ES2)

set(${PROJECT_NAME}_DEPLIB
${OPENGL_DEPLIB}
android
OpenMAXAL
)

add_definitions(-DBUILD_LIBTYPE_SHARED)

if(APPLE)
    add_definitions(-Doff64_t=off_t)
    set(CMAKE_CXX_FLAGS "-std=c++1z -stdlib=libc++" ${CMAKE_CXX_FLAGS})  

elseif(MSVC)
    add_definitions(-DSUPPORT_BUSY_WAIT_LOOP=1)

    add_definitions(-D_UNICODE)
    add_definitions(-DWINAPI_FAMILY=WINAPI_FAMILY_PC_APP)
    #add_definitions(-DNOGDI)
    #add_definitions(-DNOUSER)
endif() 

file(GLOB raylib_sources ${SOURCE_PATH}/*.c ${SOURCE_PATH}/*.h)
list(REMOVE_ITEM raylib_sources ${SOURCE_PATH}/rglfw.c)
list(REMOVE_ITEM raylib_sources ${SOURCE_PATH}/raudio.c)

list(REMOVE_ITEM raylib_sources ${SOURCE_PATH}/core.c)
list(APPEND raylib_sources ${M3E_SOURCE_DIR}/src/${EXT_PATH}/raylib/core.c)
list(APPEND raylib_sources 
${M3E_SOURCE_DIR}/src/${EXT_PATH}/raylib/android_fw_wrap.h
${M3E_SOURCE_DIR}/src/${EXT_PATH}/raylib/android_fw_wrap.cpp
)

set(${PROJECT_NAME}_SOURCE_FILES ${raylib_sources})

set(LIB_TYPE SHARED)
ADD_LIB(raylib)

#set(ENABLE_TEST  TRUE)
if(ENABLE_TEST)
  add_subdirectory(test)
endif(ENABLE_TEST)
