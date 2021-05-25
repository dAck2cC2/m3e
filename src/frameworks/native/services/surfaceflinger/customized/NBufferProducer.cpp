
#if defined(ENABLE_ANDROID_GL)

#include "Scheduler/MessageQueue.h"
#include "NBufferProducer.h"
#include "SurfaceFlinger.h"
#include "DisplayHardware/ComposerHal.h"
#include "Layer.h"

#include <system/window.h>

#include <gui/BufferItem.h>

namespace android {
namespace NATIVE {

using namespace hardware::graphics::composer::V2_1;

BufferProducer::BufferProducer(const sp<IGraphicBufferProducer>& producer,
    const sp<SurfaceFlinger>& flinger,
    const wp<android::Layer>& layer) :
    MonitoredProducer(producer, flinger, layer),
    mSF(flinger),
    mNativeLayer(nullptr),
    mEGLNativeWindow(0),
    mFBWidth(0),
    mFBHeight(0)
{
    auto displayId = mSF->getHwComposer().toPhysicalDisplayId(0);
    mNativeLayer = mSF->getHwComposer().createLayer(displayId.value_or(getFallbackDisplayId(0)));
    if (mNativeLayer) {
        mEGLNativeWindow = mNativeLayer->getId();
        
        mSF->getHwComposer().getComposer()->getDisplayAttribute(mEGLNativeWindow, 0, IComposerClient::Attribute::WIDTH, &mFBWidth);
        mSF->getHwComposer().getComposer()->getDisplayAttribute(mEGLNativeWindow, 0, IComposerClient::Attribute::HEIGHT, &mFBHeight);
    }
}

BufferProducer::~BufferProducer() {
    if (mNativeLayer) {
        auto displayId = mSF->getHwComposer().toPhysicalDisplayId(0);
        mSF->getHwComposer().destroyLayer(displayId.value_or(getFallbackDisplayId(0)), mNativeLayer);
        mNativeLayer = nullptr;
        mEGLNativeWindow = 0;
    }
}


int BufferProducer::query(int what, int* value) {
    switch(what) {
        case NATIVE_WINDOW_DEFAULT_WIDTH:
            *value = mFBWidth;
            return 0;
        case NATIVE_WINDOW_DEFAULT_HEIGHT:
            *value = mFBHeight;
            return 0;
        default:
            return MonitoredProducer::query(what, value);
    }
}

status_t BufferProducer::getConsumerUsage(uint64_t* outUsage) const {
    //return mProducer->getConsumerUsage(outUsage);
    if (outUsage) {
        (*outUsage) = mEGLNativeWindow;
    }
    return OK;
}

// ---------------------------------------------------------------------------
}; // namespace NATIVE
}; // namespace android

#endif // ENABLE_ANDROID_GL
