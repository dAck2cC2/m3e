#ifndef HIDL_GENERATED_ANDROID_HARDWARE_CAS_V1_0_TYPES_H
#define HIDL_GENERATED_ANDROID_HARDWARE_CAS_V1_0_TYPES_H

#include <hidl/HidlSupport.h>
#include <hidl/MQDescriptor.h>
#include <utils/NativeHandle.h>
#include <utils/misc.h>

namespace android {
namespace hardware {
namespace cas {
namespace V1_0 {

#if defined(__linux__)
#  if defined(Status)
#    undef Status
#  endif
#endif

enum class Status : uint32_t {
    OK = 0u, // 0
    ERROR_CAS_NO_LICENSE = 1u, // 1
    ERROR_CAS_LICENSE_EXPIRED = 2u, // 2
    ERROR_CAS_SESSION_NOT_OPENED = 3u, // 3
    ERROR_CAS_CANNOT_HANDLE = 4u, // 4
    ERROR_CAS_INVALID_STATE = 5u, // 5
    BAD_VALUE = 6u, // 6
    ERROR_CAS_NOT_PROVISIONED = 7u, // 7
    ERROR_CAS_RESOURCE_BUSY = 8u, // 8
    ERROR_CAS_INSUFFICIENT_OUTPUT_PROTECTION = 9u, // 9
    ERROR_CAS_TAMPER_DETECTED = 10u, // 10
    ERROR_CAS_DEVICE_REVOKED = 11u, // 11
    ERROR_CAS_DECRYPT_UNIT_NOT_INITIALIZED = 12u, // 12
    ERROR_CAS_DECRYPT = 13u, // 13
    ERROR_CAS_UNKNOWN = 14u, // 14
};

typedef ::android::hardware::hidl_vec<uint8_t> HidlCasSessionId;

typedef ::android::hardware::hidl_vec<uint8_t> HidlCasData;

struct HidlCasPluginDescriptor final {
    int32_t caSystemId __attribute__ ((aligned(4)));
    ::android::hardware::hidl_string name __attribute__ ((aligned(8)));
};

static_assert(offsetof(HidlCasPluginDescriptor, caSystemId) == 0, "wrong offset");
static_assert(offsetof(HidlCasPluginDescriptor, name) == 8, "wrong offset");
static_assert(sizeof(HidlCasPluginDescriptor) == 24, "wrong size");
static_assert(__alignof(HidlCasPluginDescriptor) == 8, "wrong alignment");

constexpr uint32_t operator|(const Status lhs, const Status rhs) {
    return static_cast<uint32_t>(static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs));
}

constexpr uint32_t operator|(const uint32_t lhs, const Status rhs) {
    return static_cast<uint32_t>(lhs | static_cast<uint32_t>(rhs));
}

constexpr uint32_t operator|(const Status lhs, const uint32_t rhs) {
    return static_cast<uint32_t>(static_cast<uint32_t>(lhs) | rhs);
}

constexpr uint32_t operator&(const Status lhs, const Status rhs) {
    return static_cast<uint32_t>(static_cast<uint32_t>(lhs) & static_cast<uint32_t>(rhs));
}

constexpr uint32_t operator&(const uint32_t lhs, const Status rhs) {
    return static_cast<uint32_t>(lhs & static_cast<uint32_t>(rhs));
}

constexpr uint32_t operator&(const Status lhs, const uint32_t rhs) {
    return static_cast<uint32_t>(static_cast<uint32_t>(lhs) & rhs);
}

constexpr uint32_t &operator|=(uint32_t& v, const Status e) {
    v |= static_cast<uint32_t>(e);
    return v;
}

constexpr uint32_t &operator&=(uint32_t& v, const Status e) {
    v &= static_cast<uint32_t>(e);
    return v;
}

template<typename>
std::string toString(uint32_t o);
template<>
std::string toString<Status>(uint32_t o);

std::string toString(Status o);

std::string toString(const HidlCasPluginDescriptor&);

bool operator==(const HidlCasPluginDescriptor&, const HidlCasPluginDescriptor&);

bool operator!=(const HidlCasPluginDescriptor&, const HidlCasPluginDescriptor&);


}  // namespace V1_0
}  // namespace cas
}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_CAS_V1_0_TYPES_H
