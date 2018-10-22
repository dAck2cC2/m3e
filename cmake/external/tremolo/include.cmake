
if (APPLE)
    add_definitions(-D__MACOSX__=1)
endif()

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/tremolo)
