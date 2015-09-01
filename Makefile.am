
AUTOMAKE_OPTIONS = foreign \
                   subdir-objects
#                   no-dependencies


noinst_HEADERS = \
    ./3rd/lame/include/lame.h \
    ./src/engine/EngineDefine.h

EXTRA_DIST = \
    ./src/main.cpp \
    ./proj/cfg/cfg_src.mk \
    ./proj/cfg/cfg_rule.mk

#ACLOCAL_AMFLAGS = -I m4

DEFS = ${CFLAGS} \
       -DHAVE_PTHREADS

noinst_LTLIBRARIES = libutils.la

libutils_la_LDFLAGS = -shared \
                      -version-info 0:0 \
                      -export-dynamic \
                      -lpthread \
                      -no-undefined

#libutils_la_LIBADD = libpthread.so
libutils_ladir = ./src/utils

libutils_la_SOURCES = \
    ./src/utils/RefBase.cpp \
    ./src/utils/SharedBuffer.cpp \
    ./src/utils/VectorImpl.cpp \
    ./src/utils/String8.cpp \
    ./src/utils/Unicode.cpp \
    ./src/utils/Static.cpp \
    ./src/utils/Timers.cpp \
    ./src/utils/Threads.cpp \
    ./src/utils/hexdump.cpp \
    ./src/utils/AString.cpp \
    ./src/utils/ABuffer.cpp \
    ./src/utils/AAtomizer.cpp \
    ./src/utils/AMessage.cpp \
    ./src/utils/AHandler.cpp \
    ./src/utils/ALooper.cpp \
    ./src/utils/ALooperRoster.cpp 

libutils_la_HEADERS = \
    ./src/utils/AAtomizer.h \
    ./src/utils/ABase.h \
    ./src/utils/ABuffer.h \
    ./src/utils/ADebug.h \
    ./src/utils/ADebugExt.h \
    ./src/utils/AHandler.h \
    ./src/utils/AHandlerReflector.h \
    ./src/utils/ALooper.h \
    ./src/utils/ALooperRoster.h \
    ./src/utils/AMessage.h \
    ./src/utils/AString.h \
    ./src/utils/AndroidThreads.h \
    ./src/utils/Condition.h \
    ./src/utils/Errors.h \
    ./src/utils/KeyedVector.h \
    ./src/utils/List.h \
    ./src/utils/Mutex.h \
    ./src/utils/RefBase.h \
    ./src/utils/SharedBuffer.h \
    ./src/utils/Singleton.h \
    ./src/utils/SortedVector.h \
    ./src/utils/Static.h \
    ./src/utils/String8.h \
    ./src/utils/StrongPointer.h \
    ./src/utils/Thread.h \
    ./src/utils/ThreadDefs.h \
    ./src/utils/Timers.h \
    ./src/utils/TypeHelpers.h \
    ./src/utils/Unicode.h \
    ./src/utils/UtilsDefine.h \
    ./src/utils/Vector.h \
    ./src/utils/VectorImpl.h \
    ./src/utils/atomic-arm.h \
    ./src/utils/atomic-inline.h \
    ./src/utils/atomic-mips.h \
    ./src/utils/atomic-x86.h \
    ./src/utils/atomic.h \
    ./src/utils/bitops.h \
    ./src/utils/hexdump.h \
    ./src/utils/log.h \
    ./src/utils/os_sep.h \
    ./src/utils/properties.h \
    ./src/utils/sched_policy.h

