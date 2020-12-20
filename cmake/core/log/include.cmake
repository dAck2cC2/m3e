
if(MSVC)
    include(${MSVC_INCLUDE})
    add_definitions(-FI"predefine/ssize_t")
endif()

# include
include_directories(AFTER ${M3E_SOURCE_DIR}/src/system/core/liblog/include)

