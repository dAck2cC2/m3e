project(TEST_MEDIANDK)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${INITRC_INCLUDE})
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/media/ndk/include.cmake)

set(${PROJECT_NAME}_DEPLIB
initrc
mediandk
)

if (MSVC)
    add_definitions(-UMEDIANDK_API)

    include(${MSVC_INCLUDE})
    list(APPEND ${PROJECT_NAME}_DEPLIB ${LIB_MSVC_WRAP})
endif()

set(${PROJECT_NAME}_SOURCE_FILES 
${M3E_SOURCE_DIR}/src/frameworks/av/media/ndk/tests/nativecodec.cpp
${M3E_SOURCE_DIR}/src/frameworks/av/media/ndk/tests/looper.cpp
${M3E_SOURCE_DIR}/src/frameworks/av/media/ndk/tests/looper.h
)


# project
set(EXECUTABLE_OUTPUT_PATH ${BUILD_PATH})
add_executable(test_mediandk ${${PROJECT_NAME}_SOURCE_FILES})
target_link_libraries(test_mediandk ${${PROJECT_NAME}_DEPLIB})

