
# demo program

project(TEST_GLUI)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/glui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/freeglut/include.cmake)

# dependency

set(DEMO_DEPLIBS
glui
)

ADD_DEMO(glui_example1   ${M3E_SOURCE_DIR}/${EXT_PATH}/glui/example/example1.cpp)
ADD_DEMO(glui_example2   ${M3E_SOURCE_DIR}/${EXT_PATH}/glui/example/example2.cpp)
ADD_DEMO(glui_example3   ${M3E_SOURCE_DIR}/${EXT_PATH}/glui/example/example3.cpp)
ADD_DEMO(glui_example4   ${M3E_SOURCE_DIR}/${EXT_PATH}/glui/example/example4.cpp)
ADD_DEMO(glui_example5   ${M3E_SOURCE_DIR}/${EXT_PATH}/glui/example/example5.cpp)
ADD_DEMO(glui_example6   ${M3E_SOURCE_DIR}/${EXT_PATH}/glui/example/example6.cpp)
