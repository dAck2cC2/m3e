add_definitions(-DUSE_LIBTYPE_SHARED)

if(MSVC)
    # windows.h collisions
    # https://github.com/raysan5/raylib/issues/857
    add_definitions(-DWINAPI_FAMILY=WINAPI_FAMILY_PC_APP)
endif(MSVC)

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/raylib/src)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/raylib/src/external/android/native_app_glue)
