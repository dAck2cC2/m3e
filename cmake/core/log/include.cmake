
# define
if(MSVC)
    add_definitions(-DANDROID_DLL)
elseif(APPLE)

elseif(CYGWIN)

elseif(UNIX)

endif()

# include
include_directories(AFTER ${M3E_SOURCE_DIR}/src/core/include)

