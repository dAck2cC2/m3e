
# define
DLL_PUBLIC(CUTILS)

add_definitions(-DLITTLE_ENDIAN=1)
add_definitions(-DBIG_ENDIAN=2)

if(MSVC)
    include_directories(AFTER ${MSVC_PATH})
    add_definitions(-DBYTE_ORDER=LITTLE_ENDIAN)
elseif(APPLE)
    add_definitions(-DBYTE_ORDER=LITTLE_ENDIAN)
    #add_definitions-D_STDATOMIC_HAVE_ATOMIC=1)

    add_definitions(-D_LIBCPP_HAS_NO_ATOMIC_HEADER=1)
    #add_definitions(-D_LIBCPP_HAS_C_ATOMIC_IMP=1)
elseif(CYGWIN)
    add_definitions(-Dffs=__builtin_ffs)
elseif(UNIX)

endif()

# include
include_directories(AFTER ${M3E_SOURCE_DIR}/src/system/core/libcutils/include)
