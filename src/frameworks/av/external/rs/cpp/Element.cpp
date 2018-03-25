
#include "RenderScript.h"

using namespace android;
using namespace RSC;

android::RSC::sp<const Element> Element::getSubElement(uint32_t index) {
        return nullptr;
}

const char * Element::getSubElementName(uint32_t index) {
        return nullptr;
}

size_t Element::getSubElementArraySize(uint32_t index) {
        return 0;
}

uint32_t Element::getSubElementOffsetBytes(uint32_t index) {
        return 0;
}


#define CREATE_USER(N, T) android::RSC::sp<const Element> Element::N(android::RSC::sp<RS> rs) { \
    return nullptr;                                         \
    }

CREATE_USER(BOOLEAN, BOOLEAN);
CREATE_USER(U8, UNSIGNED_8);
CREATE_USER(U8_4, UNSIGNED_8);
CREATE_USER(I8, SIGNED_8);
CREATE_USER(U16, UNSIGNED_16);
CREATE_USER(I16, SIGNED_16);
CREATE_USER(U32, UNSIGNED_32);
CREATE_USER(I32, SIGNED_32);
CREATE_USER(U64, UNSIGNED_64);
CREATE_USER(I64, SIGNED_64);
CREATE_USER(F16, FLOAT_16);
CREATE_USER(F32, FLOAT_32);
CREATE_USER(F64, FLOAT_64);
CREATE_USER(ELEMENT, ELEMENT);
CREATE_USER(TYPE, TYPE);
CREATE_USER(ALLOCATION, ALLOCATION);
CREATE_USER(SAMPLER, SAMPLER);
CREATE_USER(SCRIPT, SCRIPT);
CREATE_USER(MATRIX_4X4, MATRIX_4X4);
CREATE_USER(MATRIX_3X3, MATRIX_3X3);
CREATE_USER(MATRIX_2X2, MATRIX_2X2);

#define CREATE_PIXEL(N, T, K) android::RSC::sp<const Element> Element::N(android::RSC::sp<RS> rs) { \
    return nullptr;                                          \
}

CREATE_PIXEL(A_8, UNSIGNED_8, PIXEL_A);
CREATE_PIXEL(RGB_565, UNSIGNED_5_6_5, PIXEL_RGB);
CREATE_PIXEL(RGB_888, UNSIGNED_8, PIXEL_RGB);
CREATE_PIXEL(RGBA_4444, UNSIGNED_4_4_4_4, PIXEL_RGBA);
CREATE_PIXEL(RGBA_8888, UNSIGNED_8, PIXEL_RGBA);
CREATE_PIXEL(YUV, UNSIGNED_8, PIXEL_YUV);
CREATE_PIXEL(RGBA_5551, UNSIGNED_5_5_5_1, PIXEL_RGBA);

#define CREATE_VECTOR(N, T) android::RSC::sp<const Element> Element::N##_2(android::RSC::sp<RS> rs) { \
    return nullptr;                                           \
}
CREATE_VECTOR(U8, UNSIGNED_8);
CREATE_VECTOR(I8, SIGNED_8);
CREATE_VECTOR(U16, UNSIGNED_16);
CREATE_VECTOR(I16, SIGNED_16);
CREATE_VECTOR(U32, UNSIGNED_32);
CREATE_VECTOR(I32, SIGNED_32);
CREATE_VECTOR(U64, UNSIGNED_64);
CREATE_VECTOR(I64, SIGNED_64);
CREATE_VECTOR(F16, FLOAT_16);
CREATE_VECTOR(F32, FLOAT_32);
CREATE_VECTOR(F64, FLOAT_64);


void Element::updateVisibleSubElements() {
}

Element::Element(void *id, android::RSC::sp<RS> rs,
                 android::RSC::sp<const Element> * elements,
                 size_t elementCount,
                 const char ** elementNames,
                 size_t * elementNameLengths,
                 uint32_t * arraySizes) 
: BaseObj(id, rs) 
{
}

Element::Element(void *id, android::RSC::sp<RS> rs) 
: BaseObj(id, rs) 
{
}

Element::Element(void *id, android::RSC::sp<RS> rs,
                 RsDataType dt, RsDataKind dk, bool norm, uint32_t size) 
: BaseObj(id, rs)
{
}

Element::~Element() {
}

void Element::updateFromNative() {
}

android::RSC::sp<const Element> Element::createUser(android::RSC::sp<RS> rs, RsDataType dt) {
       return nullptr;
}

android::RSC::sp<const Element> Element::createVector(android::RSC::sp<RS> rs, RsDataType dt, uint32_t size) {
       return nullptr;
}

android::RSC::sp<const Element> Element::createPixel(android::RSC::sp<RS> rs, RsDataType dt, RsDataKind dk) {
        return nullptr;
}

bool Element::isCompatible(android::RSC::sp<const Element>e) const {
    return false;
}

Element::Builder::Builder(android::RSC::sp<RS> rs) {
}

Element::Builder::~Builder() {
}

void Element::Builder::add(android::RSC::sp<const Element>e, const char * name, uint32_t arraySize) {
}

android::RSC::sp<const Element> Element::Builder::create() {
        return nullptr;
}
