
# EGL and OpenGL
if (ENABLE_DESKTOP_GL)
    add_definitions(-DENABLE_DESKTOP_GL=1)
    find_package(OpenGL REQUIRED)
    set(OPENGL_DEPLIB EGL ${OPENGL_gl_LIBRARY})
    include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/native/opengl/include)

elseif (ENABLE_ANGLE)
    add_definitions(-DENABLE_ANGLE=1)

    if (ENABLE_ANDROID_GL)
        add_definitions(-DEGL_EGLEXT_PROTOTYPES=1)
        add_definitions(-DGL_GLEXT_PROTOTYPES=1)
        set(OPENGL_DEPLIB  EGL GLESv2 GLESv1_CM)
        include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/native/opengl/include)

    else(ENABLE_ANDROID_GL)
        set(OPENGL_DEPLIB  EGL_angle GLESv2_angle GLESv1_CM_angle)
        include(${M3E_SOURCE_DIR}/cmake/external/angle/include.cmake)    
    endif(ENABLE_ANDROID_GL)

elseif (OPENGLES2_FOUND)
    set(OPENGL_DEPLIB EGL GLESv2 GLESv1_CM)
    #include_directories(AFTER ${EGL_INCLUDE_DIR})
    #include_directories(AFTER ${OPENGLES2_INCLUDE_DIR})
    #message(STATUS "OpenGLES lib: ${OPENGLES2_LIBRARY}")
    #message(STATUS "OpenGLES inc: ${OPENGLES2_INCLUDE_DIR}")

else()
    message(FATAL_ERROR "No OpenGLES library !")
endif()
