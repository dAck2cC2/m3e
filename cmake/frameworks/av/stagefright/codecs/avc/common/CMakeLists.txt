
project(STAGEFRIGHT_AVC_COMMON)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright/codecs/amrnb/common/include.cmake)

set(${PROJECT_NAME}_DEPLIB
)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/codecs/avc/common/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/codecs/avc/common/src )

include_directories(AFTER ${HEADER_PATH})

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES  
${HEADER_PATH}/*.h 
)

set(${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/deblock.cpp
${SOURCE_PATH}/dpb.cpp 
${SOURCE_PATH}/fmo.cpp 
${SOURCE_PATH}/mb_access.cpp 
${SOURCE_PATH}/reflist.cpp 
)

# target files
#set(LIB_TYPE SHARED)
set(LIB_NAME stagefright_avc_common)
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${LIB_NAME} ${LIB_TYPE} ${${PROJECT_NAME}_SOURCE_FILES} ${${PROJECT_NAME}_HEADER_FILES})
target_link_libraries(${LIB_NAME} ${${PROJECT_NAME}_DEPLIB})

