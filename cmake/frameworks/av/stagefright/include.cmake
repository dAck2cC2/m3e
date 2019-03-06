
DLL_PUBLIC(STAGEFRIGHT)

# definition
if(MSVC)
else()
    add_definitions(-Wno-multichar)
    add_definitions(-Wno-attributes)
    add_definitions(-fpermissive)    
endif()

# include
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/include)
