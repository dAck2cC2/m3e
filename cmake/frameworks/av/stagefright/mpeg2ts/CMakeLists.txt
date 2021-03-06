project(STAGEFRIGHT_MPEG2SUPPORT)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/media_plugin/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/mediaextractor/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/audioclient/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/audioprocessing/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/mediaplayerservice/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/external/boringssl/include.cmake)

if(MSVC)
    include(${MSVC_INCLUDE})
    add_definitions(-FI"predefine/__attribute__")
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/mpeg2ts )

file(GLOB ${PROJECT_NAME}_HEADER_FILES
${SOURCE_PATH}/*.h
)

# source files
set(${PROJECT_NAME}_SOURCE_FILES 
${SOURCE_PATH}/AnotherPacketSource.cpp   
${SOURCE_PATH}/ATSParser.cpp   
${SOURCE_PATH}/CasManager.cpp             
${SOURCE_PATH}/ESQueue.cpp               
${SOURCE_PATH}/HlsSampleDecryptor.cpp     
)

# target files
if(LINUX)
    set(LIB_TYPE SHARED)
else()
    set(LIB_TYPE STATIC)
endif()
set(LIB_NAME stagefright_mpeg2support)
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${LIB_NAME} ${LIB_TYPE} ${${PROJECT_NAME}_SOURCE_FILES} ${${PROJECT_NAME}_HEADER_FILES})
target_link_libraries(${LIB_NAME} ${${PROJECT_NAME}_DEPLIB})

