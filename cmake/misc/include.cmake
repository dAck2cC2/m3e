
# define
if(APPLE)
add_definitions(-Doff64_t=off_t)
elseif(CYGWIN)
add_definitions(-Doff64_t=_off64_t)
endif()
add_definitions(-Wno-attributes)

# include
include_directories(AFTER ${M3E_SOURCE_DIR}/src/av/external)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/av/external/netd)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/av/external/media/hardware)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/av/external/media/openmax)

