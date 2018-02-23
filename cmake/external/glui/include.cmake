
# import the dll symbol
if (MSVC)
  add_definitions(-DGLUIDLL)
endif ()

# include
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/glui/include)
