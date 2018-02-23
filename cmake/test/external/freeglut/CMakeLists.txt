
# gtest program

project(TEST_GLUT)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/freeglut/include.cmake)

# dependency

set(TEST_GLUT_DEPLIB
freeglut
)

MACRO(ADD_DEMO name)
    SET(EXECUTABLE_OUTPUT_PATH ${BUILD_PATH})
    ADD_EXECUTABLE(test_glut_${name} ${ARGN})
    TARGET_LINK_LIBRARIES(test_glut_${name} ${TEST_GLUT_DEPLIB})
    IF(WIN32 AND MSVC)
        SET_TARGET_PROPERTIES(test_glut_${name} PROPERTIES DEBUG_POSTFIX d)
    ENDIF()
ENDMACRO()

ADD_DEMO(CallbackMaker   ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/progs/demos/CallbackMaker/CallbackMaker.c)
ADD_DEMO(Fractals        ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/progs/demos/Fractals/fractals.c)
ADD_DEMO(Fractals_random ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/progs/demos/Fractals_random/fractals_random.c)
ADD_DEMO(Lorenz          ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/progs/demos/Lorenz/lorenz.c)
IF (NOT WIN32)
    ADD_DEMO(One             ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/progs/demos/One/one.c)
ELSE()
    ADD_DEMO(One             ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/progs/demos/One/one.c
                             ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/progs/demos/One/one.rc)
ENDIF()
ADD_DEMO(Resizer         ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/progs/demos/Resizer/Resizer.cpp)
ADD_DEMO(multi-touch     ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/progs/demos/multi-touch/multi-touch.c)
ADD_DEMO(shapes          ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/progs/demos/shapes/shapes.c
                         ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/progs/demos/shapes/glmatrix.h
                        ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/progs/demos/shapes/glmatrix.c)
ADD_DEMO(smooth_opengl3  ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/progs/demos/smooth_opengl3/smooth_opengl3.c)
IF(UNIX)
    ADD_DEMO(spaceball       ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/progs/demos/spaceball/spaceball.c
                             ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/progs/demos/spaceball/vmath.c
                             ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/progs/demos/spaceball/vmath.h)
ENDIF()
ADD_DEMO(subwin          ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/progs/demos/subwin/subwin.c)
ADD_DEMO(timer           ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/progs/demos/timer/timer.c)
ADD_DEMO(timer_callback  ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/progs/demos/timer_callback/timer.c)

