
if(MSVC)
    add_definitions(-DMSVC_WRAP_DLL=1)
    set(LIB_MSVC_WRAP  msvc_wrap)
    include_directories(AFTER ${M3E_SOURCE_DIR}/src/system/msvc/)
endif(MSVC)
