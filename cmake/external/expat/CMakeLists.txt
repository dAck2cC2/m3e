
project(EXPAT)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/expat/include.cmake)

GET_ANDROID_MODULE(expat)

set(${PROJECT_NAME}_DEPLIB )

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/expat)

add_definitions(-DHAVE_EXPAT_CONFIG_H)
add_definitions(-DXML_BUILDING_EXPAT)
add_definitions(-UWIN32_LEAN_AND_MEAN)

if(MSVC)
    add_definitions(-D_WINIOCTL_=1)
    add_definitions(-DXMLIMPORT=__declspec\(dllexport\))

    include(${MSVC_INCLUDE})
    list(APPEND ${PROJECT_NAME}_DEPLIB ${LIB_MSVC_WRAP})
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/expat/lib )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/expat/lib )

file(GLOB EXPAT_HEADER_FILES
${HEADER_PATH}/*.h
)

set(EXPAT_SOURCE_FILES 
${SOURCE_PATH}/loadlibrary.c
${SOURCE_PATH}/xmlparse.c
${SOURCE_PATH}/xmlrole.c
${SOURCE_PATH}/xmltok.c
)

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(expat SHARED ${EXPAT_SOURCE_FILES} ${EXPAT_HEADER_FILES})
target_link_libraries(expat ${${PROJECT_NAME}_DEPLIB})
