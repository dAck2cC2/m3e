
# definition
if(MSVC)
    add_definitions(-DANDROID_DLL)
    add_definitions(-D__STDC_LIMIT_MACROS=1)
else()
    add_definitions(-Wno-multichar)
    add_definitions(-Wno-attributes)
endif()

# include
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/av/include)
