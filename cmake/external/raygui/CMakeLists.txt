project(RAYGUI)

if(NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH}/raygui)
  message(STATUS "Download\traygui")
  exec_program("git clone https://github.com/raysan5/raygui.git" ${M3E_SOURCE_DIR}/${EXT_PATH})
  #exec_program("git checkout tags/2.6" ${M3E_SOURCE_DIR}/${EXT_PATH}/raygui)
  exec_program("git reset --hard 4eda62925c53dfffa23e726dca36110267b21685" ${M3E_SOURCE_DIR}/${EXT_PATH}/raygui)
endif()

include(${M3E_SOURCE_DIR}/cmake/common.cmake)


set(ENABLE_TEST  TRUE)
if(ENABLE_TEST)
  add_subdirectory(test)
endif(ENABLE_TEST)
