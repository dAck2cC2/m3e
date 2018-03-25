# define
if(MSVC)
    add_definitions(-DANDROID_DLL)
    add_definitions(-D__STDC_LIMIT_MACROS=1)
endif(MSVC)

# include
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/native/include)

