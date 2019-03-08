DLL_PUBLIC(MEDIA)

if(MSVC)
    add_definitions(-D_ALLOW_KEYWORD_MACROS=1)
endif()

# include
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/av/include)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/av/media/libmedia/include)
