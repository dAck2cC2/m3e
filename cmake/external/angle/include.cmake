
# include
add_definitions(-DEGL_EGLEXT_PROTOTYPES)
add_definitions(-DGL_GLEXT_PROTOTYPES)
add_definitions(-DGL_GLES_PROTOTYPES)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/include)
