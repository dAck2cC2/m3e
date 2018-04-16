
//#define LOG_NDEBUG 0
#undef LOG_TAG
#define LOG_TAG "Layer"
#define ATRACE_TAG ATRACE_TAG_GRAPHICS

#include "Layer.h"

namespace android {

Layer::Layer(SurfaceFlinger* flinger, const sp<Client>& client,
        const String8& name, uint32_t w, uint32_t h, uint32_t flags)
:   mFlinger(flinger),
    mName("unnamed"),
    mHasSurface(false),
    mClientRef(client)
{

}

Layer::~Layer() {

}

void Layer::onFirstRef() {
}
    
status_t Layer::setBuffers( uint32_t w, uint32_t h,
                           PixelFormat format, uint32_t flags)
{
    return NO_INIT;
}
    
// ---------------------------------------------------------------------------
}; // namespace android
