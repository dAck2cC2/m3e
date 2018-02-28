#include <GL/glut.h>
#include "GrBackendSurface.h"
#include "GrContext.h"
#include "SkCanvas.h"
#include "SkRandom.h"
#include "SkSurface.h"

#include "gl/GrGLInterface.h"
#include "gl/GrGLUtil.h"

#if defined(SK_BUILD_FOR_ANDROID)
#include <GLES/gl.h>
#elif defined(SK_BUILD_FOR_UNIX)
#include <GL/gl.h>
#elif defined(SK_BUILD_FOR_MAC)
#include <OpenGL/gl.h>
#elif defined(SK_BUILD_FOR_IOS)
#include <OpenGLES/ES2/gl.h>
#endif

#define SURFACE_W  (720)
#define SURFACE_H  (480)

struct ApplicationState {
    ApplicationState() : fQuit(false) {}
    // Storage for the user created rectangles. The last one may still be being edited.
    SkTArray<SkRect> fRects;
    bool fQuit;
};

ApplicationState state;
const char* helpMessage = "Can you see me ? Can you see a star ?";
SkCanvas* canvas = NULL;
sk_sp<SkImage> image = NULL;
SkPaint paint;
int rotation = 0;

void display_cb ( void )
{
    SkRandom rand;
    canvas->clear(SK_ColorWHITE);
    
    paint.setColor(SK_ColorBLACK);
    canvas->drawText(helpMessage, strlen(helpMessage), SkIntToScalar(100),
                     SkIntToScalar(100), paint);
    for (int i = 0; i < state.fRects.count(); i++) {
        paint.setColor(rand.nextU() | 0x44808080);
        canvas->drawRect(state.fRects[i], paint);
    }
    
    // draw offscreen canvas
    canvas->save();
    canvas->translate(SURFACE_W / 2.0, SURFACE_H / 2.0);
    canvas->rotate(rotation++);
    canvas->drawImage(image, -50.0f, -50.0f);
    canvas->restore();
    
    canvas->flush();

    glutSwapBuffers();
    glutPostRedisplay();
}

void mouse_cb ( int button, int updown, int x, int y )
{
    if ( updown == GLUT_DOWN ) {
        state.fRects.push_back() = SkRect::MakeLTRB(SkIntToScalar(x),
                                                     SkIntToScalar(y),
                                                     SkIntToScalar(x),
                                                     SkIntToScalar(y));
    }
}

void motion_cb ( int x, int y )
{
    SkRect& rect = state.fRects.back();
    rect.fRight = x;
    rect.fBottom = y;
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

int main(int argc, char** argv)
{
    static const int kStencilBits = 8;  // Skia needs 8 stencil bits
    static const int kMsaaSampleCount = 0; //4;

    /* Initialize GLUT */
    glutInitDisplayString("stencil");
    glutInitWindowSize ( SURFACE_W, SURFACE_H ) ;
    glutInit ( &argc, argv ) ;
    glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH ) ;
    
    /* Create the window */
    glutCreateWindow ( "Skia Look" ) ;

    glutDisplayFunc ( display_cb ) ;
    glutMouseFunc ( mouse_cb ) ;
    glutMotionFunc ( motion_cb ) ;

    
    int dw = SURFACE_W, dh = SURFACE_H;
    glViewport(0, 0, dw, dh);
    glClearColor(1, 1, 1, 1);
    glClearStencil(0);
    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // setup GrContext
    auto interfaced = GrGLMakeNativeInterface();
    
    // setup contexts
    sk_sp<GrContext> grContext(GrContext::MakeGL(interfaced));
    SkASSERT(grContext);
    
    // Wrap the frame buffer object attached to the screen in a Skia render target so Skia can
    // render to it
    GrGLint buffer;
    GR_GL_GetIntegerv(interfaced.get(), GR_GL_FRAMEBUFFER_BINDING, &buffer);
    GrGLFramebufferInfo info;
    info.fFBOID = (GrGLuint) buffer;
    SkColorType colorType;
    
    int isRGBA = glutGet(GLUT_WINDOW_RGBA);
    if (isRGBA) {
        info.fFormat = GR_GL_RGBA8;
        colorType = kRGBA_8888_SkColorType;
    } else {
        colorType = kBGRA_8888_SkColorType;
        info.fFormat = GR_GL_BGRA8;
    }
    
    GrBackendRenderTarget target(dw, dh, kMsaaSampleCount, kStencilBits, info);
    
    // setup SkSurface
    // To use distance field text, use commented out SkSurfaceProps instead
    // SkSurfaceProps props(SkSurfaceProps::kUseDeviceIndependentFonts_Flag,
    //                      SkSurfaceProps::kLegacyFontHost_InitType);
    SkSurfaceProps props(SkSurfaceProps::kLegacyFontHost_InitType);
    
    sk_sp<SkSurface> surface(SkSurface::MakeFromBackendRenderTarget(grContext.get(), target,
                                                                    kBottomLeft_GrSurfaceOrigin,
                                                                    colorType, nullptr, &props));
    
    canvas = surface->getCanvas();
    //canvas->scale((float)dw/dm.w, (float)dh/dm.h);
    
    // create a surface for CPU rasterization
    sk_sp<SkSurface> cpuSurface(SkSurface::MakeRaster(canvas->imageInfo()));
    
    SkCanvas* offscreen = cpuSurface->getCanvas();
    offscreen->save();
    offscreen->translate(50.0f, 50.0f);
    offscreen->drawPath(create_star(), paint);
    offscreen->restore();
    
    image = cpuSurface->makeImageSnapshot();
    
    /* Enter the GLUT main loop */
    glutMainLoop () ;
    
    return 0;
}
