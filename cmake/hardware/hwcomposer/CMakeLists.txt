
set(HWC_VER_1    1)
set(HWC_VER_2    2)

# SurfaceFlinger of Android 9 is using HW composer 2
set(HWC_VERSION  2)

###############################################################################
# The HW composer2 works as unique so file
if(HWC_VERSION EQUAL HWC_VER_2)

project(HWCOMPOSER2)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/hidl/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/interfaces/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/include.cmake)

set( ${PROJECT_NAME}_DEPLIB
log
cutils
utils
interfaces
${OPENGL_DEPLIB}
)

if(MSVC)
    add_definitions(-DNOMINMAX)
    add_definitions(-D_ALLOW_KEYWORD_MACROS=1)
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/hardware/hwcomposer )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/hardware/hwcomposer )

include_directories(AFTER ${HEADER_PATH})

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES  
${HEADER_PATH}/hwc2/*.h
${HEADER_PATH}/com/*.h
)

# source files
file(GLOB ${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/hwc2/*.cpp
${SOURCE_PATH}/com/*.cpp
)

if(APPLE)
    find_library(APPKIT_LIBRARY AppKit)
    list(APPEND ${PROJECT_NAME}_DEPLIB ${APPKIT_LIBRARY})

    file(GLOB ${PROJECT_NAME}_HEADER_OSX ${HEADER_PATH}/osx/*.h)
    file(GLOB ${PROJECT_NAME}_SOURCE_OSX ${SOURCE_PATH}/osx/*.cpp ${SOURCE_PATH}/osx/*.mm)

    list(APPEND ${PROJECT_NAME}_HEADER_FILES ${${PROJECT_NAME}_HEADER_OSX})
    list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_SOURCE_OSX})

elseif(MSVC)
    file(GLOB ${PROJECT_NAME}_HEADER_WIN ${HEADER_PATH}/win/*.h)
    file(GLOB ${PROJECT_NAME}_SOURCE_WIN ${SOURCE_PATH}/win/*.cpp)

    list(APPEND ${PROJECT_NAME}_HEADER_FILES ${${PROJECT_NAME}_HEADER_WIN})
    list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_SOURCE_WIN})

endif()


# target files
ADD_LIB(hwcomposer2)


###############################################################################
# The legacy HW composer uses separated cmake to generate so files
else()
if(MSVC)
    add_subdirectory(win)
elseif(APPLE)
    add_subdirectory(osx)
endif()
endif()