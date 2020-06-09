
#include <OMXAL/OpenMAXAL_Android.h>
#include <android/native_window.h>

#include <gui/Surface.h>
#include <gui/SurfaceComposerClient.h>
#include <utils/String8.h>
#include <utils/KeyedVector.h>

namespace android {
	struct WindowHandle {
		sp<Surface> surface;
		sp<SurfaceComposerClient> composerClient;
		sp<SurfaceControl> control;
	};

	KeyedVector<ANativeWindow*, WindowHandle> gNativeWin;

	ANativeWindow *getNativeWindow_()
	{
		sp<SurfaceComposerClient> composerClient = new SurfaceComposerClient;
		if (composerClient->initCheck() != (status_t)OK) {
			return NULL;
		}

		sp<SurfaceControl> control =
			composerClient->createSurface(
				String8("A Surface"),
				1280,
				800,
				PIXEL_FORMAT_RGB_565,
				0);

		if ((control != NULL) || (control->isValid())) {
			return NULL;
		}
#if TODO
		SurfaceComposerClient::openGlobalTransaction();
		if ((control->setLayer(30000) != (status_t)OK)
		|| (control->show() != (status_t)OK)) {
			return NULL;
		}
		SurfaceComposerClient::closeGlobalTransaction();
#endif
		sp<Surface> surface = control->getSurface();
		if (surface == NULL) {
			return NULL;
		}

		WindowHandle hWin = {};
		hWin.surface = surface;
		hWin.composerClient = composerClient;
		hWin.control = control;

		gNativeWin.add(surface.get(), hWin);

		// composerClient->dispose() at exit
		return surface.get();
	}

	void disposeNativeWindow_(ANativeWindow * nativeWin)
	{
		WindowHandle hWin = gNativeWin.editValueFor(nativeWin);
		if (hWin.composerClient != NULL) {
			hWin.composerClient->dispose();
		}

		gNativeWin.removeItem(nativeWin);
	}

} // namespace android

XANativeHandle xaAndroidCreateNativeWindow()
{
	return android::getNativeWindow_();
}

void xaAndroidDisposeNativeWindow(XANativeHandle nativeWin)
{
	android::disposeNativeWindow_((ANativeWindow *)nativeWin);
}
