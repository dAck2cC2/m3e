project(AAC)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
#include(${M3E_SOURCE_DIR}/cmake/external/aac/include.cmake)

GET_ANDROID_MODULE(aac)

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)

set(${PROJECT_NAME}_DEPLIB
log
)

set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/aac )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/aac )

if (MSVC)
    add_definitions(-D__x86_64__)
endif()

macro(ADD_AAC_SUB_SOURCE folder_name)
    include_directories(AFTER ${SOURCE_PATH}/${folder_name}/include)
    file(GLOB  ${folder_name}_SOURCES
    ${SOURCE_PATH}/${folder_name}/src/*.cpp 
    ${SOURCE_PATH}/${folder_name}/src/*.h
    ${SOURCE_PATH}/${folder_name}/include/*.h
    )
    source_group(${folder_name} FILES ${${folder_name}_SOURCES})
    list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${folder_name}_SOURCES})
endmacro()

set(AAC_SUB_FOLDERS
libAACdec
libAACenc
libPCMutils
libFDK
libSYS
libMpegTPDec
libMpegTPEnc
libSBRdec
libSBRenc
libArithCoding
libDRCdec
libSACdec
libSACenc
)
foreach(folder ${AAC_SUB_FOLDERS})
    ADD_AAC_SUB_SOURCE(${folder})
endforeach()


set(LIB_TYPE STATIC)
ADD_LIB(FraunhoferAAC)
