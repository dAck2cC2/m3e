
if(MSVC)
    include(${MSVC_INCLUDE})
    add_definitions(-FI"predefine/__builtin_expect")
endif()

# include
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/native/libs/math/include)
