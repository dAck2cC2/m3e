project(HIDLSERVICE)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/base/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/hidl/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/system/hwbinder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/interfaces/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/libhardware/include.cmake)

set( ${PROJECT_NAME}_DEPLIB
log
cutils
utils
hidl
interfaces
)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/${EXT_PATH}/hidlservice )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/${EXT_PATH}/hidlservice )

include_directories(AFTER ${HEADER_PATH})

set(${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/main_hidlservice.cpp
)

# android.hardware.graphics.composer@2.1 
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/glfw/include.cmake)
list(APPEND ${PROJECT_NAME}_DEPLIB ${OPENGL_DEPLIB} glfw)

add_definitions(-DENABLE_GLFW=1)
if(MSVC)
    add_definitions(-DNOMINMAX)
    add_definitions(-D_ALLOW_KEYWORD_MACROS=1)
elseif(APPLE)
    add_definitions(-Denable_if_t=enable_if)
endif()

include_directories(AFTER ${SOURCE_PATH}/hwcomposer)
file(GLOB HWCOMPOSER_SOURCE ${SOURCE_PATH}/hwcomposer/hwc2/*.h)
source_group(android.hardware.graphics.composer@2.1 FILES ${HWCOMPOSER_SOURCE})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${HWCOMPOSER_SOURCE})

# android.hidl.allocator@1.0
file(GLOB ALLOCATOR_SOURCE 
${SOURCE_PATH}/hidl/allocator/1.0/*.h
${SOURCE_PATH}/hidl/allocator/1.0/*.cpp
)
source_group(android.hidl.allocator@1.0 FILES ${ALLOCATOR_SOURCE})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${ALLOCATOR_SOURCE})

# android.hidl.memroy@1.0
file(GLOB MEMORY_SOURCE 
${SOURCE_PATH}/hidl/memory/1.0/*.h 
${SOURCE_PATH}/hidl/memory/1.0/*.cpp
)
source_group(android.hidl.memroy@1.0 FILES ${MEMORY_SOURCE})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${MEMORY_SOURCE})


# target files
set(LIB_TYPE SHARED)
ADD_LIB(hidlservice_default)


#set(ENABLE_TEST  TRUE)
if(ENABLE_TEST)
  add_subdirectory(test)
endif(ENABLE_TEST)
