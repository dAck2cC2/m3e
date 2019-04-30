
# define
DLL_PUBLIC(CUTILS)

add_definitions(-DLITTLE_ENDIAN=1)
add_definitions(-DBIG_ENDIAN=2)

if(MSVC)
    include_directories(AFTER ${MSVC_PATH})
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

# include
include_directories(AFTER ${M3E_SOURCE_DIR}/src/system/core/libcutils/include)
