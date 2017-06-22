
file(GLOB UTILS_SOURCE_FILES ${M3E_SOURCE_DIR}/src/native/libutils/*.c ${M3E_SOURCE_DIR}/src/native/libutils/*.cpp)
include_directories(${M3E_SOURCE_DIR}/src/native/include)
add_library(utils SHARED ${UTILS_SOURCE_FILES})
