
#include "RenderScript.h"

enum {
    RS_SCRIPT_INTRINSIC_ID_3DLUT,
    RS_SCRIPT_INTRINSIC_ID_BLEND,
    RS_SCRIPT_INTRINSIC_ID_BLUR,
    RS_SCRIPT_INTRINSIC_ID_COLOR_MATRIX,
    RS_SCRIPT_INTRINSIC_ID_CONVOLVE_3x3,
    RS_SCRIPT_INTRINSIC_ID_CONVOLVE_5x5,
    RS_SCRIPT_INTRINSIC_ID_HISTOGRAM,
    RS_SCRIPT_INTRINSIC_ID_LUT,
    RS_SCRIPT_INTRINSIC_ID_RESIZE,
    RS_SCRIPT_INTRINSIC_ID_YUV_TO_RGB,

};

using namespace android;
using namespace RSC;

ScriptIntrinsic::ScriptIntrinsic(sp<RS> rs, int id, sp<const Element> e)
    : Script(nullptr, rs) {
}

ScriptIntrinsic::~ScriptIntrinsic() {

}

sp<ScriptIntrinsic3DLUT> ScriptIntrinsic3DLUT::create(sp<RS> rs, sp<const Element> e) {
    return nullptr;
}

ScriptIntrinsic3DLUT::ScriptIntrinsic3DLUT(sp<RS> rs, sp<const Element> e)
    : ScriptIntrinsic(rs, RS_SCRIPT_INTRINSIC_ID_3DLUT, e) {
}
void ScriptIntrinsic3DLUT::forEach(sp<Allocation> ain, sp<Allocation> aout) {
}

void ScriptIntrinsic3DLUT::setLUT(sp<Allocation> lut) {
}

sp<ScriptIntrinsicBlend> ScriptIntrinsicBlend::create(sp<RS> rs, sp<const Element> e) {
    return nullptr;
}

ScriptIntrinsicBlend::ScriptIntrinsicBlend(sp<RS> rs, sp<const Element> e)
    : ScriptIntrinsic(rs, RS_SCRIPT_INTRINSIC_ID_BLEND, e) {
}

void ScriptIntrinsicBlend::forEachClear(sp<Allocation> in, sp<Allocation> out) {
}

void ScriptIntrinsicBlend::forEachSrc(sp<Allocation> in, sp<Allocation> out) {
}

void ScriptIntrinsicBlend::forEachDst(sp<Allocation> in, sp<Allocation> out) {
}

void ScriptIntrinsicBlend::forEachSrcOver(sp<Allocation> in, sp<Allocation> out) {
}

void ScriptIntrinsicBlend::forEachDstOver(sp<Allocation> in, sp<Allocation> out) {
}

void ScriptIntrinsicBlend::forEachSrcIn(sp<Allocation> in, sp<Allocation> out) {
}

void ScriptIntrinsicBlend::forEachDstIn(sp<Allocation> in, sp<Allocation> out) {
}

void ScriptIntrinsicBlend::forEachSrcOut(sp<Allocation> in, sp<Allocation> out) {
}

void ScriptIntrinsicBlend::forEachDstOut(sp<Allocation> in, sp<Allocation> out) {
}

void ScriptIntrinsicBlend::forEachSrcAtop(sp<Allocation> in, sp<Allocation> out) {
}

void ScriptIntrinsicBlend::forEachDstAtop(sp<Allocation> in, sp<Allocation> out) {
}

void ScriptIntrinsicBlend::forEachXor(sp<Allocation> in, sp<Allocation> out) {
}

void ScriptIntrinsicBlend::forEachMultiply(sp<Allocation> in, sp<Allocation> out) {
}

void ScriptIntrinsicBlend::forEachAdd(sp<Allocation> in, sp<Allocation> out) {
}

void ScriptIntrinsicBlend::forEachSubtract(sp<Allocation> in, sp<Allocation> out) {
}


sp<ScriptIntrinsicBlur> ScriptIntrinsicBlur::create(sp<RS> rs, sp<const Element> e) {
    return nullptr;
}

ScriptIntrinsicBlur::ScriptIntrinsicBlur(sp<RS> rs, sp<const Element> e)
    : ScriptIntrinsic(rs, RS_SCRIPT_INTRINSIC_ID_BLUR, e) {

}

void ScriptIntrinsicBlur::setInput(sp<Allocation> in) {
}

void ScriptIntrinsicBlur::forEach(sp<Allocation> out) {
}

void ScriptIntrinsicBlur::setRadius(float radius) {
}



sp<ScriptIntrinsicColorMatrix> ScriptIntrinsicColorMatrix::create(sp<RS> rs) {
    return nullptr;
}

ScriptIntrinsicColorMatrix::ScriptIntrinsicColorMatrix(sp<RS> rs, sp<const Element> e)
    : ScriptIntrinsic(rs, RS_SCRIPT_INTRINSIC_ID_COLOR_MATRIX, e) {
}

void ScriptIntrinsicColorMatrix::forEach(sp<Allocation> in, sp<Allocation> out) {
}

void ScriptIntrinsicColorMatrix::setAdd(float* add) {
}

void ScriptIntrinsicColorMatrix::setColorMatrix3(float* m) {
}


void ScriptIntrinsicColorMatrix::setColorMatrix4(float* m) {
}


void ScriptIntrinsicColorMatrix::setGreyscale() {
}


void ScriptIntrinsicColorMatrix::setRGBtoYUV() {
}


void ScriptIntrinsicColorMatrix::setYUVtoRGB() {
}



sp<ScriptIntrinsicConvolve3x3> ScriptIntrinsicConvolve3x3::create(sp<RS> rs, sp<const Element> e) {
    return nullptr;
}

ScriptIntrinsicConvolve3x3::ScriptIntrinsicConvolve3x3(sp<RS> rs, sp<const Element> e)
    : ScriptIntrinsic(rs, RS_SCRIPT_INTRINSIC_ID_CONVOLVE_3x3, e) {

}

void ScriptIntrinsicConvolve3x3::setInput(sp<Allocation> in) {
}

void ScriptIntrinsicConvolve3x3::forEach(sp<Allocation> out) {
}

void ScriptIntrinsicConvolve3x3::setCoefficients(float* v) {
}

sp<ScriptIntrinsicConvolve5x5> ScriptIntrinsicConvolve5x5::create(sp<RS> rs, sp<const Element> e) {
        return nullptr;
}

ScriptIntrinsicConvolve5x5::ScriptIntrinsicConvolve5x5(sp<RS> rs, sp<const Element> e)
    : ScriptIntrinsic(rs, RS_SCRIPT_INTRINSIC_ID_CONVOLVE_5x5, e) {

}

void ScriptIntrinsicConvolve5x5::setInput(sp<Allocation> in) {
}

void ScriptIntrinsicConvolve5x5::forEach(sp<Allocation> out) {
}

void ScriptIntrinsicConvolve5x5::setCoefficients(float* v) {
}

sp<ScriptIntrinsicHistogram> ScriptIntrinsicHistogram::create(sp<RS> rs, sp<const Element> e) {
    return new ScriptIntrinsicHistogram(rs, e);
}

ScriptIntrinsicHistogram::ScriptIntrinsicHistogram(sp<RS> rs, sp<const Element> e)
    : ScriptIntrinsic(rs, RS_SCRIPT_INTRINSIC_ID_HISTOGRAM, e) {

}

void ScriptIntrinsicHistogram::setOutput(sp<Allocation> out) {
}

void ScriptIntrinsicHistogram::setDotCoefficients(float r, float g, float b, float a) {
}

void ScriptIntrinsicHistogram::forEach(sp<Allocation> ain) {
}


void ScriptIntrinsicHistogram::forEach_dot(sp<Allocation> ain) {
}

sp<ScriptIntrinsicLUT> ScriptIntrinsicLUT::create(sp<RS> rs, sp<const Element> e) {
        return nullptr;
}

ScriptIntrinsicLUT::ScriptIntrinsicLUT(sp<RS> rs, sp<const Element> e) 
    : ScriptIntrinsic(rs, RS_SCRIPT_INTRINSIC_ID_LUT, e) {
}

void ScriptIntrinsicLUT::forEach(sp<Allocation> ain, sp<Allocation> aout) {

}

void ScriptIntrinsicLUT::setTable(unsigned int offset, unsigned char base, unsigned int length, unsigned char* lutValues) {
}

void ScriptIntrinsicLUT::setRed(unsigned char base, unsigned int length, unsigned char* lutValues) {
}

void ScriptIntrinsicLUT::setGreen(unsigned char base, unsigned int length, unsigned char* lutValues) {
}

void ScriptIntrinsicLUT::setBlue(unsigned char base, unsigned int length, unsigned char* lutValues) {
}

void ScriptIntrinsicLUT::setAlpha(unsigned char base, unsigned int length, unsigned char* lutValues) {
}

ScriptIntrinsicLUT::~ScriptIntrinsicLUT() {

}

sp<ScriptIntrinsicResize> ScriptIntrinsicResize::create(sp<RS> rs) {
    return new ScriptIntrinsicResize(rs, nullptr);
}

ScriptIntrinsicResize::ScriptIntrinsicResize(sp<RS> rs, sp<const Element> e)
    : ScriptIntrinsic(rs, RS_SCRIPT_INTRINSIC_ID_RESIZE, e) {

}
void ScriptIntrinsicResize::forEach_bicubic(sp<Allocation> aout) {
}
void ScriptIntrinsicResize::setInput(sp<Allocation> ain) {
}


sp<ScriptIntrinsicYuvToRGB> ScriptIntrinsicYuvToRGB::create(sp<RS> rs, sp<const Element> e) {
        return nullptr;
}

ScriptIntrinsicYuvToRGB::ScriptIntrinsicYuvToRGB(sp<RS> rs, sp<const Element> e)
    : ScriptIntrinsic(rs, RS_SCRIPT_INTRINSIC_ID_YUV_TO_RGB, e) {

}

void ScriptIntrinsicYuvToRGB::setInput(sp<Allocation> in) {
}

void ScriptIntrinsicYuvToRGB::forEach(sp<Allocation> out) {
}
