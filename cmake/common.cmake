
# common definition
set(BUILD_PATH  ${M3E_BINARY_DIR}/build)
set(MSVC_PATH   ${M3E_SOURCE_DIR}/src/system/msvc)
set(EXT_PATH    external)

# test application
macro(ADD_DEMO name)
    set(EXECUTABLE_OUTPUT_PATH ${BUILD_PATH})
    add_executable(test_${name} ${ARGN})
    target_link_libraries(test_${name} ${DEMO_DEPLIBS})
    if(WIN32 AND MSVC)
        set_target_properties(test_${name} PROPERTIES DEBUG_POSTFIX d)
    endif()
endmacro()
