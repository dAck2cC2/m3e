
# define

add_definitions(-DLITTLE_ENDIAN=1)
add_definitions(-DBIG_ENDIAN=2)

if(MSVC)
    include_directories(AFTER ${MSVC_PATH})
    add_definitions(-DBYTE_ORDER=LITTLE_ENDIAN)
    add_definitions(-DANDROID_DLL)
elseif(APPLE)
    add_definitions(-DBYTE_ORDER=LITTLE_ENDIAN)
elseif(CYGWIN)
    add_definitions(-Dffs=__builtin_ffs)
elseif(UNIX)

endif()

# include
include_directories(AFTER ${M3E_SOURCE_DIR}/src/system/core/include)

