
project(STAGEFRIGHT_FOUNDATION)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/misc/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/stagefright_foundation/include.cmake)

set(STAGEFRIGHT_FOUNDATION_DEPLIB
utils
misc
)

# dependency
set(STAGEFRIGHT_FOUNDATION_DEP 
${STAGEFRIGHT_FOUNDATION_DEPLIB}
)

# define
if(CYGWIN)
add_definitions(-D_GNU_SOURCE)
endif()

# include files
include_directories(AFTER ${M3E_SOURCE_DIR}/src/av/include)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/av/include/media/stagefright/foundation)

# header files
file(GLOB STAGEFRIGHT_FOUNDATION_HEADER_FILES 
${M3E_SOURCE_DIR}/src/av/include/media/stagefright/foundation/*.h 
)

# source files
#file(GLOB STAGEFRIGHT_FOUNDATION_SOURCE_FILES 
#${M3E_SOURCE_DIR}/src/av/media/libstagefright/foundation/*.cpp
#)
set(STAGEFRIGHT_FOUNDATION_SOURCE_FILES
${M3E_SOURCE_DIR}/src/av/media/libstagefright/foundation/AAtomizer.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/foundation/ABitReader.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/foundation/ABuffer.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/foundation/ADebug.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/foundation/AHandler.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/foundation/AHierarchicalStateMachine.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/foundation/ALooper.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/foundation/ALooperRoster.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/foundation/AMessage.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/foundation/AString.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/foundation/AStringUtils.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/foundation/ColorUtils.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/foundation/MediaBuffer.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/foundation/MediaBufferGroup.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/foundation/MetaData.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/foundation/ParsedMessage.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/foundation/base64.cpp
${M3E_SOURCE_DIR}/src/av/media/libstagefright/foundation/hexdump.cpp
)

# target files
set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(stagefright_foundation SHARED ${STAGEFRIGHT_FOUNDATION_SOURCE_FILES} ${STAGEFRIGHT_FOUNDATION_HEADER_FILES})
target_link_libraries(stagefright_foundation ${STAGEFRIGHT_FOUNDATION_DEPLIB})
