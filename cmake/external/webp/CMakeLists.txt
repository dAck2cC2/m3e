# webp
project(WEBP)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/webp/include.cmake)

GET_ANDROID_MODULE(webp)

add_subdirectory(dec)
add_subdirectory(enc)
