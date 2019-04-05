project(INTERFACES)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/interfaces/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/base/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/hidl/include.cmake)

set(${PROJECT_NAME}_DEPLIB
log
utils
hidl
)

# define
if(APPLE)
    set(CMAKE_CXX_FLAGS "-std=c++1z -stdlib=libc++" ${CMAKE_CXX_FLAGS}) 
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/hardware/interfaces/ )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/hardware/interfaces/ )

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES
${HEADER_PATH}/configstore/include/android/hardware/configstore/1.0/*.h
${HEADER_PATH}/configstore/utils/include/configstore/*.h
${HEADER_PATH}/graphics/allocator/include/android/hardware/graphics/allocator/2.0/*.h
${HEADER_PATH}/graphics/bufferqueue/include/android/hardware/graphics/bufferqueue/1.0/*.h
${HEADER_PATH}/graphics/common/include/android/hardware/graphics/common/1.0/*.h
${HEADER_PATH}/graphics/mapper/include/android/hardware/graphics/mapper/2.0/*.h
${HEADER_PATH}/media/include/android/hardware/media/1.0/*.h
${HEADER_PATH}/media/omx/include/android/hardware/media/omx/1.0/*.h
${HEADER_PATH}/cas/include/android/hardware/cas/1.0/*.h
${HEADER_PATH}/cas/native/include/android/hardware/cas/native/1.0/*.h
)

# source files
set(${PROJECT_NAME}_SOURCE_FILES 
${SOURCE_PATH}/configstore/utils/ConfigStoreUtils.cpp
${SOURCE_PATH}/media/omx/OmxNodeAll.cpp
${SOURCE_PATH}/media/omx/OmxBufferSourceAll.cpp
)

ADD_LIB(interfaces)
