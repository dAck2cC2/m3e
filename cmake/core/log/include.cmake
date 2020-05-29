
# define
DLL_PUBLIC(LOG)

if(MSVC)
    include(${M3E_SOURCE_DIR}/cmake/core/msvc/include.cmake)
endif()

# include
include_directories(AFTER ${M3E_SOURCE_DIR}/src/system/core/liblog/include)

