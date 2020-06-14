
if(MSVC)    
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("/std:c++17" _cpp_latest_flag_suppoted)
    if (_cpp_latest_flag_suppoted)
        add_compile_options("/std:c++17")
    endif()

    if (CFG_NO_POPCNT)
        add_definitions(-DCFG_NO_POPCNT=1)
    endif (CFG_NO_POPCNT)

    add_definitions(-DMSVC_WRAP_DLL=1)
    set(LIB_MSVC_WRAP  msvc_wrap)
    include_directories(AFTER ${MSVC_PATH})
endif(MSVC)
