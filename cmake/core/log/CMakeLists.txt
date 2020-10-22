
project(LOG)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)

set(${PROJECT_NAME}_DEPLIB )

if (MSVC)
    include(${MSVC_INCLUDE})
    list(APPEND LOG_DEPLIB ${LIB_MSVC_WRAP})
elseif(APPLE)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -stdlib=libc++")
endif()

add_definitions(-DFAKE_LOG_DEVICE=1)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/system/core/liblog/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/system/core/liblog )

include_directories(AFTER ${SOURCE_PATH})

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES
${HEADER_PATH}/android/*.h
${HEADER_PATH}/log/*.h
${HEADER_PATH}/private/*.h
${SOURCE_PATH}/*.h 
)

# source files
set(${PROJECT_NAME}_SOURCE_FILES
# liblog_sources
${SOURCE_PATH}/config_read.cpp
${SOURCE_PATH}/config_write.cpp
${SOURCE_PATH}/log_event_list.cpp
${SOURCE_PATH}/log_event_write.cpp
${SOURCE_PATH}/logger_lock.cpp
${SOURCE_PATH}/logger_name.cpp
#${SOURCE_PATH}/logger_read.cpp
${SOURCE_PATH}/logger_write.cpp
${SOURCE_PATH}/logprint.cpp
#${SOURCE_PATH}/stderr_write.cpp

# liblog_host_sources
${SOURCE_PATH}/fake_log_device.cpp
${SOURCE_PATH}/fake_writer.cpp

# local file logger
${SOURCE_PATH}/local/file_writer.cpp
)

#set_source_files_properties( ${LOG_SOURCE_FILES} PROPERTIES LANGUAGE "CXX" )

# target files
if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()
set(LIB_TYPE SHARED)
ADD_LIB(log)

if(UNIX AND NOT APPLE)
    find_package(Threads)
    target_link_libraries(log ${CMAKE_THREAD_LIBS_INIT})
endif()


#set(ENABLE_TEST TRUE)
if(ENABLE_TEST)
    add_subdirectory(test)
endif(ENABLE_TEST)
