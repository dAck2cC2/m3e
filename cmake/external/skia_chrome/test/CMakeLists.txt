
# demo program

project(TEST_SKIA_CHROME)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/skia_chrome/include.cmake)

# core ####################################
set(DEMO_DEPLIBS
skia_chrome
)
ADD_DEMO(skia_chrome_core   ${M3E_SOURCE_DIR}/src/${EXT_PATH}/skia_chrome/test_core.cpp)

# OpenGL ####################################
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia_chrome/src/gpu)
include(${M3E_SOURCE_DIR}/cmake/external/freeglut/include.cmake)
set(DEMO_DEPLIBS
skia_chrome
freeglut
)
ADD_DEMO(skia_glut   ${M3E_SOURCE_DIR}/src/${EXT_PATH}/skia_chrome/test_glut.cpp)
