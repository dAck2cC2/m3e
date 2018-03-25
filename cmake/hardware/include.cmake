# define
if(MSVC)
    add_definitions(-DANDROID_DLL)
endif()

# include
include_directories(AFTER ${M3E_SOURCE_DIR}/src/hardware/include)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/system/media/audio/include)
