# gtest program

project(TEST_GLUI)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/glui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/freeglut/include.cmake)

# dependency

set(TEST_GLUI_DEPLIB
glui
)

MACRO(ADD_DEMO name)
    SET(EXECUTABLE_OUTPUT_PATH ${BUILD_PATH})
    ADD_EXECUTABLE(test_glui_${name} ${ARGN})
    TARGET_LINK_LIBRARIES(test_glui_${name} ${TEST_GLUI_DEPLIB})
    IF(WIN32 AND MSVC)
        SET_TARGET_PROPERTIES(test_glui_${name} PROPERTIES DEBUG_POSTFIX d)
    ENDIF()
ENDMACRO()

ADD_DEMO(example1   ${M3E_SOURCE_DIR}/${EXT_PATH}/glui/example/example1.cpp)
ADD_DEMO(example2   ${M3E_SOURCE_DIR}/${EXT_PATH}/glui/example/example2.cpp)
ADD_DEMO(example3   ${M3E_SOURCE_DIR}/${EXT_PATH}/glui/example/example3.cpp)
ADD_DEMO(example4   ${M3E_SOURCE_DIR}/${EXT_PATH}/glui/example/example4.cpp)
ADD_DEMO(example5   ${M3E_SOURCE_DIR}/${EXT_PATH}/glui/example/example5.cpp)
ADD_DEMO(example6   ${M3E_SOURCE_DIR}/${EXT_PATH}/glui/example/example6.cpp)
