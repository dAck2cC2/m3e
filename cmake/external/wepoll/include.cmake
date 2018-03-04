
# import the dll symbol
if (MSVC)
  add_definitions(-DWEPOLL_EXPORT=)
endif (MSVC)

# include
include_directories(AFTER ${M3E_SOURCE_DIR}/${EXT_PATH}/wepoll/include)
