#ifndef HIDL_GENERATED_ANDROID_HARDWARE_CAS_NATIVE_V1_0_TYPES_H
#define HIDL_GENERATED_ANDROID_HARDWARE_CAS_NATIVE_V1_0_TYPES_H

#include <hidl/HidlSupport.h>
#include <hidl/MQDescriptor.h>
#include <utils/NativeHandle.h>
#include <utils/misc.h>

namespace android {
namespace hardware {
namespace cas {
namespace native {
namespace V1_0 {

enum class ScramblingControl : uint32_t {
    UNSCRAMBLED = 0u, // 0
    RESERVED = 1u, // 1
    EVENKEY = 2u, // 2
    ODDKEY = 3u, // 3
};

struct SubSample final {
    uint32_t numBytesOfClearData __attribute__ ((aligned(4)));
    uint32_t numBytesOfEncryptedData __attribute__ ((aligned(4)));
};

static_assert(offsetof(SubSample, numBytesOfClearData) == 0, "wrong offset");
static_assert(offsetof(SubSample, numBytesOfEncryptedData) == 4, "wrong offset");
static_assert(sizeof(SubSample) == 8, "wrong size");
static_assert(__alignof(SubSample) == 4, "wrong alignment");

struct SharedBuffer final {
    ::android::hardware::hidl_memory heapBase __attribute__ ((aligned(8)));
    uint64_t offset __attribute__ ((aligned(8)));
    uint64_t size __attribute__ ((aligned(8)));
};

static_assert(offsetof(SharedBuffer, heapBase) == 0, "wrong offset");
static_assert(offsetof(SharedBuffer, offset) == 40, "wrong offset");
static_assert(offsetof(SharedBuffer, size) == 48, "wrong offset");
static_assert(sizeof(SharedBuffer) == 56, "wrong size");
static_assert(__alignof(SharedBuffer) == 8, "wrong alignment");

enum class BufferType : uint32_t {
    SHARED_MEMORY = 0u, // 0
    NATIVE_HANDLE = 1u, // 1
};

struct DestinationBuffer final {
    BufferType type __attribute__ ((aligned(4)));
    SharedBuffer nonsecureMemory __attribute__ ((aligned(8)));
    ::android::hardware::hidl_handle secureMemory __attribute__ ((aligned(8)));
};

static_assert(offsetof(DestinationBuffer, type) == 0, "wrong offset");
static_assert(offsetof(DestinationBuffer, nonsecureMemory) == 8, "wrong offset");
static_assert(offsetof(DestinationBuffer, secureMemory) == 64, "wrong offset");
static_assert(sizeof(DestinationBuffer) == 80, "wrong size");
static_assert(__alignof(DestinationBuffer) == 8, "wrong alignment");

constexpr uint32_t operator|(const ScramblingControl lhs, const ScramblingControl rhs) {
    return static_cast<uint32_t>(static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs));
}

constexpr uint32_t operator|(const uint32_t lhs, const ScramblingControl rhs) {
    return static_cast<uint32_t>(lhs | static_cast<uint32_t>(rhs));
}

constexpr uint32_t operator|(const ScramblingControl lhs, const uint32_t rhs) {
    return static_cast<uint32_t>(static_cast<uint32_t>(lhs) | rhs);
}

constexpr uint32_t operator&(const ScramblingControl lhs, const ScramblingControl rhs) {
    return static_cast<uint32_t>(static_cast<uint32_t>(lhs) & static_cast<uint32_t>(rhs));
}

constexpr uint32_t operator&(const uint32_t lhs, const ScramblingControl rhs) {
    return static_cast<uint32_t>(lhs & static_cast<uint32_t>(rhs));
}

constexpr uint32_t operator&(const ScramblingControl lhs, const uint32_t rhs) {
    return static_cast<uint32_t>(static_cast<uint32_t>(lhs) & rhs);
}

constexpr uint32_t &operator|=(uint32_t& v, const ScramblingControl e) {
    v |= static_cast<uint32_t>(e);
    return v;
}

constexpr uint32_t &operator&=(uint32_t& v, const ScramblingControl e) {
    v &= static_cast<uint32_t>(e);
    return v;
}

template<typename>
std::string toString(uint32_t o);
template<>
std::string toString<ScramblingControl>(uint32_t o);

std::string toString(ScramblingControl o);

std::string toString(const SubSample&);

bool operator==(const SubSample&, const SubSample&);

bool operator!=(const SubSample&, const SubSample&);

std::string toString(const SharedBuffer&);

// operator== and operator!= are not generated for SharedBuffer

constexpr uint32_t operator|(const BufferType lhs, const BufferType rhs) {
    return static_cast<uint32_t>(static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs));
}

constexpr uint32_t operator|(const uint32_t lhs, const BufferType rhs) {
    return static_cast<uint32_t>(lhs | static_cast<uint32_t>(rhs));
}

constexpr uint32_t operator|(const BufferType lhs, const uint32_t rhs) {
    return static_cast<uint32_t>(static_cast<uint32_t>(lhs) | rhs);
}

constexpr uint32_t operator&(const BufferType lhs, const BufferType rhs) {
    return static_cast<uint32_t>(static_cast<uint32_t>(lhs) & static_cast<uint32_t>(rhs));
}

constexpr uint32_t operator&(const uint32_t lhs, const BufferType rhs) {
    return static_cast<uint32_t>(lhs & static_cast<uint32_t>(rhs));
}

constexpr uint32_t operator&(const BufferType lhs, const uint32_t rhs) {
    return static_cast<uint32_t>(static_cast<uint32_t>(lhs) & rhs);
}

constexpr uint32_t &operator|=(uint32_t& v, const BufferType e) {
    v |= static_cast<uint32_t>(e);
    return v;
}

constexpr uint32_t &operator&=(uint32_t& v, const BufferType e) {
    v &= static_cast<uint32_t>(e);
    return v;
}

template<typename>
std::string toString(uint32_t o);
template<>
std::string toString<BufferType>(uint32_t o);

std::string toString(BufferType o);

std::string toString(const DestinationBuffer&);

// operator== and operator!= are not generated for DestinationBuffer


}  // namespace V1_0
}  // namespace native
}  // namespace cas
}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_CAS_NATIVE_V1_0_TYPES_H
