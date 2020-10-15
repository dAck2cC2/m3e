
project(BOOTANIMATION)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

# dependency
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/hidl/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/interfaces/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/math/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/ui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/gui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/base/androidfw/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/skia_android/include.cmake)

# private header of initrc_if.h
include_directories(AFTER ${INITRC_PATH})

set(BOOTANIMATION_DEPLIB
log
cutils
utils
binder
ui
gui
androidfw
skia_android
${OPENGL_DEPLIB}
)

if(MSVC)
    add_definitions(-DNOMINMAX=1)
    add_definitions(-D_ALLOW_KEYWORD_MACROS=1)
    add_definitions(-Dstrcasecmp=strcmp)

    include(${MSVC_INCLUDE})
    list(APPEND BOOTANIMATION_DEPLIB ${LIB_MSVC_WRAP})

    # for the skia
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("/std:c++17" _cpp_flag_suppoted)
    if (_cpp_flag_suppoted)
        add_compile_options("/std:c++17")
    endif()
elseif (APPLE)
    set(CMAKE_CXX_FLAGS "-std=c++1z -stdlib=libc++" ${CMAKE_CXX_FLAGS})  
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/base/cmds/bootanimation )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/base/cmds/bootanimation )

# source files
set( BOOTANIMATION_HEADER_FILES 
${HEADER_PATH}/BootAnimation.h
)

set( BOOTANIMATION_SOURCE_FILES 
${SOURCE_PATH}/BootAnimation.cpp
${SOURCE_PATH}/main_bootanimation.cpp
)

set(LIB_NAME bootanimation_default)

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${LIB_NAME} SHARED ${BOOTANIMATION_SOURCE_FILES} ${BOOTANIMATION_HEADER_FILES})
target_link_libraries(${LIB_NAME} ${BOOTANIMATION_DEPLIB})

add_custom_command(TARGET ${LIB_NAME} POST_BUILD
COMMAND ${CMAKE_COMMAND} -E make_directory 
$<TARGET_FILE_DIR:${LIB_NAME}>/assets/
)

add_custom_command(TARGET ${LIB_NAME} POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory
${M3E_SOURCE_DIR}/src/frameworks/base/core/res/assets/images/ $<TARGET_FILE_DIR:${LIB_NAME}>/assets/
)

# test 
set(ENABLE_TEST true)
if (ENABLE_TEST)
    add_subdirectory(test)
endif(ENABLE_TEST)
