# gtest program

# dependency

SET(BINTEST_DEPLIB
gtest
utils
)

SET(LIBMISC_DEP ${BINTEST_DEPLIB})

# include and define

INCLUDE_DIRECTORIES(
${M3E_SOURCE_DIR}/external/gtest/include
${M3E_SOURCE_DIR}/src/native/include
)

# main source

SET(BINTEST_SOURCE_FILES 
${M3E_SOURCE_DIR}/src/test/main.cpp
)

# test libutils

SET(BINTEST_SOURCE_FILES ${BINTEST_SOURCE_FILES}
#${M3E_SOURCE_DIR}/src/test/utils/BitSet_test.cpp
#${M3E_SOURCE_DIR}/src/test/utils/BlobCache_test.cpp
#${M3E_SOURCE_DIR}/src/test/utils/Looper_test.cpp
#${M3E_SOURCE_DIR}/src/test/utils/LruCache_test.cpp
${M3E_SOURCE_DIR}/src/test/utils/RefBase_test.cpp
#${M3E_SOURCE_DIR}/src/test/utils/Singleton_test.cpp
#${M3E_SOURCE_DIR}/src/test/utils/Singleton_test1.cpp
#${M3E_SOURCE_DIR}/src/test/utils/Singleton_test2.cpp
${M3E_SOURCE_DIR}/src/test/utils/String8_test.cpp
${M3E_SOURCE_DIR}/src/test/utils/StrongPointer_test.cpp
#${M3E_SOURCE_DIR}/src/test/utils/SystemClock_test.cpp
${M3E_SOURCE_DIR}/src/test/utils/Unicode_test.cpp
#${M3E_SOURCE_DIR}/src/test/utils/Vector_test.cpp
)

# project
ADD_EXECUTABLE(test ${BINTEST_SOURCE_FILES})
TARGET_LINK_LIBRARIES(test ${BINTEST_DEPLIB})
