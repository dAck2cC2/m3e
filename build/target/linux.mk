#
#  Created by Jeremy on 2015-08-08.
#  Copyright 2015. All rights reserved.  
#

CFLAGS += -D_LINUX 
CFLAGS += -DHAVE_PTHREADS
CFLAGS += -D__unused= 
CFLAGS += -fpermissive
CFLAGS += -std=c++0x
CFLAGS += -fPIC

LIBS += -lpthread

HOST_SHLIB_SUFFIX := .so
TARGET_SHLIB_SUFFIX := .so


