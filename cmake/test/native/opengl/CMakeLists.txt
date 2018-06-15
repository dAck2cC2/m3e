
project(TEST_OPENGL)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/EGL/include.cmake)

set(DEMO_DEPLIBS 
EGL
)

ADD_DEMO(egl   ${M3E_SOURCE_DIR}/src/test/native/opengl/test_egl.cpp)
