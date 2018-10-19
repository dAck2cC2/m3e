
if (MSVC)
    add_definitions(-DEAS_PUBLIC=__declspec\(dllimport\))
endif()

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/sonivox/)
