
# define
if(MSVC)
    include(${M3E_SOURCE_DIR}/cmake/core/msvc/include.cmake)
    add_definitions(-DZLIB_DLL)
endif(MSVC)

# include
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/zlib/src)
