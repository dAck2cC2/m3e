project(DRMFW)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/drm/drmframework/include.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)

set( ${PROJECT_NAME}_DEPLIB
log
cutils
utils
binder
)

if(MSVC)
    add_definitions(-Dstrcasecmp=_stricmp)

    include(${M3E_SOURCE_DIR}/cmake/core/msvc/include.cmake)
    list(APPEND ${PROJECT_NAME}_DEPLIB ${LIB_MSVC_WRAP})
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/drm/libdrmframework/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/drm/libdrmframework )

include_directories(AFTER ${HEADER_PATH})
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/av/drm/common/include)

file(GLOB ${PROJECT_NAME}_HEADER_FILES  
${M3E_SOURCE_DIR}/src/frameworks/av/drm/common/include/*.h
${M3E_SOURCE_DIR}/src/frameworks/av/include/drm/*.h
${HEADER_PATH}/*.h
)

set(${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/DrmManagerClientImpl.cpp 
${SOURCE_PATH}/DrmManagerClient.cpp 
${SOURCE_PATH}/NoOpDrmManagerClientImpl.cpp
)

set( SOURCE_COM_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/drm/common )
list(APPEND ${PROJECT_NAME}_SOURCE_FILES
${SOURCE_COM_PATH}/DrmConstraints.cpp 
${SOURCE_COM_PATH}/DrmMetadata.cpp 
${SOURCE_COM_PATH}/DrmConvertedStatus.cpp 
${SOURCE_COM_PATH}/DrmEngineBase.cpp 
${SOURCE_COM_PATH}/DrmInfo.cpp 
${SOURCE_COM_PATH}/DrmInfoRequest.cpp 
${SOURCE_COM_PATH}/DrmInfoStatus.cpp 
${SOURCE_COM_PATH}/DrmRights.cpp 
${SOURCE_COM_PATH}/DrmSupportInfo.cpp 
${SOURCE_COM_PATH}/IDrmManagerService.cpp 
${SOURCE_COM_PATH}/IDrmServiceListener.cpp 
${SOURCE_COM_PATH}/DrmInfoEvent.cpp 
${SOURCE_COM_PATH}/ReadWriteUtils.cpp
)

# target files
set(LIB_NAME drmframework)
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${LIB_NAME} SHARED ${${PROJECT_NAME}_SOURCE_FILES} ${${PROJECT_NAME}_HEADER_FILES})
target_link_libraries(${LIB_NAME} ${${PROJECT_NAME}_DEPLIB})
