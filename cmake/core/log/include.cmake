
# define
if (MSVC)
    add_definitions(-DANDROID_API_LOG=__declspec\(dllimport\))
else(MSVC)
    add_definitions(-DANDROID_API_LOG= )
endif(MSVC)

# include
include_directories(AFTER ${M3E_SOURCE_DIR}/src/system/core/include)

