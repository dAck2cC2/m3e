
project(M3ECMD)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/utils/include.cmake)

# dependency
set(M3ECMD_DEPLIB
utils
stagefright_foundation
stagefright
engine
)

set(M3ECMD_DEP ${M3ECMD_DEPLIB})

# include
include_directories(AFTER ${M3E_SOURCE_DIR}/src/av/include)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/engine/include)

# main source
set(M3ECMD_SOURCE_FILES 
${M3E_SOURCE_DIR}/src/engine/cmd/main.cpp
)

# project
set(EXECUTABLE_OUTPUT_PATH ${BUILD_PATH})
add_executable(m3ecmd ${M3ECMD_SOURCE_FILES})
target_link_libraries(m3ecmd ${M3ECMD_DEPLIB})
