
project(CUTILS)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)

set(${PROJECT_NAME}_DEPLIB
log
)

if (MSVC)
    include(${M3E_SOURCE_DIR}/cmake/core/msvc/include.cmake)
    list(APPEND ${PROJECT_NAME}_DEPLIB ${LIB_MSVC_WRAP})
elseif(LINUX)
    list(APPEND ${PROJECT_NAME}_DEPLIB dl)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-g")
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/system/core/libcutils/include/ )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/system/core/libcutils )

include_directories(AFTER ${SOURCE_PATH})

# header files
file(GLOB CUTILS_HEADER_FILES
${HEADER_PATH}/cutils/*.h
${HEADER_PATH}/private/*.h
${SOURCE_PATH}/*.h
${SOURCE_PATH}/sys/*.h
)

# source files
file(GLOB CUTILS_SOURCE_FILES 
${SOURCE_PATH}/sys/*.cpp
)

list(APPEND CUTILS_SOURCE_FILES
${SOURCE_PATH}/config_utils.cpp
${SOURCE_PATH}/fs_config.cpp
${SOURCE_PATH}/canned_fs_config.cpp
${SOURCE_PATH}/hashmap.cpp
${SOURCE_PATH}/iosched_policy.cpp
${SOURCE_PATH}/load_file.cpp
${SOURCE_PATH}/native_handle.cpp
${SOURCE_PATH}/open_memstream.c
${SOURCE_PATH}/record_stream.cpp
${SOURCE_PATH}/sched_policy.cpp
${SOURCE_PATH}/sockets.cpp
${SOURCE_PATH}/strdup16to8.cpp
${SOURCE_PATH}/strdup8to16.cpp
${SOURCE_PATH}/strlcpy.c
${SOURCE_PATH}/threads.cpp

${SOURCE_PATH}/ashmem-host.cpp
${SOURCE_PATH}/trace-host.cpp

${SOURCE_PATH}/qtaguid.cpp
${SOURCE_PATH}/properties.cpp
)

if(MSVC)
    list(APPEND CUTILS_SOURCE_FILES
    ${SOURCE_PATH}/socket_inaddr_any_server_windows.cpp
    ${SOURCE_PATH}/socket_network_client_windows.cpp
    ${SOURCE_PATH}/sockets_windows.cpp
    )
else()
    list(APPEND CUTILS_SOURCE_FILES
    ${SOURCE_PATH}/socket_inaddr_any_server_unix.cpp
    ${SOURCE_PATH}/socket_network_client_unix.cpp
    ${SOURCE_PATH}/sockets_unix.cpp
    )
endif()

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
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(cutils SHARED ${CUTILS_HEADER_FILES} ${CUTILS_SOURCE_FILES})
target_link_libraries(cutils ${${PROJECT_NAME}_DEPLIB})

if(UNIX AND NOT APPLE)
    #find_package(Threads)
    #target_link_libraries(cutils ${CMAKE_THREAD_LIBS_INIT})
endif()

#set(ENABLE_TEST TRUE)
if(ENABLE_TEST)
  add_subdirectory(test)
endif(ENABLE_TEST)
