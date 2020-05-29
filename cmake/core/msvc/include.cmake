
if(MSVC)
    add_definitions(-DMSVC_WRAP_DLL=1)
    set(LIB_MSVC_WRAP  msvc_wrap)
    include_directories(AFTER ${MSVC_PATH})
    include_directories(AFTER ${M3E_CFG_PATH})
endif(MSVC)
