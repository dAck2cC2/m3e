project(HIDL-GEN)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

if(NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH}/hidl)
  message(STATUS Download\t hidl)
  exec_program("git clone ${EXT_LINK}/system/tools/hidl" ${M3E_SOURCE_DIR}/${EXT_PATH})
  exec_program("git checkout tags/${EXT_TAG_UPDATE}" ${M3E_SOURCE_DIR}/${EXT_PATH}/hidl)
  
  # apply patch
  exec_program("git apply ${M3E_SOURCE_DIR}/src/${EXT_PATH}/hidl/hidl.patch" ${M3E_SOURCE_DIR}/${EXT_PATH}/hidl)
endif()

if (NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH}/hidl/hidl-gen_y.cpp)
  if (MSVC)
    exec_program("bison --defines=hidl-gen_y.h -o hidl-gen_y.cpp hidl-gen_y.yy" ${M3E_SOURCE_DIR}/${EXT_PATH}/hidl)
  else ()
    exec_program("yacc --defines=hidl-gen_y.h -o hidl-gen_y.cpp hidl-gen_y.yy" ${M3E_SOURCE_DIR}/${EXT_PATH}/hidl)
  endif()
endif()

if (NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH}/hidl/hidl-gen_l.cpp)
  if (MSVC)
    exec_program("flex -o hidl-gen_l.cpp hidl-gen_l.ll" ${M3E_SOURCE_DIR}/${EXT_PATH}/hidl)
  else()
    exec_program("lex -o hidl-gen_l.cpp hidl-gen_l.ll" ${M3E_SOURCE_DIR}/${EXT_PATH}/hidl)
  endif()
endif()

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/base/include.cmake)


set(${PROJECT_NAME}_DEPLIB
base
)

set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/hidl )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/hidl )

include_directories(AFTER ${HEADER_PATH})


if(APPLE)
  set(CMAKE_CXX_FLAGS "-std=c++1z -stdlib=libc++" ${CMAKE_CXX_FLAGS}) 
elseif (MSVC)
  include(${M3E_SOURCE_DIR}/cmake/core/msvc/include.cmake)
  list(APPEND ${PROJECT_NAME}_DEPLIB ${LIB_MSVC_WRAP})

  add_definitions(-Dmode_t=int)
endif()

file(GLOB ${PROJECT_NAME}_HEADER_FILES
${HEADER_PATH}/*.h
${HEADER_PATH}/include_hash/hidl-hash/*.h
${HEADER_PATH}/utils/include/hidl-util/*.h
)

###############################################################################
#  libhidl-gen-utils
include_directories(AFTER 
${HEADER_PATH}/utils/include/hidl-util
${HEADER_PATH}/utils/include
)
set(HIDL_SOURCE_UTILS
${SOURCE_PATH}/utils/FQName.cpp
${SOURCE_PATH}/utils/Formatter.cpp
${SOURCE_PATH}/utils/FqInstance.cpp
${SOURCE_PATH}/utils/StringHelper.cpp
)
source_group(libhidl-gen-utils FILES ${HIDL_SOURCE_UTILS})

###############################################################################
#  libhidl-gen-hash
include_directories(AFTER 
${HEADER_PATH}/include_hash
${HEADER_PATH}/include_hash/hidl-hash
)
set(HIDL_SOURCE_HASH 
${SOURCE_PATH}/Hash.cpp
)
source_group(libhidl-gen-hash FILES ${HIDL_SOURCE_HASH})

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

###############################################################################
#  libhidl-gen-ast
set(HIDL_SOURCE_AST
${SOURCE_PATH}/Coordinator.cpp 
${SOURCE_PATH}/generateCpp.cpp 
${SOURCE_PATH}/generateCppAdapter.cpp
${SOURCE_PATH}/generateCppImpl.cpp 
${SOURCE_PATH}/generateJava.cpp 
${SOURCE_PATH}/generateVts.cpp 
${SOURCE_PATH}/hidl-gen_y.yy 
${SOURCE_PATH}/hidl-gen_l.ll 
${SOURCE_PATH}/AST.cpp 

${SOURCE_PATH}/hidl-gen_y.cpp
${SOURCE_PATH}/hidl-gen_l.cpp
)
source_group(libhidl-gen-ast FILES ${HIDL_SOURCE_AST})

###############################################################################
# source files
set(${PROJECT_NAME}_SOURCE_FILES 
${HIDL_SOURCE_UTILS}
${HIDL_SOURCE_HASH}
${HIDL_SOURCE_GEN}
${HIDL_SOURCE_AST}
${SOURCE_PATH}/main.cpp
)

set(EXECUTABLE_OUTPUT_PATH ${BUILD_PATH})
add_executable(hidl-gen ${${PROJECT_NAME}_HEADER_FILES} ${${PROJECT_NAME}_SOURCE_FILES})
target_link_libraries(hidl-gen ${${PROJECT_NAME}_DEPLIB})
