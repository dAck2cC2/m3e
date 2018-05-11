
project(WXWIDGETS)

if(NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH}/wxWidgets)
    message(STATUS "Download\t wxWidgets")
    exec_program("git clone https://github.com/wxWidgets/wxWidgets.git" ${M3E_SOURCE_DIR}/${EXT_PATH})
    exec_program("git reset --hard 9caa3d5d8e279a6420f040c756239bcd31a0dde7" ${M3E_SOURCE_DIR}/${EXT_PATH}/wxWidgets)
endif()

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
#include(${M3E_SOURCE_DIR}/cmake/external/wxwidgets/include.cmake)


#############################################################################
# Name:        CMakeLists.txt
# Purpose:     Primary CMake for wxWidgets
# Author:      Tobias Taschner
# Created:     2016-09-20
# Copyright:   (c) 2016 wxWidgets development team
# Licence:     wxWindows licence
#############################################################################

if(NOT CMAKE_CONFIGURATION_TYPES)
    get_property(HAVE_MULTI_CONFIG_GENERATOR GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
    # Set default configuration types for multi-config generators
    if(HAVE_MULTI_CONFIG_GENERATOR)
        set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
    endif()
endif()

if(APPLE AND NOT CMAKE_OSX_DEPLOYMENT_TARGET)
    # If no deployment target has been set default to the minimum supported
    # OS X version (this has to be set before the first project() call)
    set(CMAKE_OSX_DEPLOYMENT_TARGET 10.7 CACHE STRING "OS X Deployment Target")
endif()

include(${M3E_SOURCE_DIR}/${EXT_PATH}/wxWidgets/build/cmake/policies.cmake NO_POLICY_SCOPE)

# Initialize variables for quick access to wx root dir in sub dirs
set(wxSOURCE_DIR ${M3E_SOURCE_DIR}/${EXT_PATH}/wxWidgets)
set(wxBINARY_DIR ${BUILD_PATH})
set(wxOUTPUT_DIR ${BUILD_PATH})

# parse the version number from wx/version.h and include in wxMAJOR_VERSION and wxMINOR_VERSION
file(READ ${wxSOURCE_DIR}/include/wx/version.h WX_VERSION_H_CONTENTS)
string(REGEX MATCH "wxMAJOR_VERSION[ \t]+([0-9]+)"
    wxMAJOR_VERSION ${WX_VERSION_H_CONTENTS})
string (REGEX MATCH "([0-9]+)"
    wxMAJOR_VERSION ${wxMAJOR_VERSION})
string(REGEX MATCH "wxMINOR_VERSION[ \t]+([0-9]+)"
    wxMINOR_VERSION ${WX_VERSION_H_CONTENTS})
string (REGEX MATCH "([0-9]+)"
    wxMINOR_VERSION ${wxMINOR_VERSION})
string(REGEX MATCH "wxRELEASE_NUMBER[ \t]+([0-9]+)"
    wxRELEASE_NUMBER ${WX_VERSION_H_CONTENTS})
string (REGEX MATCH "([0-9]+)"
    wxRELEASE_NUMBER ${wxRELEASE_NUMBER})
# Determine if current version is a "Development" release
math(EXPR rel_dev "${wxMINOR_VERSION} % 2")
if(rel_dev)
    set(wxVERSION_IS_DEV TRUE)
else()
    set(wxVERSION_IS_DEV FALSE)
endif()

set(wxVERSION ${wxMAJOR_VERSION}.${wxMINOR_VERSION}.${wxRELEASE_NUMBER})
set(wxCOPYRIGHT "1992-2018 wxWidgets")

list(APPEND CMAKE_MODULE_PATH "${wxSOURCE_DIR}/build/cmake/modules")

include(${wxSOURCE_DIR}/build/cmake/files.cmake)            # Files list
include(${wxSOURCE_DIR}/build/cmake/functions.cmake)        # wxWidgets functions
include(${wxSOURCE_DIR}/build/cmake/toolkit.cmake)          # Platform/toolkit settings
include(${wxSOURCE_DIR}/build/cmake/options.cmake)          # User options
include(${wxSOURCE_DIR}/build/cmake/init.cmake)             # Init various global build vars
#include(${wxSOURCE_DIR}/build/cmake/install.cmake)          # Install target support

include(${wxSOURCE_DIR}/build/cmake/source_groups.cmake)

set(wxLIB_TARGETS)
if(wxBUILD_MONOLITHIC)
    # Initialize variables for monolithic build
    set(wxMONO_SRC_FILES)
    set(wxMONO_LIBS_PRIVATE)
    set(wxMONO_LIBS_PUBLIC)
    set(wxMONO_INCLUDE_DIRS_PRIVATE)
    set(wxMONO_INCLUDE_DIRS_PUBLIC)
endif()

# Define third party libraries
set(LIBS_THIRDPARTY zlib expat)
if(wxUSE_GUI)
    list(APPEND LIBS_THIRDPARTY jpeg png tiff)
endif()
foreach(LIB IN LISTS LIBS_THIRDPARTY)
    string(TOUPPER ${LIB} _name_upper)
    set(${_name_upper}_LIBRARIES ${LIB})
    include(${M3E_SOURCE_DIR}/cmake/external/${LIB}/include.cmake)
endforeach()

list(APPEND LIBS_THIRDPARTY regex)
include(${wxSOURCE_DIR}/build/cmake/lib/regex.cmake)

# add_opt_lib()
# Add library which may have been disabled by wxUSE_...
macro(add_opt_lib name var_name)
    if(${var_name})
        list(APPEND LIBS ${name})
    endif()
endmacro()

# Define base libraries
set(LIBS base)
add_opt_lib(net wxUSE_SOCKETS)
add_opt_lib(xml wxUSE_XML)

# Define UI libraries
if(wxUSE_GUI)
    list(APPEND LIBS core adv)
    foreach(lib
        aui
        html
        propgrid
        ribbon
        richtext
        webview
        stc
        xrc
        )
        string(TOUPPER ${lib} _name_upper)
        add_opt_lib(${lib} wxUSE_${_name_upper})
    endforeach()
    add_opt_lib(media wxUSE_MEDIACTRL)
    add_opt_lib(gl wxUSE_OPENGL)
    add_opt_lib(qa wxUSE_DEBUGREPORT)
endif() # wxUSE_GUI

# Include cmake file for every library
foreach(LIB ${LIBS})
    file(READ "${wxSOURCE_DIR}/build/cmake/lib/${LIB}/CMakeLists.txt" _cmakefile)
    string(REGEX REPLACE "../../source_groups.cmake" "${wxSOURCE_DIR}/build/cmake/source_groups.cmake" _cmakefile "${_cmakefile}")
    file(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/${LIB}/CMakeLists.txt" "${_cmakefile}")

    add_subdirectory(${LIB})
endforeach()

if(wxBUILD_MONOLITHIC)
    # Create monolithic library target
    list(LENGTH wxMONO_SRC_FILES src_file_count)
    wx_add_library(mono ${wxMONO_SRC_FILES})
    foreach(vis PRIVATE PUBLIC)
        if(wxMONO_LIBS_${vis})
            # Remove libs included in mono from list
            foreach(lib IN LISTS LIBS)
                list(REMOVE_ITEM wxMONO_LIBS_${vis} ${lib})
            endforeach()

            target_link_libraries(mono ${vis} ${wxMONO_LIBS_${vis}})
        endif()
        if(wxMONO_INCLUDE_DIRS_${vis})
            target_include_directories(mono ${vis} ${wxMONO_INCLUDE_DIRS_${vis}})
        endif()
        if(wxMONO_DEFINITIONS_${vis})
            target_compile_definitions(mono ${vis} ${wxMONO_DEFINITIONS_${vis}})
        endif()
    endforeach()
endif()


include(${wxSOURCE_DIR}/build/cmake/utils/CMakeLists.txt)


if(NOT wxBUILD_CUSTOM_SETUP_HEADER_PATH)
    file(COPY
        ${wxSOURCE_DIR}/build/cmake/setup.h.in
        DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/cmake/
        FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ
            GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
        )    
    # Write setup.h after all variables are available
    include(${wxSOURCE_DIR}/build/cmake/setup.cmake)
    file(COPY 
        ${wxSETUP_HEADER_FILE} 
        DESTINATION ${M3E_BINARY_DIR}/wxWidgets/wx/
        FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ
            GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
        )
endif()

if(UNIX)
    file(COPY
        ${wxSOURCE_DIR}/wx-config-inplace.in
        DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/
        FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ
            GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
        )     
    file(COPY
        ${wxSOURCE_DIR}/wx-config.in
        DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/
        FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ
            GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
        )      
    # Write wx-config
    include(${wxSOURCE_DIR}/build/cmake/config.cmake)
endif()

# Determine minimum required OS at runtime
set(wxREQUIRED_OS_DESC "${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_PROCESSOR}")
if(MSVC OR MINGW OR CYGWIN)
    # Determine based on used toolkit
    if(MINGW OR CYGWIN OR (MSVC_VERSION LESS 1700) OR (CMAKE_VS_PLATFORM_TOOLSET MATCHES "_xp$") )
        # Visual Studio < 2012 and MinGW always create XP compatible binaries
        # XP Toolset is required since VS 2012
        set(wxREQUIRED_OS_DESC "Windows XP / Windows Server 2003")
    else()
        set(wxREQUIRED_OS_DESC "Windows Vista / Windows Server 2008")
    endif()
    if(CMAKE_CL_64)
        wx_string_append(wxREQUIRED_OS_DESC " (x64 Edition)")
    endif()
elseif(APPLE AND NOT IPHONE)
    if(DEFINED CMAKE_OSX_DEPLOYMENT_TARGET)
        set(wxREQUIRED_OS_DESC "macOS ${CMAKE_OSX_DEPLOYMENT_TARGET}")
    endif()
endif()

# Print configuration summary
wx_print_thirdparty_library_summary()

message(STATUS "Configured wxWidgets ${wxVERSION} for ${CMAKE_SYSTEM}
    Min OS Version required at runtime:                ${wxREQUIRED_OS_DESC}
    Which GUI toolkit should wxWidgets use?            ${wxBUILD_TOOLKIT} ${wxTOOLKIT_VERSION}
    Should wxWidgets be compiled into single library?  ${wxBUILD_MONOLITHIC}
    Should wxWidgets be linked as a shared library?    ${wxBUILD_SHARED}
    Should wxWidgets support Unicode?                  ${wxUSE_UNICODE}
    What wxWidgets compatibility level should be used? ${wxBUILD_COMPATIBILITY}"
    )
