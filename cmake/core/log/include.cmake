
# define
DLL_PUBLIC(LOG)

if(MSVC)
    include(${MSVC_INCLUDE})
endif()

# include
include_directories(AFTER ${M3E_SOURCE_DIR}/src/system/core/liblog/include)

