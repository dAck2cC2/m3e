
find_package(OpenGL REQUIRED)
set(OPENGL_DEPLIB 
EGL 
${OPENGL_gl_LIBRARY}
)

# include
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/native/opengl/include)
