project(WAVEXTRACTOR)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/mediaextractor/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright_foundation/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/system/audio_utils/include.cmake)

set(${PROJECT_NAME}_DEPLIB
log
mediaextractor
stagefright_foundation
audioutils
)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/extractors/wav )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/extractors/wav )

file(GLOB ${PROJECT_NAME}_HEADER_FILES
${SOURCE_PATH}/*.h
)

# source files
set(${PROJECT_NAME}_SOURCE_FILES 
${SOURCE_PATH}/WAVExtractor.cpp
)

# target files
set(LIB_NAME wavextractor)

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${SYS_EXTR_PATH}" ) #->define path for archive
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${SYS_EXTR_PATH}" ) #->define path for Library
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${SYS_EXTR_PATH}" ) #->define path for Runtime
set(LIBRARY_OUTPUT_PATH ${SYS_EXTR_PATH})
add_library(${LIB_NAME} SHARED ${${PROJECT_NAME}_SOURCE_FILES} ${${PROJECT_NAME}_HEADER_FILES})
target_link_libraries(${LIB_NAME} ${${PROJECT_NAME}_DEPLIB})
