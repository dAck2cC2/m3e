
#include "RenderScript.h"

// From system/graphics.h
enum {
    HAL_PIXEL_FORMAT_YV12               = 0x32315659, // YCrCb 4:2:0 Planar
    HAL_PIXEL_FORMAT_YCrCb_420_SP       = 0x11,       // NV21
};

using namespace android;
using namespace RSC;

void Type::calcElementCount() {
}


Type::Type(void *id, sp<RS> rs) 
: BaseObj(id, rs) 
{
}

void Type::updateFromNative() {
}

sp<const Type> Type::create(sp<RS> rs, sp<const Element> e, uint32_t dimX, uint32_t dimY, uint32_t dimZ) {
    return NULL;
}

Type::Builder::Builder(sp<RS> rs, sp<const Element> e) {
}

void Type::Builder::setX(uint32_t value) {
}

void Type::Builder::setY(uint32_t value) {
}

void Type::Builder::setZ(uint32_t value) {
}

void Type::Builder::setYuvFormat(RsYuvFormat format) {
}

void Type::Builder::setMipmaps(bool value) {
}

void Type::Builder::setFaces(bool value) {
}

sp<const Type> Type::Builder::create() {
    return NULL;
}

