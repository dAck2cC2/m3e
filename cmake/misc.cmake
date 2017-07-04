
# dependency
SET(LIBMISC_DEP utils)

# header files
if(MSVC)
#ADD_DEFINITIONS(-D-Doff64_t=_off64_t)
#ADD_DEFINITIONS(-DHAVE_WIN32_THREADS)
INCLUDE_DIRECTORIES(AFTER ${M3E_SOURCE_DIR}/src/native/msvc)
endif()
INCLUDE_DIRECTORIES(AFTER ${M3E_SOURCE_DIR}/src/av/external)
INCLUDE_DIRECTORIES(AFTER ${M3E_SOURCE_DIR}/src/native/include)
INCLUDE_DIRECTORIES(AFTER ${M3E_SOURCE_DIR}/src/av/include)

# source files
FILE(GLOB LIBMISC_SOURCE_FILES 
#${M3E_SOURCE_DIR}/src/av/external/audio_utils/*.cpp 
#${M3E_SOURCE_DIR}/src/av/external/binder/*.cpp
${M3E_SOURCE_DIR}/src/av/external/libdrmframework/*.cpp
#${M3E_SOURCE_DIR}/src/av/external/netd/*.cpp
)

# target files
ADD_LIBRARY(misc SHARED ${LIBMISC_SOURCE_FILES})
TARGET_LINK_LIBRARIES(misc utils)

ADD_DEPENDENCIES(misc ${LIBMISC_DEP})
