
# include
add_definitions(-DEGL_EGLEXT_PROTOTYPES)
add_definitions(-DGL_GLEXT_PROTOTYPES)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/include)

# angle util
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/util)
