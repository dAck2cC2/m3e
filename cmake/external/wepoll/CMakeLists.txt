
project(WEPOLL)

if(NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH}/wepoll)
	message(STATUS "Download\twepoll")
	exec_program("git clone https://github.com/piscisaureus/wepoll.git" ${M3E_SOURCE_DIR}/${EXT_PATH})
    exec_program("git reset --hard 01714be0d22e6685df25a6f7433e94bc1a854866" ${M3E_SOURCE_DIR}/${EXT_PATH}/wepoll)
endif()

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/wepoll/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/wepoll/src )

include_directories(AFTER ${HEADER_PATH})
include_directories(AFTER ${SOURCE_PATH})

link_libraries(ws2_32)

if(MSVC)
    add_definitions(-DWEPOLL_EXPORT=)
    add_compile_options(/Wall /wd4127 /wd4201 /wd4242 /wd4710 /wd4711 /wd4820)
else()
    add_compile_options(-Wall)
endif()

file(GLOB SOURCES_SRC ${SOURCE_PATH}/*.c ${SOURCE_PATH}/*.h)
file(GLOB SOURCES_SRC_C ${SOURCE_PATH}/*.c)
file(GLOB SOURCES_SRC_REGULAR ${SOURCE_PATH}/regular/*.c ${SOURCE_PATH}/regular/*.h)
file(GLOB SOURCES_SRC_COMBINED ${SOURCE_PATH}/combined/*.c ${SOURCE_PATH}/combined/*.h)
file(GLOB SOURCES_INCLUDE ${HEADER_PATH}/*.h)

source_group(header FILES ${SOURCES_INCLUDE})
source_group(src FILES ${SOURCES_SRC})
source_group(src FILES ${SOURCES_SRC_REGULAR})
source_group(src FILES ${SOURCES_SRC_COMBINED})

include_directories(AFTER ${SOURCE_PATH}/regular)

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(wepoll SHARED ${HEADER_SOURCE} ${SOURCES_SRC} ${SOURCES_SRC_REGULAR})
#target_link_libraries(wepoll ${WEPOLL_DEPLIB})
