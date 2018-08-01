
# EGL and OpenGL
if (ENABLE_NATIVE_GL)
    add_definitions(-DENABLE_NATIVE_GL=1)

    find_package(OpenGL REQUIRED)
    set(OPENGL_DEPLIB EGL ${OPENGL_gl_LIBRARY})

    include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/native/opengl/include)

elseif (ENABLE_ANGLE)
    set(OPENGL_DEPLIB  angle)
    
    include(${M3E_SOURCE_DIR}/cmake/external/angle/include.cmake)

endif()
