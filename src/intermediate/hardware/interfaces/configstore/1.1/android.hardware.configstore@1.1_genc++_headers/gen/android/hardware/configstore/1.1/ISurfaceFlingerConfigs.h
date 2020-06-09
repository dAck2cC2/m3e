#ifndef HIDL_GENERATED_ANDROID_HARDWARE_CONFIGSTORE_V1_1_ISURFACEFLINGERCONFIGS_H
#define HIDL_GENERATED_ANDROID_HARDWARE_CONFIGSTORE_V1_1_ISURFACEFLINGERCONFIGS_H

#include <android/hardware/configstore/1.0/ISurfaceFlingerConfigs.h>
#include <android/hardware/configstore/1.1/types.h>

#include <android/hidl/manager/1.0/IServiceNotification.h>

#include <hidl/HidlSupport.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include <utils/NativeHandle.h>
#include <utils/misc.h>

namespace android {
namespace hardware {
namespace configstore {
namespace V1_1 {

struct ISurfaceFlingerConfigs : public ::android::hardware::configstore::V1_0::ISurfaceFlingerConfigs {
    typedef android::hardware::details::i_tag _hidl_tag;

    // Forward declaration for forward reference support:

    /**
     * New revision of ISurfaceFlingerConfigs
     */
    virtual bool isRemote() const override { return false; }


    using vsyncEventPhaseOffsetNs_cb = std::function<void(const ::android::hardware::configstore::V1_0::OptionalInt64& value)>;
    /**
     * The following two methods define (respectively):
     * 
     * - The phase offset between hardware vsync and when apps are woken up by the
     *   Choreographer callback
     * - The phase offset between hardware vsync and when SurfaceFlinger wakes up
     *   to consume input
     * 
     * Their values may be tuned to trade off between display pipeline latency (both
     * overall latency and the lengths of the app --> SF and SF --> display phases)
     * and frame delivery jitter (which typically manifests as "jank" or "jerkiness"
     * while interacting with the device). The default values must produce a
     * relatively low amount of jitter at the expense of roughly two frames of
     * app --> display latency, and unless significant testing is performed to avoid
     * increased display jitter (both manual investigation using systrace [1] and
     * automated testing using dumpsys gfxinfo [2] are recommended), they should not
     * be modified.
     * 
     * [1] https://developer.android.com/studio/profile/systrace.html
     * [2] https://developer.android.com/training/testing/performance.html
     */
    virtual ::android::hardware::Return<void> vsyncEventPhaseOffsetNs(vsyncEventPhaseOffsetNs_cb _hidl_cb) = 0;

    using vsyncSfEventPhaseOffsetNs_cb = std::function<void(const ::android::hardware::configstore::V1_0::OptionalInt64& value)>;
    virtual ::android::hardware::Return<void> vsyncSfEventPhaseOffsetNs(vsyncSfEventPhaseOffsetNs_cb _hidl_cb) = 0;

    using useContextPriority_cb = std::function<void(const ::android::hardware::configstore::V1_0::OptionalBool& value)>;
    /**
     * Instruct the Render Engine to use EGL_IMG_context_priority hint if
     * availabe.
     */
    virtual ::android::hardware::Return<void> useContextPriority(useContextPriority_cb _hidl_cb) = 0;

    using hasWideColorDisplay_cb = std::function<void(const ::android::hardware::configstore::V1_0::OptionalBool& value)>;
    /**
     * hasWideColorDisplay indicates that the device has
     * or can support a wide-color display, e.g. color space
     * greater than sRGB. Typical display may have same
     * color primaries as DCI-P3.
     * Indicate support for this feature by setting
     * TARGET_HAS_WIDE_COLOR_DISPLAY to true in BoardConfig.mk
     * This also means that the device is color managed.
     * A color managed device will use the appropriate
     * display mode depending on the content on the screen.
     * Default is sRGB.
     */
    virtual ::android::hardware::Return<void> hasWideColorDisplay(hasWideColorDisplay_cb _hidl_cb) = 0;

    using hasHDRDisplay_cb = std::function<void(const ::android::hardware::configstore::V1_0::OptionalBool& value)>;
    /**
     * hwHdrDisplay indicates that the device has
     * or can support an HDR (High Dynamic Range) display.
     * Typically an HDR display is also wide-color.
     * Indicate support for this feature by setting
     * TARGET_HAS_HDR_DISPLAY to true in BoardConfig.mk
     */
    virtual ::android::hardware::Return<void> hasHDRDisplay(hasHDRDisplay_cb _hidl_cb) = 0;

    using presentTimeOffsetFromVSyncNs_cb = std::function<void(const ::android::hardware::configstore::V1_0::OptionalInt64& value)>;
    /**
     * Specify the offset in nanoseconds to add to vsync time when timestamping
     * present fences.
     */
    virtual ::android::hardware::Return<void> presentTimeOffsetFromVSyncNs(presentTimeOffsetFromVSyncNs_cb _hidl_cb) = 0;

    using useHwcForRGBtoYUV_cb = std::function<void(const ::android::hardware::configstore::V1_0::OptionalBool& value)>;
    /**
     * Some hardware can do RGB->YUV conversion more efficiently in hardware
     * controlled by HWC than in hardware controlled by the video encoder.
     * This instruct VirtualDisplaySurface to use HWC for such conversion on
     * GL composition.
     */
    virtual ::android::hardware::Return<void> useHwcForRGBtoYUV(useHwcForRGBtoYUV_cb _hidl_cb) = 0;

    using maxVirtualDisplaySize_cb = std::function<void(const ::android::hardware::configstore::V1_0::OptionalUInt64& value)>;
    /**
     *  Maximum dimension supported by HWC for virtual display.
     *  Must be equals to min(max_width, max_height).
     */
    virtual ::android::hardware::Return<void> maxVirtualDisplaySize(maxVirtualDisplaySize_cb _hidl_cb) = 0;

    using hasSyncFramework_cb = std::function<void(const ::android::hardware::configstore::V1_0::OptionalBool& value)>;
    /**
     * Indicates if Sync framework is available. Sync framework provides fence
     * mechanism which significantly reduces buffer processing latency.
     */
    virtual ::android::hardware::Return<void> hasSyncFramework(hasSyncFramework_cb _hidl_cb) = 0;

    using useVrFlinger_cb = std::function<void(const ::android::hardware::configstore::V1_0::OptionalBool& value)>;
    /**
     * Return true if surface flinger should use vr flinger for compatible vr
     * apps, false otherwise. Devices that will never be running vr apps should
     * return false to avoid extra resource usage. Daydream ready devices must
     * return true for full vr support.
     */
    virtual ::android::hardware::Return<void> useVrFlinger(useVrFlinger_cb _hidl_cb) = 0;

    using maxFrameBufferAcquiredBuffers_cb = std::function<void(const ::android::hardware::configstore::V1_0::OptionalInt64& value)>;
    /**
     * Controls the number of buffers SurfaceFlinger will allocate for use in
     * FramebufferSurface.
     */
    virtual ::android::hardware::Return<void> maxFrameBufferAcquiredBuffers(maxFrameBufferAcquiredBuffers_cb _hidl_cb) = 0;

    using startGraphicsAllocatorService_cb = std::function<void(const ::android::hardware::configstore::V1_0::OptionalBool& value)>;
    /**
     * Returns true if surface flinger should start
     * hardware.graphics.allocator@2.0::IAllocator service.
     */
    virtual ::android::hardware::Return<void> startGraphicsAllocatorService(startGraphicsAllocatorService_cb _hidl_cb) = 0;

    using primaryDisplayOrientation_cb = std::function<void(const ::android::hardware::configstore::V1_1::OptionalDisplayOrientation& value)>;
    /**
     * Returns the orientation of the primary display device.
     */
    virtual ::android::hardware::Return<void> primaryDisplayOrientation(primaryDisplayOrientation_cb _hidl_cb) = 0;

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
    static ::android::hardware::Return<::android::sp<::android::hardware::configstore::V1_1::ISurfaceFlingerConfigs>> castFrom(const ::android::sp<::android::hardware::configstore::V1_1::ISurfaceFlingerConfigs>& parent, bool emitError = false);
    static ::android::hardware::Return<::android::sp<::android::hardware::configstore::V1_1::ISurfaceFlingerConfigs>> castFrom(const ::android::sp<::android::hardware::configstore::V1_0::ISurfaceFlingerConfigs>& parent, bool emitError = false);
    static ::android::hardware::Return<::android::sp<::android::hardware::configstore::V1_1::ISurfaceFlingerConfigs>> castFrom(const ::android::sp<::android::hidl::base::V1_0::IBase>& parent, bool emitError = false);

    static const char* descriptor;

    static ::android::sp<ISurfaceFlingerConfigs> tryGetService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<ISurfaceFlingerConfigs> tryGetService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return tryGetService(str, getStub); }
    static ::android::sp<ISurfaceFlingerConfigs> tryGetService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return tryGetService(str, getStub); }
    static ::android::sp<ISurfaceFlingerConfigs> tryGetService(bool getStub) { return tryGetService("default", getStub); }
    static ::android::sp<ISurfaceFlingerConfigs> getService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<ISurfaceFlingerConfigs> getService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return getService(str, getStub); }
    static ::android::sp<ISurfaceFlingerConfigs> getService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return getService(str, getStub); }
    static ::android::sp<ISurfaceFlingerConfigs> getService(bool getStub) { return getService("default", getStub); }
    __attribute__ ((warn_unused_result))::android::status_t registerAsService(const std::string &serviceName="default");
    static bool registerForNotifications(
            const std::string &serviceName,
            const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification> &notification);
};

static inline std::string toString(const ::android::sp<::android::hardware::configstore::V1_1::ISurfaceFlingerConfigs>& o) {
    std::string os = "[class or subclass of ";
    os += ::android::hardware::configstore::V1_1::ISurfaceFlingerConfigs::descriptor;
    os += "]";
    os += o->isRemote() ? "@remote" : "@local";
    return os;
}


}  // namespace V1_1
}  // namespace configstore
}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_CONFIGSTORE_V1_1_ISURFACEFLINGERCONFIGS_H
