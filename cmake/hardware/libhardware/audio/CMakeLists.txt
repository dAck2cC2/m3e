
project(AUDIO_PRIMARY_DEFAULT)

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

    include(${MSVC_INCLUDE})
    list(APPEND ${PROJECT_NAME}_DEPLIB ${LIB_MSVC_WRAP}) 
elseif(LINUX)
    add_definitions(-D__unused= )
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/hardware/libhardware/modules/audio )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/hardware/libhardware/modules/audio )

list(APPEND ${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/audio_hw.c
)

set_source_files_properties( ${${PROJECT_NAME}_SOURCE_FILES} PROPERTIES LANGUAGE "CXX" )

# target files
ADD_SHARED_LIB(audio_primary_default)
