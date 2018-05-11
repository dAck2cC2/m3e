
if (APPLE)
    add_definitions(-D__WXOSX_COCOA__=1)
endif()

include_directories(AFTER ${M3E_BINARY_DIR}/wxWidgets)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/wxWidgets/include)
