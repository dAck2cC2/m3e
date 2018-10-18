
project(HARDWARE)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)

set( HW_DEPLIB
cutils
utils
)


set( HEADER_PATH ${M3E_SOURCE_DIR}/src/hardware/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/hardware )

# header files
file(GLOB HW_HEADER_FILES  ${HEADER_PATH}/hardware/*.h)

# source files
file(GLOB HW_SOURCE_FILES ${SOURCE_PATH}/*.c)

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(hardware SHARED ${HW_SOURCE_FILES} ${HW_HEADER_FILES})
target_link_libraries(hardware ${HW_DEPLIB})


add_subdirectory(audio)  
