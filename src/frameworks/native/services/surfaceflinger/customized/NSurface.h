#pragma once

#ifndef NATIVE_SURFACE_H
#define NATIVE_SURFACE_H

namespace android {
namespace NATIVE {

class Surface : public android::Surface {
private:
    sp<SurfaceFlinger>  mSF;
    android::hardware::graphics::composer::V2_1::Layer mLayer;
    
public:
    explicit Surface(const sp<IGraphicBufferProducer>& bufferProducer, bool controlledByApp, sp<SurfaceFlinger>& sf)
    : android::Surface(bufferProducer, controlledByApp),
      mSF(sf),
      mLayer(0)
    {
        mSF->getBE().mHwc->getComposer()->createLayer(0, &mLayer);
        oem[0] = mLayer;
    };
    
protected:
    virtual ~Surface() {};
}; // Surface

} // NATIVE
} // android

#endif // NATIVE_SURFACE_H
