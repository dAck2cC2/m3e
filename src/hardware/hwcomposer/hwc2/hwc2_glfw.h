

#if ENABLE_GLFW

#ifndef HARDWARE_GRAPHICS_COMPOSER_V2_1_ICOMPOSER_GLFW_H
#define HARDWARE_GRAPHICS_COMPOSER_V2_1_ICOMPOSER_GLFW_H

// The necessary header files are included in cpp file

// specific header files for platform
#include <cutils/properties.h>
#include <utils/Vector.h>
#include <utils/Mutex.h>

#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>
#include <glfw/glfw3native.h>

namespace android {
namespace hardware {
namespace graphics {
namespace composer {
namespace V2_1 {

struct ComposerClientGLFW : public ComposerClientDefault {
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
    android::Vector<GLFWwindow*> mWindows;

    ComposerClientGLFW() :
        mCallback(),
        mTargetSlot(0),
        mAttrWidth(property_get_int32("native.display.width",  400)),
        mAttrHeight(property_get_int32("native.display.height", 300)),
        mAttrVsyncPreiod(1),
        mLockWindow("native window"),
        mWindows()
    {
        property_get("native.display.name", mWindowName, "default");
        
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_VISIBLE,    GLFW_FALSE);
        glfwWindowHint(GLFW_RESIZABLE,  GLFW_FALSE);
    }
    
    ~ComposerClientGLFW()
    {
        for (int i = 0; i < mWindows.size(); ++i) {
            if (mWindows[i]) {
                glfwDestroyWindow(mWindows[i]);
            }
        }
        mWindows.clear();
        
        glfwTerminate();
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

       GLFWwindow* win = glfwCreateWindow(mAttrWidth, mAttrHeight, mWindowName, NULL, NULL);
        LOG_ALWAYS_FATAL_IF((win == NULL), "Failed to create window %s:%d", __FILE__, __LINE__);
        if (win == NULL) {
            _hidl_cb(Error::NO_RESOURCES, 0);
            return ::android::hardware::Void();
        }

#if defined(ENABLE_ANDROID_GL)
        // The Android GL will allow surface flinger creating main window,
        // which should be invisible.
        if (mWindows.empty()) {
            glfwHideWindow(win);
        } else
#endif
        {
            glfwShowWindow(win);
        }
        
        mWindows.add(win);
        
#if defined(__APPLE__)
        _hidl_cb(Error::NONE, reinterpret_cast<uint64_t>(glfwGetCocoaLayer(win)));
#elif defined(_MSC_VER)
        _hidl_cb(Error::NONE, reinterpret_cast<uint64_t>(glfwGetWin32Window(win)));
#else
        _hidl_cb(Error::UNSUPPORTED, 0);
#endif

        return ::android::hardware::Void();
    };

    virtual ::android::hardware::Return<::android::hardware::graphics::composer::V2_1::Error> destroyLayer(uint64_t display, uint64_t layer) override
    {
        android::AutoMutex _l(mLockWindow);

        if (display != PRIMARY_DISPLAY) {
            return Error::BAD_DISPLAY;
        }
        
        for (int i = 0; i < mWindows.size(); ++i) {
            if (reinterpret_cast<uint64_t>(
#if defined(__APPLE__)
                    glfwGetCocoaLayer(mWindows[i])
#elif defined(_MSC_VER)
                    glfwGetWin32Window(mWindows[i])
#else
                    0
#endif
                                           ) == layer) {
                glfwDestroyWindow(mWindows[i]);
                mWindows.removeAt(i);
                break;
            }
        }

        return Error::NONE;
    };

    virtual ::android::hardware::Return<void> executeCommands(uint32_t inLength, const ::android::hardware::hidl_vec<::android::hardware::hidl_handle>& inHandles, executeCommands_cb _hidl_cb) override
    {
        glfwPollEvents();
        
        _hidl_cb(Error::NONE, false, 0, 0);
        return ::android::hardware::Void();
    };

    
}; // ComposerClientGLFW

struct ComposerGLFW : public ComposerDefault {
    virtual ::android::hardware::Return<void> createClient(createClient_cb _hidl_cb) override {
        _hidl_cb(Error::NONE, new ComposerClientGLFW());
        return  ::android::hardware::Void();
    };

}; // ComposerGLFW

}  // namespace V2_1
}  // namespace composer
}  // namespace graphics
}  // namespace hardware
}  // namespace android

#endif // HARDWARE_GRAPHICS_COMPOSER_V2_1_ICOMPOSER_GLFW_H
#endif // ENABLE_GLFW
