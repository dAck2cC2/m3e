
#project(STAGEFRIGHT_MEDIAFILTER)
project(STAGEFRIGHT)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright_omx/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/rs/include.cmake)

set(${PROJECT_NAME}_DEPLIB
utils
ui
stagefright_foundation
RScpp
)

# define
if(CYGWIN)
    add_definitions(-DPATH_MAX=4096)
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/filters )


# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES
${SOURCE_PATH}/*.h 
)

# source files
#file(GLOB STAGEFRIGHT_MEDIAFILTER_SOURCE_FILES 
#${M3E_SOURCE_DIR}/src/av/media/libstagefright/filters/*.cpp
#)
set(${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/MediaFilter.cpp
${SOURCE_PATH}/ZeroFilter.cpp
${SOURCE_PATH}/SimpleFilter.cpp
${SOURCE_PATH}/SaturationFilter.cpp
${SOURCE_PATH}/IntrinsicBlurFilter.cpp
${SOURCE_PATH}/GraphicBufferListener.cpp
${SOURCE_PATH}/ColorConvert.cpp
${SOURCE_PATH}/RSFilter.cpp
)

# target files
set(LIB_TYPE STATIC)
set(LIB_NAME stagefright_mediafilter)
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${LIB_NAME} ${LIB_TYPE} ${${PROJECT_NAME}_SOURCE_FILES} ${${PROJECT_NAME}_HEADER_FILES})
target_link_libraries(${LIB_NAME} ${${PROJECT_NAME}_DEPLIB})
