#include "SkSurface.h"
#include "SkCanvas.h"
#include "SkPath.h"

void bitmap(const char* bmpfile, int w, int h, SkPixmap& data)
{
    typedef struct                       /**** BMP file header structure ****/
    {
        unsigned int   bfSize;           /* Size of file */
        unsigned short bfReserved1;      /* Reserved */
        unsigned short bfReserved2;      /* ... */
        unsigned int   bfOffBits;        /* Offset to bitmap data */
    } BITMAPFILEHEADER;
    
    typedef struct                       /**** BMP file info structure ****/
    {
        unsigned int   biSize;           /* Size of info header */
        int            biWidth;          /* Width of image */
        int            biHeight;         /* Height of image */
        unsigned short biPlanes;         /* Number of color planes */
        unsigned short biBitCount;       /* Number of bits per pixel */
        unsigned int   biCompression;    /* Type of compression to use */
        unsigned int   biSizeImage;      /* Size of image data */
        int            biXPelsPerMeter;  /* X pixels per meter */
        int            biYPelsPerMeter;  /* Y pixels per meter */
        unsigned int   biClrUsed;        /* Number of colors used */
        unsigned int   biClrImportant;   /* Number of important colors */
    } BITMAPINFOHEADER;
    
    BITMAPFILEHEADER bfh;
    BITMAPINFOHEADER bih;
    
    /* Magic number for file. It does not fit in the header structure due to alignment requirements, so put it outside */
    unsigned short bfType=0x4d42;
    bfh.bfReserved1 = 0;
    bfh.bfReserved2 = 0;
    bfh.bfSize = 2+sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)+w*h*3;
    bfh.bfOffBits = 0x36;
    
    bih.biSize = sizeof(BITMAPINFOHEADER);
    bih.biWidth = w;
    bih.biHeight = h;
    bih.biPlanes = 1;
    bih.biBitCount = 24;
    bih.biCompression = 0;
    bih.biSizeImage = 0;
    bih.biXPelsPerMeter = 5000;
    bih.biYPelsPerMeter = 5000;
    bih.biClrUsed = 0;
    bih.biClrImportant = 0;
    
    FILE *file = fopen(bmpfile, "wb");
    if (!file)
    {
        printf("Could not write file: %s\n", bmpfile);
        return;
    }
    
    /*Write headers*/
    fwrite(&bfType,1,sizeof(bfType),file);
    fwrite(&bfh, 1, sizeof(bfh), file);
    fwrite(&bih, 1, sizeof(bih), file);
    
    /*Write bitmap*/
    for (int y = bih.biHeight-1; y>=0; y--) /*Scanline loop backwards*/
    {
        for (int x = 0; x < bih.biWidth; x++) /*Column loop forwards*/
        {
            /*compute some pixel values*/
            unsigned char r = *((unsigned char *)data.addr() + (data.rowBytes()*y + x*3 + 0)); //255*((float)x/bih.biWidth);
            unsigned char g = *((unsigned char *)data.addr() + (data.rowBytes()*y + x*3 + 1)); //255*((float)y/bih.biHeight);
            unsigned char b = *((unsigned char *)data.addr() + (data.rowBytes()*y + x*3 + 2)); //0;
            fwrite(&b, 1, 1, file);
            fwrite(&g, 1, 1, file);
            fwrite(&r, 1, 1, file);
        }
    }
    fclose(file);
}

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

#define SURFACE_W  (720)
#define SURFACE_H  (480)

int main(int argc, char** argv)
{
	// setup SkSurface
	// To use distance field text, use commented out SkSurfaceProps instead
	// SkSurfaceProps props(SkSurfaceProps::kUseDeviceIndependentFonts_Flag,
	//                      SkSurfaceProps::kLegacyFontHost_InitType);
	SkSurfaceProps props(SkSurfaceProps::kLegacyFontHost_InitType);

	sk_sp<SkSurface> surface = SkSurface::MakeRaster(SkImageInfo::MakeN32Premul(SURFACE_W, SURFACE_H), 4 * SURFACE_W, &props);
	SkCanvas* canvas = surface->getCanvas();

    const char* helpMessage = "Can you see me ? Can you see a star ?";

	SkPaint paint;

	// create a surface for CPU rasterization
	sk_sp<SkSurface> cpuSurface(SkSurface::MakeRaster(canvas->imageInfo()));

	SkCanvas* offscreen = cpuSurface->getCanvas();
	offscreen->save();
	offscreen->translate(50.0f, 50.0f);
	offscreen->drawPath(create_star(), paint);
	offscreen->restore();

	sk_sp<SkImage> image = cpuSurface->makeImageSnapshot();

    int rotation = 0;

    canvas->clear(SK_ColorWHITE);
    paint.setColor(SK_ColorBLACK);
    canvas->drawText(helpMessage, strlen(helpMessage), SkIntToScalar(100),
                     SkIntToScalar(100), paint);

    // draw offscreen canvas
    canvas->save();
    canvas->translate(SURFACE_W / 2.0, SURFACE_H / 2.0);
    canvas->rotate(rotation++);
    canvas->drawImage(image, -50.0f, -50.0f);
    canvas->restore();
    
    canvas->flush();

    // dump the surface
    sk_sp<SkImage> snapshoot = surface->makeImageSnapshot();
    SkPixmap pixSurface;
    snapshoot->peekPixels(&pixSurface);
    SkColorType color = pixSurface.colorType();
    bitmap("test_skia_core.bmp", SURFACE_W, SURFACE_H, pixSurface);

    return 0;
}
