
#include "RenderScript.h"

using namespace android;
using namespace RSC;

void * Allocation::getIDSafe() const {
    return NULL;
}

void Allocation::updateCacheInfo(sp<const Type> t) {
}

Allocation::Allocation(void *id, sp<RS> rs, sp<const Type> t, uint32_t usage) 
: BaseObj(id, rs) 
{
}


void Allocation::validateIsInt64() {
}

void Allocation::validateIsInt32() {
}

void Allocation::validateIsInt16() {
}

void Allocation::validateIsInt8() {
}

void Allocation::validateIsFloat32() {
}

void Allocation::validateIsFloat64() {
}

void Allocation::validateIsObject() {
}

void Allocation::updateFromNative() {
}

void Allocation::syncAll(RsAllocationUsageType srcLocation) {
}

void * Allocation::getPointer(size_t *stride) {
    void *p = nullptr;
    return p;
}

// ---------------------------------------------------------------------------

void Allocation::copy1DRangeFrom(uint32_t off, size_t count, const void *data) {
}

void Allocation::copy1DRangeTo(uint32_t off, size_t count, void *data) {
}

void Allocation::copy1DRangeFrom(uint32_t off, size_t count, sp<const Allocation> data,
                                 uint32_t dataOff) {
}

void Allocation::copy1DFrom(const void* data) {
}

void Allocation::copy1DTo(void* data) {
}


void Allocation::validate2DRange(uint32_t xoff, uint32_t yoff, uint32_t w, uint32_t h) {
}

void Allocation::copy2DRangeFrom(uint32_t xoff, uint32_t yoff, uint32_t w, uint32_t h,
                                 const void *data) {
}

void Allocation::copy2DRangeFrom(uint32_t xoff, uint32_t yoff, uint32_t w, uint32_t h,
                                 sp<const Allocation> data, uint32_t dataXoff, uint32_t dataYoff) {
}

void Allocation::copy2DRangeTo(uint32_t xoff, uint32_t yoff, uint32_t w, uint32_t h,
                               void* data) {
}

void Allocation::copy2DStridedFrom(uint32_t xoff, uint32_t yoff, uint32_t w, uint32_t h,
                                   const void *data, size_t stride) {
}

void Allocation::copy2DStridedFrom(const void* data, size_t stride) {
}

void Allocation::copy2DStridedTo(uint32_t xoff, uint32_t yoff, uint32_t w, uint32_t h,
                                 void *data, size_t stride) {
}

void Allocation::copy2DStridedTo(void* data, size_t stride) {
}

void Allocation::validate3DRange(uint32_t xoff, uint32_t yoff, uint32_t zoff, uint32_t w,
                                 uint32_t h, uint32_t d) {
}

void Allocation::copy3DRangeFrom(uint32_t xoff, uint32_t yoff, uint32_t zoff, uint32_t w,
                                 uint32_t h, uint32_t d, const void* data) {
}

void Allocation::copy3DRangeFrom(uint32_t xoff, uint32_t yoff, uint32_t zoff, uint32_t w, uint32_t h, uint32_t d,
                                 sp<const Allocation> data, uint32_t dataXoff, uint32_t dataYoff, uint32_t dataZoff) {
}

void Allocation::copy3DRangeTo(uint32_t xoff, uint32_t yoff, uint32_t zoff, uint32_t w,
                                 uint32_t h, uint32_t d, void* data) {
}

sp<Allocation> Allocation::createTyped(sp<RS> rs, sp<const Type> type,
                                    RsAllocationMipmapControl mipmaps, uint32_t usage) {
    void *id = 0;
    return new Allocation(id, rs, type, usage);
}

sp<Allocation> Allocation::createTyped(sp<RS> rs, sp<const Type> type,
                                    RsAllocationMipmapControl mipmaps, uint32_t usage,
                                    void *pointer) {
    void *id = 0;
    return new Allocation(id, rs, type, usage);
}

sp<Allocation> Allocation::createTyped(sp<RS> rs, sp<const Type> type,
                                    uint32_t usage) {
    return createTyped(rs, type, RS_ALLOCATION_MIPMAP_NONE, usage);
}

sp<Allocation> Allocation::createSized(sp<RS> rs, sp<const Element> e,
                                    size_t count, uint32_t usage) {
    return createTyped(rs, NULL, usage);
}

sp<Allocation> Allocation::createSized2D(sp<RS> rs, sp<const Element> e,
                                      size_t x, size_t y, uint32_t usage) {
    return createTyped(rs, NULL, usage);
}

void Allocation::ioSendOutput() {
}

void Allocation::ioGetInput() {
}

#if !defined(RS_SERVER) && !defined(RS_COMPATIBILITY_LIB)
//#include <gui/Surface.h>

RSC::sp<Surface> Allocation::getSurface() {
    return NULL;
}

void Allocation::setSurface(RSC::sp<Surface> s) {
}

#endif

