# define
if(MSVC)
    add_definitions(-DANDROID_DLL)
    include_directories(AFTER ${M3E_SOURCE_DIR}/src/core/msvc)
endif()

# include
include_directories(AFTER ${M3E_SOURCE_DIR}/src/core/libsync/include)
