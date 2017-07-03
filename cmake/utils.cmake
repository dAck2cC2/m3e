
# header files
#SET(CMAKE_INCLUDE_DIRECTORIES_BEFORE, ON)
if(MSVC)
ADD_DEFINITIONS(-DHAVE_MS_C_RUNTIME)
INCLUDE_DIRECTORIES(AFTER ${M3E_SOURCE_DIR}/src/native/msvc)
endif()
INCLUDE_DIRECTORIES(AFTER ${M3E_SOURCE_DIR}/src/native/include)

# source files
file(GLOB LIBUTILS_SOURCE_FILES 
${M3E_SOURCE_DIR}/src/native/libutils/*.c 
${M3E_SOURCE_DIR}/src/native/libutils/*.cpp
#${M3E_SOURCE_DIR}/src/native/libutils/cutils/*.c
)

# target files
ADD_LIBRARY(utils SHARED ${LIBUTILS_SOURCE_FILES})
