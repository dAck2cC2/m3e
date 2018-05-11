
# common definition
set(BUILD_PATH  ${M3E_BINARY_DIR}/build)
set(MSVC_PATH   ${M3E_SOURCE_DIR}/src/system/msvc)
set(EXT_PATH    external)

# external module from android
set(EXT_LINK https://android.googlesource.com/platform)
set(EXT_TAG android-7.1.0_r7)

# download module
macro(GET_ANDROID_MODULE name)
    if(NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH}/${name})
        message(STATUS "Download\t ${name}")
        exec_program("git clone ${EXT_LINK}/${EXT_PATH}/${name}" ${M3E_SOURCE_DIR}/${EXT_PATH})
        exec_program("git checkout tags/${EXT_TAG}" ${M3E_SOURCE_DIR}/${EXT_PATH}/${name})

        # apply patch
        if (EXISTS ${M3E_SOURCE_DIR}/src/${EXT_PATH}/${name}/${name}.patch)
            exec_program("git apply ${M3E_SOURCE_DIR}/src/${EXT_PATH}/${name}/${name}.patch" ${M3E_SOURCE_DIR}/${EXT_PATH}/${name})
        endif()
    endif()
endmacro()

# test application
macro(ADD_DEMO name)
    set(EXECUTABLE_OUTPUT_PATH ${BUILD_PATH})
    add_executable(test_${name} ${ARGN})
    target_link_libraries(test_${name} ${DEMO_DEPLIBS})
    if(WIN32 AND MSVC)
        set_target_properties(test_${name} PROPERTIES DEBUG_POSTFIX d)
    endif()
endmacro()
