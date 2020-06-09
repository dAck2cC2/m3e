#ifndef HIDL_GENERATED_ANDROID_HARDWARE_GRAPHICS_COMPOSER_V2_1_ICOMPOSER_H
#define HIDL_GENERATED_ANDROID_HARDWARE_GRAPHICS_COMPOSER_V2_1_ICOMPOSER_H

#include <android/hardware/graphics/composer/2.1/IComposerClient.h>
#include <android/hardware/graphics/composer/2.1/types.h>
#include <android/hidl/base/1.0/IBase.h>

#include <android/hidl/manager/1.0/IServiceNotification.h>

#include <hidl/HidlSupport.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include <utils/NativeHandle.h>
#include <utils/misc.h>

namespace android {
namespace hardware {
namespace graphics {
namespace composer {
namespace V2_1 {

struct IComposer : public ::android::hidl::base::V1_0::IBase {
    typedef android::hardware::details::i_tag _hidl_tag;

    // Forward declaration for forward reference support:

    // Forward declaration for forward reference support:
    enum class Capability : int32_t;

    /**
     * Optional capabilities which may be supported by some devices. The
     * particular set of supported capabilities for a given device may be
     * retrieved using getCapabilities.
     */
    enum class Capability : int32_t {
        INVALID = 0,
        /**
         * Specifies that the device supports sideband stream layers, for
         * which buffer content updates and other synchronization will not be
         * provided through the usual validate/present cycle and must be
         * handled by an external implementation-defined mechanism. Only
         * changes to layer state (such as position, size, etc.) need to be
         * performed through the validate/present cycle.
         */
        SIDEBAND_STREAM = 1,
        /**
         * Specifies that the device will apply a color transform even when
         * either the client or the device has chosen that all layers should
         * be composed by the client. This will prevent the client from
         * applying the color transform during its composition step.
         */
        SKIP_CLIENT_COLOR_TRANSFORM = 2,
        /**
         * Specifies that the present fence must not be used as an accurate
         * representation of the actual present time of a frame.
         */
        PRESENT_FENCE_IS_NOT_RELIABLE = 3,
    };

    virtual bool isRemote() const override { return false; }


    using getCapabilities_cb = std::function<void(const ::android::hardware::hidl_vec<::android::hardware::graphics::composer::V2_1::IComposer::Capability>& capabilities)>;
    // @entry @exit @callflow(next="*")
    /**
     * Provides a list of supported capabilities (as described in the
     * definition of Capability above). This list must not change after
     * initialization.
     * 
     * @return capabilities is a list of supported capabilities.
     */
    virtual ::android::hardware::Return<void> getCapabilities(getCapabilities_cb _hidl_cb) = 0;

    using dumpDebugInfo_cb = std::function<void(const ::android::hardware::hidl_string& debugInfo)>;
    // @entry @exit @callflow(next="*")
    /**
     * Retrieves implementation-defined debug information, which will be
     * displayed during, for example, `dumpsys SurfaceFlinger`.
     * 
     * @return debugInfo is a string of debug information.
     */
    virtual ::android::hardware::Return<void> dumpDebugInfo(dumpDebugInfo_cb _hidl_cb) = 0;

    using createClient_cb = std::function<void(::android::hardware::graphics::composer::V2_1::Error error, const ::android::sp<::android::hardware::graphics::composer::V2_1::IComposerClient>& client)>;
    // @entry @callflow(next="*")
    /**
     * Creates a client of the composer. All resources created by the client
     * are owned by the client and are only visible to the client.
     * 
     * There can only be one client at any time.
     * 
     * @return error is NONE upon success. Otherwise,
     *         NO_RESOURCES when no more client can be created currently.
     * @return client is the newly created client.
     */
    virtual ::android::hardware::Return<void> createClient(createClient_cb _hidl_cb) = 0;

    using interfaceChain_cb = std::function<void(const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& descriptors)>;
    virtual ::android::hardware::Return<void> interfaceChain(interfaceChain_cb _hidl_cb) override;

    virtual ::android::hardware::Return<void> debug(const ::android::hardware::hidl_handle& fd, const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& options) override;

    using interfaceDescriptor_cb = std::function<void(const ::android::hardware::hidl_string& descriptor)>;
    virtual ::android::hardware::Return<void> interfaceDescriptor(interfaceDescriptor_cb _hidl_cb) override;

    using getHashChain_cb = std::function<void(const ::android::hardware::hidl_vec<::android::hardware::hidl_array<uint8_t, 32>>& hashchain)>;
    virtual ::android::hardware::Return<void> getHashChain(getHashChain_cb _hidl_cb) override;

    virtual ::android::hardware::Return<void> setHALInstrumentation() override;

    virtual ::android::hardware::Return<bool> linkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient, uint64_t cookie) override;

    virtual ::android::hardware::Return<void> ping() override;

    using getDebugInfo_cb = std::function<void(const ::android::hidl::base::V1_0::DebugInfo& info)>;
    virtual ::android::hardware::Return<void> getDebugInfo(getDebugInfo_cb _hidl_cb) override;

    virtual ::android::hardware::Return<void> notifySyspropsChanged() override;

    virtual ::android::hardware::Return<bool> unlinkToDeath(const ::android::sp<::android::hardware::hidl_death_recipient>& recipient) override;
    // cast static functions
    static ::android::hardware::Return<::android::sp<::android::hardware::graphics::composer::V2_1::IComposer>> castFrom(const ::android::sp<::android::hardware::graphics::composer::V2_1::IComposer>& parent, bool emitError = false);
    static ::android::hardware::Return<::android::sp<::android::hardware::graphics::composer::V2_1::IComposer>> castFrom(const ::android::sp<::android::hidl::base::V1_0::IBase>& parent, bool emitError = false);

    static const char* descriptor;

    static ::android::sp<IComposer> tryGetService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IComposer> tryGetService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return tryGetService(str, getStub); }
    static ::android::sp<IComposer> tryGetService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return tryGetService(str, getStub); }
    static ::android::sp<IComposer> tryGetService(bool getStub) { return tryGetService("default", getStub); }
    static ::android::sp<IComposer> getService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IComposer> getService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return getService(str, getStub); }
    static ::android::sp<IComposer> getService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return getService(str, getStub); }
    static ::android::sp<IComposer> getService(bool getStub) { return getService("default", getStub); }
    __attribute__ ((warn_unused_result))::android::status_t registerAsService(const std::string &serviceName="default");
    static bool registerForNotifications(
            const std::string &serviceName,
            const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification> &notification);
};

constexpr int32_t operator|(const ::android::hardware::graphics::composer::V2_1::IComposer::Capability lhs, const ::android::hardware::graphics::composer::V2_1::IComposer::Capability rhs) {
    return static_cast<int32_t>(static_cast<int32_t>(lhs) | static_cast<int32_t>(rhs));
}

constexpr int32_t operator|(const int32_t lhs, const ::android::hardware::graphics::composer::V2_1::IComposer::Capability rhs) {
    return static_cast<int32_t>(lhs | static_cast<int32_t>(rhs));
}

constexpr int32_t operator|(const ::android::hardware::graphics::composer::V2_1::IComposer::Capability lhs, const int32_t rhs) {
    return static_cast<int32_t>(static_cast<int32_t>(lhs) | rhs);
}

constexpr int32_t operator&(const ::android::hardware::graphics::composer::V2_1::IComposer::Capability lhs, const ::android::hardware::graphics::composer::V2_1::IComposer::Capability rhs) {
    return static_cast<int32_t>(static_cast<int32_t>(lhs) & static_cast<int32_t>(rhs));
}

constexpr int32_t operator&(const int32_t lhs, const ::android::hardware::graphics::composer::V2_1::IComposer::Capability rhs) {
    return static_cast<int32_t>(lhs & static_cast<int32_t>(rhs));
}

constexpr int32_t operator&(const ::android::hardware::graphics::composer::V2_1::IComposer::Capability lhs, const int32_t rhs) {
    return static_cast<int32_t>(static_cast<int32_t>(lhs) & rhs);
}

constexpr int32_t &operator|=(int32_t& v, const ::android::hardware::graphics::composer::V2_1::IComposer::Capability e) {
    v |= static_cast<int32_t>(e);
    return v;
}

constexpr int32_t &operator&=(int32_t& v, const ::android::hardware::graphics::composer::V2_1::IComposer::Capability e) {
    v &= static_cast<int32_t>(e);
    return v;
}

template<typename>
static inline std::string toString(int32_t o);
template<>
inline std::string toString<::android::hardware::graphics::composer::V2_1::IComposer::Capability>(int32_t o) {
    using ::android::hardware::details::toHexString;
    std::string os;
    ::android::hardware::hidl_bitfield<::android::hardware::graphics::composer::V2_1::IComposer::Capability> flipped = 0;
    bool first = true;
    if ((o & ::android::hardware::graphics::composer::V2_1::IComposer::Capability::INVALID) == static_cast<int32_t>(::android::hardware::graphics::composer::V2_1::IComposer::Capability::INVALID)) {
        os += (first ? "" : " | ");
        os += "INVALID";
        first = false;
        flipped |= ::android::hardware::graphics::composer::V2_1::IComposer::Capability::INVALID;
    }
    if ((o & ::android::hardware::graphics::composer::V2_1::IComposer::Capability::SIDEBAND_STREAM) == static_cast<int32_t>(::android::hardware::graphics::composer::V2_1::IComposer::Capability::SIDEBAND_STREAM)) {
        os += (first ? "" : " | ");
        os += "SIDEBAND_STREAM";
        first = false;
        flipped |= ::android::hardware::graphics::composer::V2_1::IComposer::Capability::SIDEBAND_STREAM;
    }
    if ((o & ::android::hardware::graphics::composer::V2_1::IComposer::Capability::SKIP_CLIENT_COLOR_TRANSFORM) == static_cast<int32_t>(::android::hardware::graphics::composer::V2_1::IComposer::Capability::SKIP_CLIENT_COLOR_TRANSFORM)) {
        os += (first ? "" : " | ");
        os += "SKIP_CLIENT_COLOR_TRANSFORM";
        first = false;
        flipped |= ::android::hardware::graphics::composer::V2_1::IComposer::Capability::SKIP_CLIENT_COLOR_TRANSFORM;
    }
    if ((o & ::android::hardware::graphics::composer::V2_1::IComposer::Capability::PRESENT_FENCE_IS_NOT_RELIABLE) == static_cast<int32_t>(::android::hardware::graphics::composer::V2_1::IComposer::Capability::PRESENT_FENCE_IS_NOT_RELIABLE)) {
        os += (first ? "" : " | ");
        os += "PRESENT_FENCE_IS_NOT_RELIABLE";
        first = false;
        flipped |= ::android::hardware::graphics::composer::V2_1::IComposer::Capability::PRESENT_FENCE_IS_NOT_RELIABLE;
    }
    if (o != flipped) {
        os += (first ? "" : " | ");
        os += toHexString(o & (~flipped));
    }os += " (";
    os += toHexString(o);
    os += ")";
    return os;
}

static inline std::string toString(::android::hardware::graphics::composer::V2_1::IComposer::Capability o) {
    using ::android::hardware::details::toHexString;
    if (o == ::android::hardware::graphics::composer::V2_1::IComposer::Capability::INVALID) {
        return "INVALID";
    }
    if (o == ::android::hardware::graphics::composer::V2_1::IComposer::Capability::SIDEBAND_STREAM) {
        return "SIDEBAND_STREAM";
    }
    if (o == ::android::hardware::graphics::composer::V2_1::IComposer::Capability::SKIP_CLIENT_COLOR_TRANSFORM) {
        return "SKIP_CLIENT_COLOR_TRANSFORM";
    }
    if (o == ::android::hardware::graphics::composer::V2_1::IComposer::Capability::PRESENT_FENCE_IS_NOT_RELIABLE) {
        return "PRESENT_FENCE_IS_NOT_RELIABLE";
    }
    std::string os;
    os += toHexString(static_cast<int32_t>(o));
    return os;
}

static inline std::string toString(const ::android::sp<::android::hardware::graphics::composer::V2_1::IComposer>& o) {
    std::string os = "[class or subclass of ";
    os += ::android::hardware::graphics::composer::V2_1::IComposer::descriptor;
    os += "]";
    os += o->isRemote() ? "@remote" : "@local";
    return os;
}


}  // namespace V2_1
}  // namespace composer
}  // namespace graphics
}  // namespace hardware
}  // namespace android
namespace android {
namespace hardware {
template<> struct hidl_enum_iterator<::android::hardware::graphics::composer::V2_1::IComposer::Capability>
{
    const ::android::hardware::graphics::composer::V2_1::IComposer::Capability* begin() { return static_begin(); }
    const ::android::hardware::graphics::composer::V2_1::IComposer::Capability* end() { return begin() + 4; }
    private:
    static const ::android::hardware::graphics::composer::V2_1::IComposer::Capability* static_begin() {
        static const ::android::hardware::graphics::composer::V2_1::IComposer::Capability kVals[4] {
            ::android::hardware::graphics::composer::V2_1::IComposer::Capability::INVALID,
            ::android::hardware::graphics::composer::V2_1::IComposer::Capability::SIDEBAND_STREAM,
            ::android::hardware::graphics::composer::V2_1::IComposer::Capability::SKIP_CLIENT_COLOR_TRANSFORM,
            ::android::hardware::graphics::composer::V2_1::IComposer::Capability::PRESENT_FENCE_IS_NOT_RELIABLE,
        };
        return &kVals[0];
    }};

}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_GRAPHICS_COMPOSER_V2_1_ICOMPOSER_H
