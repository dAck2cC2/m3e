
project(ANGLE)

if(NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH}/angle)
    message(STATUS "Download\t angel")
    exec_program("git clone https://github.com/google/angle.git" ${M3E_SOURCE_DIR}/${EXT_PATH})
    exec_program("git reset --hard b2c60b1a195049ede3f3d28a81cb1ff35929f88b" ${M3E_SOURCE_DIR}/${EXT_PATH}/angle)
	if (MSVC)
		exec_program("git apply ${M3E_SOURCE_DIR}/src/${EXT_PATH}/angle/angle.patch" ${M3E_SOURCE_DIR}/${EXT_PATH}/angle)
	endif(MSVC)
endif()

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

set( ID_SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/src )
if(NOT EXISTS ${ID_SOURCE_PATH}/id)
    exec_program("mkdir id" ${ID_SOURCE_PATH}/angle/src)
    exec_program("python commit_id.py gen ../ ./id/commit.h" ${ID_SOURCE_PATH})
endif()

###########################################################
# Sub Folder
###########################################################

add_subdirectory(glesv2)
add_subdirectory(glesv1_cm)
add_subdirectory(egl)
add_subdirectory(util)
