
project(LOG)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)

add_definitions(-DANDROID_IMPLEMENTATION=1)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/system/core/include/log )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/system/core/liblog )

OPTION( LOG_ENABLE_LOGGABLE
  "Set to ON to enable loggable implementation"
  OFF
)

add_definitions(-DFAKE_LOG_DEVICE=1)

set(LOG_DEPLIB )

# header files
file(GLOB LOG_HEADER_FILES
${HEADER_PATH}/*.h
${SOURCE_PATH}/*.h 
)

# source files
file(GLOB LOG_SOURCE_FILES 
${SOURCE_PATH}/*.c
)

if (LOG_ENABLE_LOGGABLE)
    include_directories(AFTER ${M3E_SOURCE_DIR}/src/system/core/libcutils)
    list(APPEND LOG_HEADER_FILES ${M3E_SOURCE_DIR}/src/system/core/libcutils/sys/_system_properties.h )
    list(APPEND LOG_SOURCE_FILES ${M3E_SOURCE_DIR}/src/system/core/libcutils/sys/_system_properties.cpp )
    list(REMOVE_ITEM LOG_SOURCE_FILES ${SOURCE_PATH}/fake_log_device.c)
else (LOG_ENABLE_LOGGABLE)
    list(REMOVE_ITEM LOG_SOURCE_FILES ${SOURCE_PATH}/log_is_loggable.c)
endif (LOG_ENABLE_LOGGABLE)

if(MSVC)
    include_directories(AFTER ${MSVC_PATH})
    set(LOG_SOURCE_FILES ${LOG_SOURCE_FILES} ${MSVC_PATH}/unistd.h)
    set(LOG_SOURCE_FILES ${LOG_SOURCE_FILES} ${MSVC_PATH}/sys/time.h)
    set(LOG_SOURCE_FILES ${LOG_SOURCE_FILES} ${MSVC_PATH}/sys/time.c)
endif(MSVC)

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(log SHARED ${LOG_SOURCE_FILES} ${LOG_HEADER_FILES})
target_link_libraries(log ${LOG_DEPLIB})

if(UNIX AND NOT APPLE)
    find_package(Threads)
    target_link_libraries(log ${CMAKE_THREAD_LIBS_INIT})
endif()

