# define
#DLL_PUBLIC(HIDL)

if(MSVC)
    add_definitions(-D__WORDSIZE=64)
    add_definitions(-DNOMINMAX)
endif()

# include
include_directories(AFTER ${HIDL_ROOT_PATH}/system/libhidl/base/include)
include_directories(AFTER ${HIDL_ROOT_PATH}/system/libhidl/libhidlmemory/include)
include_directories(AFTER ${HIDL_ROOT_PATH}/system/libhidl/transport/include)
include_directories(AFTER ${HIDL_ROOT_PATH}/system/libhidl/transport/token/1.0/utils/include)
include_directories(AFTER ${HIDL_ROOT_PATH}/system/libhidl/transport/allocator/1.0/utils/include)
