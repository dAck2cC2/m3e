
project(ANGLE)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)

if(NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH}/angle)
    message(STATUS "Download\t angel")
    exec_program("git clone https://github.com/google/angle.git" ${M3E_SOURCE_DIR}/${EXT_PATH})
    exec_program("git reset --hard 98d0f30c43933b54ca8d9264056ccbaa0f014c8f" ${M3E_SOURCE_DIR}/${EXT_PATH}/angle)
	if (MSVC)
		exec_program("git apply ${M3E_SOURCE_DIR}/src/${EXT_PATH}/angle/angle.patch" ${M3E_SOURCE_DIR}/${EXT_PATH}/angle)
	endif(MSVC)
endif()

###########################################################
# Sub Folder
###########################################################

add_subdirectory(angle)
add_subdirectory(glesv2)
add_subdirectory(glesv1_cm)
add_subdirectory(egl)

#set(ENABLE_TEST "TRUE")
if(ENABLE_TEST)
    # util is just reference, but not really used
    add_subdirectory(util)
    add_subdirectory(test)
endif(ENABLE_TEST)
