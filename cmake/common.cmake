###############################################################################
# common definition
set(BUILD_PATH    ${M3E_BINARY_DIR}/build)
set(MSVC_PATH     ${M3E_SOURCE_DIR}/src/external/msvc)
set(MSVC_INCLUDE  ${M3E_SOURCE_DIR}/cmake/external/msvc/include.cmake)
set(GENERIC_PATH  ${M3E_SOURCE_DIR}/src/system/generic)
set(EXT_PATH      external)
set(TMP_PATH      ${M3E_BINARY_DIR}/intermediates)
#set(M3E_CFG_PATH  ${BUILD_PATH}/header)
set(TOOL_PATH     ${M3E_SOURCE_DIR}/tool/build)

if(MSVC)
    set(BIN_HIDL_GEN  ${M3E_SOURCE_DIR}/tool/build/hidl-gen.exe)
else()
    set(BIN_HIDL_GEN  ${M3E_SOURCE_DIR}/tool/build/hidl-gen)
endif()
set(HIDL_HEADER_PATH  hidlc++_headers)
set(HIDL_SOURCE_PATH  hidlc++)
set(HIDL_ROOT_PATH    ${M3E_SOURCE_DIR}/${EXT_PATH}/hidl_root)

if(MSVC)
    set(BIN_AIDL_CPP  ${M3E_SOURCE_DIR}/tool/build/aidl-cpp.exe)
else()
    set(BIN_AIDL_CPP  ${M3E_SOURCE_DIR}/tool/build/aidl-cpp)
endif()
set(AIDL_HEADER_PATH  aidlc++_headers)
set(AIDL_SOURCE_PATH  aidlc++)


# refer to 
# frameworks/av/media/libstagefright/MediaExtractorFactory.cpp
# void MediaExtractorFactory::UpdateExtractors
set(SYS_EXTR_PATH ${BUILD_PATH}/system/extractors)
set(VND_EXTR_PATH ${BUILD_PATH}/vendor/extractors)

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${BUILD_PATH}" ) #->define path for archive
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${BUILD_PATH}" ) #->define path for Library
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BUILD_PATH}" ) #->define path for Runtime

if (MSVC)
    set(LIB_TYPE STATIC)
else(MSVC)
    set(LIB_TYPE SHARED)
endif(MSVC)

###############################################################################
# external module from android
set(EXT_LINK https://android.googlesource.com/platform)
set(EXT_TAG android-9.0.0_r56)
set(EXT_TAG_UPDATE android-9.0.0_r56)

set(EXT_UPDATE 
safe-iop
zlib
boringssl
expat
aac
dng_sdk
flac
giflib
libgsm
piex
libpng
sonic
sonivox
tremolo
libvpx
webp
libyuv
skia
)

# moudles which are going to be updated
#jsoncpp
#jpeg
#libhevc

###############################################################################
# download module
macro(GET_ANDROID_MODULE name)
    foreach(update_name ${EXT_UPDATE})
        if (${name} MATCHES ${update_name})
            set(EXT_TAG ${EXT_TAG_UPDATE})
        endif()
    endforeach()

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

###############################################################################
# test application
macro(ADD_DEMO name)
    set(EXECUTABLE_OUTPUT_PATH ${BUILD_PATH})
    add_executable(test_${name} ${ARGN})
    target_link_libraries(test_${name} ${DEMO_DEPLIBS})
    if(WIN32 AND MSVC)
        set_target_properties(test_${name} PROPERTIES DEBUG_POSTFIX d)
    endif()
endmacro()

###############################################################################
# public the API for dll
macro(DLL_PUBLIC name)
    if(${PROJECT_NAME} STREQUAL ${name})
        if(MSVC)
            add_definitions(-DANDROID_API_${name}=__declspec\(dllexport\))
        else(MSVC)
            add_definitions(-DANDROID_API_${name}= )
        endif(MSVC)    
    else()
        if(MSVC)
            add_definitions(-DANDROID_API_${name}=__declspec\(dllimport\))
        else(MSVC)
            add_definitions(-DANDROID_API_${name}= )
        endif(MSVC)
        #add_definitions(-DANDROID_API= )
    endif()
endmacro()

###############################################################################
# buid library
macro(ADD_LIB name)
    set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
    add_library(${name} ${LIB_TYPE} ${${PROJECT_NAME}_SOURCE_FILES} ${${PROJECT_NAME}_HEADER_FILES})
    target_link_libraries(${name} ${${PROJECT_NAME}_DEPLIB})
endmacro()

###############################################################################
# generate source code of HIDL interface
macro(ADD_HIDL_SOURCE  package_name)
    string(REPLACE "@" ";" _name_list ${package_name})
    list(GET _name_list 0 _base_name)
    list(GET _name_list 1 _version)

    string(REPLACE "." "/" _path_name ${_base_name})
    string(APPEND _path_name "/${_version}")
    #message(STATUS "hidl path : ${_path_name}")

    string(REPLACE "." "_" _lib_name ${_base_name})
    string(REPLACE "." "_" _lib_ver ${_version})
    string(APPEND _lib_name "_${_lib_ver}")
    #message(STATUS "hidl lib  : ${_lib_name}")

    if (NOT EXISTS ${TMP_PATH}/${HIDL_HEADER_PATH}/${_path_name})
        exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_HEADER_PATH} -L c++-headers ${package_name}")
    endif()
    if (NOT EXISTS ${TMP_PATH}/${HIDL_SOURCE_PATH}/${_path_name})
        exec_program("${BIN_HIDL_GEN} -p ${HIDL_ROOT_PATH} -o ${TMP_PATH}/${HIDL_SOURCE_PATH} -L c++-sources ${package_name}")
    endif()

    file(GLOB ANDROID_${_lib_name}_SOURCES
        ${TMP_PATH}/${HIDL_HEADER_PATH}/${_path_name}/*.h
        ${TMP_PATH}/${HIDL_SOURCE_PATH}/${_path_name}/*.cpp
    )
    source_group(${package_name} FILES ${ANDROID_${_lib_name}_SOURCES})
    list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${ANDROID_${_lib_name}_SOURCES})
endmacro()

###############################################################################
# generate source code of AIDL interface
macro(ADD_AIDL_SOURCE file_name)
    string(TOLOWER ${PROJECT_NAME} _path_name)

    if(NOT EXISTS ${TMP_PATH}/${AIDL_HEADER_PATH}/${_path_name})
        exec_program("mkdir ${_path_name}" ${TMP_PATH}/${AIDL_HEADER_PATH})
    endif()
    if(NOT EXISTS ${TMP_PATH}/${AIDL_SOURCE_PATH}/${_path_name})
        exec_program("mkdir ${_path_name}" ${TMP_PATH}/${AIDL_SOURCE_PATH})
    endif()

    string(REPLACE "/" ";" _name_list ${file_name})
    list(GET _name_list -1 _aidl_name)
    string(REPLACE "aidl" "cpp" _cpp_name ${_aidl_name})
    #message(STATUS "aidl cpp : ${_path_name}/${_cpp_name}")

    if (NOT EXISTS ${TMP_PATH}/${AIDL_SOURCE_PATH}/${_path_name}/${_cpp_name})
        exec_program("${BIN_AIDL_CPP} \
        -I${SOURCE_PATH}/aidl \
        ${SOURCE_PATH}/aidl/${file_name} \
        ${TMP_PATH}/${AIDL_HEADER_PATH}/${_path_name} \
        ${TMP_PATH}/${AIDL_SOURCE_PATH}/${_path_name}/${_cpp_name}"
        )
    endif()

    list(REMOVE_AT _name_list -1)
    string(REPLACE ";" "/" _aidl_path "${_name_list}")
    #message(STATUS "aidl header path : ${_aidl_path}")

    string(REPLACE ".aidl" "" _aidl_interface ${_aidl_name})
    string(REGEX REPLACE "I([^ ]*)" "\\1" _aidl_base ${_aidl_interface})
    #message(STATUS "aidl base : ${_aidl_interface} -> ${_aidl_base}")

    set(ANDROID_${_aidl_base}_SOURCES
    ${TMP_PATH}/${AIDL_HEADER_PATH}/${_path_name}/${_aidl_path}/I${_aidl_base}.h
    ${TMP_PATH}/${AIDL_HEADER_PATH}/${_path_name}/${_aidl_path}/Bp${_aidl_base}.h
    ${TMP_PATH}/${AIDL_HEADER_PATH}/${_path_name}/${_aidl_path}/Bn${_aidl_base}.h
    ${TMP_PATH}/${AIDL_SOURCE_PATH}/${_path_name}/${_cpp_name}
    )
    source_group(${_aidl_name} FILES ${ANDROID_${_aidl_base}_SOURCES})
    list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${ANDROID_${_aidl_base}_SOURCES})

    if (MSVC)
        add_definitions(-DEXPORT_I${_aidl_base}=__declspec\(dllexport\))
        add_definitions(-DEXPORT_Bp${_aidl_base}=__declspec\(dllexport\))
        add_definitions(-DEXPORT_Bn${_aidl_base}=__declspec\(dllexport\))
    endif(MSVC)
endmacro()
