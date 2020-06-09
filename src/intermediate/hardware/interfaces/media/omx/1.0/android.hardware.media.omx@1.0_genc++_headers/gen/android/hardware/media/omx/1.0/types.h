#ifndef HIDL_GENERATED_ANDROID_HARDWARE_MEDIA_OMX_V1_0_TYPES_H
#define HIDL_GENERATED_ANDROID_HARDWARE_MEDIA_OMX_V1_0_TYPES_H

#include <android/hardware/media/1.0/types.h>

#include <hidl/HidlSupport.h>
#include <hidl/MQDescriptor.h>
#include <utils/NativeHandle.h>
#include <utils/misc.h>

namespace android {
namespace hardware {
namespace media {
namespace omx {
namespace V1_0 {

// Forward declaration for forward reference support:
enum class Status : int32_t;
struct Message;
struct CodecBuffer;
enum class PortMode : int32_t;
struct ColorAspects;

typedef uint32_t BufferId;

/**
 * Ref: system/core/include/utils/Errors.h
 * Ref: bionic/libc/kernel/uapi/asm-generic/errno-base.h
 * Ref: bionic/libc/kernel/uapi/asm-generic/errno.h
 * Ref: frameworks/av/include/media/stagefright/MediaError.h
 * Ref: frameworks/av/media/libstagefright/omx/OMXUtils.cpp: StatusFromOMXError
 */
enum class Status : int32_t {
    OK = 0,
    NO_ERROR = 0,
    NAME_NOT_FOUND = -2, // (-2)
    WOULD_BLOCK = -11, // (-11)
    NO_MEMORY = -12, // (-12)
    ALREADY_EXISTS = -17, // (-17)
    NO_INIT = -19, // (-19)
    BAD_VALUE = -22, // (-22)
    DEAD_OBJECT = -32, // (-32)
    INVALID_OPERATION = -38, // (-38)
    TIMED_OUT = -110, // (-110)
    ERROR_UNSUPPORTED = -1010, // (-1010)
    UNKNOWN_ERROR = -2147483648, // (-2147483648)
    BUFFER_NEEDS_REALLOCATION = 1,
    RELEASE_ALL_BUFFERS = 2,
};

/**
 * Ref: frameworks/av/include/media/IOMX.h: omx_message
 * 
 * Data structure for an OMX message. This is essentially a union of different
 * message types.
 */
struct Message final {
    // Forward declaration for forward reference support:
    enum class Type : uint32_t;
    struct EventData;
    struct BufferData;
    struct ExtendedBufferData;
    struct RenderData;
    union Data;

    enum class Type : uint32_t {
        EVENT = 0u,
        EMPTY_BUFFER_DONE = 1u, // (::android::hardware::media::omx::V1_0::Message::Type.EVENT implicitly + 1)
        FILL_BUFFER_DONE = 2u, // (::android::hardware::media::omx::V1_0::Message::Type.EMPTY_BUFFER_DONE implicitly + 1)
        FRAME_RENDERED = 3u, // (::android::hardware::media::omx::V1_0::Message::Type.FILL_BUFFER_DONE implicitly + 1)
    };

    struct EventData final {
        uint32_t event __attribute__ ((aligned(4)));
        uint32_t data1 __attribute__ ((aligned(4)));
        uint32_t data2 __attribute__ ((aligned(4)));
        uint32_t data3 __attribute__ ((aligned(4)));
        uint32_t data4 __attribute__ ((aligned(4)));
    };

    static_assert(offsetof(::android::hardware::media::omx::V1_0::Message::EventData, event) == 0, "wrong offset");
    static_assert(offsetof(::android::hardware::media::omx::V1_0::Message::EventData, data1) == 4, "wrong offset");
    static_assert(offsetof(::android::hardware::media::omx::V1_0::Message::EventData, data2) == 8, "wrong offset");
    static_assert(offsetof(::android::hardware::media::omx::V1_0::Message::EventData, data3) == 12, "wrong offset");
    static_assert(offsetof(::android::hardware::media::omx::V1_0::Message::EventData, data4) == 16, "wrong offset");
    static_assert(sizeof(::android::hardware::media::omx::V1_0::Message::EventData) == 20, "wrong size");
    static_assert(__alignof(::android::hardware::media::omx::V1_0::Message::EventData) == 4, "wrong alignment");

    struct BufferData final {
        uint32_t buffer __attribute__ ((aligned(4)));
    };

    static_assert(offsetof(::android::hardware::media::omx::V1_0::Message::BufferData, buffer) == 0, "wrong offset");
    static_assert(sizeof(::android::hardware::media::omx::V1_0::Message::BufferData) == 4, "wrong size");
    static_assert(__alignof(::android::hardware::media::omx::V1_0::Message::BufferData) == 4, "wrong alignment");

    struct ExtendedBufferData final {
        uint32_t buffer __attribute__ ((aligned(4)));
        uint32_t rangeOffset __attribute__ ((aligned(4)));
        uint32_t rangeLength __attribute__ ((aligned(4)));
        uint32_t flags __attribute__ ((aligned(4)));
        uint64_t timestampUs __attribute__ ((aligned(8)));
    };

    static_assert(offsetof(::android::hardware::media::omx::V1_0::Message::ExtendedBufferData, buffer) == 0, "wrong offset");
    static_assert(offsetof(::android::hardware::media::omx::V1_0::Message::ExtendedBufferData, rangeOffset) == 4, "wrong offset");
    static_assert(offsetof(::android::hardware::media::omx::V1_0::Message::ExtendedBufferData, rangeLength) == 8, "wrong offset");
    static_assert(offsetof(::android::hardware::media::omx::V1_0::Message::ExtendedBufferData, flags) == 12, "wrong offset");
    static_assert(offsetof(::android::hardware::media::omx::V1_0::Message::ExtendedBufferData, timestampUs) == 16, "wrong offset");
    static_assert(sizeof(::android::hardware::media::omx::V1_0::Message::ExtendedBufferData) == 24, "wrong size");
    static_assert(__alignof(::android::hardware::media::omx::V1_0::Message::ExtendedBufferData) == 8, "wrong alignment");

    struct RenderData final {
        uint64_t timestampUs __attribute__ ((aligned(8)));
        int64_t systemTimeNs __attribute__ ((aligned(8)));
    };

    static_assert(offsetof(::android::hardware::media::omx::V1_0::Message::RenderData, timestampUs) == 0, "wrong offset");
    static_assert(offsetof(::android::hardware::media::omx::V1_0::Message::RenderData, systemTimeNs) == 8, "wrong offset");
    static_assert(sizeof(::android::hardware::media::omx::V1_0::Message::RenderData) == 16, "wrong size");
    static_assert(__alignof(::android::hardware::media::omx::V1_0::Message::RenderData) == 8, "wrong alignment");

    union Data final {
        ::android::hardware::media::omx::V1_0::Message::EventData eventData __attribute__ ((aligned(4)));
        ::android::hardware::media::omx::V1_0::Message::BufferData bufferData __attribute__ ((aligned(4)));
        ::android::hardware::media::omx::V1_0::Message::ExtendedBufferData extendedBufferData __attribute__ ((aligned(8)));
        ::android::hardware::media::omx::V1_0::Message::RenderData renderData __attribute__ ((aligned(8)));
    };

    static_assert(offsetof(::android::hardware::media::omx::V1_0::Message::Data, eventData) == 0, "wrong offset");
    static_assert(offsetof(::android::hardware::media::omx::V1_0::Message::Data, bufferData) == 0, "wrong offset");
    static_assert(offsetof(::android::hardware::media::omx::V1_0::Message::Data, extendedBufferData) == 0, "wrong offset");
    static_assert(offsetof(::android::hardware::media::omx::V1_0::Message::Data, renderData) == 0, "wrong offset");
    static_assert(sizeof(::android::hardware::media::omx::V1_0::Message::Data) == 24, "wrong size");
    static_assert(__alignof(::android::hardware::media::omx::V1_0::Message::Data) == 8, "wrong alignment");

    ::android::hardware::media::omx::V1_0::Message::Type type __attribute__ ((aligned(4)));
    ::android::hardware::hidl_handle fence __attribute__ ((aligned(8)));
    ::android::hardware::media::omx::V1_0::Message::Data data __attribute__ ((aligned(8)));
};

static_assert(offsetof(::android::hardware::media::omx::V1_0::Message, type) == 0, "wrong offset");
static_assert(offsetof(::android::hardware::media::omx::V1_0::Message, fence) == 8, "wrong offset");
static_assert(offsetof(::android::hardware::media::omx::V1_0::Message, data) == 24, "wrong offset");
static_assert(sizeof(::android::hardware::media::omx::V1_0::Message) == 48, "wrong size");
static_assert(__alignof(::android::hardware::media::omx::V1_0::Message) == 8, "wrong alignment");

/**
 * Ref: frameworks/native/include/ui/GraphicBuffer.h
 * Ref: system/core/include/system/window.h
 * Ref: frameworks/native/include/binder/IMemory.h
 * Ref: frameworks/native/libs/binder/IMemory.cpp
 * Ref: frameworks/av/include/media/OMXBuffer.h
 * 
 * Data structure for buffer information. This is essentially a union of
 * different buffer types.
 */
struct CodecBuffer final {
    // Forward declaration for forward reference support:
    enum class Type : int32_t;
    struct PresetAttributes;
    union Attributes;

    enum class Type : int32_t {
        INVALID = 0,
        PRESET = 1, // (::android::hardware::media::omx::V1_0::CodecBuffer::Type.INVALID implicitly + 1)
        SHARED_MEM = 2, // (::android::hardware::media::omx::V1_0::CodecBuffer::Type.PRESET implicitly + 1)
        ANW_BUFFER = 3, // (::android::hardware::media::omx::V1_0::CodecBuffer::Type.SHARED_MEM implicitly + 1)
        NATIVE_HANDLE = 4, // (::android::hardware::media::omx::V1_0::CodecBuffer::Type.ANW_BUFFER implicitly + 1)
    };

    struct PresetAttributes final {
        uint32_t rangeOffset __attribute__ ((aligned(4)));
        uint32_t rangeLength __attribute__ ((aligned(4)));
    };

    static_assert(offsetof(::android::hardware::media::omx::V1_0::CodecBuffer::PresetAttributes, rangeOffset) == 0, "wrong offset");
    static_assert(offsetof(::android::hardware::media::omx::V1_0::CodecBuffer::PresetAttributes, rangeLength) == 4, "wrong offset");
    static_assert(sizeof(::android::hardware::media::omx::V1_0::CodecBuffer::PresetAttributes) == 8, "wrong size");
    static_assert(__alignof(::android::hardware::media::omx::V1_0::CodecBuffer::PresetAttributes) == 4, "wrong alignment");

    union Attributes final {
        ::android::hardware::media::omx::V1_0::CodecBuffer::PresetAttributes preset __attribute__ ((aligned(4)));
        ::android::hardware::media::V1_0::AnwBufferAttributes anwBuffer __attribute__ ((aligned(8)));
    };

    static_assert(offsetof(::android::hardware::media::omx::V1_0::CodecBuffer::Attributes, preset) == 0, "wrong offset");
    static_assert(offsetof(::android::hardware::media::omx::V1_0::CodecBuffer::Attributes, anwBuffer) == 0, "wrong offset");
    static_assert(sizeof(::android::hardware::media::omx::V1_0::CodecBuffer::Attributes) == 40, "wrong size");
    static_assert(__alignof(::android::hardware::media::omx::V1_0::CodecBuffer::Attributes) == 8, "wrong alignment");

    ::android::hardware::media::omx::V1_0::CodecBuffer::Type type __attribute__ ((aligned(4)));
    ::android::hardware::media::omx::V1_0::CodecBuffer::Attributes attr __attribute__ ((aligned(8)));
    ::android::hardware::hidl_handle nativeHandle __attribute__ ((aligned(8)));
    ::android::hardware::hidl_memory sharedMemory __attribute__ ((aligned(8)));
};

static_assert(offsetof(::android::hardware::media::omx::V1_0::CodecBuffer, type) == 0, "wrong offset");
static_assert(offsetof(::android::hardware::media::omx::V1_0::CodecBuffer, attr) == 8, "wrong offset");
static_assert(offsetof(::android::hardware::media::omx::V1_0::CodecBuffer, nativeHandle) == 48, "wrong offset");
static_assert(offsetof(::android::hardware::media::omx::V1_0::CodecBuffer, sharedMemory) == 64, "wrong offset");
static_assert(sizeof(::android::hardware::media::omx::V1_0::CodecBuffer) == 104, "wrong size");
static_assert(__alignof(::android::hardware::media::omx::V1_0::CodecBuffer) == 8, "wrong alignment");

/**
 * Ref: frameworks/av/include/media/IOMX.h
 * 
 * Enumeration of port modes.
 */
enum class PortMode : int32_t {
    PRESET_START = 0,
    PRESET_BYTE_BUFFER = 1, // (::android::hardware::media::omx::V1_0::PortMode.PRESET_START implicitly + 1)
    PRESET_ANW_BUFFER = 2, // (::android::hardware::media::omx::V1_0::PortMode.PRESET_BYTE_BUFFER implicitly + 1)
    PRESET_SECURE_BUFFER = 3, // (::android::hardware::media::omx::V1_0::PortMode.PRESET_ANW_BUFFER implicitly + 1)
    PRESET_END = 4, // (::android::hardware::media::omx::V1_0::PortMode.PRESET_SECURE_BUFFER implicitly + 1)
    DYNAMIC_START = 100,
    DYNAMIC_ANW_BUFFER = 101, // (::android::hardware::media::omx::V1_0::PortMode.DYNAMIC_START implicitly + 1)
    DYNAMIC_NATIVE_HANDLE = 102, // (::android::hardware::media::omx::V1_0::PortMode.DYNAMIC_ANW_BUFFER implicitly + 1)
    DYNAMIC_END = 103, // (::android::hardware::media::omx::V1_0::PortMode.DYNAMIC_NATIVE_HANDLE implicitly + 1)
};

/**
 * Ref: frameworks/native/include/media/hardware/VideoAPI.h
 * 
 * Framework defined color aspects. These are based mainly on ISO 23001-8 spec. As this standard
 * continues to evolve, new values may be defined in the future. Use OTHER for these future values
 * as well as for values not listed here, as those are not supported by the framework.
 */
struct ColorAspects final {
    // Forward declaration for forward reference support:
    enum class Range : uint32_t;
    enum class Primaries : uint32_t;
    enum class Transfer : uint32_t;
    enum class MatrixCoeffs : uint32_t;

    enum class Range : uint32_t {
        UNSPECIFIED = 0u,
        FULL = 1u, // (::android::hardware::media::omx::V1_0::ColorAspects::Range.UNSPECIFIED implicitly + 1)
        LIMITED = 2u, // (::android::hardware::media::omx::V1_0::ColorAspects::Range.FULL implicitly + 1)
        OTHER = 255u,
    };

    enum class Primaries : uint32_t {
        UNSPECIFIED = 0u,
        BT709_5 = 1u, // (::android::hardware::media::omx::V1_0::ColorAspects::Primaries.UNSPECIFIED implicitly + 1)
        BT470_6M = 2u, // (::android::hardware::media::omx::V1_0::ColorAspects::Primaries.BT709_5 implicitly + 1)
        BT601_6_625 = 3u, // (::android::hardware::media::omx::V1_0::ColorAspects::Primaries.BT470_6M implicitly + 1)
        BT601_6_525 = 4u, // (::android::hardware::media::omx::V1_0::ColorAspects::Primaries.BT601_6_625 implicitly + 1)
        GENERIC_FILM = 5u, // (::android::hardware::media::omx::V1_0::ColorAspects::Primaries.BT601_6_525 implicitly + 1)
        BT2020 = 6u, // (::android::hardware::media::omx::V1_0::ColorAspects::Primaries.GENERIC_FILM implicitly + 1)
        OTHER = 255u,
    };

    enum class Transfer : uint32_t {
        UNSPECIFIED = 0u,
        LINEAR = 1u, // (::android::hardware::media::omx::V1_0::ColorAspects::Transfer.UNSPECIFIED implicitly + 1)
        SRGB = 2u, // (::android::hardware::media::omx::V1_0::ColorAspects::Transfer.LINEAR implicitly + 1)
        SMPTE170M = 3u, // (::android::hardware::media::omx::V1_0::ColorAspects::Transfer.SRGB implicitly + 1)
        GAMMA22 = 4u, // (::android::hardware::media::omx::V1_0::ColorAspects::Transfer.SMPTE170M implicitly + 1)
        GAMMA28 = 5u, // (::android::hardware::media::omx::V1_0::ColorAspects::Transfer.GAMMA22 implicitly + 1)
        ST2084 = 6u, // (::android::hardware::media::omx::V1_0::ColorAspects::Transfer.GAMMA28 implicitly + 1)
        HLG = 7u, // (::android::hardware::media::omx::V1_0::ColorAspects::Transfer.ST2084 implicitly + 1)
        SMPTE240M = 64u,
        XVYCC = 65u, // (::android::hardware::media::omx::V1_0::ColorAspects::Transfer.SMPTE240M implicitly + 1)
        BT1361 = 66u, // (::android::hardware::media::omx::V1_0::ColorAspects::Transfer.XVYCC implicitly + 1)
        ST428 = 67u, // (::android::hardware::media::omx::V1_0::ColorAspects::Transfer.BT1361 implicitly + 1)
        OTHER = 255u,
    };

    enum class MatrixCoeffs : uint32_t {
        UNSPECIFIED = 0u,
        BT709_5 = 1u, // (::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs.UNSPECIFIED implicitly + 1)
        BT470_6M = 2u, // (::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs.BT709_5 implicitly + 1)
        BT601_6 = 3u, // (::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs.BT470_6M implicitly + 1)
        SMPTE240M = 4u, // (::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs.BT601_6 implicitly + 1)
        BT2020 = 5u, // (::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs.SMPTE240M implicitly + 1)
        BT2020CONSTANT = 6u, // (::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs.BT2020 implicitly + 1)
        OTHER = 255u,
    };

    ::android::hardware::media::omx::V1_0::ColorAspects::Range range __attribute__ ((aligned(4)));
    ::android::hardware::media::omx::V1_0::ColorAspects::Primaries primaries __attribute__ ((aligned(4)));
    ::android::hardware::media::omx::V1_0::ColorAspects::Transfer transfer __attribute__ ((aligned(4)));
    ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs matrixCoeffs __attribute__ ((aligned(4)));
};

static_assert(offsetof(::android::hardware::media::omx::V1_0::ColorAspects, range) == 0, "wrong offset");
static_assert(offsetof(::android::hardware::media::omx::V1_0::ColorAspects, primaries) == 4, "wrong offset");
static_assert(offsetof(::android::hardware::media::omx::V1_0::ColorAspects, transfer) == 8, "wrong offset");
static_assert(offsetof(::android::hardware::media::omx::V1_0::ColorAspects, matrixCoeffs) == 12, "wrong offset");
static_assert(sizeof(::android::hardware::media::omx::V1_0::ColorAspects) == 16, "wrong size");
static_assert(__alignof(::android::hardware::media::omx::V1_0::ColorAspects) == 4, "wrong alignment");

constexpr int32_t operator|(const ::android::hardware::media::omx::V1_0::Status lhs, const ::android::hardware::media::omx::V1_0::Status rhs) {
    return static_cast<int32_t>(static_cast<int32_t>(lhs) | static_cast<int32_t>(rhs));
}

constexpr int32_t operator|(const int32_t lhs, const ::android::hardware::media::omx::V1_0::Status rhs) {
    return static_cast<int32_t>(lhs | static_cast<int32_t>(rhs));
}

constexpr int32_t operator|(const ::android::hardware::media::omx::V1_0::Status lhs, const int32_t rhs) {
    return static_cast<int32_t>(static_cast<int32_t>(lhs) | rhs);
}

constexpr int32_t operator&(const ::android::hardware::media::omx::V1_0::Status lhs, const ::android::hardware::media::omx::V1_0::Status rhs) {
    return static_cast<int32_t>(static_cast<int32_t>(lhs) & static_cast<int32_t>(rhs));
}

constexpr int32_t operator&(const int32_t lhs, const ::android::hardware::media::omx::V1_0::Status rhs) {
    return static_cast<int32_t>(lhs & static_cast<int32_t>(rhs));
}

constexpr int32_t operator&(const ::android::hardware::media::omx::V1_0::Status lhs, const int32_t rhs) {
    return static_cast<int32_t>(static_cast<int32_t>(lhs) & rhs);
}

constexpr int32_t &operator|=(int32_t& v, const ::android::hardware::media::omx::V1_0::Status e) {
    v |= static_cast<int32_t>(e);
    return v;
}

constexpr int32_t &operator&=(int32_t& v, const ::android::hardware::media::omx::V1_0::Status e) {
    v &= static_cast<int32_t>(e);
    return v;
}

template<typename>
static inline std::string toString(int32_t o);
template<>
inline std::string toString<::android::hardware::media::omx::V1_0::Status>(int32_t o) {
    using ::android::hardware::details::toHexString;
    std::string os;
    ::android::hardware::hidl_bitfield<::android::hardware::media::omx::V1_0::Status> flipped = 0;
    bool first = true;
    if ((o & ::android::hardware::media::omx::V1_0::Status::OK) == static_cast<int32_t>(::android::hardware::media::omx::V1_0::Status::OK)) {
        os += (first ? "" : " | ");
        os += "OK";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::Status::OK;
    }
    if ((o & ::android::hardware::media::omx::V1_0::Status::NO_ERROR) == static_cast<int32_t>(::android::hardware::media::omx::V1_0::Status::NO_ERROR)) {
        os += (first ? "" : " | ");
        os += "NO_ERROR";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::Status::NO_ERROR;
    }
    if ((o & ::android::hardware::media::omx::V1_0::Status::NAME_NOT_FOUND) == static_cast<int32_t>(::android::hardware::media::omx::V1_0::Status::NAME_NOT_FOUND)) {
        os += (first ? "" : " | ");
        os += "NAME_NOT_FOUND";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::Status::NAME_NOT_FOUND;
    }
    if ((o & ::android::hardware::media::omx::V1_0::Status::WOULD_BLOCK) == static_cast<int32_t>(::android::hardware::media::omx::V1_0::Status::WOULD_BLOCK)) {
        os += (first ? "" : " | ");
        os += "WOULD_BLOCK";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::Status::WOULD_BLOCK;
    }
    if ((o & ::android::hardware::media::omx::V1_0::Status::NO_MEMORY) == static_cast<int32_t>(::android::hardware::media::omx::V1_0::Status::NO_MEMORY)) {
        os += (first ? "" : " | ");
        os += "NO_MEMORY";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::Status::NO_MEMORY;
    }
    if ((o & ::android::hardware::media::omx::V1_0::Status::ALREADY_EXISTS) == static_cast<int32_t>(::android::hardware::media::omx::V1_0::Status::ALREADY_EXISTS)) {
        os += (first ? "" : " | ");
        os += "ALREADY_EXISTS";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::Status::ALREADY_EXISTS;
    }
    if ((o & ::android::hardware::media::omx::V1_0::Status::NO_INIT) == static_cast<int32_t>(::android::hardware::media::omx::V1_0::Status::NO_INIT)) {
        os += (first ? "" : " | ");
        os += "NO_INIT";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::Status::NO_INIT;
    }
    if ((o & ::android::hardware::media::omx::V1_0::Status::BAD_VALUE) == static_cast<int32_t>(::android::hardware::media::omx::V1_0::Status::BAD_VALUE)) {
        os += (first ? "" : " | ");
        os += "BAD_VALUE";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::Status::BAD_VALUE;
    }
    if ((o & ::android::hardware::media::omx::V1_0::Status::DEAD_OBJECT) == static_cast<int32_t>(::android::hardware::media::omx::V1_0::Status::DEAD_OBJECT)) {
        os += (first ? "" : " | ");
        os += "DEAD_OBJECT";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::Status::DEAD_OBJECT;
    }
    if ((o & ::android::hardware::media::omx::V1_0::Status::INVALID_OPERATION) == static_cast<int32_t>(::android::hardware::media::omx::V1_0::Status::INVALID_OPERATION)) {
        os += (first ? "" : " | ");
        os += "INVALID_OPERATION";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::Status::INVALID_OPERATION;
    }
    if ((o & ::android::hardware::media::omx::V1_0::Status::TIMED_OUT) == static_cast<int32_t>(::android::hardware::media::omx::V1_0::Status::TIMED_OUT)) {
        os += (first ? "" : " | ");
        os += "TIMED_OUT";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::Status::TIMED_OUT;
    }
    if ((o & ::android::hardware::media::omx::V1_0::Status::ERROR_UNSUPPORTED) == static_cast<int32_t>(::android::hardware::media::omx::V1_0::Status::ERROR_UNSUPPORTED)) {
        os += (first ? "" : " | ");
        os += "ERROR_UNSUPPORTED";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::Status::ERROR_UNSUPPORTED;
    }
    if ((o & ::android::hardware::media::omx::V1_0::Status::UNKNOWN_ERROR) == static_cast<int32_t>(::android::hardware::media::omx::V1_0::Status::UNKNOWN_ERROR)) {
        os += (first ? "" : " | ");
        os += "UNKNOWN_ERROR";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::Status::UNKNOWN_ERROR;
    }
    if ((o & ::android::hardware::media::omx::V1_0::Status::BUFFER_NEEDS_REALLOCATION) == static_cast<int32_t>(::android::hardware::media::omx::V1_0::Status::BUFFER_NEEDS_REALLOCATION)) {
        os += (first ? "" : " | ");
        os += "BUFFER_NEEDS_REALLOCATION";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::Status::BUFFER_NEEDS_REALLOCATION;
    }
    if ((o & ::android::hardware::media::omx::V1_0::Status::RELEASE_ALL_BUFFERS) == static_cast<int32_t>(::android::hardware::media::omx::V1_0::Status::RELEASE_ALL_BUFFERS)) {
        os += (first ? "" : " | ");
        os += "RELEASE_ALL_BUFFERS";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::Status::RELEASE_ALL_BUFFERS;
    }
    if (o != flipped) {
        os += (first ? "" : " | ");
        os += toHexString(o & (~flipped));
    }os += " (";
    os += toHexString(o);
    os += ")";
    return os;
}

static inline std::string toString(::android::hardware::media::omx::V1_0::Status o) {
    using ::android::hardware::details::toHexString;
    if (o == ::android::hardware::media::omx::V1_0::Status::OK) {
        return "OK";
    }
    if (o == ::android::hardware::media::omx::V1_0::Status::NO_ERROR) {
        return "NO_ERROR";
    }
    if (o == ::android::hardware::media::omx::V1_0::Status::NAME_NOT_FOUND) {
        return "NAME_NOT_FOUND";
    }
    if (o == ::android::hardware::media::omx::V1_0::Status::WOULD_BLOCK) {
        return "WOULD_BLOCK";
    }
    if (o == ::android::hardware::media::omx::V1_0::Status::NO_MEMORY) {
        return "NO_MEMORY";
    }
    if (o == ::android::hardware::media::omx::V1_0::Status::ALREADY_EXISTS) {
        return "ALREADY_EXISTS";
    }
    if (o == ::android::hardware::media::omx::V1_0::Status::NO_INIT) {
        return "NO_INIT";
    }
    if (o == ::android::hardware::media::omx::V1_0::Status::BAD_VALUE) {
        return "BAD_VALUE";
    }
    if (o == ::android::hardware::media::omx::V1_0::Status::DEAD_OBJECT) {
        return "DEAD_OBJECT";
    }
    if (o == ::android::hardware::media::omx::V1_0::Status::INVALID_OPERATION) {
        return "INVALID_OPERATION";
    }
    if (o == ::android::hardware::media::omx::V1_0::Status::TIMED_OUT) {
        return "TIMED_OUT";
    }
    if (o == ::android::hardware::media::omx::V1_0::Status::ERROR_UNSUPPORTED) {
        return "ERROR_UNSUPPORTED";
    }
    if (o == ::android::hardware::media::omx::V1_0::Status::UNKNOWN_ERROR) {
        return "UNKNOWN_ERROR";
    }
    if (o == ::android::hardware::media::omx::V1_0::Status::BUFFER_NEEDS_REALLOCATION) {
        return "BUFFER_NEEDS_REALLOCATION";
    }
    if (o == ::android::hardware::media::omx::V1_0::Status::RELEASE_ALL_BUFFERS) {
        return "RELEASE_ALL_BUFFERS";
    }
    std::string os;
    os += toHexString(static_cast<int32_t>(o));
    return os;
}

constexpr uint32_t operator|(const ::android::hardware::media::omx::V1_0::Message::Type lhs, const ::android::hardware::media::omx::V1_0::Message::Type rhs) {
    return static_cast<uint32_t>(static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs));
}

constexpr uint32_t operator|(const uint32_t lhs, const ::android::hardware::media::omx::V1_0::Message::Type rhs) {
    return static_cast<uint32_t>(lhs | static_cast<uint32_t>(rhs));
}

constexpr uint32_t operator|(const ::android::hardware::media::omx::V1_0::Message::Type lhs, const uint32_t rhs) {
    return static_cast<uint32_t>(static_cast<uint32_t>(lhs) | rhs);
}

constexpr uint32_t operator&(const ::android::hardware::media::omx::V1_0::Message::Type lhs, const ::android::hardware::media::omx::V1_0::Message::Type rhs) {
    return static_cast<uint32_t>(static_cast<uint32_t>(lhs) & static_cast<uint32_t>(rhs));
}

constexpr uint32_t operator&(const uint32_t lhs, const ::android::hardware::media::omx::V1_0::Message::Type rhs) {
    return static_cast<uint32_t>(lhs & static_cast<uint32_t>(rhs));
}

constexpr uint32_t operator&(const ::android::hardware::media::omx::V1_0::Message::Type lhs, const uint32_t rhs) {
    return static_cast<uint32_t>(static_cast<uint32_t>(lhs) & rhs);
}

constexpr uint32_t &operator|=(uint32_t& v, const ::android::hardware::media::omx::V1_0::Message::Type e) {
    v |= static_cast<uint32_t>(e);
    return v;
}

constexpr uint32_t &operator&=(uint32_t& v, const ::android::hardware::media::omx::V1_0::Message::Type e) {
    v &= static_cast<uint32_t>(e);
    return v;
}

template<typename>
static inline std::string toString(uint32_t o);
template<>
inline std::string toString<::android::hardware::media::omx::V1_0::Message::Type>(uint32_t o) {
    using ::android::hardware::details::toHexString;
    std::string os;
    ::android::hardware::hidl_bitfield<::android::hardware::media::omx::V1_0::Message::Type> flipped = 0;
    bool first = true;
    if ((o & ::android::hardware::media::omx::V1_0::Message::Type::EVENT) == static_cast<uint32_t>(::android::hardware::media::omx::V1_0::Message::Type::EVENT)) {
        os += (first ? "" : " | ");
        os += "EVENT";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::Message::Type::EVENT;
    }
    if ((o & ::android::hardware::media::omx::V1_0::Message::Type::EMPTY_BUFFER_DONE) == static_cast<uint32_t>(::android::hardware::media::omx::V1_0::Message::Type::EMPTY_BUFFER_DONE)) {
        os += (first ? "" : " | ");
        os += "EMPTY_BUFFER_DONE";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::Message::Type::EMPTY_BUFFER_DONE;
    }
    if ((o & ::android::hardware::media::omx::V1_0::Message::Type::FILL_BUFFER_DONE) == static_cast<uint32_t>(::android::hardware::media::omx::V1_0::Message::Type::FILL_BUFFER_DONE)) {
        os += (first ? "" : " | ");
        os += "FILL_BUFFER_DONE";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::Message::Type::FILL_BUFFER_DONE;
    }
    if ((o & ::android::hardware::media::omx::V1_0::Message::Type::FRAME_RENDERED) == static_cast<uint32_t>(::android::hardware::media::omx::V1_0::Message::Type::FRAME_RENDERED)) {
        os += (first ? "" : " | ");
        os += "FRAME_RENDERED";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::Message::Type::FRAME_RENDERED;
    }
    if (o != flipped) {
        os += (first ? "" : " | ");
        os += toHexString(o & (~flipped));
    }os += " (";
    os += toHexString(o);
    os += ")";
    return os;
}

static inline std::string toString(::android::hardware::media::omx::V1_0::Message::Type o) {
    using ::android::hardware::details::toHexString;
    if (o == ::android::hardware::media::omx::V1_0::Message::Type::EVENT) {
        return "EVENT";
    }
    if (o == ::android::hardware::media::omx::V1_0::Message::Type::EMPTY_BUFFER_DONE) {
        return "EMPTY_BUFFER_DONE";
    }
    if (o == ::android::hardware::media::omx::V1_0::Message::Type::FILL_BUFFER_DONE) {
        return "FILL_BUFFER_DONE";
    }
    if (o == ::android::hardware::media::omx::V1_0::Message::Type::FRAME_RENDERED) {
        return "FRAME_RENDERED";
    }
    std::string os;
    os += toHexString(static_cast<uint32_t>(o));
    return os;
}

static inline std::string toString(const ::android::hardware::media::omx::V1_0::Message::EventData& o) {
    using ::android::hardware::toString;
    std::string os;
    os += "{";
    os += ".event = ";
    os += ::android::hardware::toString(o.event);
    os += ", .data1 = ";
    os += ::android::hardware::toString(o.data1);
    os += ", .data2 = ";
    os += ::android::hardware::toString(o.data2);
    os += ", .data3 = ";
    os += ::android::hardware::toString(o.data3);
    os += ", .data4 = ";
    os += ::android::hardware::toString(o.data4);
    os += "}"; return os;
}

static inline bool operator==(const ::android::hardware::media::omx::V1_0::Message::EventData& lhs, const ::android::hardware::media::omx::V1_0::Message::EventData& rhs) {
    if (lhs.event != rhs.event) {
        return false;
    }
    if (lhs.data1 != rhs.data1) {
        return false;
    }
    if (lhs.data2 != rhs.data2) {
        return false;
    }
    if (lhs.data3 != rhs.data3) {
        return false;
    }
    if (lhs.data4 != rhs.data4) {
        return false;
    }
    return true;
}

static inline bool operator!=(const ::android::hardware::media::omx::V1_0::Message::EventData& lhs,const ::android::hardware::media::omx::V1_0::Message::EventData& rhs){
    return !(lhs == rhs);
}

static inline std::string toString(const ::android::hardware::media::omx::V1_0::Message::BufferData& o) {
    using ::android::hardware::toString;
    std::string os;
    os += "{";
    os += ".buffer = ";
    os += ::android::hardware::toString(o.buffer);
    os += "}"; return os;
}

static inline bool operator==(const ::android::hardware::media::omx::V1_0::Message::BufferData& lhs, const ::android::hardware::media::omx::V1_0::Message::BufferData& rhs) {
    if (lhs.buffer != rhs.buffer) {
        return false;
    }
    return true;
}

static inline bool operator!=(const ::android::hardware::media::omx::V1_0::Message::BufferData& lhs,const ::android::hardware::media::omx::V1_0::Message::BufferData& rhs){
    return !(lhs == rhs);
}

static inline std::string toString(const ::android::hardware::media::omx::V1_0::Message::ExtendedBufferData& o) {
    using ::android::hardware::toString;
    std::string os;
    os += "{";
    os += ".buffer = ";
    os += ::android::hardware::toString(o.buffer);
    os += ", .rangeOffset = ";
    os += ::android::hardware::toString(o.rangeOffset);
    os += ", .rangeLength = ";
    os += ::android::hardware::toString(o.rangeLength);
    os += ", .flags = ";
    os += ::android::hardware::toString(o.flags);
    os += ", .timestampUs = ";
    os += ::android::hardware::toString(o.timestampUs);
    os += "}"; return os;
}

static inline bool operator==(const ::android::hardware::media::omx::V1_0::Message::ExtendedBufferData& lhs, const ::android::hardware::media::omx::V1_0::Message::ExtendedBufferData& rhs) {
    if (lhs.buffer != rhs.buffer) {
        return false;
    }
    if (lhs.rangeOffset != rhs.rangeOffset) {
        return false;
    }
    if (lhs.rangeLength != rhs.rangeLength) {
        return false;
    }
    if (lhs.flags != rhs.flags) {
        return false;
    }
    if (lhs.timestampUs != rhs.timestampUs) {
        return false;
    }
    return true;
}

static inline bool operator!=(const ::android::hardware::media::omx::V1_0::Message::ExtendedBufferData& lhs,const ::android::hardware::media::omx::V1_0::Message::ExtendedBufferData& rhs){
    return !(lhs == rhs);
}

static inline std::string toString(const ::android::hardware::media::omx::V1_0::Message::RenderData& o) {
    using ::android::hardware::toString;
    std::string os;
    os += "{";
    os += ".timestampUs = ";
    os += ::android::hardware::toString(o.timestampUs);
    os += ", .systemTimeNs = ";
    os += ::android::hardware::toString(o.systemTimeNs);
    os += "}"; return os;
}

static inline bool operator==(const ::android::hardware::media::omx::V1_0::Message::RenderData& lhs, const ::android::hardware::media::omx::V1_0::Message::RenderData& rhs) {
    if (lhs.timestampUs != rhs.timestampUs) {
        return false;
    }
    if (lhs.systemTimeNs != rhs.systemTimeNs) {
        return false;
    }
    return true;
}

static inline bool operator!=(const ::android::hardware::media::omx::V1_0::Message::RenderData& lhs,const ::android::hardware::media::omx::V1_0::Message::RenderData& rhs){
    return !(lhs == rhs);
}

static inline std::string toString(const ::android::hardware::media::omx::V1_0::Message::Data& o) {
    using ::android::hardware::toString;
    std::string os;
    os += "{";
    os += ".eventData = ";
    os += ::android::hardware::media::omx::V1_0::toString(o.eventData);
    os += ", .bufferData = ";
    os += ::android::hardware::media::omx::V1_0::toString(o.bufferData);
    os += ", .extendedBufferData = ";
    os += ::android::hardware::media::omx::V1_0::toString(o.extendedBufferData);
    os += ", .renderData = ";
    os += ::android::hardware::media::omx::V1_0::toString(o.renderData);
    os += "}"; return os;
}

// operator== and operator!= are not generated for Data

static inline std::string toString(const ::android::hardware::media::omx::V1_0::Message& o) {
    using ::android::hardware::toString;
    std::string os;
    os += "{";
    os += ".type = ";
    os += ::android::hardware::media::omx::V1_0::toString(o.type);
    os += ", .fence = ";
    os += ::android::hardware::toString(o.fence);
    os += ", .data = ";
    os += ::android::hardware::media::omx::V1_0::toString(o.data);
    os += "}"; return os;
}

// operator== and operator!= are not generated for Message

constexpr int32_t operator|(const ::android::hardware::media::omx::V1_0::CodecBuffer::Type lhs, const ::android::hardware::media::omx::V1_0::CodecBuffer::Type rhs) {
    return static_cast<int32_t>(static_cast<int32_t>(lhs) | static_cast<int32_t>(rhs));
}

constexpr int32_t operator|(const int32_t lhs, const ::android::hardware::media::omx::V1_0::CodecBuffer::Type rhs) {
    return static_cast<int32_t>(lhs | static_cast<int32_t>(rhs));
}

constexpr int32_t operator|(const ::android::hardware::media::omx::V1_0::CodecBuffer::Type lhs, const int32_t rhs) {
    return static_cast<int32_t>(static_cast<int32_t>(lhs) | rhs);
}

constexpr int32_t operator&(const ::android::hardware::media::omx::V1_0::CodecBuffer::Type lhs, const ::android::hardware::media::omx::V1_0::CodecBuffer::Type rhs) {
    return static_cast<int32_t>(static_cast<int32_t>(lhs) & static_cast<int32_t>(rhs));
}

constexpr int32_t operator&(const int32_t lhs, const ::android::hardware::media::omx::V1_0::CodecBuffer::Type rhs) {
    return static_cast<int32_t>(lhs & static_cast<int32_t>(rhs));
}

constexpr int32_t operator&(const ::android::hardware::media::omx::V1_0::CodecBuffer::Type lhs, const int32_t rhs) {
    return static_cast<int32_t>(static_cast<int32_t>(lhs) & rhs);
}

constexpr int32_t &operator|=(int32_t& v, const ::android::hardware::media::omx::V1_0::CodecBuffer::Type e) {
    v |= static_cast<int32_t>(e);
    return v;
}

constexpr int32_t &operator&=(int32_t& v, const ::android::hardware::media::omx::V1_0::CodecBuffer::Type e) {
    v &= static_cast<int32_t>(e);
    return v;
}

template<typename>
static inline std::string toString(int32_t o);
template<>
inline std::string toString<::android::hardware::media::omx::V1_0::CodecBuffer::Type>(int32_t o) {
    using ::android::hardware::details::toHexString;
    std::string os;
    ::android::hardware::hidl_bitfield<::android::hardware::media::omx::V1_0::CodecBuffer::Type> flipped = 0;
    bool first = true;
    if ((o & ::android::hardware::media::omx::V1_0::CodecBuffer::Type::INVALID) == static_cast<int32_t>(::android::hardware::media::omx::V1_0::CodecBuffer::Type::INVALID)) {
        os += (first ? "" : " | ");
        os += "INVALID";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::CodecBuffer::Type::INVALID;
    }
    if ((o & ::android::hardware::media::omx::V1_0::CodecBuffer::Type::PRESET) == static_cast<int32_t>(::android::hardware::media::omx::V1_0::CodecBuffer::Type::PRESET)) {
        os += (first ? "" : " | ");
        os += "PRESET";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::CodecBuffer::Type::PRESET;
    }
    if ((o & ::android::hardware::media::omx::V1_0::CodecBuffer::Type::SHARED_MEM) == static_cast<int32_t>(::android::hardware::media::omx::V1_0::CodecBuffer::Type::SHARED_MEM)) {
        os += (first ? "" : " | ");
        os += "SHARED_MEM";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::CodecBuffer::Type::SHARED_MEM;
    }
    if ((o & ::android::hardware::media::omx::V1_0::CodecBuffer::Type::ANW_BUFFER) == static_cast<int32_t>(::android::hardware::media::omx::V1_0::CodecBuffer::Type::ANW_BUFFER)) {
        os += (first ? "" : " | ");
        os += "ANW_BUFFER";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::CodecBuffer::Type::ANW_BUFFER;
    }
    if ((o & ::android::hardware::media::omx::V1_0::CodecBuffer::Type::NATIVE_HANDLE) == static_cast<int32_t>(::android::hardware::media::omx::V1_0::CodecBuffer::Type::NATIVE_HANDLE)) {
        os += (first ? "" : " | ");
        os += "NATIVE_HANDLE";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::CodecBuffer::Type::NATIVE_HANDLE;
    }
    if (o != flipped) {
        os += (first ? "" : " | ");
        os += toHexString(o & (~flipped));
    }os += " (";
    os += toHexString(o);
    os += ")";
    return os;
}

static inline std::string toString(::android::hardware::media::omx::V1_0::CodecBuffer::Type o) {
    using ::android::hardware::details::toHexString;
    if (o == ::android::hardware::media::omx::V1_0::CodecBuffer::Type::INVALID) {
        return "INVALID";
    }
    if (o == ::android::hardware::media::omx::V1_0::CodecBuffer::Type::PRESET) {
        return "PRESET";
    }
    if (o == ::android::hardware::media::omx::V1_0::CodecBuffer::Type::SHARED_MEM) {
        return "SHARED_MEM";
    }
    if (o == ::android::hardware::media::omx::V1_0::CodecBuffer::Type::ANW_BUFFER) {
        return "ANW_BUFFER";
    }
    if (o == ::android::hardware::media::omx::V1_0::CodecBuffer::Type::NATIVE_HANDLE) {
        return "NATIVE_HANDLE";
    }
    std::string os;
    os += toHexString(static_cast<int32_t>(o));
    return os;
}

static inline std::string toString(const ::android::hardware::media::omx::V1_0::CodecBuffer::PresetAttributes& o) {
    using ::android::hardware::toString;
    std::string os;
    os += "{";
    os += ".rangeOffset = ";
    os += ::android::hardware::toString(o.rangeOffset);
    os += ", .rangeLength = ";
    os += ::android::hardware::toString(o.rangeLength);
    os += "}"; return os;
}

static inline bool operator==(const ::android::hardware::media::omx::V1_0::CodecBuffer::PresetAttributes& lhs, const ::android::hardware::media::omx::V1_0::CodecBuffer::PresetAttributes& rhs) {
    if (lhs.rangeOffset != rhs.rangeOffset) {
        return false;
    }
    if (lhs.rangeLength != rhs.rangeLength) {
        return false;
    }
    return true;
}

static inline bool operator!=(const ::android::hardware::media::omx::V1_0::CodecBuffer::PresetAttributes& lhs,const ::android::hardware::media::omx::V1_0::CodecBuffer::PresetAttributes& rhs){
    return !(lhs == rhs);
}

static inline std::string toString(const ::android::hardware::media::omx::V1_0::CodecBuffer::Attributes& o) {
    using ::android::hardware::toString;
    std::string os;
    os += "{";
    os += ".preset = ";
    os += ::android::hardware::media::omx::V1_0::toString(o.preset);
    os += ", .anwBuffer = ";
    os += ::android::hardware::media::V1_0::toString(o.anwBuffer);
    os += "}"; return os;
}

// operator== and operator!= are not generated for Attributes

static inline std::string toString(const ::android::hardware::media::omx::V1_0::CodecBuffer& o) {
    using ::android::hardware::toString;
    std::string os;
    os += "{";
    os += ".type = ";
    os += ::android::hardware::media::omx::V1_0::toString(o.type);
    os += ", .attr = ";
    os += ::android::hardware::media::omx::V1_0::toString(o.attr);
    os += ", .nativeHandle = ";
    os += ::android::hardware::toString(o.nativeHandle);
    os += ", .sharedMemory = ";
    os += ::android::hardware::toString(o.sharedMemory);
    os += "}"; return os;
}

// operator== and operator!= are not generated for CodecBuffer

constexpr int32_t operator|(const ::android::hardware::media::omx::V1_0::PortMode lhs, const ::android::hardware::media::omx::V1_0::PortMode rhs) {
    return static_cast<int32_t>(static_cast<int32_t>(lhs) | static_cast<int32_t>(rhs));
}

constexpr int32_t operator|(const int32_t lhs, const ::android::hardware::media::omx::V1_0::PortMode rhs) {
    return static_cast<int32_t>(lhs | static_cast<int32_t>(rhs));
}

constexpr int32_t operator|(const ::android::hardware::media::omx::V1_0::PortMode lhs, const int32_t rhs) {
    return static_cast<int32_t>(static_cast<int32_t>(lhs) | rhs);
}

constexpr int32_t operator&(const ::android::hardware::media::omx::V1_0::PortMode lhs, const ::android::hardware::media::omx::V1_0::PortMode rhs) {
    return static_cast<int32_t>(static_cast<int32_t>(lhs) & static_cast<int32_t>(rhs));
}

constexpr int32_t operator&(const int32_t lhs, const ::android::hardware::media::omx::V1_0::PortMode rhs) {
    return static_cast<int32_t>(lhs & static_cast<int32_t>(rhs));
}

constexpr int32_t operator&(const ::android::hardware::media::omx::V1_0::PortMode lhs, const int32_t rhs) {
    return static_cast<int32_t>(static_cast<int32_t>(lhs) & rhs);
}

constexpr int32_t &operator|=(int32_t& v, const ::android::hardware::media::omx::V1_0::PortMode e) {
    v |= static_cast<int32_t>(e);
    return v;
}

constexpr int32_t &operator&=(int32_t& v, const ::android::hardware::media::omx::V1_0::PortMode e) {
    v &= static_cast<int32_t>(e);
    return v;
}

template<typename>
static inline std::string toString(int32_t o);
template<>
inline std::string toString<::android::hardware::media::omx::V1_0::PortMode>(int32_t o) {
    using ::android::hardware::details::toHexString;
    std::string os;
    ::android::hardware::hidl_bitfield<::android::hardware::media::omx::V1_0::PortMode> flipped = 0;
    bool first = true;
    if ((o & ::android::hardware::media::omx::V1_0::PortMode::PRESET_START) == static_cast<int32_t>(::android::hardware::media::omx::V1_0::PortMode::PRESET_START)) {
        os += (first ? "" : " | ");
        os += "PRESET_START";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::PortMode::PRESET_START;
    }
    if ((o & ::android::hardware::media::omx::V1_0::PortMode::PRESET_BYTE_BUFFER) == static_cast<int32_t>(::android::hardware::media::omx::V1_0::PortMode::PRESET_BYTE_BUFFER)) {
        os += (first ? "" : " | ");
        os += "PRESET_BYTE_BUFFER";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::PortMode::PRESET_BYTE_BUFFER;
    }
    if ((o & ::android::hardware::media::omx::V1_0::PortMode::PRESET_ANW_BUFFER) == static_cast<int32_t>(::android::hardware::media::omx::V1_0::PortMode::PRESET_ANW_BUFFER)) {
        os += (first ? "" : " | ");
        os += "PRESET_ANW_BUFFER";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::PortMode::PRESET_ANW_BUFFER;
    }
    if ((o & ::android::hardware::media::omx::V1_0::PortMode::PRESET_SECURE_BUFFER) == static_cast<int32_t>(::android::hardware::media::omx::V1_0::PortMode::PRESET_SECURE_BUFFER)) {
        os += (first ? "" : " | ");
        os += "PRESET_SECURE_BUFFER";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::PortMode::PRESET_SECURE_BUFFER;
    }
    if ((o & ::android::hardware::media::omx::V1_0::PortMode::PRESET_END) == static_cast<int32_t>(::android::hardware::media::omx::V1_0::PortMode::PRESET_END)) {
        os += (first ? "" : " | ");
        os += "PRESET_END";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::PortMode::PRESET_END;
    }
    if ((o & ::android::hardware::media::omx::V1_0::PortMode::DYNAMIC_START) == static_cast<int32_t>(::android::hardware::media::omx::V1_0::PortMode::DYNAMIC_START)) {
        os += (first ? "" : " | ");
        os += "DYNAMIC_START";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::PortMode::DYNAMIC_START;
    }
    if ((o & ::android::hardware::media::omx::V1_0::PortMode::DYNAMIC_ANW_BUFFER) == static_cast<int32_t>(::android::hardware::media::omx::V1_0::PortMode::DYNAMIC_ANW_BUFFER)) {
        os += (first ? "" : " | ");
        os += "DYNAMIC_ANW_BUFFER";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::PortMode::DYNAMIC_ANW_BUFFER;
    }
    if ((o & ::android::hardware::media::omx::V1_0::PortMode::DYNAMIC_NATIVE_HANDLE) == static_cast<int32_t>(::android::hardware::media::omx::V1_0::PortMode::DYNAMIC_NATIVE_HANDLE)) {
        os += (first ? "" : " | ");
        os += "DYNAMIC_NATIVE_HANDLE";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::PortMode::DYNAMIC_NATIVE_HANDLE;
    }
    if ((o & ::android::hardware::media::omx::V1_0::PortMode::DYNAMIC_END) == static_cast<int32_t>(::android::hardware::media::omx::V1_0::PortMode::DYNAMIC_END)) {
        os += (first ? "" : " | ");
        os += "DYNAMIC_END";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::PortMode::DYNAMIC_END;
    }
    if (o != flipped) {
        os += (first ? "" : " | ");
        os += toHexString(o & (~flipped));
    }os += " (";
    os += toHexString(o);
    os += ")";
    return os;
}

static inline std::string toString(::android::hardware::media::omx::V1_0::PortMode o) {
    using ::android::hardware::details::toHexString;
    if (o == ::android::hardware::media::omx::V1_0::PortMode::PRESET_START) {
        return "PRESET_START";
    }
    if (o == ::android::hardware::media::omx::V1_0::PortMode::PRESET_BYTE_BUFFER) {
        return "PRESET_BYTE_BUFFER";
    }
    if (o == ::android::hardware::media::omx::V1_0::PortMode::PRESET_ANW_BUFFER) {
        return "PRESET_ANW_BUFFER";
    }
    if (o == ::android::hardware::media::omx::V1_0::PortMode::PRESET_SECURE_BUFFER) {
        return "PRESET_SECURE_BUFFER";
    }
    if (o == ::android::hardware::media::omx::V1_0::PortMode::PRESET_END) {
        return "PRESET_END";
    }
    if (o == ::android::hardware::media::omx::V1_0::PortMode::DYNAMIC_START) {
        return "DYNAMIC_START";
    }
    if (o == ::android::hardware::media::omx::V1_0::PortMode::DYNAMIC_ANW_BUFFER) {
        return "DYNAMIC_ANW_BUFFER";
    }
    if (o == ::android::hardware::media::omx::V1_0::PortMode::DYNAMIC_NATIVE_HANDLE) {
        return "DYNAMIC_NATIVE_HANDLE";
    }
    if (o == ::android::hardware::media::omx::V1_0::PortMode::DYNAMIC_END) {
        return "DYNAMIC_END";
    }
    std::string os;
    os += toHexString(static_cast<int32_t>(o));
    return os;
}

constexpr uint32_t operator|(const ::android::hardware::media::omx::V1_0::ColorAspects::Range lhs, const ::android::hardware::media::omx::V1_0::ColorAspects::Range rhs) {
    return static_cast<uint32_t>(static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs));
}

constexpr uint32_t operator|(const uint32_t lhs, const ::android::hardware::media::omx::V1_0::ColorAspects::Range rhs) {
    return static_cast<uint32_t>(lhs | static_cast<uint32_t>(rhs));
}

constexpr uint32_t operator|(const ::android::hardware::media::omx::V1_0::ColorAspects::Range lhs, const uint32_t rhs) {
    return static_cast<uint32_t>(static_cast<uint32_t>(lhs) | rhs);
}

constexpr uint32_t operator&(const ::android::hardware::media::omx::V1_0::ColorAspects::Range lhs, const ::android::hardware::media::omx::V1_0::ColorAspects::Range rhs) {
    return static_cast<uint32_t>(static_cast<uint32_t>(lhs) & static_cast<uint32_t>(rhs));
}

constexpr uint32_t operator&(const uint32_t lhs, const ::android::hardware::media::omx::V1_0::ColorAspects::Range rhs) {
    return static_cast<uint32_t>(lhs & static_cast<uint32_t>(rhs));
}

constexpr uint32_t operator&(const ::android::hardware::media::omx::V1_0::ColorAspects::Range lhs, const uint32_t rhs) {
    return static_cast<uint32_t>(static_cast<uint32_t>(lhs) & rhs);
}

constexpr uint32_t &operator|=(uint32_t& v, const ::android::hardware::media::omx::V1_0::ColorAspects::Range e) {
    v |= static_cast<uint32_t>(e);
    return v;
}

constexpr uint32_t &operator&=(uint32_t& v, const ::android::hardware::media::omx::V1_0::ColorAspects::Range e) {
    v &= static_cast<uint32_t>(e);
    return v;
}

template<typename>
static inline std::string toString(uint32_t o);
template<>
inline std::string toString<::android::hardware::media::omx::V1_0::ColorAspects::Range>(uint32_t o) {
    using ::android::hardware::details::toHexString;
    std::string os;
    ::android::hardware::hidl_bitfield<::android::hardware::media::omx::V1_0::ColorAspects::Range> flipped = 0;
    bool first = true;
    if ((o & ::android::hardware::media::omx::V1_0::ColorAspects::Range::UNSPECIFIED) == static_cast<uint32_t>(::android::hardware::media::omx::V1_0::ColorAspects::Range::UNSPECIFIED)) {
        os += (first ? "" : " | ");
        os += "UNSPECIFIED";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::ColorAspects::Range::UNSPECIFIED;
    }
    if ((o & ::android::hardware::media::omx::V1_0::ColorAspects::Range::FULL) == static_cast<uint32_t>(::android::hardware::media::omx::V1_0::ColorAspects::Range::FULL)) {
        os += (first ? "" : " | ");
        os += "FULL";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::ColorAspects::Range::FULL;
    }
    if ((o & ::android::hardware::media::omx::V1_0::ColorAspects::Range::LIMITED) == static_cast<uint32_t>(::android::hardware::media::omx::V1_0::ColorAspects::Range::LIMITED)) {
        os += (first ? "" : " | ");
        os += "LIMITED";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::ColorAspects::Range::LIMITED;
    }
    if ((o & ::android::hardware::media::omx::V1_0::ColorAspects::Range::OTHER) == static_cast<uint32_t>(::android::hardware::media::omx::V1_0::ColorAspects::Range::OTHER)) {
        os += (first ? "" : " | ");
        os += "OTHER";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::ColorAspects::Range::OTHER;
    }
    if (o != flipped) {
        os += (first ? "" : " | ");
        os += toHexString(o & (~flipped));
    }os += " (";
    os += toHexString(o);
    os += ")";
    return os;
}

static inline std::string toString(::android::hardware::media::omx::V1_0::ColorAspects::Range o) {
    using ::android::hardware::details::toHexString;
    if (o == ::android::hardware::media::omx::V1_0::ColorAspects::Range::UNSPECIFIED) {
        return "UNSPECIFIED";
    }
    if (o == ::android::hardware::media::omx::V1_0::ColorAspects::Range::FULL) {
        return "FULL";
    }
    if (o == ::android::hardware::media::omx::V1_0::ColorAspects::Range::LIMITED) {
        return "LIMITED";
    }
    if (o == ::android::hardware::media::omx::V1_0::ColorAspects::Range::OTHER) {
        return "OTHER";
    }
    std::string os;
    os += toHexString(static_cast<uint32_t>(o));
    return os;
}

constexpr uint32_t operator|(const ::android::hardware::media::omx::V1_0::ColorAspects::Primaries lhs, const ::android::hardware::media::omx::V1_0::ColorAspects::Primaries rhs) {
    return static_cast<uint32_t>(static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs));
}

constexpr uint32_t operator|(const uint32_t lhs, const ::android::hardware::media::omx::V1_0::ColorAspects::Primaries rhs) {
    return static_cast<uint32_t>(lhs | static_cast<uint32_t>(rhs));
}

constexpr uint32_t operator|(const ::android::hardware::media::omx::V1_0::ColorAspects::Primaries lhs, const uint32_t rhs) {
    return static_cast<uint32_t>(static_cast<uint32_t>(lhs) | rhs);
}

constexpr uint32_t operator&(const ::android::hardware::media::omx::V1_0::ColorAspects::Primaries lhs, const ::android::hardware::media::omx::V1_0::ColorAspects::Primaries rhs) {
    return static_cast<uint32_t>(static_cast<uint32_t>(lhs) & static_cast<uint32_t>(rhs));
}

constexpr uint32_t operator&(const uint32_t lhs, const ::android::hardware::media::omx::V1_0::ColorAspects::Primaries rhs) {
    return static_cast<uint32_t>(lhs & static_cast<uint32_t>(rhs));
}

constexpr uint32_t operator&(const ::android::hardware::media::omx::V1_0::ColorAspects::Primaries lhs, const uint32_t rhs) {
    return static_cast<uint32_t>(static_cast<uint32_t>(lhs) & rhs);
}

constexpr uint32_t &operator|=(uint32_t& v, const ::android::hardware::media::omx::V1_0::ColorAspects::Primaries e) {
    v |= static_cast<uint32_t>(e);
    return v;
}

constexpr uint32_t &operator&=(uint32_t& v, const ::android::hardware::media::omx::V1_0::ColorAspects::Primaries e) {
    v &= static_cast<uint32_t>(e);
    return v;
}

template<typename>
static inline std::string toString(uint32_t o);
template<>
inline std::string toString<::android::hardware::media::omx::V1_0::ColorAspects::Primaries>(uint32_t o) {
    using ::android::hardware::details::toHexString;
    std::string os;
    ::android::hardware::hidl_bitfield<::android::hardware::media::omx::V1_0::ColorAspects::Primaries> flipped = 0;
    bool first = true;
    if ((o & ::android::hardware::media::omx::V1_0::ColorAspects::Primaries::UNSPECIFIED) == static_cast<uint32_t>(::android::hardware::media::omx::V1_0::ColorAspects::Primaries::UNSPECIFIED)) {
        os += (first ? "" : " | ");
        os += "UNSPECIFIED";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::ColorAspects::Primaries::UNSPECIFIED;
    }
    if ((o & ::android::hardware::media::omx::V1_0::ColorAspects::Primaries::BT709_5) == static_cast<uint32_t>(::android::hardware::media::omx::V1_0::ColorAspects::Primaries::BT709_5)) {
        os += (first ? "" : " | ");
        os += "BT709_5";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::ColorAspects::Primaries::BT709_5;
    }
    if ((o & ::android::hardware::media::omx::V1_0::ColorAspects::Primaries::BT470_6M) == static_cast<uint32_t>(::android::hardware::media::omx::V1_0::ColorAspects::Primaries::BT470_6M)) {
        os += (first ? "" : " | ");
        os += "BT470_6M";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::ColorAspects::Primaries::BT470_6M;
    }
    if ((o & ::android::hardware::media::omx::V1_0::ColorAspects::Primaries::BT601_6_625) == static_cast<uint32_t>(::android::hardware::media::omx::V1_0::ColorAspects::Primaries::BT601_6_625)) {
        os += (first ? "" : " | ");
        os += "BT601_6_625";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::ColorAspects::Primaries::BT601_6_625;
    }
    if ((o & ::android::hardware::media::omx::V1_0::ColorAspects::Primaries::BT601_6_525) == static_cast<uint32_t>(::android::hardware::media::omx::V1_0::ColorAspects::Primaries::BT601_6_525)) {
        os += (first ? "" : " | ");
        os += "BT601_6_525";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::ColorAspects::Primaries::BT601_6_525;
    }
    if ((o & ::android::hardware::media::omx::V1_0::ColorAspects::Primaries::GENERIC_FILM) == static_cast<uint32_t>(::android::hardware::media::omx::V1_0::ColorAspects::Primaries::GENERIC_FILM)) {
        os += (first ? "" : " | ");
        os += "GENERIC_FILM";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::ColorAspects::Primaries::GENERIC_FILM;
    }
    if ((o & ::android::hardware::media::omx::V1_0::ColorAspects::Primaries::BT2020) == static_cast<uint32_t>(::android::hardware::media::omx::V1_0::ColorAspects::Primaries::BT2020)) {
        os += (first ? "" : " | ");
        os += "BT2020";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::ColorAspects::Primaries::BT2020;
    }
    if ((o & ::android::hardware::media::omx::V1_0::ColorAspects::Primaries::OTHER) == static_cast<uint32_t>(::android::hardware::media::omx::V1_0::ColorAspects::Primaries::OTHER)) {
        os += (first ? "" : " | ");
        os += "OTHER";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::ColorAspects::Primaries::OTHER;
    }
    if (o != flipped) {
        os += (first ? "" : " | ");
        os += toHexString(o & (~flipped));
    }os += " (";
    os += toHexString(o);
    os += ")";
    return os;
}

static inline std::string toString(::android::hardware::media::omx::V1_0::ColorAspects::Primaries o) {
    using ::android::hardware::details::toHexString;
    if (o == ::android::hardware::media::omx::V1_0::ColorAspects::Primaries::UNSPECIFIED) {
        return "UNSPECIFIED";
    }
    if (o == ::android::hardware::media::omx::V1_0::ColorAspects::Primaries::BT709_5) {
        return "BT709_5";
    }
    if (o == ::android::hardware::media::omx::V1_0::ColorAspects::Primaries::BT470_6M) {
        return "BT470_6M";
    }
    if (o == ::android::hardware::media::omx::V1_0::ColorAspects::Primaries::BT601_6_625) {
        return "BT601_6_625";
    }
    if (o == ::android::hardware::media::omx::V1_0::ColorAspects::Primaries::BT601_6_525) {
        return "BT601_6_525";
    }
    if (o == ::android::hardware::media::omx::V1_0::ColorAspects::Primaries::GENERIC_FILM) {
        return "GENERIC_FILM";
    }
    if (o == ::android::hardware::media::omx::V1_0::ColorAspects::Primaries::BT2020) {
        return "BT2020";
    }
    if (o == ::android::hardware::media::omx::V1_0::ColorAspects::Primaries::OTHER) {
        return "OTHER";
    }
    std::string os;
    os += toHexString(static_cast<uint32_t>(o));
    return os;
}

constexpr uint32_t operator|(const ::android::hardware::media::omx::V1_0::ColorAspects::Transfer lhs, const ::android::hardware::media::omx::V1_0::ColorAspects::Transfer rhs) {
    return static_cast<uint32_t>(static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs));
}

constexpr uint32_t operator|(const uint32_t lhs, const ::android::hardware::media::omx::V1_0::ColorAspects::Transfer rhs) {
    return static_cast<uint32_t>(lhs | static_cast<uint32_t>(rhs));
}

constexpr uint32_t operator|(const ::android::hardware::media::omx::V1_0::ColorAspects::Transfer lhs, const uint32_t rhs) {
    return static_cast<uint32_t>(static_cast<uint32_t>(lhs) | rhs);
}

constexpr uint32_t operator&(const ::android::hardware::media::omx::V1_0::ColorAspects::Transfer lhs, const ::android::hardware::media::omx::V1_0::ColorAspects::Transfer rhs) {
    return static_cast<uint32_t>(static_cast<uint32_t>(lhs) & static_cast<uint32_t>(rhs));
}

constexpr uint32_t operator&(const uint32_t lhs, const ::android::hardware::media::omx::V1_0::ColorAspects::Transfer rhs) {
    return static_cast<uint32_t>(lhs & static_cast<uint32_t>(rhs));
}

constexpr uint32_t operator&(const ::android::hardware::media::omx::V1_0::ColorAspects::Transfer lhs, const uint32_t rhs) {
    return static_cast<uint32_t>(static_cast<uint32_t>(lhs) & rhs);
}

constexpr uint32_t &operator|=(uint32_t& v, const ::android::hardware::media::omx::V1_0::ColorAspects::Transfer e) {
    v |= static_cast<uint32_t>(e);
    return v;
}

constexpr uint32_t &operator&=(uint32_t& v, const ::android::hardware::media::omx::V1_0::ColorAspects::Transfer e) {
    v &= static_cast<uint32_t>(e);
    return v;
}

template<typename>
static inline std::string toString(uint32_t o);
template<>
inline std::string toString<::android::hardware::media::omx::V1_0::ColorAspects::Transfer>(uint32_t o) {
    using ::android::hardware::details::toHexString;
    std::string os;
    ::android::hardware::hidl_bitfield<::android::hardware::media::omx::V1_0::ColorAspects::Transfer> flipped = 0;
    bool first = true;
    if ((o & ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::UNSPECIFIED) == static_cast<uint32_t>(::android::hardware::media::omx::V1_0::ColorAspects::Transfer::UNSPECIFIED)) {
        os += (first ? "" : " | ");
        os += "UNSPECIFIED";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::UNSPECIFIED;
    }
    if ((o & ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::LINEAR) == static_cast<uint32_t>(::android::hardware::media::omx::V1_0::ColorAspects::Transfer::LINEAR)) {
        os += (first ? "" : " | ");
        os += "LINEAR";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::LINEAR;
    }
    if ((o & ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::SRGB) == static_cast<uint32_t>(::android::hardware::media::omx::V1_0::ColorAspects::Transfer::SRGB)) {
        os += (first ? "" : " | ");
        os += "SRGB";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::SRGB;
    }
    if ((o & ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::SMPTE170M) == static_cast<uint32_t>(::android::hardware::media::omx::V1_0::ColorAspects::Transfer::SMPTE170M)) {
        os += (first ? "" : " | ");
        os += "SMPTE170M";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::SMPTE170M;
    }
    if ((o & ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::GAMMA22) == static_cast<uint32_t>(::android::hardware::media::omx::V1_0::ColorAspects::Transfer::GAMMA22)) {
        os += (first ? "" : " | ");
        os += "GAMMA22";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::GAMMA22;
    }
    if ((o & ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::GAMMA28) == static_cast<uint32_t>(::android::hardware::media::omx::V1_0::ColorAspects::Transfer::GAMMA28)) {
        os += (first ? "" : " | ");
        os += "GAMMA28";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::GAMMA28;
    }
    if ((o & ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::ST2084) == static_cast<uint32_t>(::android::hardware::media::omx::V1_0::ColorAspects::Transfer::ST2084)) {
        os += (first ? "" : " | ");
        os += "ST2084";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::ST2084;
    }
    if ((o & ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::HLG) == static_cast<uint32_t>(::android::hardware::media::omx::V1_0::ColorAspects::Transfer::HLG)) {
        os += (first ? "" : " | ");
        os += "HLG";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::HLG;
    }
    if ((o & ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::SMPTE240M) == static_cast<uint32_t>(::android::hardware::media::omx::V1_0::ColorAspects::Transfer::SMPTE240M)) {
        os += (first ? "" : " | ");
        os += "SMPTE240M";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::SMPTE240M;
    }
    if ((o & ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::XVYCC) == static_cast<uint32_t>(::android::hardware::media::omx::V1_0::ColorAspects::Transfer::XVYCC)) {
        os += (first ? "" : " | ");
        os += "XVYCC";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::XVYCC;
    }
    if ((o & ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::BT1361) == static_cast<uint32_t>(::android::hardware::media::omx::V1_0::ColorAspects::Transfer::BT1361)) {
        os += (first ? "" : " | ");
        os += "BT1361";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::BT1361;
    }
    if ((o & ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::ST428) == static_cast<uint32_t>(::android::hardware::media::omx::V1_0::ColorAspects::Transfer::ST428)) {
        os += (first ? "" : " | ");
        os += "ST428";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::ST428;
    }
    if ((o & ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::OTHER) == static_cast<uint32_t>(::android::hardware::media::omx::V1_0::ColorAspects::Transfer::OTHER)) {
        os += (first ? "" : " | ");
        os += "OTHER";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::OTHER;
    }
    if (o != flipped) {
        os += (first ? "" : " | ");
        os += toHexString(o & (~flipped));
    }os += " (";
    os += toHexString(o);
    os += ")";
    return os;
}

static inline std::string toString(::android::hardware::media::omx::V1_0::ColorAspects::Transfer o) {
    using ::android::hardware::details::toHexString;
    if (o == ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::UNSPECIFIED) {
        return "UNSPECIFIED";
    }
    if (o == ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::LINEAR) {
        return "LINEAR";
    }
    if (o == ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::SRGB) {
        return "SRGB";
    }
    if (o == ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::SMPTE170M) {
        return "SMPTE170M";
    }
    if (o == ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::GAMMA22) {
        return "GAMMA22";
    }
    if (o == ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::GAMMA28) {
        return "GAMMA28";
    }
    if (o == ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::ST2084) {
        return "ST2084";
    }
    if (o == ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::HLG) {
        return "HLG";
    }
    if (o == ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::SMPTE240M) {
        return "SMPTE240M";
    }
    if (o == ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::XVYCC) {
        return "XVYCC";
    }
    if (o == ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::BT1361) {
        return "BT1361";
    }
    if (o == ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::ST428) {
        return "ST428";
    }
    if (o == ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::OTHER) {
        return "OTHER";
    }
    std::string os;
    os += toHexString(static_cast<uint32_t>(o));
    return os;
}

constexpr uint32_t operator|(const ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs lhs, const ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs rhs) {
    return static_cast<uint32_t>(static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs));
}

constexpr uint32_t operator|(const uint32_t lhs, const ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs rhs) {
    return static_cast<uint32_t>(lhs | static_cast<uint32_t>(rhs));
}

constexpr uint32_t operator|(const ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs lhs, const uint32_t rhs) {
    return static_cast<uint32_t>(static_cast<uint32_t>(lhs) | rhs);
}

constexpr uint32_t operator&(const ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs lhs, const ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs rhs) {
    return static_cast<uint32_t>(static_cast<uint32_t>(lhs) & static_cast<uint32_t>(rhs));
}

constexpr uint32_t operator&(const uint32_t lhs, const ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs rhs) {
    return static_cast<uint32_t>(lhs & static_cast<uint32_t>(rhs));
}

constexpr uint32_t operator&(const ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs lhs, const uint32_t rhs) {
    return static_cast<uint32_t>(static_cast<uint32_t>(lhs) & rhs);
}

constexpr uint32_t &operator|=(uint32_t& v, const ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs e) {
    v |= static_cast<uint32_t>(e);
    return v;
}

constexpr uint32_t &operator&=(uint32_t& v, const ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs e) {
    v &= static_cast<uint32_t>(e);
    return v;
}

template<typename>
static inline std::string toString(uint32_t o);
template<>
inline std::string toString<::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs>(uint32_t o) {
    using ::android::hardware::details::toHexString;
    std::string os;
    ::android::hardware::hidl_bitfield<::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs> flipped = 0;
    bool first = true;
    if ((o & ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs::UNSPECIFIED) == static_cast<uint32_t>(::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs::UNSPECIFIED)) {
        os += (first ? "" : " | ");
        os += "UNSPECIFIED";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs::UNSPECIFIED;
    }
    if ((o & ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs::BT709_5) == static_cast<uint32_t>(::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs::BT709_5)) {
        os += (first ? "" : " | ");
        os += "BT709_5";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs::BT709_5;
    }
    if ((o & ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs::BT470_6M) == static_cast<uint32_t>(::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs::BT470_6M)) {
        os += (first ? "" : " | ");
        os += "BT470_6M";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs::BT470_6M;
    }
    if ((o & ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs::BT601_6) == static_cast<uint32_t>(::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs::BT601_6)) {
        os += (first ? "" : " | ");
        os += "BT601_6";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs::BT601_6;
    }
    if ((o & ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs::SMPTE240M) == static_cast<uint32_t>(::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs::SMPTE240M)) {
        os += (first ? "" : " | ");
        os += "SMPTE240M";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs::SMPTE240M;
    }
    if ((o & ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs::BT2020) == static_cast<uint32_t>(::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs::BT2020)) {
        os += (first ? "" : " | ");
        os += "BT2020";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs::BT2020;
    }
    if ((o & ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs::BT2020CONSTANT) == static_cast<uint32_t>(::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs::BT2020CONSTANT)) {
        os += (first ? "" : " | ");
        os += "BT2020CONSTANT";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs::BT2020CONSTANT;
    }
    if ((o & ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs::OTHER) == static_cast<uint32_t>(::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs::OTHER)) {
        os += (first ? "" : " | ");
        os += "OTHER";
        first = false;
        flipped |= ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs::OTHER;
    }
    if (o != flipped) {
        os += (first ? "" : " | ");
        os += toHexString(o & (~flipped));
    }os += " (";
    os += toHexString(o);
    os += ")";
    return os;
}

static inline std::string toString(::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs o) {
    using ::android::hardware::details::toHexString;
    if (o == ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs::UNSPECIFIED) {
        return "UNSPECIFIED";
    }
    if (o == ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs::BT709_5) {
        return "BT709_5";
    }
    if (o == ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs::BT470_6M) {
        return "BT470_6M";
    }
    if (o == ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs::BT601_6) {
        return "BT601_6";
    }
    if (o == ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs::SMPTE240M) {
        return "SMPTE240M";
    }
    if (o == ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs::BT2020) {
        return "BT2020";
    }
    if (o == ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs::BT2020CONSTANT) {
        return "BT2020CONSTANT";
    }
    if (o == ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs::OTHER) {
        return "OTHER";
    }
    std::string os;
    os += toHexString(static_cast<uint32_t>(o));
    return os;
}

static inline std::string toString(const ::android::hardware::media::omx::V1_0::ColorAspects& o) {
    using ::android::hardware::toString;
    std::string os;
    os += "{";
    os += ".range = ";
    os += ::android::hardware::media::omx::V1_0::toString(o.range);
    os += ", .primaries = ";
    os += ::android::hardware::media::omx::V1_0::toString(o.primaries);
    os += ", .transfer = ";
    os += ::android::hardware::media::omx::V1_0::toString(o.transfer);
    os += ", .matrixCoeffs = ";
    os += ::android::hardware::media::omx::V1_0::toString(o.matrixCoeffs);
    os += "}"; return os;
}

static inline bool operator==(const ::android::hardware::media::omx::V1_0::ColorAspects& lhs, const ::android::hardware::media::omx::V1_0::ColorAspects& rhs) {
    if (lhs.range != rhs.range) {
        return false;
    }
    if (lhs.primaries != rhs.primaries) {
        return false;
    }
    if (lhs.transfer != rhs.transfer) {
        return false;
    }
    if (lhs.matrixCoeffs != rhs.matrixCoeffs) {
        return false;
    }
    return true;
}

static inline bool operator!=(const ::android::hardware::media::omx::V1_0::ColorAspects& lhs,const ::android::hardware::media::omx::V1_0::ColorAspects& rhs){
    return !(lhs == rhs);
}


}  // namespace V1_0
}  // namespace omx
}  // namespace media
}  // namespace hardware
}  // namespace android
namespace android {
namespace hardware {
template<> struct hidl_enum_iterator<::android::hardware::media::omx::V1_0::Status>
{
    const ::android::hardware::media::omx::V1_0::Status* begin() { return static_begin(); }
    const ::android::hardware::media::omx::V1_0::Status* end() { return begin() + 15; }
    private:
    static const ::android::hardware::media::omx::V1_0::Status* static_begin() {
        static const ::android::hardware::media::omx::V1_0::Status kVals[15] {
            ::android::hardware::media::omx::V1_0::Status::OK,
            ::android::hardware::media::omx::V1_0::Status::NO_ERROR,
            ::android::hardware::media::omx::V1_0::Status::NAME_NOT_FOUND,
            ::android::hardware::media::omx::V1_0::Status::WOULD_BLOCK,
            ::android::hardware::media::omx::V1_0::Status::NO_MEMORY,
            ::android::hardware::media::omx::V1_0::Status::ALREADY_EXISTS,
            ::android::hardware::media::omx::V1_0::Status::NO_INIT,
            ::android::hardware::media::omx::V1_0::Status::BAD_VALUE,
            ::android::hardware::media::omx::V1_0::Status::DEAD_OBJECT,
            ::android::hardware::media::omx::V1_0::Status::INVALID_OPERATION,
            ::android::hardware::media::omx::V1_0::Status::TIMED_OUT,
            ::android::hardware::media::omx::V1_0::Status::ERROR_UNSUPPORTED,
            ::android::hardware::media::omx::V1_0::Status::UNKNOWN_ERROR,
            ::android::hardware::media::omx::V1_0::Status::BUFFER_NEEDS_REALLOCATION,
            ::android::hardware::media::omx::V1_0::Status::RELEASE_ALL_BUFFERS,
        };
        return &kVals[0];
    }};

}  // namespace hardware
}  // namespace android
namespace android {
namespace hardware {
template<> struct hidl_enum_iterator<::android::hardware::media::omx::V1_0::Message::Type>
{
    const ::android::hardware::media::omx::V1_0::Message::Type* begin() { return static_begin(); }
    const ::android::hardware::media::omx::V1_0::Message::Type* end() { return begin() + 4; }
    private:
    static const ::android::hardware::media::omx::V1_0::Message::Type* static_begin() {
        static const ::android::hardware::media::omx::V1_0::Message::Type kVals[4] {
            ::android::hardware::media::omx::V1_0::Message::Type::EVENT,
            ::android::hardware::media::omx::V1_0::Message::Type::EMPTY_BUFFER_DONE,
            ::android::hardware::media::omx::V1_0::Message::Type::FILL_BUFFER_DONE,
            ::android::hardware::media::omx::V1_0::Message::Type::FRAME_RENDERED,
        };
        return &kVals[0];
    }};

}  // namespace hardware
}  // namespace android
namespace android {
namespace hardware {
template<> struct hidl_enum_iterator<::android::hardware::media::omx::V1_0::CodecBuffer::Type>
{
    const ::android::hardware::media::omx::V1_0::CodecBuffer::Type* begin() { return static_begin(); }
    const ::android::hardware::media::omx::V1_0::CodecBuffer::Type* end() { return begin() + 5; }
    private:
    static const ::android::hardware::media::omx::V1_0::CodecBuffer::Type* static_begin() {
        static const ::android::hardware::media::omx::V1_0::CodecBuffer::Type kVals[5] {
            ::android::hardware::media::omx::V1_0::CodecBuffer::Type::INVALID,
            ::android::hardware::media::omx::V1_0::CodecBuffer::Type::PRESET,
            ::android::hardware::media::omx::V1_0::CodecBuffer::Type::SHARED_MEM,
            ::android::hardware::media::omx::V1_0::CodecBuffer::Type::ANW_BUFFER,
            ::android::hardware::media::omx::V1_0::CodecBuffer::Type::NATIVE_HANDLE,
        };
        return &kVals[0];
    }};

}  // namespace hardware
}  // namespace android
namespace android {
namespace hardware {
template<> struct hidl_enum_iterator<::android::hardware::media::omx::V1_0::PortMode>
{
    const ::android::hardware::media::omx::V1_0::PortMode* begin() { return static_begin(); }
    const ::android::hardware::media::omx::V1_0::PortMode* end() { return begin() + 9; }
    private:
    static const ::android::hardware::media::omx::V1_0::PortMode* static_begin() {
        static const ::android::hardware::media::omx::V1_0::PortMode kVals[9] {
            ::android::hardware::media::omx::V1_0::PortMode::PRESET_START,
            ::android::hardware::media::omx::V1_0::PortMode::PRESET_BYTE_BUFFER,
            ::android::hardware::media::omx::V1_0::PortMode::PRESET_ANW_BUFFER,
            ::android::hardware::media::omx::V1_0::PortMode::PRESET_SECURE_BUFFER,
            ::android::hardware::media::omx::V1_0::PortMode::PRESET_END,
            ::android::hardware::media::omx::V1_0::PortMode::DYNAMIC_START,
            ::android::hardware::media::omx::V1_0::PortMode::DYNAMIC_ANW_BUFFER,
            ::android::hardware::media::omx::V1_0::PortMode::DYNAMIC_NATIVE_HANDLE,
            ::android::hardware::media::omx::V1_0::PortMode::DYNAMIC_END,
        };
        return &kVals[0];
    }};

}  // namespace hardware
}  // namespace android
namespace android {
namespace hardware {
template<> struct hidl_enum_iterator<::android::hardware::media::omx::V1_0::ColorAspects::Range>
{
    const ::android::hardware::media::omx::V1_0::ColorAspects::Range* begin() { return static_begin(); }
    const ::android::hardware::media::omx::V1_0::ColorAspects::Range* end() { return begin() + 4; }
    private:
    static const ::android::hardware::media::omx::V1_0::ColorAspects::Range* static_begin() {
        static const ::android::hardware::media::omx::V1_0::ColorAspects::Range kVals[4] {
            ::android::hardware::media::omx::V1_0::ColorAspects::Range::UNSPECIFIED,
            ::android::hardware::media::omx::V1_0::ColorAspects::Range::FULL,
            ::android::hardware::media::omx::V1_0::ColorAspects::Range::LIMITED,
            ::android::hardware::media::omx::V1_0::ColorAspects::Range::OTHER,
        };
        return &kVals[0];
    }};

}  // namespace hardware
}  // namespace android
namespace android {
namespace hardware {
template<> struct hidl_enum_iterator<::android::hardware::media::omx::V1_0::ColorAspects::Primaries>
{
    const ::android::hardware::media::omx::V1_0::ColorAspects::Primaries* begin() { return static_begin(); }
    const ::android::hardware::media::omx::V1_0::ColorAspects::Primaries* end() { return begin() + 8; }
    private:
    static const ::android::hardware::media::omx::V1_0::ColorAspects::Primaries* static_begin() {
        static const ::android::hardware::media::omx::V1_0::ColorAspects::Primaries kVals[8] {
            ::android::hardware::media::omx::V1_0::ColorAspects::Primaries::UNSPECIFIED,
            ::android::hardware::media::omx::V1_0::ColorAspects::Primaries::BT709_5,
            ::android::hardware::media::omx::V1_0::ColorAspects::Primaries::BT470_6M,
            ::android::hardware::media::omx::V1_0::ColorAspects::Primaries::BT601_6_625,
            ::android::hardware::media::omx::V1_0::ColorAspects::Primaries::BT601_6_525,
            ::android::hardware::media::omx::V1_0::ColorAspects::Primaries::GENERIC_FILM,
            ::android::hardware::media::omx::V1_0::ColorAspects::Primaries::BT2020,
            ::android::hardware::media::omx::V1_0::ColorAspects::Primaries::OTHER,
        };
        return &kVals[0];
    }};

}  // namespace hardware
}  // namespace android
namespace android {
namespace hardware {
template<> struct hidl_enum_iterator<::android::hardware::media::omx::V1_0::ColorAspects::Transfer>
{
    const ::android::hardware::media::omx::V1_0::ColorAspects::Transfer* begin() { return static_begin(); }
    const ::android::hardware::media::omx::V1_0::ColorAspects::Transfer* end() { return begin() + 13; }
    private:
    static const ::android::hardware::media::omx::V1_0::ColorAspects::Transfer* static_begin() {
        static const ::android::hardware::media::omx::V1_0::ColorAspects::Transfer kVals[13] {
            ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::UNSPECIFIED,
            ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::LINEAR,
            ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::SRGB,
            ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::SMPTE170M,
            ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::GAMMA22,
            ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::GAMMA28,
            ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::ST2084,
            ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::HLG,
            ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::SMPTE240M,
            ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::XVYCC,
            ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::BT1361,
            ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::ST428,
            ::android::hardware::media::omx::V1_0::ColorAspects::Transfer::OTHER,
        };
        return &kVals[0];
    }};

}  // namespace hardware
}  // namespace android
namespace android {
namespace hardware {
template<> struct hidl_enum_iterator<::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs>
{
    const ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs* begin() { return static_begin(); }
    const ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs* end() { return begin() + 8; }
    private:
    static const ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs* static_begin() {
        static const ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs kVals[8] {
            ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs::UNSPECIFIED,
            ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs::BT709_5,
            ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs::BT470_6M,
            ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs::BT601_6,
            ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs::SMPTE240M,
            ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs::BT2020,
            ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs::BT2020CONSTANT,
            ::android::hardware::media::omx::V1_0::ColorAspects::MatrixCoeffs::OTHER,
        };
        return &kVals[0];
    }};

}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_MEDIA_OMX_V1_0_TYPES_H
