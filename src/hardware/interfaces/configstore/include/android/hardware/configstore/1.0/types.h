#ifndef HIDL_GENERATED_ANDROID_HARDWARE_CONFIGSTORE_V1_0_TYPES_H
#define HIDL_GENERATED_ANDROID_HARDWARE_CONFIGSTORE_V1_0_TYPES_H

#include <hidl/HidlSupport.h>
#include <hidl/MQDescriptor.h>
#include <utils/NativeHandle.h>
#include <utils/misc.h>

namespace android {
namespace hardware {
namespace configstore {
namespace V1_0 {

struct OptionalBool final {
    bool specified __attribute__ ((aligned(1)));
    bool value __attribute__ ((aligned(1)));
};

static_assert(offsetof(OptionalBool, specified) == 0, "wrong offset");
static_assert(offsetof(OptionalBool, value) == 1, "wrong offset");
static_assert(sizeof(OptionalBool) == 2, "wrong size");
static_assert(__alignof(OptionalBool) == 1, "wrong alignment");

struct OptionalInt32 final {
    bool specified __attribute__ ((aligned(1)));
    int32_t value __attribute__ ((aligned(4)));
};

static_assert(offsetof(OptionalInt32, specified) == 0, "wrong offset");
static_assert(offsetof(OptionalInt32, value) == 4, "wrong offset");
static_assert(sizeof(OptionalInt32) == 8, "wrong size");
static_assert(__alignof(OptionalInt32) == 4, "wrong alignment");

struct OptionalUInt32 final {
    bool specified __attribute__ ((aligned(1)));
    uint32_t value __attribute__ ((aligned(4)));
};

static_assert(offsetof(OptionalUInt32, specified) == 0, "wrong offset");
static_assert(offsetof(OptionalUInt32, value) == 4, "wrong offset");
static_assert(sizeof(OptionalUInt32) == 8, "wrong size");
static_assert(__alignof(OptionalUInt32) == 4, "wrong alignment");

struct OptionalInt64 final {
    bool specified __attribute__ ((aligned(1)));
    int64_t value __attribute__ ((aligned(8)));
};

static_assert(offsetof(OptionalInt64, specified) == 0, "wrong offset");
static_assert(offsetof(OptionalInt64, value) == 8, "wrong offset");
static_assert(sizeof(OptionalInt64) == 16, "wrong size");
static_assert(__alignof(OptionalInt64) == 8, "wrong alignment");

struct OptionalUInt64 final {
    bool specified __attribute__ ((aligned(1)));
    uint64_t value __attribute__ ((aligned(8)));
};

static_assert(offsetof(OptionalUInt64, specified) == 0, "wrong offset");
static_assert(offsetof(OptionalUInt64, value) == 8, "wrong offset");
static_assert(sizeof(OptionalUInt64) == 16, "wrong size");
static_assert(__alignof(OptionalUInt64) == 8, "wrong alignment");

struct OptionalString final {
    bool specified __attribute__ ((aligned(1)));
    ::android::hardware::hidl_string value __attribute__ ((aligned(8)));
};

static_assert(offsetof(OptionalString, specified) == 0, "wrong offset");
static_assert(offsetof(OptionalString, value) == 8, "wrong offset");
static_assert(sizeof(OptionalString) == 24, "wrong size");
static_assert(__alignof(OptionalString) == 8, "wrong alignment");

std::string toString(const OptionalBool&);

bool operator==(const OptionalBool&, const OptionalBool&);

bool operator!=(const OptionalBool&, const OptionalBool&);

std::string toString(const OptionalInt32&);

bool operator==(const OptionalInt32&, const OptionalInt32&);

bool operator!=(const OptionalInt32&, const OptionalInt32&);

std::string toString(const OptionalUInt32&);

bool operator==(const OptionalUInt32&, const OptionalUInt32&);

bool operator!=(const OptionalUInt32&, const OptionalUInt32&);

std::string toString(const OptionalInt64&);

bool operator==(const OptionalInt64&, const OptionalInt64&);

bool operator!=(const OptionalInt64&, const OptionalInt64&);

std::string toString(const OptionalUInt64&);

bool operator==(const OptionalUInt64&, const OptionalUInt64&);

bool operator!=(const OptionalUInt64&, const OptionalUInt64&);

std::string toString(const OptionalString&);

bool operator==(const OptionalString&, const OptionalString&);

bool operator!=(const OptionalString&, const OptionalString&);


}  // namespace V1_0
}  // namespace configstore
}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_CONFIGSTORE_V1_0_TYPES_H
