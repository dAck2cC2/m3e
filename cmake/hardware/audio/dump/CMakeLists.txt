project(AUDIO_PRIMARY_DUMP)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)

set( ${PROJECT_NAME}_DEPLIB
log
cutils
)

if(MSVC)
    include(${MSVC_INCLUDE})
    list(APPEND ${PROJECT_NAME}_DEPLIB ${LIB_MSVC_WRAP})
endif()

set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/hardware/audio/dump )

list(APPEND ${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/audio_dump.cpp
)

# target files
set(LIB_NAME audio_primary_dump)
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${LIB_NAME} SHARED ${${PROJECT_NAME}_SOURCE_FILES})
target_link_libraries(${LIB_NAME} ${${PROJECT_NAME}_DEPLIB})
