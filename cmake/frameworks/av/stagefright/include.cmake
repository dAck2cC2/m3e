
DLL_PUBLIC(STAGEFRIGHT)

# definition
if(MSVC)
else()
    add_definitions(-Wno-multichar)
    add_definitions(-Wno-attributes)
endif()

# include
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/av/include)
