
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
${M3E_SOURCE_DIR}/src/av/external/gui/BufferItem.h
${M3E_SOURCE_DIR}/src/av/external/gui/BufferQueue.h
${M3E_SOURCE_DIR}/src/av/external/gui/IConsumerListener.h
${M3E_SOURCE_DIR}/src/av/external/rs/cpp/RenderScript.h
${M3E_SOURCE_DIR}/src/av/external/rs/cpp/rsCppStructs.h
${M3E_SOURCE_DIR}/src/av/external/rs/rsDefines.h
)
set(MISC_SOURCE_FILES ${MISC_SOURCE_FILES}
${M3E_SOURCE_DIR}/src/av/external/ui/Fence.cpp
${M3E_SOURCE_DIR}/src/av/external/ui/GraphicBuffer.cpp
${M3E_SOURCE_DIR}/src/av/external/ui/Region.cpp
${M3E_SOURCE_DIR}/src/av/external/mediautils/BatteryNotifier.cpp
${M3E_SOURCE_DIR}/src/av/external/gui/Surface.cpp
${M3E_SOURCE_DIR}/src/av/external/gui/BufferItem.cpp
${M3E_SOURCE_DIR}/src/av/external/gui/BufferQueue.cpp
${M3E_SOURCE_DIR}/src/av/external/gui/IConsumerListener.cpp
${M3E_SOURCE_DIR}/src/av/external/rs/cpp/BaseObj.cpp
${M3E_SOURCE_DIR}/src/av/external/rs/cpp/Allocation.cpp
${M3E_SOURCE_DIR}/src/av/external/rs/cpp/Type.cpp
${M3E_SOURCE_DIR}/src/av/external/rs/cpp/RenderScript.cpp
${M3E_SOURCE_DIR}/src/av/external/rs/cpp/Element.cpp
${M3E_SOURCE_DIR}/src/av/external/rs/cpp/ScriptIntrinsics.cpp
${M3E_SOURCE_DIR}/src/av/external/rs/cpp/Script.cpp
)
add_definitions(-DPATH_MAX=4096)
add_definitions(-DRS_COMPATIBILITY_LIB)
endif(ENABLE_CODEC_SELECTOR)

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(misc SHARED ${MISC_SOURCE_FILES} ${MISC_HEADER_FILES})
target_link_libraries(misc ${MISC_DEPLIB})

#add_dependencies()
#ADD_DEPENDENCIES(misc ${LIBMISC_DEP})
