
project(CRYPTO)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/boringssl/include.cmake)

set(${PROJECT_NAME}_DEPLIB
)

set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/boringssl/src/include/openssl )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/boringssl/src )

file(GLOB PUBLIC_HEADER ${HEADER_PATH}/*.h)
source_group(public FILES ${PUBLIC_HEADER})

###############################################################################
#    From boringssl/src/crypto/CMakeLists.txt
###############################################################################

if(NOT OPENSSL_NO_ASM)
  if(UNIX)
    if (${ARCH} STREQUAL "aarch64")
      # The "armx" Perl scripts look for "64" in the style argument
      # in order to decide whether to generate 32- or 64-bit asm.
      if (APPLE)
        set(PERLASM_STYLE ios64)
      else()
        set(PERLASM_STYLE linux64)
      endif()
    elseif (${ARCH} STREQUAL "arm")
      if (APPLE)
        set(PERLASM_STYLE ios32)
      else()
        set(PERLASM_STYLE linux32)
      endif()
    elseif (${ARCH} STREQUAL "ppc64le")
      set(PERLASM_STYLE linux64le)
    else()
      if (${ARCH} STREQUAL "x86")
        set(PERLASM_FLAGS "-fPIC -DOPENSSL_IA32_SSE2")
      endif()
      if (APPLE)
        set(PERLASM_STYLE macosx)
      else()
        set(PERLASM_STYLE elf)
      endif()
    endif()
    set(ASM_EXT S)
    enable_language(ASM)
    set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -Wa,--noexecstack")

    # Clang's integerated assembler does not support debug symbols.
    if(NOT CMAKE_ASM_COMPILER_ID MATCHES "Clang")
      set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -Wa,-g")
    endif()

    # CMake does not add -isysroot and -arch flags to assembly.
    if (APPLE)
      if (CMAKE_OSX_SYSROOT)
        set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -isysroot ${CMAKE_OSX_SYSROOT}")
      endif()
      foreach(arch ${CMAKE_OSX_ARCHITECTURES})
        set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -arch ${arch}")
      endforeach()
    endif()
  else()
    if (CMAKE_CL_64)
      set(PERLASM_STYLE nasm)
    else()
      set(PERLASM_STYLE win32n)
      set(PERLASM_FLAGS "-DOPENSSL_IA32_SSE2")
    endif()

    # On Windows, we use the NASM output, specifically built with Yasm.
    set(ASM_EXT asm)
    #enable_language(C ASM_NASM)
    enable_language(C ASM_MASM)
  endif()
endif()


# Level 0.1 - depends on nothing outside this set.

# stack
file(GLOB ${PROJECT_NAME}_STACK_SOURCE ${SOURCE_PATH}/crypto/stack/*.c)
source_group(stack FILES ${${PROJECT_NAME}_STACK_SOURCE})


# Level 2

# engine
file(GLOB ${PROJECT_NAME}_ENGINE_SOURCE ${SOURCE_PATH}/crypto/engine/*.c)
source_group(engine FILES ${${PROJECT_NAME}_ENGINE_SOURCE})


# fipsmodule
if(MSVC)
  set(BCM_ASM_SOURCES
  ${SOURCE_PATH}/../win-x86/crypto/fipsmodule/aesni-x86.asm
  )
endif()
#set_source_files_properties(${BCM_ASM_SOURCES} PROPERTIES COMPILE_FLAGS "-x assembler-with-cpp")
set(${PROJECT_NAME}_FIPSMODULE_SOURCE 
${SOURCE_PATH}/crypto/fipsmodule/bcm.c
${BCM_ASM_SOURCES}
)
source_group(fipsmodule FILES ${${PROJECT_NAME}_FIPSMODULE_SOURCE})

# base
set(${PROJECT_NAME}_BASE_SOURCE 
${SOURCE_PATH}/crypto/cpu-aarch64-linux.c
${SOURCE_PATH}/crypto/cpu-arm.c
${SOURCE_PATH}/crypto/cpu-arm-linux.c
${SOURCE_PATH}/crypto/cpu-intel.c
${SOURCE_PATH}/crypto/cpu-ppc64le.c
${SOURCE_PATH}/crypto/crypto.c
${SOURCE_PATH}/crypto/ex_data.c
${SOURCE_PATH}/crypto/mem.c
${SOURCE_PATH}/crypto/refcount_c11.c
${SOURCE_PATH}/crypto/refcount_lock.c
${SOURCE_PATH}/crypto/thread.c
${SOURCE_PATH}/crypto/thread_none.c
${SOURCE_PATH}/crypto/thread_pthread.c
${SOURCE_PATH}/crypto/thread_win.c
)
source_group(base FILES ${${PROJECT_NAME}_BASE_SOURCE})

###############################################
# build library of crypto 
###############################################
set(${PROJECT_NAME}_SOURCE_FILES
${PUBLIC_HEADER}
${${PROJECT_NAME}_STACK_SOURCE}
${${PROJECT_NAME}_ENGINE_SOURCE}
${${PROJECT_NAME}_FIPSMODULE_SOURCE}
${${PROJECT_NAME}_BASE_SOURCE}
)

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(crypto SHARED ${${PROJECT_NAME}_SOURCE_FILES})
target_link_libraries(crypto ${${PROJECT_NAME}_DEPLIB})

