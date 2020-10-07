#ifndef HARDWARE_GRAPHICS_COMPOSER_V2_1_ICOMPOSER_DEFAULT_H
#define HARDWARE_GRAPHICS_COMPOSER_V2_1_ICOMPOSER_DEFAULT_H

// The necessary header files are included in cpp file

namespace android {
namespace hardware {
namespace graphics {
namespace composer {
namespace V2_1 {

struct ComposerClientDefault : public IComposerClient {
    virtual ::android::hardware::Return<void> registerCallback(const ::android::sp<::android::hardware::graphics::composer::V2_1::IComposerCallback>& callback) override { /* EMPTY */ return ::android::hardware::Void(); };
    
    virtual ::android::hardware::Return<uint32_t> getMaxVirtualDisplayCount() override { /* EMPTY */ return 0; };

    virtual ::android::hardware::Return<void> createVirtualDisplay(uint32_t width, uint32_t height, ::android::hardware::graphics::common::V1_0::PixelFormat formatHint, uint32_t outputBufferSlotCount, createVirtualDisplay_cb _hidl_cb) override { /* EMPTY */ return ::android::hardware::Void(); };

    virtual ::android::hardware::Return<::android::hardware::graphics::composer::V2_1::Error> destroyVirtualDisplay(uint64_t display) override { /* EMPTY */ return Error::UNSUPPORTED; };

    virtual ::android::hardware::Return<void> createLayer(uint64_t display, uint32_t bufferSlotCount, createLayer_cb _hidl_cb) override { /* EMPTY */ return ::android::hardware::Void(); };
    
    virtual ::android::hardware::Return<::android::hardware::graphics::composer::V2_1::Error> destroyLayer(uint64_t display, uint64_t layer) override { /* EMPTY */ return Error::UNSUPPORTED; };

    virtual ::android::hardware::Return<void> getActiveConfig(uint64_t display, getActiveConfig_cb _hidl_cb) override { /* EMPTY */ return ::android::hardware::Void(); };
    
    virtual ::android::hardware::Return<::android::hardware::graphics::composer::V2_1::Error> getClientTargetSupport(uint64_t display, uint32_t width, uint32_t height, ::android::hardware::graphics::common::V1_0::PixelFormat format, ::android::hardware::graphics::common::V1_0::Dataspace dataspace) override { /* EMPTY */ return Error::UNSUPPORTED; };
    
    virtual ::android::hardware::Return<void> getColorModes(uint64_t display, getColorModes_cb _hidl_cb) override { /* EMPTY */ return ::android::hardware::Void(); };

    virtual ::android::hardware::Return<void> getDisplayAttribute(uint64_t display, uint32_t config, ::android::hardware::graphics::composer::V2_1::IComposerClient::Attribute attribute, getDisplayAttribute_cb _hidl_cb) override { /* EMPTY */ return ::android::hardware::Void(); };

    virtual ::android::hardware::Return<void> getDisplayConfigs(uint64_t display, getDisplayConfigs_cb _hidl_cb) override { /* EMPTY */ return ::android::hardware::Void(); };

    virtual ::android::hardware::Return<void> getDisplayName(uint64_t display, getDisplayName_cb _hidl_cb) override { /* EMPTY */ return ::android::hardware::Void(); };
    
    virtual ::android::hardware::Return<void> getDisplayType(uint64_t display, getDisplayType_cb _hidl_cb) override { /* EMPTY */ return ::android::hardware::Void(); };

    virtual ::android::hardware::Return<void> getDozeSupport(uint64_t display, getDozeSupport_cb _hidl_cb) override { /* EMPTY */ return ::android::hardware::Void(); };

    virtual ::android::hardware::Return<void> getHdrCapabilities(uint64_t display, getHdrCapabilities_cb _hidl_cb) override { /* EMPTY */ return ::android::hardware::Void(); };
    
    virtual ::android::hardware::Return<::android::hardware::graphics::composer::V2_1::Error> setClientTargetSlotCount(uint64_t display, uint32_t clientTargetSlotCount) override { /* EMPTY */ return Error::UNSUPPORTED; };

    virtual ::android::hardware::Return<::android::hardware::graphics::composer::V2_1::Error> setActiveConfig(uint64_t display, uint32_t config) override { /* EMPTY */ return Error::UNSUPPORTED; };

    virtual ::android::hardware::Return<::android::hardware::graphics::composer::V2_1::Error> setColorMode(uint64_t display, ::android::hardware::graphics::common::V1_0::ColorMode mode) override { /* EMPTY */ return Error::UNSUPPORTED; };

    virtual ::android::hardware::Return<::android::hardware::graphics::composer::V2_1::Error> setPowerMode(uint64_t display, ::android::hardware::graphics::composer::V2_1::IComposerClient::PowerMode mode) override { /* EMPTY */ return Error::UNSUPPORTED; };

    virtual ::android::hardware::Return<::android::hardware::graphics::composer::V2_1::Error> setVsyncEnabled(uint64_t display, ::android::hardware::graphics::composer::V2_1::IComposerClient::Vsync enabled) override { /* EMPTY */ return Error::UNSUPPORTED; };

    virtual ::android::hardware::Return<::android::hardware::graphics::composer::V2_1::Error> setInputCommandQueue(const ::android::hardware::MQDescriptorSync<uint32_t>& descriptor) override { /* EMPTY */ return Error::UNSUPPORTED; };

    virtual ::android::hardware::Return<void> getOutputCommandQueue(getOutputCommandQueue_cb _hidl_cb) override { /* EMPTY */ return ::android::hardware::Void(); };
    
    virtual ::android::hardware::Return<void> executeCommands(uint32_t inLength, const ::android::hardware::hidl_vec<::android::hardware::hidl_handle>& inHandles, executeCommands_cb _hidl_cb) override { /* EMPTY */ return ::android::hardware::Void();
    };
    

}; // ComposerClientDefault

struct ComposerDefault : public IComposer {
    virtual ::android::hardware::Return<void> getCapabilities(getCapabilities_cb _hidl_cb) override { /* EMPTY */ return ::android::hardware::Void(); };
    
    virtual ::android::hardware::Return<void> dumpDebugInfo(dumpDebugInfo_cb _hidl_cb) override { /* EMPTY */ return ::android::hardware::Void(); };

}; // ComposerDefault


}  // namespace V2_1
}  // namespace composer
}  // namespace graphics
}  // namespace hardware
}  // namespace android

#endif // HARDWARE_GRAPHICS_COMPOSER_V2_1_ICOMPOSER_DEFAULT_H
