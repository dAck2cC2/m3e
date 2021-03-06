
# define
DLL_PUBLIC(CUTILS)

add_definitions(-DLITTLE_ENDIAN=1)
add_definitions(-DBIG_ENDIAN=2)

if(MSVC)
    include(${MSVC_INCLUDE})
    add_definitions(-DBYTE_ORDER=LITTLE_ENDIAN)
elseif(APPLE)
    add_definitions(-DBYTE_ORDER=LITTLE_ENDIAN)
elseif(CYGWIN)
    add_definitions(-Dffs=__builtin_ffs)
elseif(LINUX)
    add_definitions(-D_GNU_SOURCE=1)
elseif(UNIX)
    add_definitions(-D_USING_LIBCXX=1)
endif()

if (CFG_NO_POPCNT)
    add_definitions(-DCFG_NO_POPCNT=1)
endif (CFG_NO_POPCNT)

# include
#include_directories(AFTER ${M3E_CFG_PATH})
include_directories(AFTER ${M3E_SOURCE_DIR}/src/system/core/libcutils/include)
