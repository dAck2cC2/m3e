#
#  Created by Jeremy on 2015-08-08.
#  Copyright 2015. All rights reserved.  
#

TARGET := m3e.exe

CFLAGS += -D_CYGWIN 
CFLAGS += -DHAVE_PTHREADS
#CFLAGS += -DHAVE_WIN32_THREADS
CFLAGS += -DO_LARGEFILE=0
CFLAGS += -Dlseek64=lseek
CFLAGS += -Doff64_t=_off64_t

EXT_LIB += ./lib/libmp3lame.a

-include ../cfg/cfg_src.mk
-include ../cfg/cfg_rule.mk


