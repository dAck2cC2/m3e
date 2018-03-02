
project(MISC)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/misc/include.cmake)

add_definitions(-DANDROID_IMPLEMENTATION=1)

# dependency
set(MISC_DEPLIB
utils
)

# include files
#include_directories(AFTER ${M3E_SOURCE_DIR}/src/av/include)

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
