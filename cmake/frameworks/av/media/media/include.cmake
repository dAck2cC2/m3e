DLL_PUBLIC(MEDIA)

if(MSVC)
    add_definitions(-D_ALLOW_KEYWORD_MACROS=1)
endif()

# include
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/av/media/libmedia/include)
include_directories(AFTER ${M3E_SOURCE_DIR}/src/frameworks/av/media/libmedia/aidl)

include_directories(AFTER ${TMP_PATH}/${AIDL_HEADER_PATH}/media)
