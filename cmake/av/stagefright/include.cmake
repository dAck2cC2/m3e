
# include
include_directories(AFTER ${M3E_SOURCE_DIR}/src/av/include)

# definition
if(MSVC)
else()
add_definitions(-Wno-multichar)
add_definitions(-Wno-attributes)
endif()
