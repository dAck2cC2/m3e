
# definition
if(MSVC)
    add_definitions(-DANDROID_DLL)
else()
    add_definitions(-Wno-multichar)
    add_definitions(-Wno-attributes)
endif()

# include
include_directories(AFTER ${M3E_SOURCE_DIR}/src/av/include)
