# define
DLL_PUBLIC(INTERFACES)

# include
include_directories(AFTER ${HIDL_ROOT_PATH}/hardware/interfaces/configstore/utils/include)
include_directories(AFTER ${HIDL_ROOT_PATH}/hardware/interfaces/audio/common/all-versions/default/include)
include_directories(AFTER ${HIDL_ROOT_PATH}/hardware/interfaces/audio/common/all-versions/util/include)
include_directories(AFTER ${HIDL_ROOT_PATH}/hardware/interfaces/audio/common/2.0/default)
include_directories(AFTER ${HIDL_ROOT_PATH}/hardware/interfaces/audio/common/4.0/default)

include_directories(AFTER ${TMP_PATH}/${HIDL_HEADER_PATH})
