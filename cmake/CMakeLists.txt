
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
add_subdirectory(core)
add_subdirectory(utils)
add_subdirectory(gtest)
add_subdirectory(test)
add_subdirectory(misc)
add_subdirectory(stagefright_foundation)
add_subdirectory(media)
add_subdirectory(stagefright)
add_subdirectory(audio)
add_subdirectory(engine)
add_subdirectory(m3ecmd)

if(ENABLE_CODEC_SELECTOR)
add_subdirectory(stagefright_mediafilter)
add_subdirectory(stagefright_omx)
add_subdirectory(stagefright_color_conversion)
endif(ENABLE_CODEC_SELECTOR)
