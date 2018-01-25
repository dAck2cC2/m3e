
project(STAGEFRIGHT_MEDIAFILTER)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/misc/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/stagefright/include.cmake)

# dependency
set(STAGEFRIGHT_MEDIAFILTER_DEPLIB
utils
misc
stagefright_foundation
)

# define
if(CYGWIN)
add_definitions(-DPATH_MAX=4096)
endif()

# include files
#include_directories(AFTER ${M3E_SOURCE_DIR}/src/av/include)

# header files
file(GLOB STAGEFRIGHT_MEDIAFILTER_HEADER_FILES 
${M3E_SOURCE_DIR}/src/av/media/libstagefright/filters/*.h 
)

# source files
#file(GLOB STAGEFRIGHT_MEDIAFILTER_SOURCE_FILES 
#${M3E_SOURCE_DIR}/src/av/media/libstagefright/filters/*.cpp
#)
set(STAGEFRIGHT_MEDIAFILTER_SOURCE_FILES
${M3E_SOURCE_DIR}/src/av/media/libstagefright/filters/MediaFilter.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/filters/ZeroFilter.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/filters/SimpleFilter.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/filters/SaturationFilter.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/filters/IntrinsicBlurFilter.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/filters/GraphicBufferListener.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/filters/ColorConvert.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/filters/RSFilter.cpp
)

# target files
set(STAGEFRIGHT_MEDIAFILTER_DEP ${STAGEFRIGHT_MEDIAFILTER_DEPLIB})
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(stagefright_mediafilter STATIC ${STAGEFRIGHT_MEDIAFILTER_SOURCE_FILES} ${STAGEFRIGHT_MEDIAFILTER_HEADER_FILES})
target_link_libraries(stagefright_mediafilter ${STAGEFRIGHT_MEDIAFILTER_DEPLIB})
