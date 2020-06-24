#pragma once

#ifndef NATIVE_SURFACE_FLINGER_H
#define NATIVE_SURFACE_FLINGER_H


#include "Client.h"
#include "DisplayHardware/ComposerHal.h"

#if !defined(ENABLE_ANDROID_GL)
#include "customized/NBufferLayer.h"
#endif

namespace android {
namespace NATIVE {

class SurfaceFlinger : public android::SurfaceFlinger {
public:
    SurfaceFlinger() :
    android::SurfaceFlinger(),
    mClients()
    {};

    void runLoop()
    {
        bool isRunning = true;

        while (isRunning) {
            // The message which is used to create surface must be executed in main thread.
            timedWaitForEvent(1000 / 60);

            //IPCThreadState::self()->handlePolledCommands();
            
            // Clear events that the application did not process from this frame
            if (getBE().mHwc == NULL) {
                isRunning = false;
            }
            else if (getBE().mHwc->getComposer() == NULL) {
                isRunning = false;

            } else {
                // pop native window event and message loop
                android::hardware::graphics::composer::V2_1::Error ret = getBE().mHwc->getComposer()->executeCommands();
                if (ret != android::hardware::graphics::composer::V2_1::Error::NONE) {
                    isRunning = false;

                }
            }

            if (!isRunning) {
                break;
            }
        } // while (isRunning)
    };

    
private:
    ~SurfaceFlinger() {};
    
    /* ------------------------------------------------------------------------
     * ISurfaceComposer interface
     */
    virtual sp<ISurfaceComposerClient> createConnection() override
    {
        sp<Client> client = new Client(this);
        if (client != NULL) {
            status_t err = client->initCheck();
            if (err == NO_ERROR) {
                /*
                * Not sure how to support such usage in Binder driver currently.
                * Where to keep the Binder Native(server) instance ?
                */
                /*
                * Anyway, we have to keep the client for multi-window update.
                */
                mClients.push_back(client);
                
                return client;
            }
        }
        return nullptr;
    };

    /* ------------------------------------------------------------------------
     * Message handling
     */
    void timedWaitForEvent(int timeoutMillis = -1)
    {
            mEventQueue->waitMessage(timeoutMillis);
    };
#if !defined(ENABLE_ANDROID_GL)
    /* ------------------------------------------------------------------------
     * Layer management
     */
    status_t createBufferLayer(const sp<Client>& client,
    const String8& name, uint32_t w, uint32_t h, uint32_t flags, PixelFormat& format,
    sp<IBinder>* handle, sp<IGraphicBufferProducer>* gbp, sp<Layer>* outLayer) override
    {
        // initialize the surfaces
        switch (format) {
        case PIXEL_FORMAT_TRANSPARENT:
        case PIXEL_FORMAT_TRANSLUCENT:
            format = PIXEL_FORMAT_RGBA_8888;
            break;
        case PIXEL_FORMAT_OPAQUE:
            format = PIXEL_FORMAT_RGBX_8888;
            break;
        }

        sp<BufferLayer> layer = new NATIVE::BufferLayer(this, client, name, w, h, flags);
        status_t err = layer->setBuffers(w, h, format, flags);
        if (err == NO_ERROR) {
            *handle = layer->getHandle();
            *gbp = layer->getProducer();
            *outLayer = layer;
        }

        ALOGE_IF(err, "createBufferLayer() failed (%s)", strerror(-err));
        return err;
    };
#endif // ENABLE_ANDROID_GL
private:
    Vector< sp<Client> > mClients;
}; // SurfaceFlinger

} // NATIVE
} // android

#endif // NATIVE_SURFACE_FLINGER_H
