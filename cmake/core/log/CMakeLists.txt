
project(LOG)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)


OPTION( LOG_ENABLE_LOGGABLE
  "Set to ON to enable loggable implementation"
  OFF
)

add_definitions(-DANDROID_IMPLEMENTATION=1)
add_definitions(-DFAKE_LOG_DEVICE=1)

set(LOG_DEPLIB

)

# header files
file(GLOB LOG_HEADER_FILES
${M3E_SOURCE_DIR}/src/core/include/log/*.h
${M3E_SOURCE_DIR}/src/core/liblog/*.h 
)

# source files
file(GLOB LOG_SOURCE_FILES 
${M3E_SOURCE_DIR}/src/core/liblog/*.c 
)

if (LOG_ENABLE_LOGGABLE)
    include_directories(AFTER ${M3E_SOURCE_DIR}/src/core/libcutils)
    list(APPEND LOG_HEADER_FILES ${M3E_SOURCE_DIR}/src/core/libcutils/sys/_system_properties.h )
    list(APPEND LOG_SOURCE_FILES ${M3E_SOURCE_DIR}/src/core/libcutils/sys/_system_properties.cpp )
    list(REMOVE_ITEM LOG_SOURCE_FILES ${M3E_SOURCE_DIR}/src/core/liblog/fake_log_device.c)
else (LOG_ENABLE_LOGGABLE)
    list(REMOVE_ITEM LOG_SOURCE_FILES ${M3E_SOURCE_DIR}/src/core/liblog/log_is_loggable.c)
endif (LOG_ENABLE_LOGGABLE)

if(MSVC)
    include_directories(AFTER ${M3E_SOURCE_DIR}/src/core/msvc)
    set(LOG_SOURCE_FILES ${LOG_SOURCE_FILES} ${M3E_SOURCE_DIR}/src/core/msvc/unistd.h)
    set(LOG_SOURCE_FILES ${LOG_SOURCE_FILES} ${M3E_SOURCE_DIR}/src/core/msvc/sys/time.h)
    set(LOG_SOURCE_FILES ${LOG_SOURCE_FILES} ${M3E_SOURCE_DIR}/src/core/msvc/sys/time.c)
endif(MSVC)

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(log SHARED ${LOG_SOURCE_FILES} ${LOG_HEADER_FILES})
target_link_libraries(log ${LOG_DEPLIB})

if(UNIX AND NOT APPLE)
    find_package(Threads)
    target_link_libraries(log ${CMAKE_THREAD_LIBS_INIT})
endif()

