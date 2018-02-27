//#include "GrBackendSurface.h"
//#include "GrContext.h"
//#include "SkRandom.h"
#include "SkSurface.h"
#include "SkCanvas.h"
#include "SkPath.h"

//#include "gl/GrGLInterface.h"
//#include "gl/GrGLUtil.h"

// Creates a star type shape using a SkPath
static SkPath create_star() {
	static const int kNumPoints = 5;
	SkPath concavePath;
	SkPoint points[kNumPoints] = { { 0, SkIntToScalar(-50) } };
	SkMatrix rot;
	rot.setRotate(SkIntToScalar(360) / kNumPoints);
	for (int i = 1; i < kNumPoints; ++i) {
		rot.mapPoints(points + i, points + i - 1, 1);
	}
	concavePath.moveTo(points[0]);
	for (int i = 0; i < kNumPoints; ++i) {
		concavePath.lineTo(points[(2 * i) % kNumPoints]);
	}
	concavePath.setFillType(SkPath::kEvenOdd_FillType);
	SkASSERT(!concavePath.isConvex());
	concavePath.close();
	return concavePath;
}

int main(int argc, char** argv)
{
	// setup SkSurface
	// To use distance field text, use commented out SkSurfaceProps instead
	// SkSurfaceProps props(SkSurfaceProps::kUseDeviceIndependentFonts_Flag,
	//                      SkSurfaceProps::kLegacyFontHost_InitType);
	SkSurfaceProps props(SkSurfaceProps::kLegacyFontHost_InitType);

	sk_sp<SkSurface> surface = SkSurface::MakeRaster(SkImageInfo::MakeN32Premul(720, 480), 4 * 720, &props);
	SkCanvas* canvas = surface->getCanvas();

	SkPaint paint;

	// create a surface for CPU rasterization
	sk_sp<SkSurface> cpuSurface(SkSurface::MakeRaster(canvas->imageInfo()));

	SkCanvas* offscreen = cpuSurface->getCanvas();
	offscreen->save();
	offscreen->translate(50.0f, 50.0f);
	offscreen->drawPath(create_star(), paint);
	offscreen->restore();

	sk_sp<SkImage> image = cpuSurface->makeImageSnapshot();

	while (1) {
		;
	}

    return 0;
}
