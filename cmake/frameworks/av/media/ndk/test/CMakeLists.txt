project(TEST_MEDIANDK)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/initrc/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/ndk/include.cmake)

set(${PROJECT_NAME}_DEPLIB
initrc
mediandk
)

if (MSVC)
    add_definitions(-UMEDIANDK_API)
endif()

set(${PROJECT_NAME}_SOURCE_FILES 
${M3E_SOURCE_DIR}/src/frameworks/av/media/ndk/tests/nativecodec.cpp
)


# project
set(EXECUTABLE_OUTPUT_PATH ${BUILD_PATH})
add_executable(test_mediandk ${${PROJECT_NAME}_SOURCE_FILES})
target_link_libraries(test_mediandk ${${PROJECT_NAME}_DEPLIB})

