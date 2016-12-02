
CLEAR_VARS:= $(BUILD_SYSTEM)/clear_vars.mk
BUILD_COMBOS:= $(BUILD_SYSTEM)/combo
BUILD_COPY_HEADERS := $(BUILD_SYSTEM)/copy_headers.mk
BUILD_STATIC_LIBRARY:= $(BUILD_SYSTEM)/static_library.mk
BUILD_SHARED_LIBRARY:= $(BUILD_SYSTEM)/shared_library.mk
BUILD_PREBUILT:= $(BUILD_SYSTEM)/prebuilt.mk
BUILD_NOTICE_FILE:= $(BUILD_SYSTEM)/notice_files.mk
BUILD_EXECUTABLE:= $(BUILD_SYSTEM)/executable.mk


include $(BUILD_SYSTEM)/envsetup.mk

combo_target := HOST_
combo_2nd_arch_prefix := 
include $(BUILD_SYSTEM)/combo/select.mk

# Pruned directory options used when using findleaves.py
# See envsetup.mk for a description of SCAN_EXCLUDE_DIRS
FIND_LEAVES_EXCLUDES := $(addprefix --prune=, $(SCAN_EXCLUDE_DIRS) .repo .git)

MAKECMDGOALS:= showcommands
SHOW_COMMANDS:= $(filter showcommands,$(MAKECMDGOALS))
hide := $(if $(SHOW_COMMANDS),,@)


#ifeq ($(HOST_OS),linux)
#RELATIVE_PWD := PWD=/proc/self/cwd
#else
#RELATIVE_PWD := 
#endif
