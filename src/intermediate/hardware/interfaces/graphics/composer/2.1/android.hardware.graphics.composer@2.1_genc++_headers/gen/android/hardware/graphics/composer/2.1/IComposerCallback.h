#ifndef HIDL_GENERATED_ANDROID_HARDWARE_GRAPHICS_COMPOSER_V2_1_ICOMPOSERCALLBACK_H
#define HIDL_GENERATED_ANDROID_HARDWARE_GRAPHICS_COMPOSER_V2_1_ICOMPOSERCALLBACK_H

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

struct IComposerCallback : public ::android::hidl::base::V1_0::IBase {
    typedef android::hardware::details::i_tag _hidl_tag;

    // Forward declaration for forward reference support:

    // Forward declaration for forward reference support:
    enum class Connection : int32_t;

    enum class Connection : int32_t {
        INVALID = 0,
        /**
         * The display has been connected  */
        CONNECTED = 1,
        /**
         * The display has been disconnected  */
        DISCONNECTED = 2,
    };

    virtual bool isRemote() const override { return false; }


    // @callflow(next="*")
    /**
     * Notifies the client that the given display has either been connected or
     * disconnected. Every active display (even a built-in physical display)
     * must trigger at least one hotplug notification, even if it only occurs
     * immediately after callback registration.
     * 
     * Displays which have been connected are assumed to be in PowerMode::OFF,
     * and the onVsync callback should not be called for a display until vsync
     * has been enabled with setVsyncEnabled.
     * 
     * The client may call back into the device while the callback is in
     * progress. The device must serialize calls to this callback such that
     * only one thread is calling it at a time.
     * 
     * @param display is the display that triggers the hotplug event.
     * @param connected indicates whether the display is connected or
     *        disconnected.
     */
    virtual ::android::hardware::Return<void> onHotplug(uint64_t display, ::android::hardware::graphics::composer::V2_1::IComposerCallback::Connection connected) = 0;

    // @callflow(next="*")
    /**
     * Notifies the client to trigger a screen refresh. This forces all layer
     * state for this display to be resent, and the display to be validated
     * and presented, even if there have been no changes.
     * 
     * This refresh will occur some time after the callback is initiated, but
     * not necessarily before it returns.  It is safe to trigger this callback
     * from other functions which call into the device.
     * 
     * @param display is the display to refresh.
     */
    virtual ::android::hardware::Return<void> onRefresh(uint64_t display) = 0;

    // @callflow(next="*")
    /**
     * Notifies the client that a vsync event has occurred. This callback must
     * only be triggered when vsync is enabled for this display (through
     * setVsyncEnabled).
     * 
     * @param display is the display which has received a vsync event
     * @param timestamp is the CLOCK_MONOTONIC time at which the vsync event
     *        occurred, in nanoseconds.
     */
    virtual ::android::hardware::Return<void> onVsync(uint64_t display, int64_t timestamp) = 0;

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
    static ::android::hardware::Return<::android::sp<::android::hardware::graphics::composer::V2_1::IComposerCallback>> castFrom(const ::android::sp<::android::hardware::graphics::composer::V2_1::IComposerCallback>& parent, bool emitError = false);
    static ::android::hardware::Return<::android::sp<::android::hardware::graphics::composer::V2_1::IComposerCallback>> castFrom(const ::android::sp<::android::hidl::base::V1_0::IBase>& parent, bool emitError = false);

    static const char* descriptor;

    static ::android::sp<IComposerCallback> tryGetService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IComposerCallback> tryGetService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return tryGetService(str, getStub); }
    static ::android::sp<IComposerCallback> tryGetService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return tryGetService(str, getStub); }
    static ::android::sp<IComposerCallback> tryGetService(bool getStub) { return tryGetService("default", getStub); }
    static ::android::sp<IComposerCallback> getService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IComposerCallback> getService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return getService(str, getStub); }
    static ::android::sp<IComposerCallback> getService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return getService(str, getStub); }
    static ::android::sp<IComposerCallback> getService(bool getStub) { return getService("default", getStub); }
    __attribute__ ((warn_unused_result))::android::status_t registerAsService(const std::string &serviceName="default");
    static bool registerForNotifications(
            const std::string &serviceName,
            const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification> &notification);
};

constexpr int32_t operator|(const ::android::hardware::graphics::composer::V2_1::IComposerCallback::Connection lhs, const ::android::hardware::graphics::composer::V2_1::IComposerCallback::Connection rhs) {
    return static_cast<int32_t>(static_cast<int32_t>(lhs) | static_cast<int32_t>(rhs));
}

constexpr int32_t operator|(const int32_t lhs, const ::android::hardware::graphics::composer::V2_1::IComposerCallback::Connection rhs) {
    return static_cast<int32_t>(lhs | static_cast<int32_t>(rhs));
}

constexpr int32_t operator|(const ::android::hardware::graphics::composer::V2_1::IComposerCallback::Connection lhs, const int32_t rhs) {
    return static_cast<int32_t>(static_cast<int32_t>(lhs) | rhs);
}

constexpr int32_t operator&(const ::android::hardware::graphics::composer::V2_1::IComposerCallback::Connection lhs, const ::android::hardware::graphics::composer::V2_1::IComposerCallback::Connection rhs) {
    return static_cast<int32_t>(static_cast<int32_t>(lhs) & static_cast<int32_t>(rhs));
}

constexpr int32_t operator&(const int32_t lhs, const ::android::hardware::graphics::composer::V2_1::IComposerCallback::Connection rhs) {
    return static_cast<int32_t>(lhs & static_cast<int32_t>(rhs));
}

constexpr int32_t operator&(const ::android::hardware::graphics::composer::V2_1::IComposerCallback::Connection lhs, const int32_t rhs) {
    return static_cast<int32_t>(static_cast<int32_t>(lhs) & rhs);
}

constexpr int32_t &operator|=(int32_t& v, const ::android::hardware::graphics::composer::V2_1::IComposerCallback::Connection e) {
    v |= static_cast<int32_t>(e);
    return v;
}

constexpr int32_t &operator&=(int32_t& v, const ::android::hardware::graphics::composer::V2_1::IComposerCallback::Connection e) {
    v &= static_cast<int32_t>(e);
    return v;
}

template<typename>
static inline std::string toString(int32_t o);
template<>
inline std::string toString<::android::hardware::graphics::composer::V2_1::IComposerCallback::Connection>(int32_t o) {
    using ::android::hardware::details::toHexString;
    std::string os;
    ::android::hardware::hidl_bitfield<::android::hardware::graphics::composer::V2_1::IComposerCallback::Connection> flipped = 0;
    bool first = true;
    if ((o & ::android::hardware::graphics::composer::V2_1::IComposerCallback::Connection::INVALID) == static_cast<int32_t>(::android::hardware::graphics::composer::V2_1::IComposerCallback::Connection::INVALID)) {
        os += (first ? "" : " | ");
        os += "INVALID";
        first = false;
        flipped |= ::android::hardware::graphics::composer::V2_1::IComposerCallback::Connection::INVALID;
    }
    if ((o & ::android::hardware::graphics::composer::V2_1::IComposerCallback::Connection::CONNECTED) == static_cast<int32_t>(::android::hardware::graphics::composer::V2_1::IComposerCallback::Connection::CONNECTED)) {
        os += (first ? "" : " | ");
        os += "CONNECTED";
        first = false;
        flipped |= ::android::hardware::graphics::composer::V2_1::IComposerCallback::Connection::CONNECTED;
    }
    if ((o & ::android::hardware::graphics::composer::V2_1::IComposerCallback::Connection::DISCONNECTED) == static_cast<int32_t>(::android::hardware::graphics::composer::V2_1::IComposerCallback::Connection::DISCONNECTED)) {
        os += (first ? "" : " | ");
        os += "DISCONNECTED";
        first = false;
        flipped |= ::android::hardware::graphics::composer::V2_1::IComposerCallback::Connection::DISCONNECTED;
    }
    if (o != flipped) {
        os += (first ? "" : " | ");
        os += toHexString(o & (~flipped));
    }os += " (";
    os += toHexString(o);
    os += ")";
    return os;
}

static inline std::string toString(::android::hardware::graphics::composer::V2_1::IComposerCallback::Connection o) {
    using ::android::hardware::details::toHexString;
    if (o == ::android::hardware::graphics::composer::V2_1::IComposerCallback::Connection::INVALID) {
        return "INVALID";
    }
    if (o == ::android::hardware::graphics::composer::V2_1::IComposerCallback::Connection::CONNECTED) {
        return "CONNECTED";
    }
    if (o == ::android::hardware::graphics::composer::V2_1::IComposerCallback::Connection::DISCONNECTED) {
        return "DISCONNECTED";
    }
    std::string os;
    os += toHexString(static_cast<int32_t>(o));
    return os;
}

static inline std::string toString(const ::android::sp<::android::hardware::graphics::composer::V2_1::IComposerCallback>& o) {
    std::string os = "[class or subclass of ";
    os += ::android::hardware::graphics::composer::V2_1::IComposerCallback::descriptor;
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
template<> struct hidl_enum_iterator<::android::hardware::graphics::composer::V2_1::IComposerCallback::Connection>
{
    const ::android::hardware::graphics::composer::V2_1::IComposerCallback::Connection* begin() { return static_begin(); }
    const ::android::hardware::graphics::composer::V2_1::IComposerCallback::Connection* end() { return begin() + 3; }
    private:
    static const ::android::hardware::graphics::composer::V2_1::IComposerCallback::Connection* static_begin() {
        static const ::android::hardware::graphics::composer::V2_1::IComposerCallback::Connection kVals[3] {
            ::android::hardware::graphics::composer::V2_1::IComposerCallback::Connection::INVALID,
            ::android::hardware::graphics::composer::V2_1::IComposerCallback::Connection::CONNECTED,
            ::android::hardware::graphics::composer::V2_1::IComposerCallback::Connection::DISCONNECTED,
        };
        return &kVals[0];
    }};

}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_GRAPHICS_COMPOSER_V2_1_ICOMPOSERCALLBACK_H
