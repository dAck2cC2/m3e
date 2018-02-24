
set( IrrXML_SRCS
${M3E_SOURCE_DIR}/${EXT_PATH}/assimp/contrib/irrXML/CXMLReaderImpl.h
${M3E_SOURCE_DIR}/${EXT_PATH}/assimp/contrib/irrXML/heapsort.h
${M3E_SOURCE_DIR}/${EXT_PATH}/assimp/contrib/irrXML/irrArray.h
${M3E_SOURCE_DIR}/${EXT_PATH}/assimp/contrib/irrXML/irrString.h
${M3E_SOURCE_DIR}/${EXT_PATH}/assimp/contrib/irrXML/irrTypes.h
${M3E_SOURCE_DIR}/${EXT_PATH}/assimp/contrib/irrXML/irrXML.cpp
${M3E_SOURCE_DIR}/${EXT_PATH}/assimp/contrib/irrXML/irrXML.h
)

if ( MSVC )
  ADD_DEFINITIONS( -D_SCL_SECURE_NO_WARNINGS )
  ADD_DEFINITIONS( -D_CRT_SECURE_NO_WARNINGS )
endif ( MSVC )

add_library(IrrXML STATIC ${IrrXML_SRCS})
set(IRRXML_INCLUDE_DIR "${M3E_SOURCE_DIR}/${EXT_PATH}/assimp/contrib/irrXML" CACHE INTERNAL "IrrXML_Include" )
set(IRRXML_LIBRARY "IrrXML" CACHE INTERNAL "IrrXML" )

install(TARGETS IrrXML
  ARCHIVE DESTINATION ${ASSIMP_LIB_INSTALL_DIR}
  COMPONENT ${LIBASSIMP_COMPONENT})
