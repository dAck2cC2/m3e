
project(MISC)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/misc/include.cmake)

set(MISC_DEPLIB
utils
)

# dependency
set(MISC_DEP ${MISC_DEPLIB})

# include files
include_directories(AFTER ${M3E_SOURCE_DIR}/src/av/include)

# header files
file(GLOB MISC_HEADER_FILES 
${M3E_SOURCE_DIR}/src/av/external/audio_utils/*.h 
${M3E_SOURCE_DIR}/src/av/external/binder/*.h
${M3E_SOURCE_DIR}/src/av/external/libdrmframework/*.h
${M3E_SOURCE_DIR}/src/av/external/netd/*.h
)

# source files
file(GLOB MISC_SOURCE_FILES 
${M3E_SOURCE_DIR}/src/av/external/audio_utils/*.cpp 
${M3E_SOURCE_DIR}/src/av/external/binder/*.cpp
${M3E_SOURCE_DIR}/src/av/external/libdrmframework/*.cpp
${M3E_SOURCE_DIR}/src/av/external/netd/*.cpp
)

if(ENABLE_CODEC_SELECTOR)
set(MISC_HEADER_FILES ${MISC_HEADER_FILES}
${M3E_SOURCE_DIR}/src/av/external/ui/Fence.h
${M3E_SOURCE_DIR}/src/av/external/ui/GraphicBuffer.h
${M3E_SOURCE_DIR}/src/av/external/ui/Region.h
${M3E_SOURCE_DIR}/src/av/external/mediautils/BatteryNotifier.h
${M3E_SOURCE_DIR}/src/av/external/gui/Surface.h
)
set(MISC_SOURCE_FILES ${MISC_SOURCE_FILES}
${M3E_SOURCE_DIR}/src/av/external/ui/Fence.cpp
${M3E_SOURCE_DIR}/src/av/external/ui/GraphicBuffer.cpp
${M3E_SOURCE_DIR}/src/av/external/ui/Region.cpp
${M3E_SOURCE_DIR}/src/av/external/mediautils/BatteryNotifier.cpp
${M3E_SOURCE_DIR}/src/av/external/gui/Surface.cpp
#${M3E_SOURCE_DIR}/src/av/external/rs/cpp/Allocation.cpp
)
endif(ENABLE_CODEC_SELECTOR)

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(misc SHARED ${MISC_SOURCE_FILES} ${MISC_HEADER_FILES})
target_link_libraries(misc ${MISC_DEPLIB})

#add_dependencies()
#ADD_DEPENDENCIES(misc ${LIBMISC_DEP})
