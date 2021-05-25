
#include <pthread.h>

#include <initrc/initrc.h>

#include <ui/DisplayInfo.h>
#include <gui/ISurfaceComposer.h>
#include <gui/Surface.h>
#include <gui/SurfaceComposerClient.h>

using namespace android;

static void test_window(void) {
    sp<SurfaceComposerClient> mSession = new SurfaceComposerClient();

    sp<IBinder> mDisplayToken;

    mDisplayToken = SurfaceComposerClient::getInternalDisplayToken();
    if (mDisplayToken == nullptr)
        return;

    DisplayInfo dinfo;
    status_t status = SurfaceComposerClient::getDisplayInfo(mDisplayToken, &dinfo);
    if (status)
        return;

    // create the native surface
    sp<SurfaceControl> control = mSession->createSurface(String8("test_surfaceflinger"),
        dinfo.w, dinfo.h, PIXEL_FORMAT_RGB_565);

    while (true) {

    }
}

static pthread_t mGUIThread = NULL;

void* _threadLoop(void* user)
{
    test_window();

    return nullptr;
}

int main(int argc, char** argv)
{
	InitRC_entry(argc, argv);

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    int result = pthread_create(&(mGUIThread), &attr,
        _threadLoop,
        NULL);
    pthread_attr_destroy(&attr);

	InitRC_run();

	return 0;
}
