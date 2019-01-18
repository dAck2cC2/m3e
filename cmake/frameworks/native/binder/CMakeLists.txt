
project(BINDER)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)

# dependency
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/base/include.cmake)

set(BINDER_DEPLIB
utils
log
)

if (MSVC)
    include(${M3E_SOURCE_DIR}/cmake/core/msvc/include.cmake)
    list(APPEND BINDER_DEPLIB ${LIB_MSVC_WRAP})
endif(MSVC)

OPTION( BINDER_ENABLE_LOCAL
  "Set to ON to enable local binder implementation"
  ON
)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/libs/binder/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/libs/binder )

# header files
file(GLOB BINDER_HEADER_FILES  
${HEADER_PATH}/binder/*.h
${HEADER_PATH}/private/binder/*.h
)

# source files
file(GLOB BINDER_SOURCE_FILES ${SOURCE_PATH}/*.cpp)

if (BINDER_ENABLE_LOCAL)
    add_definitions(-DBINDER_LOCAL=1)
    file(GLOB BINDER_LOCAL_SRC ${SOURCE_PATH}/local/*.cpp)
    list(APPEND BINDER_SOURCE_FILES ${BINDER_LOCAL_SRC})
endif ()

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(binder SHARED ${BINDER_SOURCE_FILES} ${BINDER_HEADER_FILES})
target_link_libraries(binder ${BINDER_DEPLIB})

set(ENABLE_TEST true)
if(ENABLE_TEST)
    add_subdirectory(test)
endif()
