# define
if(MSVC)
    add_definitions(-DANDROID_DLL)
endif(MSVC)

# include
include_directories(AFTER ${M3E_SOURCE_DIR}/src/native/include)

