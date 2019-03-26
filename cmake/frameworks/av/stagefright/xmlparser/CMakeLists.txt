
project(XMLPARSER)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/frameworks/av/stagefright/xmlparser/include.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)

set(${PROJECT_NAME}_DEPLIB
log
cutils
utils
expat
)

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/xmlparser/include/media/stagefright/xmlparser )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/frameworks/av/media/libstagefright/xmlparser )

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES 
${HEADER_PATH}/*.h 
)

set(${PROJECT_NAME}_SOURCE_FILES
${SOURCE_PATH}/MediaCodecsXmlParser.cpp         
)

# target files
ADD_LIB(stagefright_xmlparser)
