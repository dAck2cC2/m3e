project(TEST_HIDLSERVICE)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/hidl/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/interfaces/include.cmake)

set(DEMO_DEPLIBS
log
cutils
utils
hidl
interfaces
hardware
)

set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/${EXT_PATH}/hidlservice/test )

ADD_DEMO(hwcomposer
${SOURCE_PATH}/test_hwcomposer.cpp
)
