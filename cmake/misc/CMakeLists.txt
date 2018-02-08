
project(MISC)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/misc/include.cmake)

set(MISC_DEPLIB
utils
)

# dependency
set(MISC_DEP ${MISC_DEPLIB})

# include files
#include_directories(AFTER ${M3E_SOURCE_DIR}/src/av/include)

add_definitions(-DLITTLE_ENDIAN=1)
add_definitions(-DBIG_ENDIAN=2)
if(MSVC OR APPLE)
add_definitions(-DBYTE_ORDER=LITTLE_ENDIAN)
endif()

# header files
file(GLOB MISC_HEADER_FILES 
${M3E_SOURCE_DIR}/src/misc/binder/*.h
)

# source files
file(GLOB MISC_SOURCE_FILES 
${M3E_SOURCE_DIR}/src/misc/binder/*.cpp
)

if(MSVC)
set(MISC_SOURCE_FILES ${MISC_SOURCE_FILES}
${M3E_SOURCE_DIR}/src/core/msvc/getpagesize.c
)
endif()

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(misc SHARED ${MISC_SOURCE_FILES} ${MISC_HEADER_FILES})
target_link_libraries(misc ${MISC_DEPLIB})

#add_dependencies()
#ADD_DEPENDENCIES(misc ${LIBMISC_DEP})
