#
#  Created by Jeremy on 2015-08-08.
#  Copyright 2015. All rights reserved.  
#

CFLAGS += -D_MACOSX
CFLAGS += -DHAVE_PTHREADS
CFLAGS += -DPATH_MAX=4096
CFLAGS += -Doff64_t=off_t
CFLAGS += -DO_LARGEFILE=0
CFLAGS += -Dlseek64=lseek
#CFLAGS += -D_LIBCPP_HAS_NO_UNICODE_CHARS
#CFLAGS += -D__linux__
CFLAGS += -std=c++11

LIBS += -lpthread

