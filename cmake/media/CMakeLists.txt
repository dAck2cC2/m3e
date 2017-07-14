
project(MEDIA)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/utils.cmake)
include(${M3E_SOURCE_DIR}/cmake/misc.cmake)

set(MEDIA_DEPLIB
utils
misc
stagefright_foundation
)

# dependency
set(MEDIA_DEP 
${MEDIA_DEPLIB}
)

# define
if(APPLE)
add_definitions(-Disnanf=isnan)
endif()

# include files
include_directories(AFTER ${M3E_SOURCE_DIR}/src/av/include)

# header files
file(GLOB MEDIA_HEADER_FILES 
${M3E_SOURCE_DIR}/src/av/include/media/*.h 
)

# source files
file(GLOB MEDIA_SOURCE_FILES 
${M3E_SOURCE_DIR}/src/av/media/libmedia/*.cpp
)

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(media SHARED ${MEDIA_SOURCE_FILES} ${MEDIA_HEADER_FILES})
target_link_libraries(media ${MEDIA_DEPLIB})

