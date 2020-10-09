project(MP3EXTRACTOR)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/mediaextractor/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright_foundation/include.cmake)


set(${PROJECT_NAME}_DEPLIB
log
mediaextractor
stagefright_foundation
stagefright_id3
)


if(APPLE)
    add_definitions(-Doff64_t=off_t)
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/extractors/mp3 )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/extractors/mp3 )

file(GLOB ${PROJECT_NAME}_HEADER_FILES
${SOURCE_PATH}/*.h
)

# source files
set(${PROJECT_NAME}_SOURCE_FILES 
${SOURCE_PATH}/MP3Extractor.cpp
${SOURCE_PATH}/VBRISeeker.cpp
${SOURCE_PATH}/XINGSeeker.cpp
)

# target files
set(LIB_NAME mp3extractor)

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${SYS_EXTR_PATH}" ) #->define path for archive
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${SYS_EXTR_PATH}" ) #->define path for Library
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${SYS_EXTR_PATH}" ) #->define path for Runtime
set(LIBRARY_OUTPUT_PATH ${SYS_EXTR_PATH})
add_library(${LIB_NAME} SHARED ${${PROJECT_NAME}_SOURCE_FILES} ${${PROJECT_NAME}_HEADER_FILES})
target_link_libraries(${LIB_NAME} ${${PROJECT_NAME}_DEPLIB})
