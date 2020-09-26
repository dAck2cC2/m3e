
# the subdirectory

if (MSVC)
    add_subdirectory(msvc)
endif(MSVC)

add_subdirectory(log)
add_subdirectory(cutils)
add_subdirectory(utils)

if(ENABLE_AV_UTILS)
    add_subdirectory(base)
    add_subdirectory(ziparchive)
    add_subdirectory(grallocusage)
    add_subdirectory(vndksupport)
    add_subdirectory(sync)
endif(ENABLE_AV_UTILS)

if(ENABLE_HIDL_GEN)
    add_subdirectory(base)
endif(ENABLE_HIDL_GEN)
