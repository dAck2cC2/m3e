
# define
if(APPLE)
add_definitions(-Doff64_t=off_t)
endif()

# include
include_directories(AFTER ${M3E_SOURCE_DIR}/src/av/external)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/av/external/netd)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/av/external/media/hardware)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/av/external/media/openmax)

