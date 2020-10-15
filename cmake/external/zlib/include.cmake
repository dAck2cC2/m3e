
# define
if(MSVC)
    include(${MSVC_INCLUDE})
    add_definitions(-DZLIB_DLL)
endif(MSVC)

# include
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/zlib/src)
