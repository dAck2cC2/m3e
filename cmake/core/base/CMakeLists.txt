
project(BASE)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/base/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)

set(${PROJECT_NAME}_DEPLIB
log
cutils
)

add_definitions(-D_FILE_OFFSET_BITS=64)
if (MSVC)
    add_definitions(-Dstrncasecmp=_strnicmp)
    add_definitions(-Dstrcasecmp=_stricmp)
    add_definitions(-DNOMINMAX=1)

    include(${MSVC_INCLUDE})
    list(APPEND BASE_DEPLIB ${LIB_MSVC_WRAP})
    add_definitions(-FI"predefine/__attribute__")
elseif(APPLE)
    add_definitions(-DPAGE_SIZE=4096)
elseif(LINUX)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17")
endif()


set( HEADER_PATH ${M3E_SOURCE_DIR}/src/system/core/base/include/android-base )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/system/core/base )


# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES
${HEADER_PATH}/*.h
${SOURCE_PATH}/*.h 
)

# source files
file(GLOB ${PROJECT_NAME}_SOURCE_FILES 
${SOURCE_PATH}/chrono_utils.cpp
${SOURCE_PATH}/cmsg.cpp
${SOURCE_PATH}/file.cpp
${SOURCE_PATH}/logging.cpp
${SOURCE_PATH}/mapped_file.cpp
${SOURCE_PATH}/parsenetaddress.cpp
${SOURCE_PATH}/properties.cpp
${SOURCE_PATH}/quick_exit.cpp
${SOURCE_PATH}/stringprintf.cpp
${SOURCE_PATH}/strings.cpp
${SOURCE_PATH}/threads.cpp
${SOURCE_PATH}/test_utils.cpp
)

if(MSVC)
    list(APPEND ${PROJECT_NAME}_SOURCE_FILES 
    ${SOURCE_PATH}/errors_windows.cpp
    ${SOURCE_PATH}/utf8.cpp
    )
else()
    list(APPEND ${PROJECT_NAME}_SOURCE_FILES 
    ${SOURCE_PATH}/errors_unix.cpp  
    )
endif()

# target files
ADD_SHARED_LIB(base)

#set(ENABLE_TEST TRUE)
if(ENABLE_TEST)
    add_subdirectory(test)
endif(ENABLE_TEST)
