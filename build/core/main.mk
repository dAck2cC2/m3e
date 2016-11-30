TOP := .
TOPDIR :=

#OUT_DIR := $(TOPDIR)out
#HOST_OUT_INTERMEDIATE_LIBRARIES := $(OUT_DIR)/bin

BUILD_SYSTEM := $(TOPDIR)build/core

include $(BUILD_SYSTEM)/config.mk
include $(BUILD_SYSTEM)/definitions.mk

.PHONY: all

all: m3e
#all: libmp3lame

subdir_makefiles := $(SOONG_ANDROID_MK) $(call first-makefiles-under,$(TOP))
$(foreach mk,$(subdir_makefiles),$(info including $(mk) ...)$(eval include $(mk)))

# -------------------------------------------------------------------
# All module makefiles have been included at this point.
# -------------------------------------------------------------------



