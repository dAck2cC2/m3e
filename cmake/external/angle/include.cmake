
# include
add_definitions(-DEGL_EGL_PROTOTYPES=1)
add_definitions(-DEGL_EGLEXT_PROTOTYPES=1)
add_definitions(-DGL_GLES_PROTOTYPES=1)
add_definitions(-DGL_GLEXT_PROTOTYPES=1)

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/include)
