#
#  Created by Jeremy on 2015-08-08.
#  Copyright 2015. All rights reserved.  
#

# **************************************
# Build Path and Target
# **************************************

BUILD_ROOT := ./build
BUILD_DIR += $(BUILD_ROOT)


# **************************************
# Object
# **************************************t

OBJS := $(patsubst %.cpp, $(BUILD_ROOT)/%.o, $(CPPSRC)) \
        $(patsubst %.c, $(BUILD_ROOT)/%.o, $(CSRC))


# **************************************
# Enviornment
# **************************************t

# Internal Include Path
INT_INCLUDE += -I$(SRC_DIR) 
LIBS += 

# External Library
EXT_INCLUDE += -I../../3rd/lame/inc
EXT_LIB += 


# Compile Flag
CFLAGS += -g -Wno-deprecated -Wall -Wno-multichar -DDEBUG
#-Werror


# Use GXX for all C and C++ files
#GCC = gcc
#CC = $(GCC)
GXX = g++
CXX = $(GXX)
#AR = ar
CXXFLAGS = $(CFLAGS)

#ASTYLE_DIR  = $(patsubst $(BUILD_ROOT)%, $(SRC_DIR)%, $(BUILD_DIR))
ASTYLE_FILE = $(shell find $(SRC_DIR) -type f)
ASTYLE_OPT += --mode=c -A3 -z2 -s4 -f -n -p
ASTYLE := astyle
DTOU := dos2unix

# **************************************
# Rule
# **************************************t

# the Project
all: check_dir $(TARGET)

check_dir:
	@for DIR in $(BUILD_DIR) ; do \
	if [ ! -d $$DIR ] ; then mkdir -p $$DIR ; fi \
	done

format:
	@for FILE in $(ASTYLE_FILE) ; do \
	$(ASTYLE) $(ASTYLE_OPT) $$FILE ;\
	$(DTOU) $$FILE ;\
	done
	@$(DTOU) ../cfg/*.*
	@$(DTOU) ./Makefile

$(TARGET) : $(OBJS)
	@echo [Linking][$(TARGET)]
	@$(GXX) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS) $(EXT_LIB)

$(BUILD_ROOT)/%.o : $(SRC_DIR)/%.c
	@echo [Compiling][$*.c]
	@$(GXX) $(CFLAGS) $(INT_INCLUDE) $(EXT_INCLUDE) -g -c -MD  -o $@ $<
	@set -e ; cp $(BUILD_ROOT)/$*.d $(BUILD_ROOT)/$*.dep; \
        sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
        -e '/^$$/ d' -e 's/$$/ :/' < $(BUILD_ROOT)/$*.d >> $(BUILD_ROOT)/$*.dep; \
        rm -f $(BUILD_ROOT)/$*.d

$(BUILD_ROOT)/%.o : $(SRC_DIR)/%.cpp
	@echo [Compiling][$*.cpp]
	@$(GXX) $(CFLAGS) $(INT_INCLUDE) $(EXT_INCLUDE) -g -c -MD  -o $@ $<
	@set -e ; cp $(BUILD_ROOT)/$*.d $(BUILD_ROOT)/$*.dep; \
        sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
        -e '/^$$/ d' -e 's/$$/ :/' < $(BUILD_ROOT)/$*.d >> $(BUILD_ROOT)/$*.dep; \
        rm -f $(BUILD_ROOT)/$*.d

.PHONY: install
install:
	@echo "[Message][I have no idea what to do... m(_ _)m]"

.PHONY: clean distclean
clean distclean:
	@echo [Cleaning]...
	@rm -rf $(BUILD_ROOT) $(TARGET)

test:
#	@echo $(ASTYLE_DIR)
#	@echo $(OBJS)

-include $(OBJS:$(BUILD_ROOT)/%.o=$(BUILD_ROOT)/.%.dep)



