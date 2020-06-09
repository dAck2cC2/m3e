
project(BASE)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/base/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)

set(BASE_DEPLIB
log
cutils
)

if (MSVC)
    add_definitions(-Dstrncasecmp=_strnicmp)
    add_definitions(-Dstrcasecmp=_stricmp)
    
    include(${M3E_SOURCE_DIR}/cmake/core/msvc/include.cmake)
    list(APPEND BASE_DEPLIB ${LIB_MSVC_WRAP})
endif(MSVC)


set( HEADER_PATH ${M3E_SOURCE_DIR}/src/system/core/base/include/android-base )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/system/core/base )


# header files
file(GLOB BASE_HEADER_FILES
${HEADER_PATH}/*.h
${SOURCE_PATH}/*.h 
)

# source files
file(GLOB BASE_SOURCE_FILES 
${SOURCE_PATH}/file.cpp
${SOURCE_PATH}/logging.cpp
${SOURCE_PATH}/parsenetaddress.cpp
${SOURCE_PATH}/quick_exit.cpp
${SOURCE_PATH}/stringprintf.cpp
${SOURCE_PATH}/strings.cpp
${SOURCE_PATH}/test_utils.cpp
${SOURCE_PATH}/properties.cpp
)

if(MSVC)
    list(APPEND BASE_SOURCE_FILES
    ${SOURCE_PATH}/errors_windows.cpp
    ${SOURCE_PATH}/utf8.cpp
    )
else()
    list(APPEND BASE_SOURCE_FILES
    ${SOURCE_PATH}/errors_unix.cpp  
    )
endif()

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(base SHARED ${BASE_SOURCE_FILES} ${BASE_HEADER_FILES})
target_link_libraries(base ${BASE_DEPLIB})

#set(ENABLE_TEST TRUE)
if(ENABLE_TEST)
    add_subdirectory(test)
endif(ENABLE_TEST)
