
if(MSVC)
    if (CFG_NO_POPCNT)
        add_definitions(-DCFG_NO_POPCNT=1)
    endif (CFG_NO_POPCNT)

    add_definitions(-DMSVC_WRAP_DLL=1)
    set(LIB_MSVC_WRAP  msvc_wrap)
    include_directories(AFTER ${MSVC_PATH})
endif(MSVC)
