
project(OGG)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/ogg/include.cmake)

if(NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH}/ogg)
    message(STATUS "Download\t ogg")
    exec_program("git clone https://git.xiph.org/ogg.git" ${M3E_SOURCE_DIR}/${EXT_PATH})
    exec_program("git checkout v1.3.3" ${M3E_SOURCE_DIR}/${EXT_PATH}/ogg)
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/ogg/include/ogg )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/ogg )

# Required modules
include(GNUInstallDirs)
include(CheckIncludeFiles)

# Build options
option(BUILD_SHARED_LIBS "Build shared library" OFF)
if(APPLE)
    option(BUILD_FRAMEWORK "Build Framework bundle for OSX" OFF)
endif()

# Extract project version from configure.ac
file(READ ${SOURCE_PATH}/configure.ac CONFIGURE_AC_CONTENTS)
string(REGEX MATCH "AC_INIT\\(\\[libogg\\],\\[([0-9]*).([0-9]*).([0-9]*)" DUMMY ${CONFIGURE_AC_CONTENTS})
set(PROJECT_VERSION_MAJOR ${CMAKE_MATCH_1})
set(PROJECT_VERSION_MINOR ${CMAKE_MATCH_2})
set(PROJECT_VERSION_PATCH ${CMAKE_MATCH_3})
set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})

# Helper function to get version-info
function(get_version_info result current_var_name age_var_name revision_var_name)
    string(REGEX MATCH "${current_var_name}=([0-9]*)" DUMMY ${CONFIGURE_AC_CONTENTS})
    set(VERSION_INFO_CURRENT ${CMAKE_MATCH_1})

    string(REGEX MATCH "${age_var_name}=([0-9]*)" DUMMY ${CONFIGURE_AC_CONTENTS})
    set(VERSION_INFO_AGE ${CMAKE_MATCH_1})

    string(REGEX MATCH "${revision_var_name}=([0-9]*)" DUMMY ${CONFIGURE_AC_CONTENTS})
    set(VERSION_INFO_REVISION ${CMAKE_MATCH_1})

    math(EXPR VERSION_INFO_CURRENT_MINUS_AGE "${VERSION_INFO_CURRENT} - ${VERSION_INFO_AGE}")

    set(${result} "${VERSION_INFO_CURRENT_MINUS_AGE}.${VERSION_INFO_AGE}.${VERSION_INFO_REVISION}" PARENT_SCOPE)
endfunction()

# Helper function to configure pkg-config files
function(configure_pkg_config_file pkg_config_file_in)
    set(prefix ${CMAKE_INSTALL_PREFIX})
    set(exec_prefix ${CMAKE_INSTALL_FULL_BINDIR})
    set(libdir ${CMAKE_INSTALL_FULL_LIBDIR})
    set(includedir ${CMAKE_INSTALL_FULL_INCLUDEDIR})
    set(VERSION ${PROJECT_VERSION})
    string(REPLACE ".in" "" pkg_config_file ${pkg_config_file_in})
    configure_file(${pkg_config_file_in} ${CMAKE_CURRENT_BINARY_DIR}/${pkg_config_file} @ONLY)
endfunction()

message(STATUS "Configuring ${PROJECT_NAME} ${PROJECT_VERSION}")

# Configure config_type.h
check_include_files(inttypes.h INCLUDE_INTTYPES_H)
check_include_files(stdint.h INCLUDE_STDINT_H)
check_include_files(sys/types.h INCLUDE_SYS_TYPES_H)

set(SIZE16 int16_t)
set(USIZE16 uint16_t)
set(SIZE32 int32_t)
set(USIZE32 uint32_t)
set(SIZE64 int64_t)

configure_file(${SOURCE_PATH}/include/ogg/config_types.h.in ${SOURCE_PATH}/include/ogg/config_types.h @ONLY)

set(OGG_HEADERS
${SOURCE_PATH}/include/ogg/config_types.h
${SOURCE_PATH}/include/ogg/ogg.h
${SOURCE_PATH}/include/ogg/os_types.h
)

set(OGG_SOURCES
${SOURCE_PATH}/src/bitwise.c
${SOURCE_PATH}/src/framing.c
)

if(MSVC)
    list(APPEND OGG_SOURCES ${SOURCE_PATH}/win32/ogg.def)
endif()

if(BUILD_FRAMEWORK)
    set(BUILD_SHARED_LIBS TRUE)
endif()

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(ogg ${OGG_HEADERS} ${OGG_SOURCES})

get_version_info(OGG_VERSION_INFO "LIB_CURRENT" "LIB_AGE" "LIB_REVISION")
set_target_properties(
    ogg PROPERTIES
    SOVERSION ${OGG_VERSION_INFO}
    PUBLIC_HEADER "${OGG_HEADERS}"
)

if(BUILD_FRAMEWORK)
    set_target_properties(ogg PROPERTIES
        FRAMEWORK TRUE
        FRAMEWORK_VERSION ${PROJECT_VERSION}
        MACOSX_FRAMEWORK_IDENTIFIER org.xiph.ogg
        MACOSX_FRAMEWORK_SHORT_VERSION_STRING ${PROJECT_VERSION}
        MACOSX_FRAMEWORK_BUNDLE_VERSION ${PROJECT_VERSION}
        XCODE_ATTRIBUTE_INSTALL_PATH "@rpath"
        OUTPUT_NAME Ogg
    )
endif()
