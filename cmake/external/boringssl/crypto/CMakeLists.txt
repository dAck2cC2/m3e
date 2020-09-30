
project(CRYPTO)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/boringssl/include.cmake)

set(${PROJECT_NAME}_DEPLIB
)

set( HEADER_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/boringssl/src/include/openssl )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/boringssl/src )

file(GLOB PUBLIC_HEADER ${HEADER_PATH}/*.h)
source_group(public FILES ${PUBLIC_HEADER})

set(${PROJECT_NAME}_SOURCE_FILES
${PUBLIC_HEADER}
)

set(PROJECT_SOURCE_DIR ${SOURCE_PATH})

if (MSVC)
  set(OS_NAME "win")
elseif(APPLE)
  set(OS_NAME "mac")
elseif(LINUX)
  set(OS_NAME "linux")
else()
  message(FATAL_ERROR "Unsupported platform")
endif()

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
        set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -isysroot \"${CMAKE_OSX_SYSROOT}\"")
      endif()
      foreach(arch ${CMAKE_OSX_ARCHITECTURES})
        set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -arch ${arch}")
      endforeach()
    endif()
  else()
    if (${ARCH} STREQUAL "x86_64")
      set(PERLASM_STYLE nasm)
    else()
      set(PERLASM_STYLE win32n)
      set(PERLASM_FLAGS "-DOPENSSL_IA32_SSE2")
    endif()
    set(CMAKE_ASM_NASM_FLAGS "-gcv8")

    # On Windows, we use the NASM output, specifically built with Yasm.
    set(ASM_EXT asm)
    enable_language(ASM_NASM)
  endif()
endif()

function(perlasm dest src)
  add_custom_command(
    OUTPUT ${dest}
    COMMAND ${PERL_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/${src} ${PERLASM_STYLE} ${PERLASM_FLAGS} ${ARGN} ${dest}
    DEPENDS
    ${src}
    ${PROJECT_SOURCE_DIR}/crypto/perlasm/arm-xlate.pl
    ${PROJECT_SOURCE_DIR}/crypto/perlasm/ppc-xlate.pl
    ${PROJECT_SOURCE_DIR}/crypto/perlasm/x86_64-xlate.pl
    ${PROJECT_SOURCE_DIR}/crypto/perlasm/x86asm.pl
    ${PROJECT_SOURCE_DIR}/crypto/perlasm/x86gas.pl
    ${PROJECT_SOURCE_DIR}/crypto/perlasm/x86masm.pl
    ${PROJECT_SOURCE_DIR}/crypto/perlasm/x86nasm.pl
    WORKING_DIRECTORY .
  )
endfunction()

# Level 0.1 - depends on nothing outside this set.

#add_subdirectory(stack)
set(${PROJECT_NAME}_stack_SOURCE ${SOURCE_PATH}/crypto/stack/stack.c)
source_group(stack FILES ${${PROJECT_NAME}_stack_SOURCE})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_stack_SOURCE})

#add_subdirectory(lhash)
set(${PROJECT_NAME}_lhash_SOURCE ${SOURCE_PATH}/crypto/lhash/lhash.c)
source_group(lhash FILES ${${PROJECT_NAME}_lhash_SOURCE})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_lhash_SOURCE})

#add_subdirectory(err)
set(${PROJECT_NAME}_err_SOURCE 
${SOURCE_PATH}/crypto/err/err.c
${SOURCE_PATH}/../err_data.c
)
source_group(err FILES ${${PROJECT_NAME}_err_SOURCE})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_err_SOURCE})

#add_subdirectory(buf)
set(${PROJECT_NAME}_buf_SOURCE ${SOURCE_PATH}/crypto/buf/buf.c)
source_group(buf FILES ${${PROJECT_NAME}_buf_SOURCE})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_buf_SOURCE})

#add_subdirectory(base64)
set(${PROJECT_NAME}_base64_SOURCE ${SOURCE_PATH}/crypto/base64/base64.c)
source_group(base64 FILES ${${PROJECT_NAME}_base64_SOURCE})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_base64_SOURCE})

#add_subdirectory(bytestring)
set(${PROJECT_NAME}_bytestring_SOURCE 
${SOURCE_PATH}/crypto/bytestring/asn1_compat.c
${SOURCE_PATH}/crypto/bytestring/ber.c
${SOURCE_PATH}/crypto/bytestring/cbs.c
${SOURCE_PATH}/crypto/bytestring/cbb.c
)
source_group(bytestring FILES ${${PROJECT_NAME}_bytestring_SOURCE})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_bytestring_SOURCE})

#add_subdirectory(pool)
set(${PROJECT_NAME}_pool_SOURCE ${SOURCE_PATH}/crypto/pool/pool.c)
source_group(pool FILES ${${PROJECT_NAME}_pool_SOURCE})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_pool_SOURCE})

# Level 0.2 - depends on nothing but itself

#add_subdirectory(rc4)
set(${PROJECT_NAME}_rc4_SOURCE ${SOURCE_PATH}/crypto/rc4/rc4.c)
source_group(rc4 FILES ${${PROJECT_NAME}_rc4_SOURCE})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_rc4_SOURCE})

#add_subdirectory(conf)
set(${PROJECT_NAME}_conf_SOURCE ${SOURCE_PATH}/crypto/conf/conf.c)
source_group(conf FILES ${${PROJECT_NAME}_conf_SOURCE})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_conf_SOURCE})

#add_subdirectory(chacha)
set(CHACHA_ARCH_SOURCES
${SOURCE_PATH}/../${OS_NAME}-${ARCH}/crypto/chacha/chacha-${ARCH}.${ASM_EXT}
)
set(${PROJECT_NAME}_chacha_SOURCE 
${SOURCE_PATH}/crypto/chacha/chacha.c
${CHACHA_ARCH_SOURCES}
)
source_group(chacha FILES ${${PROJECT_NAME}_chacha_SOURCE})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_chacha_SOURCE})

#add_subdirectory(poly1305)
set(${PROJECT_NAME}_poly1305_SOURCE 
${SOURCE_PATH}/crypto/poly1305/poly1305.c
${SOURCE_PATH}/crypto/poly1305/poly1305_arm.c
${SOURCE_PATH}/crypto/poly1305/poly1305_vec.c
)
source_group(poly1305 FILES ${${PROJECT_NAME}_poly1305_SOURCE})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_poly1305_SOURCE})

#add_subdirectory(curve25519)
set(${PROJECT_NAME}_curve25519_SOURCE ${SOURCE_PATH}/crypto/curve25519/spake25519.c)
source_group(curve25519 FILES ${${PROJECT_NAME}_curve25519_SOURCE})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_curve25519_SOURCE})

# Level 1, depends only on 0.*

#add_subdirectory(digest_extra)
set(${PROJECT_NAME}_digest_extra_SOURCE ${SOURCE_PATH}/crypto/digest_extra/digest_extra.c)
source_group(digest_extra FILES ${${PROJECT_NAME}_digest_extra_SOURCE})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_digest_extra_SOURCE})

#add_subdirectory(cipher_extra)
if (${ARCH} STREQUAL "x86_64")
  set(CIPHER_ARCH_SOURCES
  ${SOURCE_PATH}/../${OS_NAME}-${ARCH}/crypto/cipher_extra/aes128gcmsiv-x86_64.${ASM_EXT}
  )
  if (APPLE)
    list(APPEND CIPHER_ARCH_SOURCES
    ${SOURCE_PATH}/../${OS_NAME}-${ARCH}/crypto/cipher_extra/chacha20_poly1305_x86_64.${ASM_EXT}
    )
  endif()
endif()
set(${PROJECT_NAME}_cipher_extra_SOURCE 
${SOURCE_PATH}/crypto/cipher_extra/cipher_extra.c
${SOURCE_PATH}/crypto/cipher_extra/derive_key.c
${SOURCE_PATH}/crypto/cipher_extra/e_null.c
${SOURCE_PATH}/crypto/cipher_extra/e_rc2.c
${SOURCE_PATH}/crypto/cipher_extra/e_rc4.c
${SOURCE_PATH}/crypto/cipher_extra/e_aesgcmsiv.c
${SOURCE_PATH}/crypto/cipher_extra/e_aesctrhmac.c
${SOURCE_PATH}/crypto/cipher_extra/e_chacha20poly1305.c
${SOURCE_PATH}/crypto/cipher_extra/tls_cbc.c
${SOURCE_PATH}/crypto/cipher_extra/e_tls.c
${SOURCE_PATH}/crypto/cipher_extra/e_ssl3.c
${CIPHER_ARCH_SOURCES}
)
source_group(cipher_extra FILES ${${PROJECT_NAME}_cipher_extra_SOURCE})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_cipher_extra_SOURCE})

#add_subdirectory(rand_extra)
set(${PROJECT_NAME}_rand_extra_SOURCE 
${SOURCE_PATH}/crypto/rand_extra/deterministic.c
${SOURCE_PATH}/crypto/rand_extra/forkunsafe.c
${SOURCE_PATH}/crypto/rand_extra/fuchsia.c
${SOURCE_PATH}/crypto/rand_extra/rand_extra.c
${SOURCE_PATH}/crypto/rand_extra/windows.c
)
source_group(rand_extra FILES ${${PROJECT_NAME}_rand_extra_SOURCE})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_rand_extra_SOURCE})

#add_subdirectory(bio)
set(${PROJECT_NAME}_bio_SOURCE 
${SOURCE_PATH}/crypto/bio/bio.c
${SOURCE_PATH}/crypto/bio/bio_mem.c
${SOURCE_PATH}/crypto/bio/connect.c
${SOURCE_PATH}/crypto/bio/fd.c
${SOURCE_PATH}/crypto/bio/file.c
${SOURCE_PATH}/crypto/bio/hexdump.c
${SOURCE_PATH}/crypto/bio/pair.c
${SOURCE_PATH}/crypto/bio/printf.c
${SOURCE_PATH}/crypto/bio/socket.c
${SOURCE_PATH}/crypto/bio/socket_helper.c
)
source_group(bio FILES ${${PROJECT_NAME}_bio_SOURCE})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_bio_SOURCE})

#add_subdirectory(bn_extra)
file(GLOB ${PROJECT_NAME}_bn_extra_SOURCE 
${SOURCE_PATH}/crypto/bn_extra/bn_asn1.c
${SOURCE_PATH}/crypto/bn_extra/convert.c
)
source_group(bn_extra FILES ${${PROJECT_NAME}_bn_extra_SOURCE})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_bn_extra_SOURCE})

#add_subdirectory(obj)
file(GLOB ${PROJECT_NAME}_obj_SOURCE 
${SOURCE_PATH}/crypto/obj/obj.c
${SOURCE_PATH}/crypto/obj/obj_xref.c
)
source_group(obj FILES ${${PROJECT_NAME}_obj_SOURCE})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_obj_SOURCE})

#add_subdirectory(asn1)
set(${PROJECT_NAME}_asn1_SOURCE 
${SOURCE_PATH}/crypto/asn1/a_bitstr.c
${SOURCE_PATH}/crypto/asn1/a_bool.c
${SOURCE_PATH}/crypto/asn1/a_d2i_fp.c
${SOURCE_PATH}/crypto/asn1/a_dup.c
${SOURCE_PATH}/crypto/asn1/a_enum.c
${SOURCE_PATH}/crypto/asn1/a_gentm.c
${SOURCE_PATH}/crypto/asn1/a_i2d_fp.c
${SOURCE_PATH}/crypto/asn1/a_int.c
${SOURCE_PATH}/crypto/asn1/a_mbstr.c
${SOURCE_PATH}/crypto/asn1/a_object.c
${SOURCE_PATH}/crypto/asn1/a_octet.c
${SOURCE_PATH}/crypto/asn1/a_print.c
${SOURCE_PATH}/crypto/asn1/a_strnid.c
${SOURCE_PATH}/crypto/asn1/a_time.c
${SOURCE_PATH}/crypto/asn1/a_type.c
${SOURCE_PATH}/crypto/asn1/a_utctm.c
${SOURCE_PATH}/crypto/asn1/a_utf8.c
${SOURCE_PATH}/crypto/asn1/asn1_lib.c
${SOURCE_PATH}/crypto/asn1/asn1_par.c
${SOURCE_PATH}/crypto/asn1/asn_pack.c
${SOURCE_PATH}/crypto/asn1/f_enum.c
${SOURCE_PATH}/crypto/asn1/f_int.c
${SOURCE_PATH}/crypto/asn1/f_string.c
${SOURCE_PATH}/crypto/asn1/tasn_dec.c
${SOURCE_PATH}/crypto/asn1/tasn_enc.c
${SOURCE_PATH}/crypto/asn1/tasn_fre.c
${SOURCE_PATH}/crypto/asn1/tasn_new.c
${SOURCE_PATH}/crypto/asn1/tasn_typ.c
${SOURCE_PATH}/crypto/asn1/tasn_utl.c
${SOURCE_PATH}/crypto/asn1/time_support.c
)
source_group(asn1 FILES ${${PROJECT_NAME}_asn1_SOURCE})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_asn1_SOURCE})

# Level 2

# add_subdirectory(engine)
file(GLOB ${PROJECT_NAME}_engine_SOURCE ${SOURCE_PATH}/crypto/engine/engine.c)
source_group(engine FILES ${${PROJECT_NAME}_engine_SOURCE})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_engine_SOURCE})

#add_subdirectory(dh)
file(GLOB ${PROJECT_NAME}_dh_SOURCE 
${SOURCE_PATH}/crypto/dh/dh.c
${SOURCE_PATH}/crypto/dh/params.c
${SOURCE_PATH}/crypto/dh/check.c
${SOURCE_PATH}/crypto/dh/dh_asn1.c
)
source_group(dh FILES ${${PROJECT_NAME}_dh_SOURCE})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_dh_SOURCE})

#add_subdirectory(dsa)
file(GLOB ${PROJECT_NAME}_dsa_SOURCE 
${SOURCE_PATH}/crypto/dsa/dsa.c
${SOURCE_PATH}/crypto/dsa/dsa_asn1.c
)
source_group(dsa FILES ${${PROJECT_NAME}_dsa_SOURCE})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_dsa_SOURCE})

#add_subdirectory(rsa_extra)
file(GLOB ${PROJECT_NAME}_rsa_extra_SOURCE ${SOURCE_PATH}/crypto/rsa_extra/rsa_asn1.c)
source_group(rsa_extra FILES ${${PROJECT_NAME}_rsa_extra_SOURCE})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_rsa_extra_SOURCE})

#add_subdirectory(ec_extra)
file(GLOB ${PROJECT_NAME}_ec_extra_SOURCE ${SOURCE_PATH}/crypto/ec_extra/ec_asn1.c)
source_group(ec_extra FILES ${${PROJECT_NAME}_ec_extra_SOURCE})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_ec_extra_SOURCE})

#add_subdirectory(ecdh)
file(GLOB ${PROJECT_NAME}_ecdh_SOURCE ${SOURCE_PATH}/crypto/ecdh/ecdh.c)
source_group(ecdh FILES ${${PROJECT_NAME}_ecdh_SOURCE})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_ecdh_SOURCE})

#add_subdirectory(ecdsa_extra)
file(GLOB ${PROJECT_NAME}_ecdsa_extra_SOURCE ${SOURCE_PATH}/crypto/ecdsa_extra/ecdsa_asn1.c)
source_group(ecdsa_extra FILES ${${PROJECT_NAME}_ecdsa_extra_SOURCE})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_ecdsa_extra_SOURCE})

# Level 3

#add_subdirectory(cmac)
file(GLOB ${PROJECT_NAME}_cmac_SOURCE ${SOURCE_PATH}/crypto/cmac/cmac.c)
source_group(cmac FILES ${${PROJECT_NAME}_cmac_SOURCE})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_cmac_SOURCE})

#add_subdirectory(evp)
file(GLOB ${PROJECT_NAME}_evp_SOURCE 
${SOURCE_PATH}/crypto/evp/digestsign.c
${SOURCE_PATH}/crypto/evp/evp.c
${SOURCE_PATH}/crypto/evp/evp_asn1.c
${SOURCE_PATH}/crypto/evp/evp_ctx.c
${SOURCE_PATH}/crypto/evp/p_dsa_asn1.c
${SOURCE_PATH}/crypto/evp/p_ec.c
${SOURCE_PATH}/crypto/evp/p_ec_asn1.c
${SOURCE_PATH}/crypto/evp/p_ed25519.c
${SOURCE_PATH}/crypto/evp/p_ed25519_asn1.c
${SOURCE_PATH}/crypto/evp/p_rsa.c
${SOURCE_PATH}/crypto/evp/p_rsa_asn1.c
${SOURCE_PATH}/crypto/evp/pbkdf.c
${SOURCE_PATH}/crypto/evp/print.c
${SOURCE_PATH}/crypto/evp/scrypt.c
${SOURCE_PATH}/crypto/evp/sign.c
)
source_group(evp FILES ${${PROJECT_NAME}_evp_SOURCE})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_evp_SOURCE})

#add_subdirectory(hkdf)
file(GLOB ${PROJECT_NAME}_hkdf_SOURCE ${SOURCE_PATH}/crypto/hkdf/hkdf.c)
source_group(hkdf FILES ${${PROJECT_NAME}_hkdf_SOURCE})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_hkdf_SOURCE})

#add_subdirectory(pem)
file(GLOB ${PROJECT_NAME}_pem_SOURCE 
${SOURCE_PATH}/crypto/pem/pem_all.c
${SOURCE_PATH}/crypto/pem/pem_info.c
${SOURCE_PATH}/crypto/pem/pem_lib.c
${SOURCE_PATH}/crypto/pem/pem_oth.c
${SOURCE_PATH}/crypto/pem/pem_pk8.c
${SOURCE_PATH}/crypto/pem/pem_pkey.c
${SOURCE_PATH}/crypto/pem/pem_x509.c
${SOURCE_PATH}/crypto/pem/pem_xaux.c
)
source_group(pem FILES ${${PROJECT_NAME}_pem_SOURCE})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_pem_SOURCE})

#add_subdirectory(x509)
file(GLOB ${PROJECT_NAME}_x509_SOURCE 
${SOURCE_PATH}/crypto/x509/a_digest.c
${SOURCE_PATH}/crypto/x509/a_sign.c
${SOURCE_PATH}/crypto/x509/a_strex.c
${SOURCE_PATH}/crypto/x509/a_verify.c
${SOURCE_PATH}/crypto/x509/algorithm.c
${SOURCE_PATH}/crypto/x509/asn1_gen.c
${SOURCE_PATH}/crypto/x509/by_dir.c
${SOURCE_PATH}/crypto/x509/by_file.c
${SOURCE_PATH}/crypto/x509/i2d_pr.c
${SOURCE_PATH}/crypto/x509/rsa_pss.c
${SOURCE_PATH}/crypto/x509/t_crl.c
${SOURCE_PATH}/crypto/x509/t_req.c
${SOURCE_PATH}/crypto/x509/t_x509.c
${SOURCE_PATH}/crypto/x509/t_x509a.c
${SOURCE_PATH}/crypto/x509/x509.c
${SOURCE_PATH}/crypto/x509/x509_att.c
${SOURCE_PATH}/crypto/x509/x509_cmp.c
${SOURCE_PATH}/crypto/x509/x509_d2.c
${SOURCE_PATH}/crypto/x509/x509_def.c
${SOURCE_PATH}/crypto/x509/x509_ext.c
${SOURCE_PATH}/crypto/x509/x509_lu.c
${SOURCE_PATH}/crypto/x509/x509_obj.c
${SOURCE_PATH}/crypto/x509/x509_r2x.c
${SOURCE_PATH}/crypto/x509/x509_req.c
${SOURCE_PATH}/crypto/x509/x509_set.c
${SOURCE_PATH}/crypto/x509/x509_trs.c
${SOURCE_PATH}/crypto/x509/x509_txt.c
${SOURCE_PATH}/crypto/x509/x509_v3.c
${SOURCE_PATH}/crypto/x509/x509_vfy.c
${SOURCE_PATH}/crypto/x509/x509_vpm.c
${SOURCE_PATH}/crypto/x509/x509cset.c
${SOURCE_PATH}/crypto/x509/x509name.c
${SOURCE_PATH}/crypto/x509/x509rset.c
${SOURCE_PATH}/crypto/x509/x509spki.c
${SOURCE_PATH}/crypto/x509/x_algor.c
${SOURCE_PATH}/crypto/x509/x_all.c
${SOURCE_PATH}/crypto/x509/x_attrib.c
${SOURCE_PATH}/crypto/x509/x_crl.c
${SOURCE_PATH}/crypto/x509/x_exten.c
${SOURCE_PATH}/crypto/x509/x_info.c
${SOURCE_PATH}/crypto/x509/x_name.c
${SOURCE_PATH}/crypto/x509/x_pkey.c
${SOURCE_PATH}/crypto/x509/x_pubkey.c
${SOURCE_PATH}/crypto/x509/x_req.c
${SOURCE_PATH}/crypto/x509/x_sig.c
${SOURCE_PATH}/crypto/x509/x_spki.c
${SOURCE_PATH}/crypto/x509/x_val.c
${SOURCE_PATH}/crypto/x509/x_x509.c
${SOURCE_PATH}/crypto/x509/x_x509a.c
)
source_group(x509 FILES ${${PROJECT_NAME}_x509_SOURCE})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_x509_SOURCE})

#add_subdirectory(x509v3)
file(GLOB ${PROJECT_NAME}_x509v3_SOURCE 
${SOURCE_PATH}/crypto/x509v3/pcy_cache.c
${SOURCE_PATH}/crypto/x509v3/pcy_data.c
${SOURCE_PATH}/crypto/x509v3/pcy_lib.c
${SOURCE_PATH}/crypto/x509v3/pcy_map.c
${SOURCE_PATH}/crypto/x509v3/pcy_node.c
${SOURCE_PATH}/crypto/x509v3/pcy_tree.c
${SOURCE_PATH}/crypto/x509v3/v3_akey.c
${SOURCE_PATH}/crypto/x509v3/v3_akeya.c
${SOURCE_PATH}/crypto/x509v3/v3_alt.c
${SOURCE_PATH}/crypto/x509v3/v3_bcons.c
${SOURCE_PATH}/crypto/x509v3/v3_bitst.c
${SOURCE_PATH}/crypto/x509v3/v3_conf.c
${SOURCE_PATH}/crypto/x509v3/v3_cpols.c
${SOURCE_PATH}/crypto/x509v3/v3_crld.c
${SOURCE_PATH}/crypto/x509v3/v3_enum.c
${SOURCE_PATH}/crypto/x509v3/v3_extku.c
${SOURCE_PATH}/crypto/x509v3/v3_genn.c
${SOURCE_PATH}/crypto/x509v3/v3_ia5.c
${SOURCE_PATH}/crypto/x509v3/v3_info.c
${SOURCE_PATH}/crypto/x509v3/v3_int.c
${SOURCE_PATH}/crypto/x509v3/v3_lib.c
${SOURCE_PATH}/crypto/x509v3/v3_ncons.c
${SOURCE_PATH}/crypto/x509v3/v3_pci.c
${SOURCE_PATH}/crypto/x509v3/v3_pcia.c
${SOURCE_PATH}/crypto/x509v3/v3_pcons.c
${SOURCE_PATH}/crypto/x509v3/v3_pku.c
${SOURCE_PATH}/crypto/x509v3/v3_pmaps.c
${SOURCE_PATH}/crypto/x509v3/v3_prn.c
${SOURCE_PATH}/crypto/x509v3/v3_purp.c
${SOURCE_PATH}/crypto/x509v3/v3_skey.c
${SOURCE_PATH}/crypto/x509v3/v3_sxnet.c
${SOURCE_PATH}/crypto/x509v3/v3_utl.c
)
source_group(x509v3 FILES ${${PROJECT_NAME}_x509v3_SOURCE})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_x509v3_SOURCE})

# Level 4

#add_subdirectory(pkcs7)
file(GLOB ${PROJECT_NAME}_pkcs7_SOURCE 
${SOURCE_PATH}/crypto/pkcs7/pkcs7.c
${SOURCE_PATH}/crypto/pkcs7/pkcs7_x509.c
)
source_group(pkcs7 FILES ${${PROJECT_NAME}_pkcs7_SOURCE})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_pkcs7_SOURCE})

#add_subdirectory(pkcs8)
file(GLOB ${PROJECT_NAME}_pkcs8_SOURCE 
${SOURCE_PATH}/crypto/pkcs8/pkcs8.c
${SOURCE_PATH}/crypto/pkcs8/pkcs8_x509.c
${SOURCE_PATH}/crypto/pkcs8/p5_pbev2.c
)
source_group(pkcs8 FILES ${${PROJECT_NAME}_pkcs8_SOURCE})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_pkcs8_SOURCE})

# Test support code
#add_subdirectory(test)

# add_subdirectory(fipsmodule)
if (${ARCH} STREQUAL "x86_64")
  set(BCM_ASM_SOURCES
  ${SOURCE_PATH}/../${OS_NAME}-${ARCH}/crypto/fipsmodule/aesni-gcm-x86_64.${ASM_EXT}
  ${SOURCE_PATH}/../${OS_NAME}-${ARCH}/crypto/fipsmodule/aesni-x86_64.${ASM_EXT}
  ${SOURCE_PATH}/../${OS_NAME}-${ARCH}/crypto/fipsmodule/aes-x86_64.${ASM_EXT}
  ${SOURCE_PATH}/../${OS_NAME}-${ARCH}/crypto/fipsmodule/bsaes-x86_64.${ASM_EXT}
  ${SOURCE_PATH}/../${OS_NAME}-${ARCH}/crypto/fipsmodule/ghash-x86_64.${ASM_EXT}
  ${SOURCE_PATH}/../${OS_NAME}-${ARCH}/crypto/fipsmodule/md5-x86_64.${ASM_EXT}
  ${SOURCE_PATH}/../${OS_NAME}-${ARCH}/crypto/fipsmodule/p256-x86_64-asm.${ASM_EXT}
  ${SOURCE_PATH}/../${OS_NAME}-${ARCH}/crypto/fipsmodule/rdrand-x86_64.${ASM_EXT}
  ${SOURCE_PATH}/../${OS_NAME}-${ARCH}/crypto/fipsmodule/rsaz-avx2.${ASM_EXT}
  ${SOURCE_PATH}/../${OS_NAME}-${ARCH}/crypto/fipsmodule/sha1-x86_64.${ASM_EXT}
  ${SOURCE_PATH}/../${OS_NAME}-${ARCH}/crypto/fipsmodule/sha256-x86_64.${ASM_EXT}
  ${SOURCE_PATH}/../${OS_NAME}-${ARCH}/crypto/fipsmodule/sha512-x86_64.${ASM_EXT}
  ${SOURCE_PATH}/../${OS_NAME}-${ARCH}/crypto/fipsmodule/vpaes-x86_64.${ASM_EXT}
  ${SOURCE_PATH}/../${OS_NAME}-${ARCH}/crypto/fipsmodule/x86_64-mont.${ASM_EXT}
  ${SOURCE_PATH}/../${OS_NAME}-${ARCH}/crypto/fipsmodule/x86_64-mont5.${ASM_EXT}
  )
elseif(${ARCH} STREQUAL "x86")
else()
  message(FATAL_ERROR "Please fill in arch related assemble files")
endif()
#set_source_files_properties(${BCM_ASM_SOURCES} PROPERTIES COMPILE_FLAGS "-x assembler-with-cpp")
set(${PROJECT_NAME}_fipsmodule_SOURCE 
${SOURCE_PATH}/crypto/fipsmodule/bcm.c
${SOURCE_PATH}/crypto/fipsmodule/is_fips.c
${BCM_ASM_SOURCES}
)
source_group(fipsmodule FILES ${${PROJECT_NAME}_fipsmodule_SOURCE})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_fipsmodule_SOURCE})

# add_library( crypto_base
set(${PROJECT_NAME}_crypto_base_SOURCE 
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
source_group(base FILES ${${PROJECT_NAME}_crypto_base_SOURCE})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_crypto_base_SOURCE})


#add_subdirectory(third_party/fiat)
file(GLOB ${PROJECT_NAME}_fiat_SOURCE ${SOURCE_PATH}/third_party/fiat/curve25519.c)
source_group(fiat FILES ${${PROJECT_NAME}_fiat_SOURCE})
list(APPEND ${PROJECT_NAME}_SOURCE_FILES ${${PROJECT_NAME}_fiat_SOURCE})


###############################################
# build library of crypto 
###############################################

ADD_LIB(crypto)
