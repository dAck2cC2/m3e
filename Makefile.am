
AUTOMAKE_OPTIONS = foreign \
                   subdir-objects
#                   no-dependencies

EXTRA_DIST = \
    3rd/include/lame/lame.h \
    proj/cfg/cfg_src.mk \
    proj/cfg/cfg_rule.mk

ACLOCAL_AMFLAGS = -I m4


noinst_LTLIBRARIES = libutils.la


#CURRENTPATH = $(shell /bin/pwd)
#AM_CPPFLAGS = -I$(CURRENTPATH)/3rd/lame/include \
#              -I$(CURRENTPATH)/src

#export AM_CPPFLAGS 

#DEFS = -D_LINUX \
#       -DHAVE_PTHREADS

DEFS = ${CFLAGS} \
       -DHAVE_PTHREADS

#libutils_la_LIBADD = libpthread.so
libutils_la_LDFLAGS = -shared \
                      -version-info 0:0 \
                      -export-dynamic \
                      -lpthread \
                      -no-undefined

#top_srcdir = ./
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


