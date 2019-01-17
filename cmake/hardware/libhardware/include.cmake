# define
DLL_PUBLIC(HARDWARE)

include(${M3E_SOURCE_DIR}/cmake/core/system/include.cmake)

# include
include_directories(AFTER ${M3E_SOURCE_DIR}/src/hardware/libhardware/include)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/system/media/audio/include)
