
project(AUDIO)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)

set(AUDIO_DEPLIB
utils
)

# dependency
set(AUDIO_DEP 
${AUDIO_DEPLIB}
)

# define
if(CYGWIN)
add_definitions(-D_GNU_SOURCE)
endif()

# include files
include_directories(AFTER ${M3E_SOURCE_DIR}/src/device/audio)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/av/external)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/av/include)

# header files
file(GLOB AUDIO_HEADER_FILES 
${M3E_SOURCE_DIR}/src/device/audio/*.h 
)

# source files
set(AUDIO_SOURCE_FILES
${M3E_SOURCE_DIR}/src/device/audio/AudioSinkFactory.cpp
${M3E_SOURCE_DIR}/src/device/audio/AudioSinkBase.cpp
${M3E_SOURCE_DIR}/src/device/audio/DumpSink.cpp
)

# OpenAL
if(APPLE OR CYGWIN)
if(APPLE)
    find_path(OPENAL_INCLUDE al.h)
    include_directories(AFTER ${OPENAL_INCLUDE})

    find_library(OPENAL_LIBRARY OpenAL)
    mark_as_advanced(OPENAL_LIBRARY)
    set(AUDIO_DEPLIB ${AUDIO_DEPLIB} ${OPENAL_LIBRARY})
elseif(CYGWIN)
    include_directories(AFTER /usr/include/AL)
    set(AUDIO_DEPLIB ${AUDIO_DEPLIB} openal)    
endif()

add_definitions(-DENABLE_AUDIO_OPENAL)
set(AUDIO_SOURCE_FILES ${AUDIO_SOURCE_FILES}
${M3E_SOURCE_DIR}/src/device/audio/OpenALSink.cpp
)
endif()

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(audio SHARED ${AUDIO_SOURCE_FILES} ${AUDIO_HEADER_FILES})
target_link_libraries(audio ${AUDIO_DEPLIB})

