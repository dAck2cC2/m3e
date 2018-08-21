project(EFFECTS)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/effects/include.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/include.cmake)

include_directories(AFTER ${M3E_SOURCE_DIR}/src/system/media/audio_effects/include)

set( ${PROJECT_NAME}_DEPLIB
log
cutils
)

if (MSVC)
    add_definitions(-Dstrlcpy=strncpy)
    add_definitions(-Dstrlcat=strncat)
endif()


set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/include/media )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libeffects )

set(${PROJECT_NAME}_HEADER_FILES  
${HEADER_PATH}/EffectsFactoryApi.h
${SOURCE_PATH}/factory/EffectsFactory.h
)

set(${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/factory/EffectsFactory.c
)

set_source_files_properties( ${${PROJECT_NAME}_SOURCE_FILES} PROPERTIES LANGUAGE "CXX" )

# target files
set(LIB_NAME effects)
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${LIB_NAME} SHARED ${${PROJECT_NAME}_SOURCE_FILES} ${${PROJECT_NAME}_HEADER_FILES})
target_link_libraries(${LIB_NAME} ${${PROJECT_NAME}_DEPLIB})
