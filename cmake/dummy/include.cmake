
# define
if(MSVC)

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
include_directories(AFTER ${M3E_SOURCE_DIR}/src/av/external)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/av/external/netd)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/av/external/media/hardware)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/av/external/media/openmax)

if(ENABLE_CODEC_SELECTOR)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/av/external/rs)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/av/external/rs/cpp)
endif(ENABLE_CODEC_SELECTOR)
