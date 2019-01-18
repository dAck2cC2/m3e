
# define
DLL_PUBLIC(BINDER)

if(MSVC)

elseif(APPLE)
    add_definitions(-Doff64_t=off_t)
    add_definitions(-Wno-attributes)
elseif(CYGWIN)
    add_definitions(-Doff64_t=_off64_t)
    add_definitions(-Wno-attributes)
else()
    add_definitions(-Wno-attributes)
endif()

include(${M3E_SOURCE_DIR}/cmake/core/base/include.cmake)

# include
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/native/binder/include)

