
# demo program

project(TEST_WXWIDGETS)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/wxwidgets/include.cmake)

set(DEMO_DEPLIBS
core
)
ADD_DEMO(wx_minimal   
${M3E_SOURCE_DIR}/${EXT_PATH}/wxWidgets/samples/minimal/minimal.cpp
)

