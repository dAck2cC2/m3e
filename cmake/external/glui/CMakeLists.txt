
project(GLUI)

if(NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH}/glui)
  message(STATUS "Download\tglui")
  exec_program("git clone https://github.com/libglui/glui.git" ${M3E_SOURCE_DIR}/${EXT_PATH})
  exec_program("git reset --hard ad0f3a89694079cd145dbc0b9b49f8a7507162d6" ${M3E_SOURCE_DIR}/${EXT_PATH}/glui)
endif()

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
#include(${M3E_SOURCE_DIR}/cmake/external/glui/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/freeglut/include.cmake)

include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/glui/include)
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/glui/)

set(GLUI_DEPLIB
freeglut
)
#find_package(OpenGL REQUIRED)
#list(APPEND GLUI_DEPLIB ${OPENGL_gl_LIBRARY})


if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  set (CMAKE_CXX_FLAGS "--std=c++11 ${CMAKE_CXX_FLAGS}")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set (CMAKE_CXX_FLAGS "--std=c++11 ${CMAKE_CXX_FLAGS}")
endif ()

if (APPLE)
  set (CMAKE_CXX_FLAGS "-Wno-deprecated-declarations ${CMAKE_CXX_FLAGS}")
elseif (MSVC)
  add_definitions(-DGLUI_BUILDING_LIB)
  add_definitions(-DGLUIDLL)
  add_definitions(-DNOMINMAX)
endif ()

file(GLOB GLUI_HEADERS
${M3E_SOURCE_DIR}/${EXT_PATH}/glui/include/GL/*.h
)

set(GLUI_SRCS
${M3E_SOURCE_DIR}/${EXT_PATH}/glui/algebra3.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/glui/arcball.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/glui/glui_add_controls.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/glui/glui_bitmaps.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/glui/glui_button.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/glui/glui_checkbox.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/glui/glui_column.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/glui/glui_commandline.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/glui/glui_control.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/glui/glui.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/glui/glui_edittext.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/glui/glui_filebrowser.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/glui/glui_listbox.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/glui/glui_list.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/glui/glui_mouse_iaction.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/glui/glui_node.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/glui/glui_panel.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/glui/glui_radio.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/glui/glui_rollout.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/glui/glui_rotation.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/glui/glui_scrollbar.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/glui/glui_separator.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/glui/glui_spinner.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/glui/glui_statictext.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/glui/glui_textbox.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/glui/glui_translation.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/glui/glui_tree.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/glui/glui_treepanel.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/glui/glui_window.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/glui/quaternion.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/glui/viewmodel.cpp
)

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})
add_library(glui SHARED ${GLUI_SRCS} ${GLUI_HEADERS})
target_link_libraries(glui ${GLUI_DEPLIB})

#set(ENABLE_TEST  TRUE)
if(ENABLE_TEST)
  add_subdirectory(test)
endif(ENABLE_TEST)
