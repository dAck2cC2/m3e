/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ANDROID_LAYER_H
#define ANDROID_LAYER_H

#include <stdint.h>
#include <sys/types.h>

#include <EGL/egl.h>
#include <EGL/eglext.h>

#include <utils/RefBase.h>
#include <utils/String8.h>
#include <utils/Timers.h>

#include <ui/FrameStats.h>
#include <ui/GraphicBuffer.h>
#include <ui/PixelFormat.h>
#include <ui/Region.h>

#include <gui/ISurfaceComposerClient.h>

#include <private/gui/LayerState.h>

#include <list>

//#include "FrameTracker.h"
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
	
	//sp<IGraphicBufferProducer> getProducer() const;
    const String8& getName() const { return mName; }; 

	class Handle;

	sp<IBinder> getHandle();
	void update();
	sp<NativeWindow> getNativeWindow() { return mNativeWindow; };

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
    
	sp<NativeWindow> mNativeWindow;
    sp<Handle> mHandle;
};

// ---------------------------------------------------------------------------

}; // namespace android

#endif // ANDROID_LAYER_H
