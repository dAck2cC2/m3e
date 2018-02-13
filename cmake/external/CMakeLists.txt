# create the folder for external module

if(NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH})
message(STATUS "Create\t${M3E_SOURCE_DIR}/${EXT_PATH}")
exec_program("mkdir ${EXT_PATH}" ${M3E_SOURCE_DIR})
endif()

# download and include external module

# skia
if(ENABLE_SKIA)
add_subdirectory(skia)
if(NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH}/skia)
message(STATUS "Download\tskia")
exec_program("git clone https://skia.googlesource.com/skia.git" ${M3E_SOURCE_DIR}/${EXT_PATH})
exec_program("git checkout chrome/m65" ${M3E_SOURCE_DIR}/${EXT_PATH}/skia)
endif()

add_subdirectory(imgui)
if(NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH}/imgui)
message(STATUS "Download\timgui")
exec_program("git clone https://skia.googlesource.com/external/github.com/ocornut/imgui.git" ${M3E_SOURCE_DIR}/${EXT_PATH})
exec_program("git reset --hard 6384eee34f08cb7eab8d835043e1738e4adcdf75" ${M3E_SOURCE_DIR}/${EXT_PATH}/imgui)
endif()

add_subdirectory(jsoncpp)
set(EXT_MODULES ${EXT_MODULES} jsoncpp)
endif(ENABLE_SKIA)

# freeglut
if(ENABLE_GLUT)
add_subdirectory(freeglut)
if(NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT)
message(STATUS "Download\timgui")
exec_program("git clone https://github.com/dcnieho/FreeGLUT.git" ${M3E_SOURCE_DIR}/${EXT_PATH})
#exec_program("git reset --hard 6384eee34f08cb7eab8d835043e1738e4adcdf75" ${M3E_SOURCE_DIR}/${EXT_PATH}/FreeGLUT)
endif()
endif(ENABLE_GLUT)

# external module from android
set(EXT_LINK https://android.googlesource.com/platform)
set(EXT_TAG android-7.1.0_r7)

if (ENABLE_CORE)
#set(EXT_MODULES ${EXT_MODULES} safe-iop)
#add_subdirectory(safe-iop)
endif(ENABLE_CORE)

if(ENABLE_TEST)
set(EXT_MODULES ${EXT_MODULES} gtest)
add_subdirectory(gtest)
endif(ENABLE_TEST)

if(ENABLE_AV_CODEC)
set(EXT_MODULES ${EXT_MODULES} 
expat
jpeg
libyuv
)
add_subdirectory(expat)
add_subdirectory(jpeg)
add_subdirectory(libyuv)
endif(ENABLE_AV_CODEC)

# download the source code of external module
foreach(MOD ${EXT_MODULES})
if(NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH}/${MOD})
message(STATUS "Download\t${MOD}")
exec_program("git clone ${EXT_LINK}/${EXT_PATH}/${MOD}" ${M3E_SOURCE_DIR}/${EXT_PATH})
exec_program("git checkout tags/${EXT_TAG}" ${M3E_SOURCE_DIR}/${EXT_PATH}/${MOD})
endif()
endforeach()

