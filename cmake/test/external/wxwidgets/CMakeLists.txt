
# demo program

project(TEST_WXWIDGETS)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/external/wxwidgets/include.cmake)

#list(APPEND CMAKE_MODULE_PATH "${M3E_SOURCE_DIR}/${EXT_PATH}/wxWidgets/build/cmake/modules")

#include(${M3E_SOURCE_DIR}/${EXT_PATH}/wxWidgets/build/cmake/functions.cmake)        # wxWidgets functions

wx_add_sample(access accesstest.cpp DEPENDS wxUSE_ACCESSIBILITY)

set(DEMO_DEPLIBS
core
)
ADD_DEMO(wx_access   
${M3E_SOURCE_DIR}/${EXT_PATH}/wxWidgets/samples/access/accesstest.cpp
)

