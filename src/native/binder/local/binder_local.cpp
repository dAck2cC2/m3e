
#define LOG_TAG "BinderLocal"

#include <stdint.h>

#include <cutils/threads.h>

#include <utils/Errors.h>
#include <utils/Vector.h>
#include <utils/Looper.h>

#include <binder/Parcel.h>
#include <binder/IPCThreadState.h>

#include <private/binder/binder_module.h>

namespace android {

struct binder_entry {
	sp<Looper> revicerLoop;
	int        senderHandler;
	Parcel*    cache;
};

static Mutex mLock;
static Vector<binder_entry> mServices;
static int  mHandlerContextManager = 0;

// ---------------------------------------------------------------------------
// Private API

static binder_entry* binder_lookupHandle_local(int handler)
{
	const size_t N = mServices.size();
	if (N <= (size_t)handler) {
		binder_entry e;
		e.revicerLoop   = NULL;
		e.senderHandler = -1;
		e.cache = NULL;
		status_t err = mServices.insertAt(e, N, handler + 1 - N);
		if (err < NO_ERROR) return NULL;
	}
	return &mServices.editItemAt(handler);
}

class BinderMessageHandler : public MessageHandler
{
public:
	Parcel*   src;
	Parcel*&  dst;
	int&      hSender;

	BinderMessageHandler(Parcel* data, Parcel*& out, int& handler) : src(data), dst(out), hSender(handler) {};

	virtual void handleMessage(const Message& evt) {
		hSender = evt.what;
		dst = src;
	};
};

#define BINDER_CMD_SIZE  (sizeof(int32_t))
#define BINDER_TR_SIZE   (sizeof(binder_transaction_data))

status_t binder_write_read_local(int handler, void* data)
{
	status_t result = BAD_VALUE;
	int bNeedRead = 0;

	binder_write_read* pbwr = (binder_write_read*)data;
	if (!pbwr) return result;

	if (handler == mHandlerContextManager) {
		handler = 0;
	}
	binder_entry* e = binder_lookupHandle_local(handler);
	if (e == NULL || e->revicerLoop == NULL) return (NO_INIT);

	// write
	if (pbwr->write_buffer && pbwr->write_size >= BINDER_CMD_SIZE) {
		int32_t* cmd = (int32_t *)(pbwr->write_buffer);
		switch (*cmd) {
		case BC_TRANSACTION:
			{
				if (pbwr->write_size < (BINDER_CMD_SIZE + BINDER_TR_SIZE)) return result;

				binder_transaction_data* tr = (binder_transaction_data *)((uint8_t *)(pbwr->write_buffer) + sizeof(uint32_t));
				binder_entry* et = binder_lookupHandle_local(tr->target.handle);
				if (et == NULL || et->revicerLoop == NULL) return (DEAD_OBJECT);

				(*cmd) = BR_TRANSACTION;
				tr->target.ptr = 0;

				Parcel* inData = new Parcel();
				if (!inData) return NO_MEMORY;

				inData->setData((uint8_t *)(pbwr->write_buffer), pbwr->write_size);

				Message evt(handler);
				sp<MessageHandler> trdata = new BinderMessageHandler(inData, et->cache, et->senderHandler);
				et->revicerLoop->sendMessage(trdata, evt);

				bNeedRead = 1;
			}
			break;
		case BC_ENTER_LOOPER:
		case BC_REGISTER_LOOPER:
			bNeedRead = 1;
			break;
		case BC_EXIT_LOOPER:
			bNeedRead = 0;
			break;
		default:
			break;
		}
	}
	pbwr->write_consumed = pbwr->write_size;

	// read
	result = NO_ERROR;
	if (bNeedRead && pbwr->read_buffer && pbwr->read_size) {
		int ret = e->revicerLoop->pollOnce(-1);
		//if (Looper::POLL_CALLBACK != ret) return NO_ERROR;

		if (e->cache != NULL && e->cache->dataSize() <= pbwr->read_size) {
			memcpy((void *)(pbwr->read_buffer), e->cache->data(), e->cache->dataSize());
		}

		if (e->cache) {
			delete (e->cache);
			e->cache = NULL;
		}
	}

	return result;
}

// ---------------------------------------------------------------------------
// Public API

int binder_open_local()
{
	int handler = mServices.size();
	binder_entry* e = binder_lookupHandle_local(handler);
	if ((!e) || (e->revicerLoop != NULL)) {
		return (-1);
	}

	e->revicerLoop = new Looper(true);
	if (e->revicerLoop == NULL) {
		return (-2);
	}

	return handler;
}

status_t binder_close_local(int handler)
{
	status_t result = BAD_VALUE;

	binder_entry* e = binder_lookupHandle_local(handler);
	if (e) {
		e->revicerLoop  = NULL;
		e->senderHandler = -1;

		result = NO_ERROR;
	}

	return result;
}

status_t binder_ioctl_local(int handler, int cmd, void* data)
{
	status_t result = NO_ERROR;

	if (handler < 0) {
		return BAD_VALUE;
	}

	switch (cmd) {
	case BINDER_VERSION:
		*((int *)data) = BINDER_CURRENT_PROTOCOL_VERSION;
		break;
	case BINDER_SET_MAX_THREADS:
		// EMPTY
		break;
	case BINDER_SET_CONTEXT_MGR:
		mHandlerContextManager = handler;
		break;
	case BINDER_WRITE_READ:
		result = binder_write_read_local(handler, data);
		break;
	case BINDER_THREAD_EXIT:
		break;
	default:
		result = BAD_VALUE;
		break;
	}

	return result;
}

} // namespace android
