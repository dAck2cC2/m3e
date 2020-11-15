
project(CUTILS)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)

# try to make simply dependency
#include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
#include(${M3E_SOURCE_DIR}/cmake/core/base/include.cmake)

set(${PROJECT_NAME}_DEPLIB
log
)

if (MSVC)
    include(${MSVC_INCLUDE})
    list(APPEND ${PROJECT_NAME}_DEPLIB ${LIB_MSVC_WRAP})
elseif(LINUX)
    list(APPEND ${PROJECT_NAME}_DEPLIB dl)
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/system/core/libcutils/include/ )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/system/core/libcutils )

include_directories(AFTER ${SOURCE_PATH})

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES
${HEADER_PATH}/cutils/*.h
${HEADER_PATH}/private/*.h
${SOURCE_PATH}/*.h
${SOURCE_PATH}/sys/*.h
)

# source files
file(GLOB ${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/sys/*.cpp
)

list(APPEND ${PROJECT_NAME}_SOURCE_FILES
# basic files from Android.bp
${SOURCE_PATH}/config_utils.cpp
${SOURCE_PATH}/canned_fs_config.cpp
${SOURCE_PATH}/iosched_policy.cpp
${SOURCE_PATH}/load_file.cpp
${SOURCE_PATH}/native_handle.cpp
${SOURCE_PATH}/record_stream.cpp
${SOURCE_PATH}/sockets.cpp
${SOURCE_PATH}/strdup16to8.cpp
${SOURCE_PATH}/strdup8to16.cpp
${SOURCE_PATH}/strlcpy.c
${SOURCE_PATH}/threads.cpp
)

list(APPEND ${PROJECT_NAME}_SOURCE_FILES
# rest of files under path
#${SOURCE_PATH}/android_get_control_file.cpp    # using android::base
${SOURCE_PATH}/android_reboot.cpp

# use host version
#${SOURCE_PATH}/ashmem-dev.cpp
${SOURCE_PATH}/ashmem-host.cpp

#${SOURCE_PATH}/fs.cpp    # not for MSVC
#${SOURCE_PATH}/fs_config.cpp    # using android::base
${SOURCE_PATH}/hashmap.cpp
${SOURCE_PATH}/iosched_policy.cpp
#${SOURCE_PATH}/klog.cpp    # no usage
${SOURCE_PATH}/multiuser.cpp
${SOURCE_PATH}/partition_utils.cpp
${SOURCE_PATH}/properties.cpp
${SOURCE_PATH}/qtaguid.cpp
#${SOURCE_PATH}/str_parms.cpp    # no usage

# use host version
#${SOURCE_PATH}/trace-container.cpp
#${SOURCE_PATH}/trace-dev.cpp
${SOURCE_PATH}/trace-host.cpp

#${SOURCE_PATH}/uevent.cpp    # not for MSVC
)

if(MSVC)
    list(APPEND ${PROJECT_NAME}_SOURCE_FILES
    ${SOURCE_PATH}/socket_inaddr_any_server_windows.cpp
    ${SOURCE_PATH}/socket_network_client_windows.cpp
    ${SOURCE_PATH}/sockets_windows.cpp
    )
else()
    list(APPEND ${PROJECT_NAME}_SOURCE_FILES
    ${SOURCE_PATH}/socket_inaddr_any_server_unix.cpp
    ${SOURCE_PATH}/socket_local_client_unix.cpp
    ${SOURCE_PATH}/socket_local_server_unix.cpp
    ${SOURCE_PATH}/socket_network_client_unix.cpp
    ${SOURCE_PATH}/sockets_unix.cpp
    )
endif()

# legacy file for M3E:
list(APPEND ${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/legacy/sched_policy.cpp
)

# header and source code for MSVC
if(MSVC)
    add_definitions(-D_ALLOW_KEYWORD_MACROS=1)
    add_definitions(-D_GNU_SOURCE)
    add_definitions(-D__STDC_LIMIT_MACROS)
elseif(APPLE)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -stdlib=libc++")
elseif(CYGWIN)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=gnu++11")
elseif(UNIX)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++0x")
endif()

# target files
ADD_SHARED_LIB(cutils)

if(UNIX AND NOT APPLE)
    #find_package(Threads)
    #target_link_libraries(cutils ${CMAKE_THREAD_LIBS_INIT})
endif()

#set(ENABLE_TEST TRUE)
if(ENABLE_TEST)
  add_subdirectory(test)
endif(ENABLE_TEST)
