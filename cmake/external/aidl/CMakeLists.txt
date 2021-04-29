project(AIDL-CPP)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

if(NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH}/aidl)
  message(STATUS Download\t aidl)
  exec_program("git clone ${EXT_LINK}/system/tools/aidl" ${M3E_SOURCE_DIR}/${EXT_PATH})
  exec_program("git checkout tags/${EXT_TAG_AIDL}" ${M3E_SOURCE_DIR}/${EXT_PATH}/aidl)
  
  # apply patch
  exec_program("git apply ${M3E_SOURCE_DIR}/src/${EXT_PATH}/aidl/aidl.patch" ${M3E_SOURCE_DIR}/${EXT_PATH}/aidl)
endif()

###############################################################################
# Generate and store the source code to src/external/aidl/
# It will not request additional tool of bison and flex then.

#if (NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH}/aidl/aidl_language_y.cpp)
#  if (MSVC)
#   exec_program("bison --defines=aidl_language_y.h -o aidl_language_y.cpp aidl_language_y.yy" ${M3E_SOURCE_DIR}/${EXT_PATH}/aidl)
#  else ()
#    exec_program("yacc --defines=aidl_language_y.h -o aidl_language_y.cpp aidl_language_y.yy" ${M3E_SOURCE_DIR}/${EXT_PATH}/aidl)
#  endif()
#endif()

#if (NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH}/aidl/aidl_language_l.cpp)
#  if (MSVC)
#    exec_program("flex -o aidl_language_l.cpp aidl_language_l.ll" ${M3E_SOURCE_DIR}/${EXT_PATH}/aidl)
#  else()
#    exec_program("lex -o aidl_language_l.cpp aidl_language_l.ll" ${M3E_SOURCE_DIR}/${EXT_PATH}/aidl)
#  endif()
#endif()

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/base/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/gtest/include.cmake)

set(${PROJECT_NAME}_DEPLIB
base
cutils
)

add_definitions(-DYYDEBUG=1)

if (MSVC)
  add_definitions(-DNOMINMAX)
  add_definitions(-Dstrcasecmp=_stricmp)
elseif(LINUX)
  add_definitions(-Dregister= )
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/aidl )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/aidl )

include_directories(AFTER ${HEADER_PATH})
include_directories(AFTER ${M3E_SOURCE_DIR}/src/${EXT_PATH}/aidl)

file(GLOB ${PROJECT_NAME}_HEADER_FILES
${HEADER_PATH}/*.h
${M3E_SOURCE_DIR}/src/${EXT_PATH}/aidl/*.h
)

set(${PROJECT_NAME}_SOURCE_FILES 
${SOURCE_PATH}/aidl.cpp 
${SOURCE_PATH}/aidl_language.cpp 
${SOURCE_PATH}/aidl_language_l.ll 
${SOURCE_PATH}/aidl_language_y.yy 
${SOURCE_PATH}/ast_cpp.cpp 
${SOURCE_PATH}/ast_java.cpp 
${SOURCE_PATH}/code_writer.cpp 
${SOURCE_PATH}/generate_cpp.cpp 
${SOURCE_PATH}/generate_java.cpp 
#${SOURCE_PATH}/generate_java_binder.cpp 
${SOURCE_PATH}/import_resolver.cpp 
${SOURCE_PATH}/line_reader.cpp 
${SOURCE_PATH}/io_delegate.cpp 
${SOURCE_PATH}/options.cpp 
${SOURCE_PATH}/type_cpp.cpp 
${SOURCE_PATH}/type_java.cpp 
${SOURCE_PATH}/type_namespace.cpp 
${SOURCE_PATH}/main_cpp.cpp

${M3E_SOURCE_DIR}/src/${EXT_PATH}/aidl/aidl_language_y.cpp
${M3E_SOURCE_DIR}/src/${EXT_PATH}/aidl/aidl_language_l.cpp
)

set(EXECUTABLE_OUTPUT_PATH ${BUILD_PATH})
add_executable(aidl-cpp ${${PROJECT_NAME}_HEADER_FILES} ${${PROJECT_NAME}_SOURCE_FILES})
target_link_libraries(aidl-cpp ${${PROJECT_NAME}_DEPLIB})
