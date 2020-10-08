project(HWCOMPOSER2_ANGLE)

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

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/${EXT_PATH}/hidlservice/hwcomposer )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/${EXT_PATH}/hidlservice/hwcomposer )

include_directories(AFTER ${HEADER_PATH})
include_directories(AFTER ${HEADER_PATH}/angle)

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES  
${HEADER_PATH}/hwc2/*.h
${HEADER_PATH}/angle/com/*.h
)

# source files
file(GLOB ${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/hwc2/*.cpp
${SOURCE_PATH}/angle/com/*.cpp
)

if(APPLE)
    find_library(APPKIT_LIBRARY AppKit)
    list(APPEND ${PROJECT_NAME}_DEPLIB ${APPKIT_LIBRARY})

    file(GLOB ${PROJECT_NAME}_HEADER_OSX ${HEADER_PATH}/angle/osx/*.h)
    file(GLOB ${PROJECT_NAME}_SOURCE_OSX ${SOURCE_PATH}/angle/osx/*.cpp ${SOURCE_PATH}/angle/osx/*.mm)

    list(APPEND ${PROJECT_NAME}_HEADER_FILES ${${PROJECT_NAME}_HEADER_OSX})
    list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_SOURCE_OSX})

elseif(MSVC)
    file(GLOB ${PROJECT_NAME}_HEADER_WIN ${HEADER_PATH}/angle/win/*.h)
    file(GLOB ${PROJECT_NAME}_SOURCE_WIN ${SOURCE_PATH}/angle/win/*.cpp)

    list(APPEND ${PROJECT_NAME}_HEADER_FILES ${${PROJECT_NAME}_HEADER_WIN})
    list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_SOURCE_WIN})

endif()


# target files
ADD_LIB(hwcomposer2_angle)
