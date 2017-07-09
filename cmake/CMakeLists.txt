
include(${M3E_SOURCE_DIR}/cmake/common.cmake)

# create hte folder for building result
if(NOT EXISTS ${BUILD_PATH})
message(Create\t${BUILD_PATH})
exec_program("mkdir ${EXT_PATH}")
endif()

# external module
set(EXT_LINK https://android.googlesource.com/platform)
set(EXT_TAG android-7.1.0_r7)
set(EXT_MODULES gtest)

# create the folder for external module
if(NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH})
message(Create\t${M3E_SOURCE_DIR}/${EXT_PATH})
exec_program("mkdir ${EXT_PATH}" ${M3E_SOURCE_DIR})
endif()

# download the source code of external module
foreach(MOD ${EXT_MODULES})
if(NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH}/${MOD})
message(Download\t${MOD})
exec_program("git clone ${EXT_LINK}/${EXT_PATH}/${MOD}" ${M3E_SOURCE_DIR}/${EXT_PATH})
exec_program("git checkout tags/${EXT_TAG}" ${M3E_SOURCE_DIR}/${EXT_PATH}/${MOD})
endif()
endforeach()

# the subdirectory
add_subdirectory(utils)
add_subdirectory(gtest)
add_subdirectory(test)
