
project(AUDIO_PRIMARY_OPENAL)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)

if (MSVC)
    include(${M3E_SOURCE_DIR}/cmake/external/openal-soft/include.cmake)
    set(LIB_OPENAL  OpenAL)

    include(${M3E_SOURCE_DIR}/cmake/core/msvc/include.cmake)
    list(APPEND ${PROJECT_NAME}_DEPLIB ${LIB_MSVC_WRAP})  
else()
    find_package(OpenAL REQUIRED)
    include_directories(AFTER ${OPENAL_INCLUDE_DIR})
    set(LIB_OPENAL ${OPENAL_LIBRARY})
endif()

set( ${PROJECT_NAME}_DEPLIB
log
cutils
${LIB_OPENAL}
)

set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/hardware/audio/openal )

list(APPEND ${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/audio_openal.cpp
)

# target files
set(LIB_NAME audio_primary_openal)
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${LIB_NAME} SHARED ${${PROJECT_NAME}_SOURCE_FILES})
target_link_libraries(${LIB_NAME} ${${PROJECT_NAME}_DEPLIB})
