
if (APPLE)
    add_definitions(-DGLFW_EXPOSE_NATIVE_COCOA)
elseif (MSVC)
    add_definitions(-DGLFW_EXPOSE_NATIVE_WIN32)
endif()

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/glfw/include)
