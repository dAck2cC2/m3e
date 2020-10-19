project(NBLOG)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/nblog/include.cmake)

# dependency
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/audio_utils/include.cmake)

set(${PROJECT_NAME}_DEPLIB
log
cutils
utils
binder
audioutils
)

if(APPLE)
    set(CMAKE_CXX_FLAGS "-std=c++1z -stdlib=libc++" ${CMAKE_CXX_FLAGS})  
elseif(MSVC)
    add_definitions(-DNOMINMAX=1)
elseif(LINUX)
    set(CMAKE_CXX_FLAGS "-std=c++14" ${CMAKE_CXX_FLAGS})
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libnblog/include/media/nblog )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libnblog )

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES  
${HEADER_PATH}/*.h
)

set(${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/NBLog.cpp                    
${SOURCE_PATH}/PerformanceAnalysis.cpp
${SOURCE_PATH}/ReportPerformance.cpp
)

set(LIB_TYPE SHARED)
ADD_LIB(nblog)
