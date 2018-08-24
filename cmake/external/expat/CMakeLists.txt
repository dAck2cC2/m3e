
project(EXPAT)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/expat/include.cmake)

GET_ANDROID_MODULE(expat)

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/expat)

add_definitions(-DHAVE_EXPAT_CONFIG_H)
add_definitions(-DXML_BUILDING_EXPAT)

set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/expat/lib )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/expat/lib )

file(GLOB EXPAT_HEADER_FILES
${HEADER_PATH}/*.h
)

set(EXPAT_SOURCE_FILES 
${SOURCE_PATH}/xmlparse.c
${SOURCE_PATH}/xmlrole.c
${SOURCE_PATH}/xmltok.c
)

if(MSVC)
    add_definitions(-D_WINIOCTL_=1)
    add_definitions(-DXMLIMPORT=__declspec\(dllexport\))
    include_directories(AFTER ${MSVC_PATH})

    list(APPEND EXPAT_HEADER_FILES
    ${MSVC_PATH}/sys/time.h
    )
    list(APPEND EXPAT_SOURCE_FILES
    ${MSVC_PATH}/sys/time.c
    ) 
endif()

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(expat SHARED ${EXPAT_SOURCE_FILES} ${EXPAT_HEADER_FILES})
