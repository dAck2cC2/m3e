
//#define LOG_NDEBUG 0
#undef LOG_TAG
#define LOG_TAG "Layer"
#define ATRACE_TAG ATRACE_TAG_GRAPHICS

#include <OSWindow.h>

#include <utils/RefBase.h>
#include <binder/Binder.h>
#include <gui/ISurfaceHandle.h>
#include <gui/IGraphicBufferProducer.h>
#include <private/gui/LayerState.h>

#include "Layer.h"
#include "SurfaceFlinger.h"
#include "RenderEngine/RenderEngine.h"

namespace android {

Layer::Layer(SurfaceFlinger* flinger, const sp<Client>& client,
        const String8& name, uint32_t w, uint32_t h, uint32_t flags)
:   mFlinger(flinger),
    mTextureName(-1U),
    mPremultipliedAlpha(true),
    mName("unnamed"),
    mHasSurface(false),
    mClientRef(client)
{
    mFlinger->getRenderEngine().genTextures(1, &mTextureName);
    mTexture.init(Texture::TEXTURE_EXTERNAL, mTextureName);
    
    uint32_t layerFlags = 0;
    if (flags & ISurfaceComposerClient::eHidden)
        layerFlags |= layer_state_t::eLayerHidden;
    if (flags & ISurfaceComposerClient::eOpaque)
        layerFlags |= layer_state_t::eLayerOpaque;
    if (flags & ISurfaceComposerClient::eSecure)
        layerFlags |= layer_state_t::eLayerSecure;
    
    if (flags & ISurfaceComposerClient::eNonPremultiplied)
        mPremultipliedAlpha = false;
    
    mName = name;
    
}

void Layer::onFirstRef() {
}

Layer::~Layer() {
    sp<Client> c(mClientRef.promote());
    if (c != 0) {
        c->detachLayer(this);
    }
}
    
status_t Layer::setBuffers( uint32_t w, uint32_t h,
                           PixelFormat format, uint32_t flags)
{
    return NO_ERROR;
}
    
/*
 * The layer handle is just a BBinder object passed to the client
 * (remote process) -- we don't keep any reference on our side such that
 * the dtor is called when the remote side let go of its reference.
 *
 * LayerCleaner ensures that mFlinger->onLayerDestroyed() is called for
 * this layer when the handle is destroyed.
 */
class Layer::Handle : public BnSurfaceHandle {
public:
    Handle(const sp<SurfaceFlinger>& flinger, const sp<Layer>& layer)
    : mFlinger(flinger), mOwner(layer) {};
    
	~Handle() {

	};

    virtual EGLNativeWindowType getNativeWindow()
    {
        EGLNativeWindowType win = 0;
        
        sp<SurfaceFlinger> flinger = mFlinger.promote();
        if (flinger != NULL) {
            win = flinger->getOSWindow()->getNativeWindow();
        }
        
        return win;
    };
    
    wp<SurfaceFlinger> mFlinger;
    wp<Layer> mOwner;
};

    
sp<IBinder> Layer::getHandle() {
    Mutex::Autolock _l(mLock);
    
    LOG_ALWAYS_FATAL_IF(mHasSurface,
                        "Layer::getHandle() has already been called");
    
    mHasSurface = true;
    if (mHandle == NULL) {
        mHandle = new Handle(mFlinger, this);
    }
    
    return (IInterface::asBinder(mHandle));
}

// ---------------------------------------------------------------------------
}; // namespace android
