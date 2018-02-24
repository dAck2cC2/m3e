
# demo program

project(TEST_ASSIMP)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/assimp/include.cmake)

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT/freeglut/freeglut/include/GL)

# dependency

IF ( MSVC )
  SET(M_LIB)
ELSE ( MSVC )
  find_library(M_LIB m)
ENDIF ( MSVC )

set(DEMO_DEPLIBS
freeglut
assimp
${M_LIB}
)

ADD_DEMO(assimp_SimpleOpenGL  
${M3E_SOURCE_DIR}/${EXT_PATH}/assimp/samples/SimpleOpenGL/Sample_SimpleOpenGL.c)
