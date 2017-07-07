
# external module
SET(EXT_LINK https://android.googlesource.com/platform)
SET(EXT_PATH external)
SET(EXT_TAG android-7.1.0_r7)
SET(EXT_MODULES gtest)

# create the folder for external module
IF(NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH})
MESSAGE(Create\t${M3E_SOURCE_DIR}/${EXT_PATH})
EXEC_PROGRAM("mkdir ${EXT_PATH}" ${M3E_SOURCE_DIR})
ENDIF()

# download the source code of external module
FOREACH(MOD ${EXT_MODULES})
IF(NOT EXISTS ${M3E_SOURCE_DIR}/${EXT_PATH}/${MOD})
MESSAGE(Download\t${MOD})
EXEC_PROGRAM("git clone ${EXT_LINK}/${EXT_PATH}/${MOD}" ${M3E_SOURCE_DIR}/${EXT_PATH})
EXEC_PROGRAM("git checkout tags/${EXT_TAG}" ${M3E_SOURCE_DIR}/${EXT_PATH}/${MOD})
ENDIF()
ENDFOREACH()

# gtest

INCLUDE_DIRECTORIES(
${M3E_SOURCE_DIR}/${EXT_PATH}/gtest
${M3E_SOURCE_DIR}/${EXT_PATH}/gtest/include
${M3E_SOURCE_DIR}/${EXT_PATH}/gtest/intlude/internal
)

FILE(GLOB LIBGTEST_HEADER_FILES
${M3E_SOURCE_DIR}/${EXT_PATH}/gtest/include/*.h
${M3E_SOURCE_DIR}/${EXT_PATH}/gtest/include/internal/*.h
)

SET(LIBGTEST_SOURCE_FILES ${M3E_SOURCE_DIR}/${EXT_PATH}/gtest/src/gtest-all.cc)

ADD_LIBRARY(gtest STATIC ${LIBGTEST_SOURCE_FILES} ${LIBGTEST_HEADER_FILES})

