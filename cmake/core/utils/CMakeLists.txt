
project(UTILS)

include(${M3E_SOURCE_DIR}/cmake/common.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/utils/include.cmake)

# dependency

include(${M3E_SOURCE_DIR}/cmake/core/log/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/cutils/include.cmake)
include(${M3E_SOURCE_DIR}/cmake/core/base/include.cmake)

set(${PROJECT_NAME}_DEPLIB
log
cutils
)

if (MSVC)
    add_definitions(-D__MINGW32__=1)
    add_definitions(-DNOMINMAX=1)
    add_definitions(-D__stdcall= )

    include(${MSVC_INCLUDE})
    list(APPEND UTILS_DEPLIB ${LIB_MSVC_WRAP})

elseif (APPLE)
    add_definitions(-DENABLE_SAFE_IOP=1)
    add_definitions(-Dtypeof=__typeof__)
    add_definitions(-DCLOCK_BOOTTIME=CLOCK_MONOTONIC)
    
elseif(LINUX)
    # to debug core dump of crashing
    #set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-g")
endif()

set( HEADER_PATH ${M3E_SOURCE_DIR}/src/system/core/libutils/include/utils )
set( SOURCE_PATH ${M3E_SOURCE_DIR}/src/system/core/libutils/ )

# header files
file(GLOB ${PROJECT_NAME}_HEADER_FILES 
${HEADER_PATH}/*.h
${SOURCE_PATH}/*.h
)

# source files
set(${PROJECT_NAME}_SOURCE_FILES 
# basic files from Android.bp
${SOURCE_PATH}/FileMap.cpp
${SOURCE_PATH}/JenkinsHash.cpp
${SOURCE_PATH}/NativeHandle.cpp
${SOURCE_PATH}/Printer.cpp
${SOURCE_PATH}/PropertyMap.cpp
${SOURCE_PATH}/RefBase.cpp
${SOURCE_PATH}/SharedBuffer.cpp
${SOURCE_PATH}/StopWatch.cpp
${SOURCE_PATH}/String8.cpp
${SOURCE_PATH}/String16.cpp
${SOURCE_PATH}/StrongPointer.cpp
${SOURCE_PATH}/SystemClock.cpp
${SOURCE_PATH}/Threads.cpp
${SOURCE_PATH}/Timers.cpp
${SOURCE_PATH}/Tokenizer.cpp
${SOURCE_PATH}/Unicode.cpp
${SOURCE_PATH}/VectorImpl.cpp
${SOURCE_PATH}/misc.cpp
)

# other files
list(APPEND ${PROJECT_NAME}_SOURCE_FILES 
${SOURCE_PATH}/CallStack.cpp
${SOURCE_PATH}/Looper.cpp
${SOURCE_PATH}/ProcessCallStack.cpp
${SOURCE_PATH}/Trace.cpp
)

# target files
ADD_SHARED_LIB(utils)

if(UNIX AND NOT APPLE)
    find_package(Threads)
    target_link_libraries(utils ${CMAKE_THREAD_LIBS_INIT})
endif()

#set(ENABLE_TEST TRUE)
if(ENABLE_TEST)
    add_subdirectory(test)
endif(ENABLE_TEST)
