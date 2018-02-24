
project(imgui)

if(NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH}/imgui)
message(STATUS "Download\timgui")
exec_program("git clone https://skia.googlesource.com/external/github.com/ocornut/imgui.git" ${M3E_SOURCE_DIR}/${EXT_PATH})
exec_program("git reset --hard 6384eee34f08cb7eab8d835043e1738e4adcdf75" ${M3E_SOURCE_DIR}/${EXT_PATH}/imgui)
endif()

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/imgui/include.cmake)

#include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/imgui/)

if(MSVC)
#add_definitions(-DIMGUI_API=__declspec(dllexport))
endif()

file(GLOB IMGUI_HEADER_FILES
${M3E_SOURCE_DIR}/${EXT_PATH}/imgui/*.h
)

set(IMGUI_SOURCE_FILES 
${M3E_SOURCE_DIR}/${EXT_PATH}/imgui/imgui.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/imgui/imgui_demo.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/imgui/imgui_draw.cpp
)

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(imgui SHARED ${IMGUI_SOURCE_FILES} ${IMGUI_HEADER_FILES})
