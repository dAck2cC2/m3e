
# define
if(MSVC)
    add_definitions(-DANDROID_DLL)
elseif(APPLE)
    add_definitions(-Doff64_t=off_t)
    add_definitions(-Wno-attributes)
elseif(CYGWIN)
    add_definitions(-Doff64_t=_off64_t)
    add_definitions(-Wno-attributes)
else()
    add_definitions(-Wno-attributes)
endif()

# include
include_directories(AFTER ${M3E_SOURCE_DIR}/src/misc)

