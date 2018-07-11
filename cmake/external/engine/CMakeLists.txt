
project(ENGINE)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/misc/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/stagefright_foundation/include.cmake)

set(ENGINE_DEPLIB
utils
stagefright_foundation
stagefright
audio
)

# dependency
set(ENGINE_DEP 
${ENGINE_DEPLIB}
)

# define
if(APPLE)
add_definitions(-DPATH_MAX=4096)
endif()

# include files
include_directories(AFTER ${M3E_SOURCE_DIR}/src/av/include)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/device)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/engine/include)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/engine/impl)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/engine/media)

# header files
file(GLOB ENGINE_HEADER_FILES 
${M3E_SOURCE_DIR}/src/engine/include/*.h 
${M3E_SOURCE_DIR}/src/engine/impl/*.h 
${M3E_SOURCE_DIR}/src/engine/media/*.h 
)

# source files
file(GLOB ENGINE_SOURCE_FILES 
${M3E_SOURCE_DIR}/src/engine/media/*.cpp
)
set(ENGINE_SOURCE_FILES ${ENGINE_SOURCE_FILES}
${M3E_SOURCE_DIR}/src/engine/impl/CAsyncEncoder.cpp
${M3E_SOURCE_DIR}/src/engine/impl/CAsyncEncoderGroup.cpp
${M3E_SOURCE_DIR}/src/engine/impl/CEncoderClient.cpp
${M3E_SOURCE_DIR}/src/engine/impl/CEngineAnalyzer.cpp
${M3E_SOURCE_DIR}/src/engine/impl/CEngineFactory.cpp
${M3E_SOURCE_DIR}/src/engine/impl/CEngineMonitor.cpp
${M3E_SOURCE_DIR}/src/engine/impl/CPlayerClient.cpp
)

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(engine SHARED ${ENGINE_SOURCE_FILES} ${ENGINE_HEADER_FILES})
target_link_libraries(engine ${ENGINE_DEPLIB})
