CFLAGS += -D_CYGWIN 
#CFLAGS += -DHAVE_MS_C_RUNTIME
CFLAGS += -std=c++11
CFLAGS += -fpermissive
CFLAGS += -D_GNU_SOURCE
CFLAGS += -DHAVE_PTHREADS
#CFLAGS += -DHAVE_WIN32_THREADS
CFLAGS += -DO_LARGEFILE=0
CFLAGS += -Dlseek64=lseek
CFLAGS += -Doff64_t=_off64_t

#SHLIB_SUFFIX := .so
HOST_SHLIB_SUFFIX := .so
TARGET_SHLIB_SUFFIX := .so

#STATIC_LIB_SUFFIX := .a
HOST_STATIC_LIB_SUFFIX := .a
TARGET_STATIC_LIB_SUFFIX := .a
