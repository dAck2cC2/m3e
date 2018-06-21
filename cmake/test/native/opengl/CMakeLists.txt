
project(TEST_OPENGL)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/initrc/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/opengl/EGL/include.cmake)

set(DEMO_DEPLIBS 
initrc
EGL
)

ADD_DEMO(egl   ${M3E_SOURCE_DIR}/src/test/native/opengl/test_egl.cpp)
