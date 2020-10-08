
#if ENABLE_ANGLE

#ifndef HARDWARE_GRAPHICS_COMPOSER_V2_1_ICOMPOSER_ANGLE_H
#define HARDWARE_GRAPHICS_COMPOSER_V2_1_ICOMPOSER_ANGLE_H

// The necessary header files are included in cpp file

// specific header files for platform
#include <cutils/properties.h>
#include <utils/Vector.h>
#include <utils/Mutex.h>
#include "com/NativeWindow.h"

namespace android {
namespace hardware {
namespace graphics {
namespace composer {
namespace V2_1 {

struct ComposerClientAngle : public ComposerClientDefault {
    static const uint64_t PRIMARY_DISPLAY = 0; // only one display
    static const uint32_t PRIMARY_CONFIGS = 1; // only one config
    
    ::android::sp<IComposerCallback> mCallback;
    uint32_t mTargetSlot;
    
    // attributes of config
    int32_t  mAttrWidth;
    int32_t  mAttrHeight;
    int32_t  mAttrVsyncPreiod;
    
    // native window
    char mWindowName[PROPERTY_VALUE_MAX];
    android::Mutex mLockWindow;
    android::Vector< android::sp<android::NativeWindow> > mWindows;

    ComposerClientAngle() :
    mCallback(),
    mTargetSlot(0),
    mAttrWidth(property_get_int32("native.display.width",  400)),
    mAttrHeight(property_get_int32("native.display.height", 300)),
    mAttrVsyncPreiod(1),
    mLockWindow("native window"),
    mWindows()
    {
        property_get("native.display.name", mWindowName, "default");
    }
    
    virtual ::android::hardware::Return<void> registerCallback(const ::android::sp<::android::hardware::graphics::composer::V2_1::IComposerCallback>& callback) override
    {
        mCallback = callback;
        if (mCallback != NULL) {
            // connect the primary display
            mCallback->onHotplug(PRIMARY_DISPLAY, IComposerCallback::Connection::CONNECTED);
        }
        return ::android::hardware::Void();
    };

    virtual ::android::hardware::Return<void> getDisplayType(uint64_t display, getDisplayType_cb _hidl_cb) override
    {
        // just support ONE primary display
        if (display == PRIMARY_DISPLAY) {
            _hidl_cb(Error::NONE, DisplayType::PHYSICAL);
        } else {
            _hidl_cb(Error::BAD_DISPLAY, DisplayType::INVALID);
        }
        return ::android::hardware::Void();
    };

    virtual ::android::hardware::Return<::android::hardware::graphics::composer::V2_1::Error> setClientTargetSlotCount(uint64_t display, uint32_t clientTargetSlotCount) override
    {
        if (display == PRIMARY_DISPLAY) {
            mTargetSlot = clientTargetSlotCount;
            return Error::NONE;
        }
        return Error::UNSUPPORTED;
    };
    
    virtual ::android::hardware::Return<void> getDisplayConfigs(uint64_t display, getDisplayConfigs_cb _hidl_cb) override
    {
        if (display == PRIMARY_DISPLAY) {
            _hidl_cb(Error::NONE, PRIMARY_CONFIGS);
        } else {
            _hidl_cb(Error::BAD_DISPLAY, 0);
        }
        return ::android::hardware::Void();
    };

    virtual ::android::hardware::Return<void> getDisplayAttribute(uint64_t display, uint32_t config, ::android::hardware::graphics::composer::V2_1::IComposerClient::Attribute attribute, getDisplayAttribute_cb _hidl_cb) override
    {
        // paramter check
        if (display != PRIMARY_DISPLAY) {
            _hidl_cb(Error::BAD_DISPLAY, 0);
        } else if  (config >= PRIMARY_CONFIGS) {
            _hidl_cb(Error::BAD_CONFIG, 0);
        }
        
        // return attributes
        else if (attribute == Attribute::WIDTH) {
            _hidl_cb(Error::NONE, mAttrWidth);
            return ::android::hardware::Void();
        } else if (attribute == Attribute::HEIGHT) {
            _hidl_cb(Error::NONE, mAttrHeight);
        } else if (attribute == Attribute::VSYNC_PERIOD) {
            _hidl_cb(Error::NONE, mAttrVsyncPreiod);
        } else {
            _hidl_cb(Error::UNSUPPORTED, 0);
        }
        
        return ::android::hardware::Void();
    };

    virtual ::android::hardware::Return<void> getActiveConfig(uint64_t display, getActiveConfig_cb _hidl_cb) override
    {
        if (display == PRIMARY_DISPLAY) {
            _hidl_cb(Error::NONE, 0);
        } else {
            _hidl_cb(Error::BAD_DISPLAY, 0);
        }
        return ::android::hardware::Void();
    };

    /*
     Use native windows as layer
     */
    virtual ::android::hardware::Return<void> createLayer(uint64_t display, uint32_t bufferSlotCount, createLayer_cb _hidl_cb) override
    {
        android::AutoMutex _l(mLockWindow);
        
        if (display != PRIMARY_DISPLAY) {
            _hidl_cb(Error::BAD_DISPLAY, 0);
            return ::android::hardware::Void();
        }

        android::sp<android::NativeWindow> win = android::CreateNativeWindow();
        LOG_ALWAYS_FATAL_IF((win == NULL), "Failed to create main window %s:%d", __FILE__, __LINE__);
        if (win == NULL) {
            _hidl_cb(Error::NO_RESOURCES, 0);
            return ::android::hardware::Void();
        }
        
        bool check = win->initialize(mWindowName, mAttrWidth, mAttrHeight);
        LOG_ALWAYS_FATAL_IF((check == false), "Failed to intialize native window %s:%d", __FILE__, __LINE__);
        if (check == false) {
            _hidl_cb(Error::NOT_VALIDATED, 0);
            return ::android::hardware::Void();
        }

        bool visible = true;
#if defined(ENABLE_ANDROID_GL)
        // The Android GL will allow surface flinger creating main window,
        // which should be invisible.
        if (mWindows.empty()) {
            visible = false;
        }
#endif
        win->setVisible(visible);
        
        mWindows.add(win);
        
        _hidl_cb(Error::NONE, reinterpret_cast<uint64_t>(win->getNativeWindow()));
        return ::android::hardware::Void();
    };

    virtual ::android::hardware::Return<::android::hardware::graphics::composer::V2_1::Error> destroyLayer(uint64_t display, uint64_t layer) override
    {
        android::AutoMutex _l(mLockWindow);

        if (display != PRIMARY_DISPLAY) {
            return Error::BAD_DISPLAY;
        }
        
        for (int i = 0; i < mWindows.size(); ++i) {
            if (reinterpret_cast<uint64_t>(mWindows[i]->getNativeWindow()) == layer) {
                mWindows.removeAt(i);
                break;
            }
        }

        return Error::NONE;
    };

    virtual ::android::hardware::Return<void> executeCommands(uint32_t inLength, const ::android::hardware::hidl_vec<::android::hardware::hidl_handle>& inHandles, executeCommands_cb _hidl_cb) override
    {
        android::AutoMutex _l(mLockWindow);

        if (mWindows.empty()) {
            _hidl_cb(Error::BAD_LAYER, false, 0, 0);
            return ::android::hardware::Void();
        }
        
        // first one is main window
        android::sp<android::NativeWindow> winMain = mWindows[0];
        if (winMain == NULL) {
            _hidl_cb(Error::NO_RESOURCES, false, 0, 0);
            return ::android::hardware::Void();
        }
        
        // Clear events that the application did not process from this frame
        Event event;
        while (winMain->popEvent(&event)) {
            // If the application did not catch a close event, close now
            if (event.Type == Event::EVENT_CLOSED) {
                _hidl_cb(Error::NOT_VALIDATED, false, 0, 0);
                return ::android::hardware::Void();
            }
        }
        
        winMain->messageLoop();
        
        _hidl_cb(Error::NONE, false, 0, 0);
        return ::android::hardware::Void();
    };

    
}; // ComposerClientAngle

struct ComposerAngle : public ComposerDefault {
    virtual ::android::hardware::Return<void> createClient(createClient_cb _hidl_cb) override {
        _hidl_cb(Error::NONE, new ComposerClientAngle());
        return  ::android::hardware::Void();
    };

}; // ComposerAngle

}  // namespace V2_1
}  // namespace composer
}  // namespace graphics
}  // namespace hardware
}  // namespace android

#endif // HARDWARE_GRAPHICS_COMPOSER_V2_1_ICOMPOSER_ANGLE_H
#endif // ENABLE_ANGLE
