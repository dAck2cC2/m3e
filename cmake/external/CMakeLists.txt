# external module
set(EXT_LINK https://android.googlesource.com/platform)
set(EXT_TAG android-7.1.0_r7)

if(ENABLE_TEST)
set(EXT_MODULES ${EXT_MODULES} gtest)
add_subdirectory(gtest)
endif(ENABLE_TEST)

if(ENABLE_CODEC_SELECTOR)
set(EXT_MODULES ${EXT_MODULES} 
expat
jpeg
libyuv
)
add_subdirectory(expat)
add_subdirectory(jpeg)
add_subdirectory(libyuv)
endif(ENABLE_CODEC_SELECTOR)

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
