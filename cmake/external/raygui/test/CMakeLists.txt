project(TEST_RAYGUI)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/raygui/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/external/raylib/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/nativehelper/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/base/android/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/nativewindow/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/native/arect/include.cmake)

include(${M3E_SOURCE_DIR}/cmake/frameworks/initrc/include.cmake)

set(DEMO_DEPLIBS
raylib
initrc
)

if(APPLE)
    add_definitions(-Doff64_t=off_t)
elseif(MSVC)
    include_directories(AFTER ${MSVC_PATH})
endif() 

#set(SOURCE_PATH ${M3E_SOURCE_DIR}/${EXT_PATH}/raygui/examples)
#ADD_DEMO(raygui_text_box  ${SOURCE_PATH}/text_box_selection/gui_text_box.c)
#ADD_DEMO(raygui_scroll_panel  ${SOURCE_PATH}/scroll_panel/gui_scroll_panel.c)

set(SOURCE_PATH  ${M3E_SOURCE_DIR}/src/${EXT_PATH}/raygui/)
ADD_DEMO(raygui  
${SOURCE_PATH}/test.c 
${SOURCE_PATH}/text_editor.h
${SOURCE_PATH}/textbox_extended_demo.h
${SOURCE_PATH}/textbox_extended_demo.h
${SOURCE_PATH}/portable_window.h
)
