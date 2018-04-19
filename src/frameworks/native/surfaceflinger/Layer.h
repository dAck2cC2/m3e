
#ifndef ANDROID_LAYER_H
#define ANDROID_LAYER_H


#include <utils/RefBase.h>
#include <utils/String8.h>

#include <gui/ISurfaceComposerClient.h>

#include "Client.h"
#include "SurfaceFlinger.h"

#include "RenderEngine/Mesh.h"
#include "RenderEngine/Texture.h"

namespace android {

// ---------------------------------------------------------------------------

class DisplayDevice;
class SurfaceFlinger;

// ---------------------------------------------------------------------------

/*
 * A new BufferQueue and a new SurfaceFlingerConsumer are created when the
 * Layer is first referenced.
 *
 * This also implements onFrameAvailable(), which notifies SurfaceFlinger
 * that new data has arrived.
 */
class Layer : public RefBase {
public:
    // -----------------------------------------------------------------------

    Layer(SurfaceFlinger* flinger, const sp<Client>& client,
            const String8& name, uint32_t w, uint32_t h, uint32_t flags);

    virtual ~Layer();

    // the this layer's size and format
    status_t setBuffers(uint32_t w, uint32_t h, PixelFormat format, uint32_t flags);


    class Handle;
    sp<IBinder> getHandle();
    //sp<IGraphicBufferProducer> getProducer() const;
    const String8& getName() const { return mName; }; 

    // -----------------------------------------------------------------------
    // Virtuals

    virtual const char* getTypeId() const { return "Layer"; }

protected:
    // constant
    sp<SurfaceFlinger> mFlinger;

    virtual void onFirstRef();

private:
    // -----------------------------------------------------------------------
 
     // constants
    uint32_t mTextureName;      // from GLES
    bool mPremultipliedAlpha;
    String8 mName;

    // The texture used to draw the layer in GLES composition mode
    mutable Texture mTexture;

    // protected by mLock
    mutable Mutex mLock;
    // Set to true once we've returned this surface's handle
    mutable bool mHasSurface;
    const wp<Client> mClientRef;
    
    sp<Handle> mHandle;
};

// ---------------------------------------------------------------------------

}; // namespace android

#endif // ANDROID_LAYER_H
