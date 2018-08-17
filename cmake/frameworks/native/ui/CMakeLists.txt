
project(UI)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/ui/include.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/sync/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)

set(UI_DEPLIB
binder
utils
log
sync
hardware
)

#include_directories(AFTER ${M3E_SOURCE_DIR}/src/native/include/private)

if(MSVC)
    add_definitions(-DANDROID_DLL=1)
    add_definitions(-DANDROID_IMPLEMENTATION=1)
    add_definitions(-DANDROID_UI_IMPLEMENTATION=1)

    add_definitions(-D_ALLOW_KEYWORD_MACROS=1)
    #add_definitions(-D__STDC_LIMIT_MACROS=1)
    #add_definitions(-DNOMINMAX)
elseif(APPLE)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -stdlib=libc++")    
endif()


set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/ui )

# header files
file(GLOB UI_HEADER_FILES  ${HEADER_PATH}/ui/*.h)

#file(GLOB UI_PRIVATE_HEADER ${HEADER_PATH}/private/ui/*.h)
#list(APPEND UI_HEADER_FILES ${UI_PRIVATE_HEADER})

# source files
file(GLOB UI_SOURCE_FILES ${SOURCE_PATH}/*.cpp)


# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(ui SHARED ${UI_SOURCE_FILES} ${UI_HEADER_FILES})
target_link_libraries(ui ${UI_DEPLIB})
