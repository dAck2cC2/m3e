# define
if(MSVC)
    add_definitions(-DANDROID_DLL)
    include_directories(AFTER ${MSVC_PATH})
endif()

# include
include_directories(AFTER ${M3E_SOURCE_DIR}/src/system/core/libsync/include)
