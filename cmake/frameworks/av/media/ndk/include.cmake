# definition
DLL_PUBLIC(MEDIANDK)

add_definitions(-D__ANDROID_API__=28)

# include
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/av/media/ndk/include)
