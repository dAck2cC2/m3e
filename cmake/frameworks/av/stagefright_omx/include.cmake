
# definition
DLL_PUBLIC(STAGEFRIGHT_OMX)

if(APPLE)
    add_definitions(-Dtypeof=__typeof__)
elseif(MSVC)
    add_definitions(-Dtypeof=decltype)
endif()

# include
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/omx/include)
