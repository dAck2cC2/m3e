
#ifndef ANDROID_SF_CLIENT_H
#define ANDROID_SF_CLIENT_H

#include <stdint.h>
#include <sys/types.h>

#include <utils/Errors.h>
#include <utils/KeyedVector.h>
#include <utils/Mutex.h>

#include <gui/ISurfaceComposerClient.h>

namespace android {

// ---------------------------------------------------------------------------

class Layer;
class SurfaceFlinger;

// ---------------------------------------------------------------------------

class Client : public BnSurfaceComposerClient
{
public:
        Client(const sp<SurfaceFlinger>& flinger);
        ~Client();
    
    status_t initCheck() const;
    
    // protected by SurfaceFlinger::mStateLock
    void attachLayer(const sp<IBinder>& handle, const sp<Layer>& layer);
    
    void detachLayer(const Layer* layer);
    
    sp<Layer> getLayerUser(const sp<IBinder>& handle) const;

private:
    // ISurfaceComposerClient interface
    virtual status_t createSurface(
            const String8& name,
            uint32_t w, uint32_t h,PixelFormat format, uint32_t flags,
            sp<IBinder>* handle,
            sp<IGraphicBufferProducer>* gbp);

    virtual status_t destroySurface(const sp<IBinder>& handle);

    virtual status_t clearLayerFrameStats(const sp<IBinder>& handle) const;

    virtual status_t getLayerFrameStats(const sp<IBinder>& handle, FrameStats* outStats) const;
    virtual status_t getTransformToDisplayInverse(
            const sp<IBinder>& handle, bool* outTransformToDisplayInverse) const;
    
private:
    // constant
    sp<SurfaceFlinger> mFlinger;
    
    // protected by mLock
    DefaultKeyedVector< wp<IBinder>, sp<Layer> > mLayers;
    
    // thread-safe
    mutable Mutex mLock;
};

// ---------------------------------------------------------------------------
}; // namespace android

#endif // ANDROID_SF_CLIENT_H
