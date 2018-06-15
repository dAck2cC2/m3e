
project(EGL)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/ui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/EGL/include.cmake)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/opengl/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/native/opengl/libs )

include_directories(AFTER ${SOURCE_PATH})
include_directories(AFTER ${SOURCE_PATH}/EGL)

add_definitions(-DANDROID_IMPLEMENTATION=1)
add_definitions(-DEGL_IMPLEMENTATION=1)

# dependency
set(EGL_DEPLIB
utils
log
ui
)

# header files
file(GLOB EGL_HEADER_FILES  
${HEADER_PATH}/KHR/*.h
${HEADER_PATH}/EGL/*.h
)

# source files
file(GLOB EGL_SOURCE_FILES 
${SOURCE_PATH}/EGL/*.h
${SOURCE_PATH}/EGL/*.cpp
)
source_group(EGL FILES ${EGL_SOURCE_FILES})

if(MSVC)
    add_definitions(-D_ALLOW_KEYWORD_MACROS=1)
    #add_definitions(-Dstrcasecmp=strcmp)
    #include_directories(AFTER ${MSVC_PATH}) 
endif(MSVC)


# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(EGL SHARED ${EGL_SOURCE_FILES} ${EGL_HEADER_FILES})
target_link_libraries(EGL ${EGL_DEPLIB})
