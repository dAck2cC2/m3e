project(NATIVEWINDOWS)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/nativewindow/include.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/grallocusage/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/frameworks/native/ui/include.cmake)

include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/native/libs/nativewindow/include-private)


set(${PROJECT_NAME}_DEPLIB
log
cutils
utils
)

if (MSVC)
    add_definitions(-DNOMINMAX=1)
    add_definitions(-D_ALLOW_KEYWORD_MACROS=1)
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/libs/nativewindow/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/libs/nativewindow )


# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES  
${HEADER_PATH}/andrloid/*.h
${HEADER_PATH}/system/*.h
${HEADER_PATH}/vndk/*.h
${SOURCE_PATH}/include-private/private/android/*.h
)

# source files
set(${PROJECT_NAME}_SOURCE_FILES 
${SOURCE_PATH}/ANativeWindow.cpp
)

# target files
ADD_SHARED_LIB(nativewindow)
