
project(AUDIO_PRIMARY)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)

set( ${PROJECT_NAME}_DEPLIB
log
cutils
)

if (MSVC)
    add_definitions(-D__unused= )
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/hardware/libhardware/modules/audio )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/hardware/libhardware/modules/audio )

list(APPEND ${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/audio_hw.c
)

if (MSVC)
    list(APPEND ${PROJECT_NAME}_SOURCE_FILES
    ${MSVC_PATH}/sys/time.h
    ${MSVC_PATH}/sys/time.c
    )
endif()

set_source_files_properties( ${${PROJECT_NAME}_SOURCE_FILES} PROPERTIES LANGUAGE "CXX" )

# target files
set(LIB_NAME audio_primary_default)
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${LIB_NAME} SHARED ${${PROJECT_NAME}_SOURCE_FILES})
target_link_libraries(${LIB_NAME} ${${PROJECT_NAME}_DEPLIB})
