project(MEDIALOG)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)


# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/media/include.cmake)

set( ${PROJECT_NAME}_DEPLIB
log
cutils
utils
binder
)

if (MSVC)
    #add_definitions(-DNOMINMAX=1)
    add_definitions(-D__unused= )
    #add_definitions(-Dmemalign=_aligned_malloc)

    #include(${MSVC_INCLUDE})
    #list(APPEND ${PROJECT_NAME}_DEPLIB ${LIB_MSVC_WRAP})
elseif(LINUX)
    add_definitions(-D__unused= )
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/services/medialog )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/services/medialog )

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES  
${HEADER_PATH}/*.h
)

set(${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/IMediaLogService.cpp
#${SOURCE_PATH}/MediaLogService.cpp 
#${SOURCE_PATH}/main_medialogservice.cpp
)

ADD_LIB(medialogservice)
