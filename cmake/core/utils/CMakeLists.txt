
project(UTILS)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
#include(${M3E_SOURCE_DIR}/cmake/external/safe-iop/include.cmake)

set(UTILS_DEPLIB
log
cutils
#safeiop
)

if (MSVC)
    add_definitions(-D__MINGW32__=1)
    add_definitions(-DNOMINMAX=1)

    include(${M3E_SOURCE_DIR}/cmake/core/msvc/include.cmake)
    list(APPEND UTILS_DEPLIB ${LIB_MSVC_WRAP})
endif(MSVC)


set( HEADER_PATH ${M3E_SOURCE_DIR}/src/system/core/libutils/include/utils )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/system/core/libutils/ )

# header files
file(GLOB UTILS_HEADER_FILES 
${HEADER_PATH}/*.h
${SOURCE_PATH}/*.h
)

# source files
file(GLOB UTILS_SOURCE_FILES ${SOURCE_PATH}/*.cpp)


# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(utils SHARED ${UTILS_SOURCE_FILES} ${UTILS_HEADER_FILES})
target_link_libraries(utils ${UTILS_DEPLIB})

if(UNIX AND NOT APPLE)
    find_package(Threads)
    target_link_libraries(utils ${CMAKE_THREAD_LIBS_INIT})
endif()

#if(ENABLE_TEST)
    add_subdirectory(test)
#endif(ENABLE_TEST)
