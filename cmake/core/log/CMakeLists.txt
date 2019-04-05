
project(LOG)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)

set(LOG_DEPLIB )

if (MSVC)
    include(${M3E_SOURCE_DIR}/cmake/core/msvc/include.cmake)
    list(APPEND LOG_DEPLIB ${LIB_MSVC_WRAP})
endif(MSVC)

add_definitions(-DFAKE_LOG_DEVICE=1)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/system/core/liblog/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/system/core/liblog )

include_directories(AFTER ${SOURCE_PATH})

# header files
file(GLOB LOG_HEADER_FILES
${HEADER_PATH}/android/*.h
${HEADER_PATH}/log/*.h
${HEADER_PATH}/private/*.h
${SOURCE_PATH}/*.h 
)

# source files
set(LOG_SOURCE_FILES 
${SOURCE_PATH}/config_read.c
${SOURCE_PATH}/config_write.c
${SOURCE_PATH}/fake_log_device.c
${SOURCE_PATH}/fake_writer.c
${SOURCE_PATH}/log_event_list.c
${SOURCE_PATH}/log_event_write.c
${SOURCE_PATH}/log_ratelimit.cpp
${SOURCE_PATH}/logger_lock.c
${SOURCE_PATH}/logger_name.c
${SOURCE_PATH}/logger_write.c
${SOURCE_PATH}/logprint.c
${SOURCE_PATH}/uio.c

${SOURCE_PATH}/local/file_writer.c
)

#set_source_files_properties( ${LOG_SOURCE_FILES} PROPERTIES LANGUAGE "CXX" )

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(log SHARED ${LOG_SOURCE_FILES} ${LOG_HEADER_FILES})
target_link_libraries(log ${LOG_DEPLIB})

if(UNIX AND NOT APPLE)
    find_package(Threads)
    target_link_libraries(log ${CMAKE_THREAD_LIBS_INIT})
endif()


if(ENABLE_TEST)
    add_subdirectory(test)
endif(ENABLE_TEST)
