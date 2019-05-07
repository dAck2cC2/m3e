
if (MSVC)
    add_definitions(-DLI_API=__declspec\(dllimport\))
else()
    add_definitions(-DLI_API= )
endif()

