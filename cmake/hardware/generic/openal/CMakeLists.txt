
project(AUDIO_PRIMARY_OPENAL)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)

if (MSVC)
    include(${M3E_SOURCE_DIR}/cmake/external/openal-soft/include.cmake)
    set(LIB_OPENAL  OpenAL)
else()
endif()


include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)

set( ${PROJECT_NAME}_DEPLIB
log
cutils
${LIB_OPENAL}
)

set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/hardware/generic/openal )

list(APPEND ${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/audio_openal.cpp
)

if (MSVC)
    list(APPEND ${PROJECT_NAME}_SOURCE_FILES
    ${MSVC_PATH}/sys/time.h
    ${MSVC_PATH}/sys/time.c
    )
endif()

# target files
set(LIB_NAME audio_primary_openal)
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${LIB_NAME} SHARED ${${PROJECT_NAME}_SOURCE_FILES})
target_link_libraries(${LIB_NAME} ${${PROJECT_NAME}_DEPLIB})
