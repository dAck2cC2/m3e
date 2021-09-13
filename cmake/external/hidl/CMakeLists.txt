project(HIDL-GEN)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

if(NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH}/hidl)
  message(STATUS Download\t hidl)
  exec_program("git clone ${EXT_LINK}/system/tools/hidl" ${M3E_SOURCE_DIR}/${EXT_PATH})
  exec_program("git checkout tags/${EXT_TAG_HIDL}" ${M3E_SOURCE_DIR}/${EXT_PATH}/hidl)
  
  # apply patch
  exec_program("git apply ${M3E_SOURCE_DIR}/src/${EXT_PATH}/hidl/hidl.patch" ${M3E_SOURCE_DIR}/${EXT_PATH}/hidl)
endif()

###############################################################################
# create default package path
# refer to hidl/main.cpp (addDefaultPackagePath)

if (NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH}/hidl_root)
  exec_program("mkdir hidl_root" ${M3E_SOURCE_DIR}/${EXT_PATH})
endif()

# hardware/interfaces
if (NOT EXISTS ${HIDL_ROOT_PATH}/hardware)
  exec_program("mkdir hardware" ${HIDL_ROOT_PATH})
endif()
if (NOT EXISTS ${HIDL_ROOT_PATH}/hardware/interfaces)
  message(STATUS Download\t hardware/interfaces)
  exec_program("git clone ${EXT_LINK}/hardware/interfaces" ${HIDL_ROOT_PATH}/hardware)
  exec_program("git checkout tags/${EXT_TAG_HIDL_ROOT}" ${HIDL_ROOT_PATH}/hardware/interfaces)

  # apply patch
  exec_program("git apply ${M3E_SOURCE_DIR}/src/${EXT_PATH}/hidl/hardware_interfaces.patch" ${HIDL_ROOT_PATH}/hardware/interfaces)
endif()

#
# No need of google codec2
#
# hardware/google/interfaces
#
#if (NOT EXISTS ${HIDL_ROOT_PATH}/hardware/google)
#  exec_program("mkdir google" ${HIDL_ROOT_PATH}/hardware)
#endif()
#if (NOT EXISTS ${HIDL_ROOT_PATH}/hardware/google/interfaces)
#  message(STATUS Download\t hardware/google/interfaces)
#  exec_program("git clone ${EXT_LINK}/hardware/google/interfaces" ${HIDL_ROOT_PATH}/hardware/google)
#  exec_program("git checkout tags/${EXT_TAG_HIDL_ROOT}" ${HIDL_ROOT_PATH}/hardware/google/interfaces)
#endif()

# system/libhidl/transport
if (NOT EXISTS ${HIDL_ROOT_PATH}/system)
  exec_program("mkdir system" ${HIDL_ROOT_PATH})
endif()
if (NOT EXISTS ${HIDL_ROOT_PATH}/system/libhidl)
  message(STATUS Download\t system/libhidl/transport)
  exec_program("git clone ${EXT_LINK}/system/libhidl" ${HIDL_ROOT_PATH}/system)
  exec_program("git checkout tags/${EXT_TAG_HIDL_ROOT}" ${HIDL_ROOT_PATH}/system/libhidl)

  # apply patch
  exec_program("git apply ${M3E_SOURCE_DIR}/src/${EXT_PATH}/hidl/system_libhidl.patch" ${HIDL_ROOT_PATH}/system/libhidl)
endif()

# frameworks/hardware/interfaces
# system/hardware/interfaces

###############################################################################
# Generate and store the source code to src/external/hidl/
# It will not request additional tool of bison and flex then.

if (NOT EXISTS ${M3E_SOURCE_DIR}/src/${EXT_PATH}/hidl/hidl-gen_y.cpp)
  if (MSVC)
    exec_program("bison --defines=hidl-gen_y.h -o hidl-gen_y.cpp hidl-gen_y.yy" ${M3E_SOURCE_DIR}/${EXT_PATH}/hidl)
    exec_program("flex -o hidl-gen_l.cpp hidl-gen_l.ll" ${M3E_SOURCE_DIR}/${EXT_PATH}/hidl)
  else (MSVC)
    exec_program("yacc --defines=hidl-gen_y.h -o hidl-gen_y.cpp hidl-gen_y.yy" ${M3E_SOURCE_DIR}/${EXT_PATH}/hidl)
    exec_program("lex -o hidl-gen_l.cpp hidl-gen_l.ll" ${M3E_SOURCE_DIR}/${EXT_PATH}/hidl)
  endif(MSVC)

  set(GENERATED_FILES
  hidl-gen_l.cpp
  hidl-gen_y.cpp
  hidl-gen_y.h
  location.hh
  position.hh
  )
  foreach(file ${GENERATED_FILES})
    exec_program("${CMAKE_COMMAND} -E copy ${file} ${M3E_SOURCE_DIR}/src/${EXT_PATH}/hidl" ${M3E_SOURCE_DIR}/${EXT_PATH}/hidl)
    exec_program("${CMAKE_COMMAND} -E remove ${file}" ${M3E_SOURCE_DIR}/${EXT_PATH}/hidl)
  endforeach()
  
endif()

###############################################################################
# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/base/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/boringssl/include.cmake)

set(${PROJECT_NAME}_DEPLIB
base
crypto
)

set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/hidl )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/hidl )

include_directories(AFTER ${HEADER_PATH})
include_directories(AFTER ${M3E_SOURCE_DIR}/src/${EXT_PATH}/hidl)

if(APPLE)
  set(CMAKE_CXX_FLAGS "-std=c++1z -stdlib=libc++" ${CMAKE_CXX_FLAGS}) 
elseif (MSVC)
  include(${MSVC_INCLUDE})
  list(APPEND ${PROJECT_NAME}_DEPLIB ${LIB_MSVC_WRAP})

  add_definitions(-Dmode_t=int)
elseif(LINUX)
  add_definitions(-Dregister= )
  set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17")
endif()

###############################################################################
# source files
file(GLOB ${PROJECT_NAME}_HEADER_FILES
${HEADER_PATH}/*.h
${M3E_SOURCE_DIR}/src/${EXT_PATH}/hidl/*.h
)

set(${PROJECT_NAME}_SOURCE_FILES 
${SOURCE_PATH}/main.cpp
)

###############################################################################
#  libhidl-gen-utils
include_directories(AFTER 
${HEADER_PATH}/utils/include/hidl-util
${HEADER_PATH}/utils/include
)
file(GLOB HIDL_SOURCE_UTILS
${HEADER_PATH}/utils/include/hidl-util/*.h
)
set(HIDL_SOURCE_UTILS
${SOURCE_PATH}/utils/FQName.cpp
${SOURCE_PATH}/utils/FqInstance.cpp
)
source_group(libhidl-gen-utils FILES ${HIDL_SOURCE_UTILS})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${HIDL_SOURCE_UTILS})

###############################################################################
#  libhidl-gen-host-utils
include_directories(AFTER 
${HEADER_PATH}/host_utils/include/hidl-util
${HEADER_PATH}/host_utils/include
)
file(GLOB HIDL_SOURCE_HOST_UTILS
${HEADER_PATH}/host_utils/include/hidl-util/*.h
)
set(HIDL_SOURCE_HOST_UTILS
${SOURCE_PATH}/host_utils/Formatter.cpp
${SOURCE_PATH}/host_utils/StringHelper.cpp
)
source_group(libhidl-gen-host-utils FILES ${HIDL_SOURCE_HOST_UTILS})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${HIDL_SOURCE_HOST_UTILS})

###############################################################################
#  libhidl-gen-hash
include_directories(AFTER 
${HEADER_PATH}/hashing/include
${HEADER_PATH}/hashing/include/hidl-hash
)
file(GLOB HIDL_SOURCE_HASH
${HEADER_PATH}/hashing/include/hidl-hash/*.h
)
set(HIDL_SOURCE_HASH 
${SOURCE_PATH}/hashing/Hash.cpp
)
source_group(libhidl-gen-hash FILES ${HIDL_SOURCE_HASH})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${HIDL_SOURCE_HASH})

###############################################################################
#  libhidl-gen
set(HIDL_SOURCE_GEN 
${SOURCE_PATH}/Annotation.cpp 
${SOURCE_PATH}/ArrayType.cpp 
${SOURCE_PATH}/CompoundType.cpp 
${SOURCE_PATH}/ConstantExpression.cpp 
${SOURCE_PATH}/DeathRecipientType.cpp 
${SOURCE_PATH}/DocComment.cpp
${SOURCE_PATH}/EnumType.cpp 
${SOURCE_PATH}/HandleType.cpp 
${SOURCE_PATH}/HidlTypeAssertion.cpp 
${SOURCE_PATH}/Interface.cpp 
${SOURCE_PATH}/Location.cpp
${SOURCE_PATH}/MemoryType.cpp 
${SOURCE_PATH}/Method.cpp 
${SOURCE_PATH}/NamedType.cpp 
${SOURCE_PATH}/PointerType.cpp 
${SOURCE_PATH}/FmqType.cpp 
${SOURCE_PATH}/RefType.cpp 
${SOURCE_PATH}/ScalarType.cpp 
${SOURCE_PATH}/Scope.cpp 
${SOURCE_PATH}/StringType.cpp 
${SOURCE_PATH}/Type.cpp 
${SOURCE_PATH}/TypeDef.cpp 
${SOURCE_PATH}/VectorType.cpp 
)
source_group(libhidl-gen FILES ${HIDL_SOURCE_GEN})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${HIDL_SOURCE_GEN})

###############################################################################
#  libhidl-gen-ast
set(HIDL_SOURCE_AST
${SOURCE_PATH}/Coordinator.cpp 
${SOURCE_PATH}/generateCpp.cpp 
${SOURCE_PATH}/generateCppAdapter.cpp
${SOURCE_PATH}/generateCppImpl.cpp 
${SOURCE_PATH}/generateDependencies.cpp
${SOURCE_PATH}/generateJava.cpp 
${SOURCE_PATH}/generateVts.cpp 
${SOURCE_PATH}/hidl-gen_y.yy 
${SOURCE_PATH}/hidl-gen_l.ll 
${SOURCE_PATH}/AST.cpp 

${M3E_SOURCE_DIR}/src/${EXT_PATH}/hidl/hidl-gen_y.cpp
${M3E_SOURCE_DIR}/src/${EXT_PATH}/hidl/hidl-gen_l.cpp
)
source_group(libhidl-gen-ast FILES ${HIDL_SOURCE_AST})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${HIDL_SOURCE_AST})

###############################################################################
# target file
set(EXECUTABLE_OUTPUT_PATH ${BUILD_PATH})
add_executable(hidl-gen ${${PROJECT_NAME}_HEADER_FILES} ${${PROJECT_NAME}_SOURCE_FILES})
target_link_libraries(hidl-gen ${${PROJECT_NAME}_DEPLIB})
