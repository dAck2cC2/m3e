project(MEDIAUTILS)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/mediautils/include.cmake)

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

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/utils/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/utils )

file(GLOB ${PROJECT_NAME}_HEADER_FILES  
${HEADER_PATH}/mediautils/*.h
${SOURCE_PATH}/*.h
)

set(${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/BatteryNotifier.cpp 
${SOURCE_PATH}/ISchedulingPolicyService.cpp 
${SOURCE_PATH}/SchedulingPolicyService.cpp
)

# target files
set(LIB_NAME mediautils)
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(${LIB_NAME} SHARED ${${PROJECT_NAME}_SOURCE_FILES} ${${PROJECT_NAME}_HEADER_FILES})
target_link_libraries(${LIB_NAME} ${${PROJECT_NAME}_DEPLIB})
