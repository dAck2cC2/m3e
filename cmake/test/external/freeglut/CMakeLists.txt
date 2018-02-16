
# gtest program

project(TEST_GLUT)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/freeglut/include.cmake)

# dependency

set(TEST_GLUT_DEPLIB
freeglut
)

# test file

set(TEST_GLUT_SOURCE_FILES 
${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/progs/demos/Lorenz/lorenz.c
#${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/progs/demos/shapes/shapes.c
#${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/progs/demos/shapes/glmatrix.h
#${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/progs/demos/shapes/glmatrix.c
)

# project
set(EXECUTABLE_OUTPUT_PATH ${BUILD_PATH})
add_executable(test_glut ${TEST_GLUT_SOURCE_FILES})
target_link_libraries(test_glut ${TEST_GLUT_DEPLIB})
