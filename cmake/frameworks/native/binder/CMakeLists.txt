
project(BINDER)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)

# dependency
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)

#include_directories(AFTER ${M3E_SOURCE_DIR}/src/native/include/private)

set(BINDER_DEPLIB
utils
log
)

OPTION( BINDER_ENABLE_LOCAL
  "Set to ON to enable local binder implementation"
  ON
)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/binder )

# header files
file(GLOB BINDER_HEADER_FILES  ${HEADER_PATH}/binder/*.h)

file(GLOB BINDER_PRIVATE_HEADER ${HEADER_PATH}/private/binder/*.h)
list(APPEND BINDER_HEADER_FILES ${BINDER_PRIVATE_HEADER})

# source files
file(GLOB BINDER_SOURCE_FILES ${SOURCE_PATH}/*.cpp)

if (BINDER_ENABLE_LOCAL)
    add_definitions(-DBINDER_LOCAL=1)
    file(GLOB BINDER_LOCAL_SRC ${SOURCE_PATH}/local/*.cpp)
    list(APPEND BINDER_SOURCE_FILES ${BINDER_LOCAL_SRC})
endif ()

if (MSVC)
	add_definitions(-Dsleep=Sleep)
    list(APPEND BINDER_SOURCE_FILES
    ${MSVC_PATH}/getpagesize.c
    )
endif (MSVC)

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(binder SHARED ${BINDER_SOURCE_FILES} ${BINDER_HEADER_FILES})
target_link_libraries(binder ${BINDER_DEPLIB})


if(ENABLE_TEST)
    add_subdirectory(test)
endif()
