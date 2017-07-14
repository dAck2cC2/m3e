
# define
if(APPLE)
add_definitions(-Doff64_t=off_t)
endif()

# include
include_directories(AFTER ${M3E_SOURCE_DIR}/src/av/external)
