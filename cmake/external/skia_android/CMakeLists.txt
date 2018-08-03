
# skia frome Android
project(SKIA_ANDROID)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/skia_android/include.cmake)

GET_ANDROID_MODULE(skia)
