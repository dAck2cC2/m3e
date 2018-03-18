
project(GUI)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/hardware/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/native/binder/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/native/gui/include.cmake)

#include_directories(AFTER ${M3E_SOURCE_DIR}/src/native/include/private)

add_definitions(-DANDROID_IMPLEMENTATION=1)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/native/include )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/native/gui )

# dependency
set(GUI_DEPLIB
binder
utils
cutils
log
)

# header files
file(GLOB GUI_HEADER_FILES  ${HEADER_PATH}/gui/*.h)

#file(GLOB GUI_PRIVATE_HEADER ${HEADER_PATH}/private/gui/*.h)
#list(APPEND GUI_HEADER_FILES ${GUI_PRIVATE_HEADER})

# source files
#file(GLOB GUI_SOURCE_FILES ${SOURCE_PATH}/*.cpp)
set(GUI_SOURCE_FILES 
#${SOURCE_PATH}/BitTube.cpp
#${SOURCE_PATH}/BufferItem.cpp
#${SOURCE_PATH}/BufferItemConsumer.cpp
#${SOURCE_PATH}/BufferQueue.cpp
#${SOURCE_PATH}/Surface.cpp
)

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(gui SHARED ${GUI_SOURCE_FILES} ${GUI_HEADER_FILES})
target_link_libraries(gui ${GUI_DEPLIB})
