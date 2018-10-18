
# demo program

project(TEST_GLUT)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/freeglut/include.cmake)

# dependency

set(DEMO_DEPLIBS
freeglut
)

ADD_DEMO(glut_CallbackMaker   ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/progs/demos/CallbackMaker/CallbackMaker.c)
ADD_DEMO(glut_Fractals        ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/progs/demos/Fractals/fractals.c)
ADD_DEMO(glut_Fractals_random ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/progs/demos/Fractals_random/fractals_random.c)
ADD_DEMO(glut_Lorenz          ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/progs/demos/Lorenz/lorenz.c)
IF (NOT WIN32)
    ADD_DEMO(glut_One             ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/progs/demos/One/one.c)
ELSE()
    ADD_DEMO(glut_One             ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/progs/demos/One/one.c
                             ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/progs/demos/One/one.rc)
ENDIF()
ADD_DEMO(glut_Resizer         ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/progs/demos/Resizer/Resizer.cpp)
ADD_DEMO(glut_multi-touch     ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/progs/demos/multi-touch/multi-touch.c)
ADD_DEMO(glut_shapes          ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/progs/demos/shapes/shapes.c
                         ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/progs/demos/shapes/glmatrix.h
                        ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/progs/demos/shapes/glmatrix.c)
ADD_DEMO(glut_smooth_opengl3  ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/progs/demos/smooth_opengl3/smooth_opengl3.c)
IF(UNIX)
    ADD_DEMO(glut_spaceball       ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/progs/demos/spaceball/spaceball.c
                             ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/progs/demos/spaceball/vmath.c
                             ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/progs/demos/spaceball/vmath.h)
ENDIF()
ADD_DEMO(glut_subwin          ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/progs/demos/subwin/subwin.c)
ADD_DEMO(glut_timer           ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/progs/demos/timer/timer.c)
ADD_DEMO(glut_timer_callback  ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/progs/demos/timer_callback/timer.c)

ADD_DEMO(glut_simple  ${M3E_SOURCE_DIR}/src/${EXT_PATH}/freeglut/test_simple.c)
