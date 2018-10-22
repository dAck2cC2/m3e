project(HEVC)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/hevc/include.cmake)

GET_ANDROID_MODULE(libhevc)
