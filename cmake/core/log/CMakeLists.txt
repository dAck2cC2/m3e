
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

# header files
file(GLOB LOG_HEADER_FILES
${HEADER_PATH}/android/*.h
${HEADER_PATH}/log/*.h
${HEADER_PATH}/private/*.h
${SOURCE_PATH}/*.h 
)

# source files
file(GLOB LOG_SOURCE_FILES 
${SOURCE_PATH}/*.c
${SOURCE_PATH}/*.cpp
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


#if(ENABLE_TEST)
    add_subdirectory(test)
#endif(ENABLE_TEST)
