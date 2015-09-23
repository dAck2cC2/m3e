#
#  Created by Jeremy on 2015-08-08.
#  Copyright 2015. All rights reserved.  
#

TARGET := m3e

CFLAGS += -D_MACOSX
CFLAGS += -DHAVE_PTHREADS
CFLAGS += -DPATH_MAX=4096
CFLAGS += -Doff64_t=off_t
CFLAGS += -DO_LARGEFILE=0
CFLAGS += -Dlseek64=lseek
CFLAGS += -D_LIBCPP_HAS_NO_UNICODE_CHARS
#CFLAGS += -D__linux__
CFLAGS += -U__cplusplus -D__cplusplus=201103L

LIBS += -lpthread
EXT_LIB += ./lib/libmp3lame.a

-include ../cfg/cfg_src.mk
-include ../cfg/cfg_rule.mk


