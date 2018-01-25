
if(CFG_NO_DEFAULT)
  if(CFG_ENABLE_CORE)
    set(ENABLE_CORE "TRUE")
  endif(CFG_ENABLE_CORE)

  if(CFG_ENABLE_AV)
    set(ENABLE_AV   "TRUE")
    set(ENABLE_CORE "TRUE")    
  endif(CFG_ENABLE_AV)
 
  if(CFG_ENABLE_CODEC_SELECTOR)
    set(ENABLE_AV             "TRUE")
    set(ENABLE_CORE           "TRUE")    
    set(ENABLE_CODEC_SELECTOR "TRUE")
  endif(CFG_ENABLE_CODEC_SELECTOR)

  if(CFG_ENABLE_TEST)
    set(ENABLE_TEST "TRUE")
  endif(CFG_ENABLE_TEST)

else(CFG_NO_DEFAULT)
  set(ENABLE_CORE  "TRUE")
  set(ENABLE_AV    "TRUE")
  set(ENABLE_APP   "TRUE")  
  set(ENABLE_TEST  "TRUE")
endif(CFG_NO_DEFAULT)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

# create hte folder for building result
if(NOT EXISTS ${BUILD_PATH})
message(STATUS "Create\t${BUILD_PATH}")
exec_program("mkdir ${BUILD_PATH}")
endif()

# external module
set(EXT_LINK https://android.googlesource.com/platform)
set(EXT_TAG android-7.1.0_r7)
set(EXT_MODULES gtest)

if(ENABLE_CODEC_SELECTOR)
set(EXT_MODULES ${EXT_MODULES} 
expat
jpeg
libyuv
)
add_subdirectory(expat)
add_subdirectory(jpeg)
add_subdirectory(libyuv)
endif()

# create the folder for external module
if(NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH})
message(STATUS "Create\t${M3E_SOURCE_DIR}/${EXT_PATH}")
exec_program("mkdir ${EXT_PATH}" ${M3E_SOURCE_DIR})
endif()

# download the source code of external module
foreach(MOD ${EXT_MODULES})
if(NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH}/${MOD})
message(STATUS "Download\t${MOD}")
exec_program("git clone ${EXT_LINK}/${EXT_PATH}/${MOD}" ${M3E_SOURCE_DIR}/${EXT_PATH})
exec_program("git checkout tags/${EXT_TAG}" ${M3E_SOURCE_DIR}/${EXT_PATH}/${MOD})
endif()
endforeach()

# the subdirectory
if(ENABLE_CORE)
add_subdirectory(core)
endif(ENABLE_CORE)

if(ENABLE_AV)
add_subdirectory(misc)
add_subdirectory(stagefright_foundation)
add_subdirectory(media)
add_subdirectory(stagefright)
add_subdirectory(audio)
endif(ENABLE_AV)

if(ENABLE_CODEC_SELECTOR)
add_subdirectory(stagefright_mediafilter)
add_subdirectory(stagefright_omx)
add_subdirectory(stagefright_color_conversion)
endif(ENABLE_CODEC_SELECTOR)

if(ENABLE_APP)
add_subdirectory(engine)
add_subdirectory(m3ecmd)
endif(ENABLE_APP)

if(ENABLE_TEST)
add_subdirectory(gtest)
add_subdirectory(test)
endif(ENABLE_TEST)
