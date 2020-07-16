project(MEDIAMETRICS)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/mediametrics/include.cmake)

# dependency
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright_foundation/include.cmake)

set( ${PROJECT_NAME}_DEPLIB
log
cutils
utils
binder
stagefright_foundation
)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libmediametrics/include/media )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libmediametrics )

file(GLOB ${PROJECT_NAME}_HEADER_FILES  
${HEADER_PATH}/*.h
)

set(${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/IMediaAnalyticsService.cpp 
${SOURCE_PATH}/MediaAnalyticsItem.cpp 
)

# target files
#set(LIB_TYPE SHARED)
ADD_LIB(mediametrics)
