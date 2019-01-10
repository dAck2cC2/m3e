
BUILD_CYGWIN=1
ENABLE_CODEC_LAME=1
#ENABLE_CODEC_MP3=1
#ENABLE_CODEC_SELECTOR=1
ENABLE_AUDIO_OPENAL=1

ifdef ENABLE_CODEC_MP3
ENABLE_CODEC_SELECTOR=1
endif

#CFLAGS += -D_CYGWIN 
#CFLAGS += -fpermissive

CPPFLAGS += -std=c++11
CFLAGS += -D_GNU_SOURCE
CFLAGS += -Doff64_t=_off64_t

#CFLAGS += -DHAVE_MS_C_RUNTIME
CFLAGS += -DHAVE_PTHREADS
#CFLAGS += -DHAVE_WIN32_THREADS

CFLAGS += -DENABLE_CUSTOMISE

#SHLIB_SUFFIX := .so
HOST_SHLIB_SUFFIX := .so
TARGET_SHLIB_SUFFIX := .so

#STATIC_LIB_SUFFIX := .a
HOST_STATIC_LIB_SUFFIX := .a
TARGET_STATIC_LIB_SUFFIX := .a
