
project(INITRC)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/initrc/include.cmake)

# dependency
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)

set(INITRC_DEPLIB
cutils
utils
hardware
)

if(MSVC)
    add_definitions(-DINITRC_API=__declspec\(dllexport\))
    add_definitions(-D_ALLOW_KEYWORD_MACROS=1)
endif()


set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/initrc/include/initrc )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/initrc )

# header files
file(GLOB INITRC_HEADER_FILES  
${HEADER_PATH}/*.h
)

# source files
file(GLOB INITRC_SOURCE_FILES 
${SOURCE_PATH}/*.h
${SOURCE_PATH}/*.cpp
)


# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(initrc SHARED ${INITRC_SOURCE_FILES} ${INITRC_HEADER_FILES})
target_link_libraries(initrc ${INITRC_DEPLIB})

