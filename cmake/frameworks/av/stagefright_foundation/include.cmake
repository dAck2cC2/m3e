
# definition
DLL_PUBLIC(STAGEFRIGHT_FOUNDATION)

if(MSVC)
    add_definitions(-D__STDC_LIMIT_MACROS=1)
    add_definitions(-DNOMINMAX=1)
else()
    add_definitions(-Wno-multichar)
    add_definitions(-Wno-attributes)
endif()

include(${M3E_SOURCE_DIR}/cmake/frameworks/native/media_plugin/include.cmake)

# include
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/av/include)
