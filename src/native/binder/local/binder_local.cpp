
#define LOG_TAG "BinderLocal"

#include <stdint.h>

#include <utils/Errors.h>
#include <utils/KeyedVector.h>
#include <utils/Looper.h>

#include <binder/Parcel.h>
#include <private/binder/binder_module.h>

namespace android {
    
struct binder_entry {
    // server
    int                 id;
	sp<Looper>          revicerLoop;
    flat_binder_object  service;

    // client
	int      senderHandler;
	Parcel*  cache;
};

static Mutex mLock;
static KeyedVector<int, binder_entry> mServices;
static int  mHandlerContextManager = 0;
static int  mHandlerCounter = 0;

// ---------------------------------------------------------------------------
// Private API

static binder_entry* binder_lookupHandle_local(int handler)
{
    const ssize_t N = mServices.indexOfKey(handler);
    if (N < 0) {
        binder_entry e;
        memset(&e, 0x00, sizeof(e));
        e.id = -1;
        e.senderHandler = -1;
        mServices.add(handler, e);
    }
    
	return &(mServices.editValueFor(handler));
}

static status_t binder_registerService_local(int handler, binder_transaction_data& tr)
{
    status_t result = NO_ERROR;

    binder_entry* e = binder_lookupHandle_local(handler);
    if (e == NULL || e->revicerLoop == NULL) {
        return NO_INIT;
    }
    
    for (int i = 0; i < ((tr.offsets_size)/sizeof(binder_size_t)); ++i) {
        binder_size_t objOffset = ((binder_size_t *)(tr.data.ptr.offsets))[i];
        flat_binder_object* obj = (flat_binder_object*)((uint8_t *)(tr.data.ptr.buffer) + objOffset);
        if (obj->type == BINDER_TYPE_BINDER) {
            if (e->service.cookie == 0) {
                e->service = *obj;
                
            } else {
                AutoMutex _l(mLock);

                int newHandler = mHandlerCounter++;
                binder_entry* add = binder_lookupHandle_local(newHandler);
                if (add == NULL) return NO_MEMORY;
                
                add->id = newHandler;
                add->revicerLoop = e->revicerLoop;
                add->service = *obj;
                
                obj->type = BINDER_TYPE_HANDLE;
                obj->binder = 0;
                obj->handle = newHandler;
                obj->cookie = 0;
            }
        }
    }
    
    return result;
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

#define BINDER_CMD_SIZE    (sizeof(int32_t))
#define BINDER_TR_SIZE     (sizeof(binder_transaction_data))
#define BINDER_TIMEOUT_MS  (500)
    
static status_t binder_write_local(int handler, binder_write_read* pbwr, int& bNeedRead, int readTimeout)
{
    status_t result = NO_ERROR;
    
    bNeedRead   = 0;
    readTimeout = -1;
    
    if ((pbwr->write_buffer != 0) && (pbwr->write_size < BINDER_CMD_SIZE)) {
        bNeedRead++;;
        return NO_ERROR;
    }
    if  ((pbwr->write_buffer == 0) && (pbwr->write_size > 0)) {
        return BAD_VALUE;
    }

    while (pbwr->write_consumed < pbwr->write_size) {
        uintptr_t data = (uintptr_t)(pbwr->write_buffer + pbwr->write_consumed);
        size_t    size = pbwr->write_size - pbwr->write_consumed;
        if (size < BINDER_CMD_SIZE) {
            bNeedRead = 0;
            return NOT_ENOUGH_DATA;
        }
        
        int32_t cmd = *((int32_t *)data);
        pbwr->write_consumed += sizeof(int32_t);
        
        switch (cmd) {
            case BC_REPLY:
            {
                if (size < (BINDER_CMD_SIZE + BINDER_TR_SIZE)) return NOT_ENOUGH_DATA;

                binder_entry* e = binder_lookupHandle_local(handler);
                if (e == NULL || e->revicerLoop == NULL) return (NO_INIT);
                
                binder_transaction_data* tr = (binder_transaction_data *)(data + BINDER_CMD_SIZE);
                tr->target.handle = e->senderHandler;
                
            }
            // continue to send this out
            case BC_TRANSACTION:
            {
                if (size < (BINDER_CMD_SIZE + BINDER_TR_SIZE)) return NOT_ENOUGH_DATA;
                
                binder_transaction_data* tr = (binder_transaction_data *)(data + BINDER_CMD_SIZE);
                pbwr->write_consumed += sizeof(binder_transaction_data);
                
                binder_entry* et = binder_lookupHandle_local(tr->target.handle);
                if (et == NULL || et->revicerLoop == NULL) return (DEAD_OBJECT);
                
                if (tr->data.ptr.offsets && tr->offsets_size) {
                    result = binder_registerService_local(handler, *tr);
                    if (result) return result;
                }
                //tr->target.ptr = 0;
                
                Parcel* inData = new Parcel();
                if (!inData) return NO_MEMORY;
                
                inData->setData((uint8_t *)data, BINDER_CMD_SIZE + BINDER_TR_SIZE);
                
                Message evt(handler);
                sp<MessageHandler> trdata = new BinderMessageHandler(inData, et->cache, et->senderHandler);
                et->revicerLoop->sendMessage(trdata, evt);
                
                bNeedRead++;
                readTimeout = BINDER_TIMEOUT_MS;
            }
                break;
            case BC_ENTER_LOOPER:
            case BC_REGISTER_LOOPER:
                bNeedRead++;
                break;
            case BC_EXIT_LOOPER:
                bNeedRead = 0;
                return;
            case BC_ACQUIRE_RESULT:
            {
                int32_t value = *((int32_t *)(data + BINDER_CMD_SIZE));
                pbwr->write_consumed += sizeof(int32_t);
            }
                break;
            case BC_FREE_BUFFER:
            {
                uintptr_t value = *((uintptr_t *)(data + BINDER_CMD_SIZE));
                pbwr->write_consumed += sizeof(uintptr_t);
            }
                break;
            case BC_INCREFS:
            {
                int32_t value = *((int32_t *)(data + BINDER_CMD_SIZE));
                pbwr->write_consumed += sizeof(int32_t);
            }
                break;
            case BC_ACQUIRE:
            {
                int32_t value = *((int32_t *)(data + BINDER_CMD_SIZE));
                pbwr->write_consumed += sizeof(int32_t);
            }
                break;
            case BC_RELEASE:
            {
                int32_t value = *((int32_t *)(data + BINDER_CMD_SIZE));
                pbwr->write_consumed += sizeof(int32_t);
            }
                break;
            case BC_DECREFS:
            {
                int32_t value = *((int32_t *)(data + BINDER_CMD_SIZE));
                pbwr->write_consumed += sizeof(int32_t);
            }
                break;
            case BC_INCREFS_DONE:
            {
                uintptr_t value = *((uintptr_t *)(pbwr->write_buffer + pbwr->write_consumed));
                pbwr->write_consumed += sizeof(uintptr_t);
                value = *((uintptr_t *)(pbwr->write_buffer + pbwr->write_consumed));
                pbwr->write_consumed += sizeof(uintptr_t);
            }
                break;
            case BC_ACQUIRE_DONE:
            {
                uintptr_t value = *((uintptr_t *)(pbwr->write_buffer + pbwr->write_consumed));
                pbwr->write_consumed += sizeof(uintptr_t);
                value = *((uintptr_t *)(pbwr->write_buffer + pbwr->write_consumed));
                pbwr->write_consumed += sizeof(uintptr_t);
            }
                break;
            case BC_ATTEMPT_ACQUIRE:
            {
                int32_t value = *((int32_t *)(pbwr->write_buffer + pbwr->write_consumed));
                pbwr->write_consumed += sizeof(int32_t);
                value = *((int32_t *)(pbwr->write_buffer + pbwr->write_consumed));
                pbwr->write_consumed += sizeof(int32_t);
            }
                break;
            case BC_REQUEST_DEATH_NOTIFICATION:
            case BC_CLEAR_DEATH_NOTIFICATION:
            case BC_DEAD_BINDER_DONE:
                break;
            default:
                assert(0);
                break;
        } // switch
    } // while

    return result;
}

status_t binder_read_local(int handler, binder_write_read* pbwr, int readTimeout)
{
    status_t result = NO_ERROR;
    
    if ((pbwr->read_buffer == 0) || (pbwr->read_size == 0)) {
        return NO_ERROR;
    }
    int32_t* cmd = (int32_t *)(pbwr->read_buffer);

    binder_entry* e = binder_lookupHandle_local(handler);
    if (e == NULL || e->revicerLoop == NULL) return (NO_INIT);
    
    int ret = e->revicerLoop->pollOnce(readTimeout);
    if (Looper::POLL_TIMEOUT == ret) {
        (*cmd) = BR_DEAD_REPLY;
        return NO_ERROR;
    }
    
    if (e->cache != NULL && e->cache->dataSize() <= pbwr->read_size) {
        memcpy((void *)(pbwr->read_buffer), e->cache->data(), e->cache->dataSize());
        pbwr->read_consumed = e->cache->dataSize();
        binder_transaction_data* tr = (binder_transaction_data *)((uint8_t *)(pbwr->read_buffer) + sizeof(uint32_t));
        tr->target.ptr = (void *)(e->service.binder);
        tr->cookie = (void *)(e->service.cookie);
        
        if (BC_TRANSACTION == (*cmd)) {
            (*cmd) = BR_TRANSACTION;
            
            binder_entry* eSender = binder_lookupHandle_local(e->senderHandler);
            
            Parcel* inData = new Parcel();
            if (!inData) return NO_MEMORY;
            inData->writeInt32(BR_TRANSACTION_COMPLETE);
            
            Message evt(handler);
            sp<MessageHandler> trdata = new BinderMessageHandler(inData, eSender->cache, eSender->senderHandler);
            eSender->revicerLoop->sendMessage(trdata, evt);
            
        } else if (BC_REPLY == (*cmd)) {
            (*cmd) = BR_REPLY;
        }
    }
    
    if (e->cache) {
        delete (e->cache);
        e->cache = NULL;
    }

    return result;
}

status_t binder_write_read_local(int handler, void* data)
{
	status_t result = BAD_VALUE;
	int bNeedRead = 0;
    int readTimeout = -1;

	binder_write_read* pbwr = (binder_write_read*)data;
	if (!pbwr) return result;
    
    result = binder_write_local(handler, pbwr, bNeedRead, readTimeout);
    
    if (bNeedRead) {
        result = binder_read_local(handler, pbwr, readTimeout);
    }
    
	return result;
}

// ---------------------------------------------------------------------------
// Public API

int binder_open_local()
{
    AutoMutex _l(mLock);

	int handler = mHandlerCounter++;
	binder_entry* e = binder_lookupHandle_local(handler);
	if ((!e) || (e->revicerLoop != NULL)) {
		return (-1);
	}

    e->id = handler;
	e->revicerLoop = new Looper(true);
	if (e->revicerLoop == NULL) {
		return (-2);
	}

	return handler;
}

status_t binder_close_local(int handler)
{
    AutoMutex _l(mLock);

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
    
    if (handler == mHandlerContextManager) {
        handler = 0;
    }

	switch (cmd) {
	case BINDER_VERSION:
		*((int *)data) = BINDER_CURRENT_PROTOCOL_VERSION;
		break;
	case BINDER_SET_MAX_THREADS:
		// EMPTY
		break;
	case BINDER_SET_CONTEXT_MGR:
        {
            binder_entry* e = binder_lookupHandle_local(0);
            if ((e != NULL) && (e->revicerLoop != NULL)) {
                mHandlerContextManager = handler;
            } else {
                result = NO_INIT;
            }
        }
		break;
	case BINDER_WRITE_READ:
		result = binder_write_read_local(handler, data);
		break;
	case BINDER_THREAD_EXIT:
		break;
	default:
		result = INVALID_OPERATION;
		break;
	}

	return result;
}

} // namespace android
