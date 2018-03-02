
# demo program

project(TEST_SKIA)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/skia/include.cmake)

set(SRC_SKIA_SAMPLE
${M3E_SOURCE_DIR}/${EXT_PATH}/skia/samplecode/SampleCode.h
${M3E_SOURCE_DIR}/${EXT_PATH}/skia/samplecode/SampleCode.cpp
)

# core ####################################
set(DEMO_DEPLIBS
skia
)
ADD_DEMO(skia_core   ${M3E_SOURCE_DIR}/src/${EXT_PATH}/skia/test_core.cpp)

# OpenGL ####################################
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/skia/src/gpu)
include(${M3E_SOURCE_DIR}/cmake/external/freeglut/include.cmake)
set(DEMO_DEPLIBS
skia
freeglut
)
ADD_DEMO(skia_glut   ${M3E_SOURCE_DIR}/src/${EXT_PATH}/skia/test_glut.cpp
                     #${SRC_SKIA_SAMPLE}
                     )
