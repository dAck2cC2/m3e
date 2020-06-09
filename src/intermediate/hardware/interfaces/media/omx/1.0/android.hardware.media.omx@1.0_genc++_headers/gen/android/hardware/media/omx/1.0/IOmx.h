#ifndef HIDL_GENERATED_ANDROID_HARDWARE_MEDIA_OMX_V1_0_IOMX_H
#define HIDL_GENERATED_ANDROID_HARDWARE_MEDIA_OMX_V1_0_IOMX_H

#include <android/hardware/graphics/bufferqueue/1.0/IGraphicBufferProducer.h>
#include <android/hardware/media/omx/1.0/IGraphicBufferSource.h>
#include <android/hardware/media/omx/1.0/IOmxNode.h>
#include <android/hardware/media/omx/1.0/IOmxObserver.h>
#include <android/hardware/media/omx/1.0/types.h>
#include <android/hidl/base/1.0/IBase.h>

#include <android/hidl/manager/1.0/IServiceNotification.h>

#include <hidl/HidlSupport.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include <utils/NativeHandle.h>
#include <utils/misc.h>

namespace android {
namespace hardware {
namespace media {
namespace omx {
namespace V1_0 {

struct IOmx : public ::android::hidl::base::V1_0::IBase {
    typedef android::hardware::details::i_tag _hidl_tag;

    // Forward declaration for forward reference support:

    /**
     * Ref: frameworks/av/include/media/IOMX.h: IOMX
     * 
     * IOmx has the ability to create OMX nodes.
     */
    // Forward declaration for forward reference support:
    struct ComponentInfo;

    /**
     * Information for an IOmxNode component.
     */
    struct ComponentInfo final {
        ::android::hardware::hidl_string mName __attribute__ ((aligned(8)));
        ::android::hardware::hidl_vec<::android::hardware::hidl_string> mRoles __attribute__ ((aligned(8)));
    };

    static_assert(offsetof(::android::hardware::media::omx::V1_0::IOmx::ComponentInfo, mName) == 0, "wrong offset");
    static_assert(offsetof(::android::hardware::media::omx::V1_0::IOmx::ComponentInfo, mRoles) == 16, "wrong offset");
    static_assert(sizeof(::android::hardware::media::omx::V1_0::IOmx::ComponentInfo) == 32, "wrong size");
    static_assert(__alignof(::android::hardware::media::omx::V1_0::IOmx::ComponentInfo) == 8, "wrong alignment");

    virtual bool isRemote() const override { return false; }


    using listNodes_cb = std::function<void(::android::hardware::media::omx::V1_0::Status status, const ::android::hardware::hidl_vec<::android::hardware::media::omx::V1_0::IOmx::ComponentInfo>& nodeList)>;
    /**
     * List available components.
     * 
     * @return status The status of the call.
     * @return nodeList The list of ComponentInfo.
     */
    virtual ::android::hardware::Return<void> listNodes(listNodes_cb _hidl_cb) = 0;

    using allocateNode_cb = std::function<void(::android::hardware::media::omx::V1_0::Status status, const ::android::sp<::android::hardware::media::omx::V1_0::IOmxNode>& omxNode)>;
    /**
     * Allocate an IOmxNode instance with the specified node name.
     * 
     * @param name The name of the node to create.
     * @param observer An observer object that will receive messages from
     * the created instance.
     * @return status The status of the call.
     * @return omxNode The allocated instance of `IOmxNode`.
     */
    virtual ::android::hardware::Return<void> allocateNode(const ::android::hardware::hidl_string& name, const ::android::sp<::android::hardware::media::omx::V1_0::IOmxObserver>& observer, allocateNode_cb _hidl_cb) = 0;

    using createInputSurface_cb = std::function<void(::android::hardware::media::omx::V1_0::Status status, const ::android::sp<::android::hardware::graphics::bufferqueue::V1_0::IGraphicBufferProducer>& producer, const ::android::sp<::android::hardware::media::omx::V1_0::IGraphicBufferSource>& source)>;
    /**
     * Create an input surface for recording.
     * 
     * @return status The status of the call.
     * @return producer The associated producer end of the buffer queue.
     * @return source The associated `IGraphicBufferSource`.
     */
    virtual ::android::hardware::Return<void> createInputSurface(createInputSurface_cb _hidl_cb) = 0;

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
    static ::android::hardware::Return<::android::sp<::android::hardware::media::omx::V1_0::IOmx>> castFrom(const ::android::sp<::android::hardware::media::omx::V1_0::IOmx>& parent, bool emitError = false);
    static ::android::hardware::Return<::android::sp<::android::hardware::media::omx::V1_0::IOmx>> castFrom(const ::android::sp<::android::hidl::base::V1_0::IBase>& parent, bool emitError = false);

    static const char* descriptor;

    static ::android::sp<IOmx> tryGetService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IOmx> tryGetService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return tryGetService(str, getStub); }
    static ::android::sp<IOmx> tryGetService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return tryGetService(str, getStub); }
    static ::android::sp<IOmx> tryGetService(bool getStub) { return tryGetService("default", getStub); }
    static ::android::sp<IOmx> getService(const std::string &serviceName="default", bool getStub=false);
    static ::android::sp<IOmx> getService(const char serviceName[], bool getStub=false)  { std::string str(serviceName ? serviceName : "");      return getService(str, getStub); }
    static ::android::sp<IOmx> getService(const ::android::hardware::hidl_string& serviceName, bool getStub=false)  { std::string str(serviceName.c_str());      return getService(str, getStub); }
    static ::android::sp<IOmx> getService(bool getStub) { return getService("default", getStub); }
    __attribute__ ((warn_unused_result))::android::status_t registerAsService(const std::string &serviceName="default");
    static bool registerForNotifications(
            const std::string &serviceName,
            const ::android::sp<::android::hidl::manager::V1_0::IServiceNotification> &notification);
};

static inline std::string toString(const ::android::hardware::media::omx::V1_0::IOmx::ComponentInfo& o) {
    using ::android::hardware::toString;
    std::string os;
    os += "{";
    os += ".mName = ";
    os += ::android::hardware::toString(o.mName);
    os += ", .mRoles = ";
    os += ::android::hardware::toString(o.mRoles);
    os += "}"; return os;
}

static inline bool operator==(const ::android::hardware::media::omx::V1_0::IOmx::ComponentInfo& lhs, const ::android::hardware::media::omx::V1_0::IOmx::ComponentInfo& rhs) {
    if (lhs.mName != rhs.mName) {
        return false;
    }
    if (lhs.mRoles != rhs.mRoles) {
        return false;
    }
    return true;
}

static inline bool operator!=(const ::android::hardware::media::omx::V1_0::IOmx::ComponentInfo& lhs,const ::android::hardware::media::omx::V1_0::IOmx::ComponentInfo& rhs){
    return !(lhs == rhs);
}

static inline std::string toString(const ::android::sp<::android::hardware::media::omx::V1_0::IOmx>& o) {
    std::string os = "[class or subclass of ";
    os += ::android::hardware::media::omx::V1_0::IOmx::descriptor;
    os += "]";
    os += o->isRemote() ? "@remote" : "@local";
    return os;
}


}  // namespace V1_0
}  // namespace omx
}  // namespace media
}  // namespace hardware
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HARDWARE_MEDIA_OMX_V1_0_IOMX_H
