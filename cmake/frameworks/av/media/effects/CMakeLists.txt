project(EFFECTS)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/effects/include.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)

include_directories(AFTER ${M3E_SOURCE_DIR}/src/system/media/audio_effects/include)

set( ${PROJECT_NAME}_DEPLIB
log
cutils
)

if (MSVC)
    add_definitions(-Dstrlcpy=strncpy)
    add_definitions(-Dstrlcat=strncat)

    include(${M3E_SOURCE_DIR}/cmake/core/msvc/include.cmake)
    list(APPEND ${PROJECT_NAME}_DEPLIB ${LIB_MSVC_WRAP})
endif()


set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libeffects/factory/include/media )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libeffects )

file(GLOB ${PROJECT_NAME}_HEADER_FILES  
${SOURCE_PATH}/factory/include/media/*.h
${SOURCE_PATH}/config/include
${SOURCE_PATH}/factory/*.h
)

set(${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/factory/EffectsFactory.c
${SOURCE_PATH}/factory/EffectsConfigLoader.c
${SOURCE_PATH}/factory/EffectsFactoryState.c
${SOURCE_PATH}/factory/EffectsXmlConfigLoader.cpp
#${SOURCE_PATH}/config/src/EffectsConfig.cpp
)

set_source_files_properties( ${${PROJECT_NAME}_SOURCE_FILES} PROPERTIES LANGUAGE "CXX" )

# target files
set(LIB_NAME effects)
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${LIB_NAME} SHARED ${${PROJECT_NAME}_SOURCE_FILES} ${${PROJECT_NAME}_HEADER_FILES})
target_link_libraries(${LIB_NAME} ${${PROJECT_NAME}_DEPLIB})
