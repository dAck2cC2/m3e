
//#define LOG_NDEBUG 0
#undef LOG_TAG
#define LOG_TAG "Layer"
#define ATRACE_TAG ATRACE_TAG_GRAPHICS

#include <utils/RefBase.h>
#include <binder/Binder.h>
#include <gui/IGraphicBufferProducer.h>
#include <gui/customized/ISurfaceHandle.h>
#include <private/gui/LayerState.h>
#include <private/binder/binder_module.h>

#include "Layer.h"

namespace android {

class SurfaceHandle : public Layer::Handle {
public:
	SurfaceHandle(const sp<SurfaceFlinger>& flinger, const sp<Layer>& layer)
    : Handle(flinger, layer), mFlinger(flinger) {};
    
	~SurfaceHandle() {};

	virtual status_t    transact(uint32_t code,
		const Parcel& data,
		Parcel* reply,
		uint32_t flags)
	{
		switch (code) {
		case GET_NATIVE_WINDOW: {
			if (!data.enforceInterface(String16(ISURFACE_HANDLE_NAME))) return PERMISSION_DENIED;

			flat_binder_object obj = {};
            obj.hdr.type = BINDER_TYPE_PTR;

			sp<Layer> layer = owner.promote();
			if (layer == NULL) {
				// garbage data to catch improper use
				obj.cookie = (uintptr_t)(0xDEADBEEF);
			}
			else {
				obj.cookie = (uintptr_t)(layer->getEGLNativeWindow());
			}

			reply->writeObject(obj, true);
			return NO_ERROR;
		}
		default:
			return BBinder::transact(code, data, reply, flags);
			break;
		}
	};

private:
    wp<SurfaceFlinger> mFlinger;
};

// ---------------------------------------------------------------------------
}; // namespace android
