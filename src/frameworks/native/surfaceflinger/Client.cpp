
#include <stdint.h>
#include <sys/types.h>

#include "Client.h"
#include "Layer.h"
#include "SurfaceFlinger.h"

namespace android {

// ---------------------------------------------------------------------------

Client::Client(const sp<SurfaceFlinger>& flinger)
    : mFlinger(flinger)
{
}

Client::~Client()
{
    const size_t count = mLayers.size();
    for (size_t i=0 ; i<count ; i++) {
        //mFlinger->removeLayer(mLayers.valueAt(i));
    }
}

status_t Client::initCheck() const {
    return NO_ERROR;
}

void Client::attachLayer(const sp<IBinder>& handle, const sp<Layer>& layer)
{
    Mutex::Autolock _l(mLock);
    mLayers.add(handle, layer);
}

void Client::detachLayer(const Layer* layer)
{
    Mutex::Autolock _l(mLock);
    // we do a linear search here, because this doesn't happen often
    const size_t count = mLayers.size();
    for (size_t i=0 ; i<count ; i++) {
        if (mLayers.valueAt(i) == layer) {
            mLayers.removeItemsAt(i, 1);
            break;
        }
    }
}

void Client::updateLayer()
{
	Mutex::Autolock _l(mLock);

	const size_t count = mLayers.size();
	for (size_t i = 0; i<count; i++) {
		mLayers.valueAt(i)->update();
	}
}

sp<Layer> Client::getLayerUser(const sp<IBinder>& handle) const
{
    Mutex::Autolock _l(mLock);
    sp<Layer> lbc;
    wp<Layer> layer(mLayers.valueFor(handle));
    if (layer != 0) {
        lbc = layer.promote();
        ALOGE_IF(lbc==0, "getLayerUser(name=%p) is dead", handle.get());
    }
    return lbc;
}

status_t Client::createSurface(
        const String8& name,
        uint32_t w, uint32_t h, PixelFormat format, uint32_t flags,
        sp<IBinder>* handle,
        sp<IGraphicBufferProducer>* gbp)
{
    /*
     * createSurface must be called from the GL thread so that it can
     * have access to the GL context.
     */
    
    class MessageCreateLayer : public MessageBase {
        SurfaceFlinger* flinger;
        Client* client;
        sp<IBinder>* handle;
        sp<IGraphicBufferProducer>* gbp;
        status_t result;
        const String8& name;
        uint32_t w, h;
        PixelFormat format;
        uint32_t flags;
    public:
        MessageCreateLayer(SurfaceFlinger* flinger,
                           const String8& name, Client* client,
                           uint32_t w, uint32_t h, PixelFormat format, uint32_t flags,
                           sp<IBinder>* handle,
                           sp<IGraphicBufferProducer>* gbp)
        : flinger(flinger), client(client),
        handle(handle), gbp(gbp), result(NO_ERROR),
        name(name), w(w), h(h), format(format), flags(flags) {
        }
        status_t getResult() const { return result; }
        virtual bool handler() {
            result = flinger->createLayer(name, client, w, h, format, flags,
                                          handle, gbp);
            return true;
        }
    };
    
    sp<MessageBase> msg = new MessageCreateLayer(mFlinger.get(),
                                                 name, this, w, h, format, flags, handle, gbp);
    mFlinger->postMessageSync(msg);
    return static_cast<MessageCreateLayer*>( msg.get() )->getResult();
}

status_t Client::destroySurface(const sp<IBinder>& handle) {
    return NO_INIT;
}

status_t Client::clearLayerFrameStats(const sp<IBinder>& handle) const {
    return NO_INIT;
}

status_t Client::getLayerFrameStats(const sp<IBinder>& handle, FrameStats* outStats) const {
    return NO_INIT;
}

status_t Client::getTransformToDisplayInverse(const sp<IBinder>& handle,
        bool* outTransformToDisplayInverse) const {
    return NO_INIT;
}

// ---------------------------------------------------------------------------
}; // namespace android
