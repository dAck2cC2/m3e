# This is included by the top-level Makefile.
# It sets up standard variables based on the
# current configuration and platform, which
# are not specific to what is being built.

# Only use ANDROID_BUILD_SHELL to wrap around bash.
# DO NOT use other shells such as zsh.
ifdef ANDROID_BUILD_SHELL
SHELL := $(ANDROID_BUILD_SHELL)
else
# Use bash, not whatever shell somebody has installed as /bin/sh
# This is repeated from main.mk, since envsetup.sh runs this file
# directly.
SHELL := /bin/bash
endif

# Utility variables.
empty :=
space := $(empty) $(empty)
comma := ,
# Note that make will eat the newline just before endef.
define newline


endef
# The pound character "#"
define pound
#
endef
# Unfortunately you can't simply define backslash as \ or \\.
backslash := \a
backslash := $(patsubst %a,%,$(backslash))

# Tell python not to spam the source tree with .pyc files.  This
# only has an effect on python 2.6 and above.
export PYTHONDONTWRITEBYTECODE := 1

ifneq ($(filter --color=always, $(GREP_OPTIONS)),)
$(warning The build system needs unmodified output of grep.)
$(error Please remove --color=always from your  $$GREP_OPTIONS)
endif

# ###############################################################
# Build system internal files
# ###############################################################

CLEAR_VARS:= $(BUILD_SYSTEM)/clear_vars.mk
BUILD_COMBOS:= $(BUILD_SYSTEM)/combo
BUILD_COPY_HEADERS := $(BUILD_SYSTEM)/copy_headers.mk
BUILD_STATIC_LIBRARY:= $(BUILD_SYSTEM)/static_library.mk
BUILD_SHARED_LIBRARY:= $(BUILD_SYSTEM)/shared_library.mk
BUILD_PREBUILT:= $(BUILD_SYSTEM)/prebuilt.mk
BUILD_NOTICE_FILE:= $(BUILD_SYSTEM)/notice_files.mk
BUILD_EXECUTABLE:= $(BUILD_SYSTEM)/executable.mk


# ###############################################################
# Parse out any modifier targets.
# ###############################################################

#MAKECMDGOALS:= showcommands

# The 'showcommands' goal says to show the full command
# lines being executed, instead of a short message about
# the kind of operation being done.
SHOW_COMMANDS:= $(filter showcommands,$(MAKECMDGOALS))
hide := $(if $(SHOW_COMMANDS),,@)

# ###############################################################
# Include sub-configuration files
# ###############################################################

# ---------------------------------------------------------------
# Define most of the global variables.  These are the ones that
# are specific to the user's build configuration.
include $(BUILD_SYSTEM)/envsetup.mk

# Pruned directory options used when using findleaves.py
# See envsetup.mk for a description of SCAN_EXCLUDE_DIRS
FIND_LEAVES_EXCLUDES := $(addprefix --prune=, $(SCAN_EXCLUDE_DIRS) .repo .git)


combo_target := HOST_
combo_2nd_arch_prefix := 
include $(BUILD_SYSTEM)/combo/select.mk

# define clang/llvm tools and global flags
include $(BUILD_SYSTEM)/clang/config.mk


#ifeq ($(HOST_OS),linux)
#RELATIVE_PWD := PWD=/proc/self/cwd
#else
#RELATIVE_PWD := 
#endif
