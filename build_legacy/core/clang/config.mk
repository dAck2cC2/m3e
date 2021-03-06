## Clang configurations.

LLVM_PREBUILTS_PATH := $(LLVM_PREBUILTS_BASE)/$(BUILD_OS)-x86/$(LLVM_PREBUILTS_VERSION)/bin
LLVM_RTLIB_PATH := $(LLVM_PREBUILTS_PATH)/../lib64/clang/$(LLVM_RELEASE_VERSION)/lib/linux/

# These will come from Soong, drop the environment versions
unexport CLANG
unexport CLANG_CXX
unexport CCC_CC
unexport CCC_CXX

CLANG_TBLGEN := $(BUILD_OUT_EXECUTABLES)/clang-tblgen$(BUILD_EXECUTABLE_SUFFIX)
LLVM_TBLGEN := $(BUILD_OUT_EXECUTABLES)/llvm-tblgen$(BUILD_EXECUTABLE_SUFFIX)

# RenderScript-specific tools
# These are tied to the version of LLVM directly in external/, so they might
# trail the host prebuilts being used for the rest of the build process.
RS_LLVM_PREBUILTS_VERSION := clang-3289846
RS_LLVM_PREBUILTS_BASE := prebuilts/clang/host
RS_LLVM_PREBUILTS_PATH := $(RS_LLVM_PREBUILTS_BASE)/$(BUILD_OS)-x86/$(RS_LLVM_PREBUILTS_VERSION)/bin
RS_CLANG := $(RS_LLVM_PREBUILTS_PATH)/clang$(BUILD_EXECUTABLE_SUFFIX)
RS_LLVM_AS := $(RS_LLVM_PREBUILTS_PATH)/llvm-as$(BUILD_EXECUTABLE_SUFFIX)
RS_LLVM_LINK := $(RS_LLVM_PREBUILTS_PATH)/llvm-link$(BUILD_EXECUTABLE_SUFFIX)

define convert-to-clang-flags
$(strip $(filter-out $(CLANG_CONFIG_UNKNOWN_CFLAGS),$(1)))
endef

CLANG_DEFAULT_UB_CHECKS := \
  bool \
  integer-divide-by-zero \
  return \
  returns-nonnull-attribute \
  shift-exponent \
  unreachable \
  vla-bound \

# TODO(danalbert): The following checks currently have compiler performance
# issues.
# CLANG_DEFAULT_UB_CHECKS += alignment
# CLANG_DEFAULT_UB_CHECKS += bounds
# CLANG_DEFAULT_UB_CHECKS += enum
# CLANG_DEFAULT_UB_CHECKS += float-cast-overflow
# CLANG_DEFAULT_UB_CHECKS += float-divide-by-zero
# CLANG_DEFAULT_UB_CHECKS += nonnull-attribute
# CLANG_DEFAULT_UB_CHECKS += null
# CLANG_DEFAULT_UB_CHECKS += shift-base
# CLANG_DEFAULT_UB_CHECKS += signed-integer-overflow

# TODO(danalbert): Fix UB in libc++'s __tree so we can turn this on.
# https://llvm.org/PR19302
# http://reviews.llvm.org/D6974
# CLANG_DEFAULT_UB_CHECKS += object-size

# HOST config
clang_2nd_arch_prefix :=
include $(BUILD_SYSTEM)/clang/HOST_$(HOST_ARCH).mk

# HOST_2ND_ARCH config
ifdef HOST_2ND_ARCH
clang_2nd_arch_prefix := $(HOST_2ND_ARCH_VAR_PREFIX)
include $(BUILD_SYSTEM)/clang/HOST_$(HOST_2ND_ARCH).mk
endif

ifdef HOST_CROSS_ARCH
clang_2nd_arch_prefix :=
include $(BUILD_SYSTEM)/clang/HOST_CROSS_$(HOST_CROSS_ARCH).mk
ifdef HOST_CROSS_2ND_ARCH
clang_2nd_arch_prefix := $(HOST_CROSS_2ND_ARCH_VAR_PREFIX)
include $(BUILD_SYSTEM)/clang/HOST_CROSS_$(HOST_CROSS_2ND_ARCH).mk
endif
endif

# TARGET config
ifdef TARGET_ARCH
clang_2nd_arch_prefix :=
include $(BUILD_SYSTEM)/clang/TARGET_$(TARGET_ARCH).mk
endif

# TARGET_2ND_ARCH config
ifdef TARGET_2ND_ARCH
clang_2nd_arch_prefix := $(TARGET_2ND_ARCH_VAR_PREFIX)
include $(BUILD_SYSTEM)/clang/TARGET_$(TARGET_2ND_ARCH).mk
endif

ifdef remove_unuse
# This allows us to use the superset of functionality that compiler-rt
# provides to Clang (for supporting features like -ftrapv).
COMPILER_RT_CONFIG_EXTRA_STATIC_LIBRARIES := libcompiler_rt-extras
endif
# A list of projects that are allowed to set LOCAL_CLANG to false.
# INTERNAL_LOCAL_CLANG_EXCEPTION_PROJECTS is defined later in other config.mk.
LOCAL_CLANG_EXCEPTION_PROJECTS = \
  bionic/tests/ \
  device/huawei/angler/ \
  device/lge/bullhead/ \
  external/gentoo/integration/ \
  hardware/qcom/ \
  $(INTERNAL_LOCAL_CLANG_EXCEPTION_PROJECTS)

# Find $1 in the exception project list.
define find_in_local_clang_exception_projects
$(subst $(space),, \
  $(foreach project,$(LOCAL_CLANG_EXCEPTION_PROJECTS), \
    $(if $(filter $(project)%,$(1)),$(project)) \
  ) \
)
endef

include $(BUILD_SYSTEM)/clang/tidy.mk
