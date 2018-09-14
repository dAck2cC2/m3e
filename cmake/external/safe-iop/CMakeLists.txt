
# safe-iop
project(SAFEIOP)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/safe-iop/include.cmake)

GET_ANDROID_MODULE(safe-iop)

if(APPLE)
    add_definitions(-Dtypeof=__typeof__)
elseif(MSVC)
    add_definitions(-Du_int32_t=uint32_t)
    add_definitions(-Dtypeof=decltype)
endif()

file(GLOB LIBSAFEIOP_HEADER_FILES
${M3E_SOURCE_DIR}/${EXT_PATH}/safe-iop/include/*.h
)

set(LIBSAFEIOP_SOURCE_FILES 
${M3E_SOURCE_DIR}/${EXT_PATH}/safe-iop/src/safe_iop.c
)

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(safeiop STATIC ${LIBSAFEIOP_SOURCE_FILES} ${LIBSAFEIOP_HEADER_FILES})
