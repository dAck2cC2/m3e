
project(ANGLE)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

if(NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH}/angle)
    message(STATUS "Download\t angel")
    exec_program("git clone https://github.com/google/angle.git" ${M3E_SOURCE_DIR}/${EXT_PATH})
    exec_program("git reset --hard 21e5e85a4976de15e252167936fd3adb876bb7da" ${M3E_SOURCE_DIR}/${EXT_PATH}/angle)
	if (MSVC)
		exec_program("git apply ${M3E_SOURCE_DIR}/src/${EXT_PATH}/angle/angle.patch" ${M3E_SOURCE_DIR}/${EXT_PATH}/angle)
	endif(MSVC)
endif()

set( ID_SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/angle/src )
if(NOT EXISTS ${ID_SOURCE_PATH}/id)
    exec_program("cmake -E make_directory id" ${ID_SOURCE_PATH})
    exec_program("python commit_id.py gen ../ ./id/commit.h" ${ID_SOURCE_PATH})
endif()

###########################################################
# Sub Folder
###########################################################

add_subdirectory(glesv2)
add_subdirectory(glesv1_cm)
add_subdirectory(egl)
add_subdirectory(util)

if(ENABLE_TEST)
    #add_subdirectory(test)
endif(ENABLE_TEST)
