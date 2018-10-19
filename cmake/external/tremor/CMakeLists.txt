project(TREMOR)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/tremor/include.cmake)

if(NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH}/tremor)
    message(STATUS "Download\t tremor")
    exec_program("git clone https://git.xiph.org/tremor.git" ${M3E_SOURCE_DIR}/${EXT_PATH})
    exec_program("git reset --hard 7c30a66346199f3f09017a09567c6c8a3a0eedc8" ${M3E_SOURCE_DIR}/${EXT_PATH}/tremor)
endif()

include(${M3E_SOURCE_DIR}/cmake/external/ogg/include.cmake)


set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/tremor )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/tremor )

file(GLOB ${PROJECT_NAME}_HEADER_FILES ${HEADER_PATH}/*.h)

set(${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/codebook.c 
)

#set(LIB_TYPE SHARED)
set(LIB_NAME vorbisidec)
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${LIB_NAME} ${LIB_TYPE} ${${PROJECT_NAME}_HEADER_FILES} ${${PROJECT_NAME}_SOURCE_FILES})
target_link_libraries(${LIB_NAME} ${${PROJECT_NAME}_DEPLIB})
