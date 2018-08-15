# piex
project(PIEX)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/piex/include.cmake)

GET_ANDROID_MODULE(piex)

if (MSVC)
    set(LIB_TYPE STATIC)
else()
    set(LIB_TYPE SHARED)
endif()

add_subdirectory(binary_parse)
add_subdirectory(image_type_recognition)
add_subdirectory(tiff_directory)
add_subdirectory(piex)
