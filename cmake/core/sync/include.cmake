if(MSVC)
    include(${MSVC_INCLUDE})
endif()

add_definitions(-D__ANDROID_API__=28)

# include
include_directories(AFTER ${M3E_SOURCE_DIR}/src/system/core/libsync/include)
