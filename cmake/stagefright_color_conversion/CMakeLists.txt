
project(STAGEFRIGHT_COLOR_CONVERSION)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/misc/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/stagefright/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/libyuv/include.cmake)

# dependency
set(STAGEFRIGHT_COLOR_CONVERSION_DEPLIB
utils
yuv
)

# header files
#file(GLOB STAGEFRIGHT_COLOR_CONVERSION_HEADER_FILES 
#)
set(STAGEFRIGHT_COLOR_CONVERSION_HEADER_FILES
)

# source files
file(GLOB STAGEFRIGHT_COLOR_CONVERSION_SOURCE_FILES 
${M3E_SOURCE_DIR}/src/av/media/libstagefright/colorconversion/*.cpp
)

# target files
set(STAGEFRIGHT_COLOR_CONVERSION_DEP ${STAGEFRIGHT_COLOR_CONVERSION_DEPLIB})
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(stagefright_color_conversion STATIC ${STAGEFRIGHT_COLOR_CONVERSION_SOURCE_FILES} ${STAGEFRIGHT_COLOR_CONVERSION_HEADER_FILES})
target_link_libraries(stagefright_color_conversion ${STAGEFRIGHT_COLOR_CONVERSION_DEPLIB})


