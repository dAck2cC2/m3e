
#define LOG_TAG "BinderLocal"

#include <stdint.h>

#include <utils/Errors.h>
#include <utils/KeyedVector.h>
#include <utils/Looper.h>

#include <binder/Parcel.h>
#include <private/binder/binder_module.h>

#define BINDER_DEBUG  0


namespace android {
    
struct binder_entry {
#if  BINDER_DEBUG
    String16*  name;
#endif //  BINDER_DEBUG
    
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
            reinterpret_cast<RefBase::weakref_type*>(obj->binder)->incWeak((void *)0);
#if  BINDER_DEBUG
            int32_t   nameLen = *reinterpret_cast<const int32_t*>(tr.data.ptr.buffer);
            char16_t* nameBuf = (char16_t *)((uint8_t *)(tr.data.ptr.buffer) + sizeof(int32_t));
#endif // ç
            int newHandler = handler;
            if (e->service.cookie == 0) {
                e->service = *obj;
#if  BINDER_DEBUG
                e->name = new String16(nameBuf);
#endif // BINDER_DEBUG

            } else {
                AutoMutex _l(mLock);

                newHandler = mHandlerCounter++;
                binder_entry* add = binder_lookupHandle_local(newHandler);
                if (add == NULL) return NO_MEMORY;
                
                add->id = newHandler;
                add->revicerLoop = e->revicerLoop;
                add->service = *obj;
#if  BINDER_DEBUG
                add->name = new String16(nameBuf);
#endif  //  BINDER_DEBUG
            }
            
            obj->type = BINDER_TYPE_HANDLE;
            obj->binder = 0;
            obj->handle = newHandler;
            obj->cookie = 0;
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
    
static status_t binder_send_local(int hDst, int hSender, uint8_t* data, size_t size)
{
    status_t result = NO_ERROR;
    
    binder_entry* eDst = binder_lookupHandle_local(hDst);
    LOG_ALWAYS_FATAL_IF((eDst == NULL), "No object. %s:%d", __FILE__, __LINE__);
    if (eDst == NULL || eDst->revicerLoop == NULL) return (DEAD_OBJECT);
    
    Parcel* inData = new Parcel();
    LOG_ALWAYS_FATAL_IF((inData == NULL), "No memory when creating Parcel. %s:%d", __FILE__, __LINE__);
    if (!inData) return NO_MEMORY;
    
    inData->setData((uint8_t *)data, size);
    
    Message evt(hSender);
    sp<MessageHandler> msg = new BinderMessageHandler(inData, eDst->cache, eDst->senderHandler);
    eDst->revicerLoop->sendMessage(msg, evt);

    return result;
}

static status_t binder_reply_local(int handler, uint8_t* data, size_t size)
{
    status_t result = NO_ERROR;
    
    binder_entry* e = binder_lookupHandle_local(handler);
    LOG_ALWAYS_FATAL_IF((e == NULL), "Invalid handler. %s:%d", __FILE__, __LINE__);

    result = binder_send_local(e->senderHandler, handler, data, size);
    
    return result;
}
    
static status_t binder_write_local(int handler, binder_write_read* pbwr, int& bNeedRead, int readTimeout)
{
    status_t result = NO_ERROR;
    
    bNeedRead   = 0;
    readTimeout = -1;
    
    if ((pbwr->write_buffer != 0) && (pbwr->write_size < BINDER_CMD_SIZE)) {
        bNeedRead++;
        return NO_ERROR;
    }
    if  ((pbwr->write_buffer == 0) && (pbwr->write_size > 0)) {
        return BAD_VALUE;
    }

    while (pbwr->write_consumed < pbwr->write_size) {
        uintptr_t data = (uintptr_t)(pbwr->write_buffer + pbwr->write_consumed);
        size_t    size = pbwr->write_size - pbwr->write_consumed;
        LOG_ALWAYS_FATAL_IF((size < BINDER_CMD_SIZE), "Wrong data format. %s:%d", __FILE__, __LINE__);
        if (size < BINDER_CMD_SIZE) {
            bNeedRead = 0;
            return NOT_ENOUGH_DATA;
        }
        
        int32_t* cmd = ((int32_t *)data);
        pbwr->write_consumed += sizeof(int32_t);
        
        switch (*cmd) {
            case BC_REPLY: {
                LOG_ALWAYS_FATAL_IF(size < (BINDER_CMD_SIZE + BINDER_TR_SIZE), "Wrong data format. %s:%d", __FILE__, __LINE__);
                (*cmd) = BR_REPLY;

                binder_entry* e = binder_lookupHandle_local(handler);
                if (e == NULL || e->revicerLoop == NULL) return (NO_INIT);
                
                binder_transaction_data* tr = (binder_transaction_data *)(data + BINDER_CMD_SIZE);
                pbwr->write_consumed += sizeof(binder_transaction_data);
                tr->target.handle = e->senderHandler;
                
                void* copyData = malloc(tr->data_size);
                LOG_ALWAYS_FATAL_IF((copyData == NULL), "No memory when creating data copy. %s:%d", __FILE__, __LINE__);
                if (!copyData) return NO_MEMORY;
                
                memcpy(copyData, tr->data.ptr.buffer, tr->data_size);
                tr->data.ptr.buffer = copyData;
                
                if (tr->data.ptr.offsets && tr->offsets_size) {
                    result = binder_registerService_local(handler, *tr);
                    if (result) return result;
                }
                
                result = binder_send_local(tr->target.handle, handler, (uint8_t *)data, BINDER_CMD_SIZE + BINDER_TR_SIZE);
            }
                break;
            case BC_TRANSACTION: {
                LOG_ALWAYS_FATAL_IF(size < (BINDER_CMD_SIZE + BINDER_TR_SIZE), "Wrong data format. %s:%d", __FILE__, __LINE__);
                (*cmd) = BR_TRANSACTION;

                binder_transaction_data* tr = (binder_transaction_data *)(data + BINDER_CMD_SIZE);
                pbwr->write_consumed += sizeof(binder_transaction_data);

                void* copyData = malloc(tr->data_size);
                LOG_ALWAYS_FATAL_IF((copyData == NULL), "No memory when creating data copy. %s:%d", __FILE__, __LINE__);
                if (!copyData) return NO_MEMORY;
                memcpy(copyData, tr->data.ptr.buffer, tr->data_size);
                tr->data.ptr.buffer = copyData;

                if (tr->data.ptr.offsets && tr->offsets_size) {
                    result = binder_registerService_local(handler, *tr);
                    if (result) return result;
                }
                
                result = binder_send_local(tr->target.handle, handler, (uint8_t *)data, BINDER_CMD_SIZE + BINDER_TR_SIZE);
                if (NO_ERROR == result) {
                    bNeedRead++;
                    readTimeout = BINDER_TIMEOUT_MS;
                }
            }
                break;
            case BC_ENTER_LOOPER:
            case BC_REGISTER_LOOPER:
                bNeedRead++;
                break;
            case BC_EXIT_LOOPER: {
                AutoMutex _l(mLock);

                binder_entry* e = binder_lookupHandle_local(handler);
                if (e == NULL || e->revicerLoop == NULL) return (NO_INIT);
                sp<Looper> loop = e->revicerLoop;
                
                for (size_t i = mServices.size(); i > -1; --i) {
                    if (loop == mServices.valueAt(i).revicerLoop) {
                        binder_entry& del = mServices.editValueAt(i);
                        del.revicerLoop = NULL;
                        del.id = -1;
                        
                        if (del.service.binder) {
                            reinterpret_cast<RefBase::weakref_type*>(del.service.binder)->decWeak((void *)0);
                            del.service.binder = 0;
                            del.service.cookie = 0;
                        }
                        
                        mServices.removeItemsAt(i);
                    }
                }

                bNeedRead = 0;
                return NO_ERROR;
            }
                break;
            case BC_FREE_BUFFER: {
                LOG_ALWAYS_FATAL_IF(size < (BINDER_CMD_SIZE + sizeof(uintptr_t)), "Wrong data format. %s:%d", __FILE__, __LINE__);

                uintptr_t buf = *((uintptr_t *)(data + BINDER_CMD_SIZE));
                pbwr->write_consumed += sizeof(uintptr_t);
                
                if (buf != 0) {
                    free((void*)buf);
                }
            }
                break;
            case BC_ACQUIRE:
            case BC_INCREFS: {
                LOG_ALWAYS_FATAL_IF(size < (BINDER_CMD_SIZE + sizeof(int32_t)), "Wrong data format. %s:%d", __FILE__, __LINE__);
                if (BC_INCREFS == (*cmd)) {
                    (*cmd) = BR_INCREFS;
                } else {
                    (*cmd) = BR_ACQUIRE;
                }

                int32_t dstHandler = *((int32_t *)(data + BINDER_CMD_SIZE));
                pbwr->write_consumed += sizeof(int32_t);
                result = binder_send_local(dstHandler, handler, (uint8_t *)data, BINDER_CMD_SIZE + sizeof(int32_t));
                if (NO_ERROR == result) {
                    bNeedRead++;
                    readTimeout = BINDER_TIMEOUT_MS;
                }
            }
                break;
            case BC_ACQUIRE_DONE:
            case BC_INCREFS_DONE: {
                uintptr_t value = *((uintptr_t *)(pbwr->write_buffer + pbwr->write_consumed));
                pbwr->write_consumed += sizeof(uintptr_t);
                value = *((uintptr_t *)(pbwr->write_buffer + pbwr->write_consumed));
                pbwr->write_consumed += sizeof(uintptr_t);
                
                (*cmd) = BR_OK;
                result = binder_reply_local(handler, (uint8_t *)data, BINDER_CMD_SIZE);
            }
                break;

            case BC_RELEASE:
            case BC_DECREFS: {
                LOG_ALWAYS_FATAL_IF(size < (BINDER_CMD_SIZE + sizeof(int32_t)), "Wrong data format. %s:%d", __FILE__, __LINE__);
                if (BC_DECREFS == (*cmd)) {
                    (*cmd) = BR_DECREFS;
                } else {
                    (*cmd) = BR_RELEASE;
                }

                int32_t dstHandler = *((int32_t *)(data + BINDER_CMD_SIZE));
                pbwr->write_consumed += sizeof(int32_t);
                result = binder_send_local(dstHandler, handler, (uint8_t *)data, BINDER_CMD_SIZE + sizeof(int32_t));
            }
                break;
            case BC_ACQUIRE_RESULT: {
                int32_t dstHandler = *((int32_t *)(data + BINDER_CMD_SIZE));
                pbwr->write_consumed += sizeof(int32_t);
            }
                break;
            case BC_ATTEMPT_ACQUIRE: {
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
                LOG_ALWAYS_FATAL("Unknown command %s:%d", __FILE__, __LINE__);
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
        pbwr->read_consumed += sizeof(int32_t);
        
        switch (*cmd) {
            case BR_REPLY:
            case BR_TRANSACTION: {
                binder_transaction_data* tr = (binder_transaction_data *)(pbwr->read_buffer + BINDER_CMD_SIZE);
                tr->target.ptr = (void *)(e->service.binder);
                tr->cookie = (void *)(e->service.cookie);
                pbwr->read_consumed += sizeof(binder_transaction_data);
                
                if (BR_TRANSACTION == (*cmd)) {
                    binder_entry* eSender = binder_lookupHandle_local(e->senderHandler);
                    
                    Parcel* inData = new Parcel();
                    if (!inData) return NO_MEMORY;
                    inData->writeInt32(BR_TRANSACTION_COMPLETE);
                    
                    Message evt(handler);
                    sp<MessageHandler> trdata = new BinderMessageHandler(inData, eSender->cache, eSender->senderHandler);
                    eSender->revicerLoop->sendMessage(trdata, evt);
                    
                }
            }
                break;
            case BR_ACQUIRE:
            case BR_RELEASE:
            case BR_INCREFS:
            case BR_DECREFS: {
                int32_t* hTarget = (int32_t *)(pbwr->read_buffer + BINDER_CMD_SIZE);
                binder_entry* e = binder_lookupHandle_local((*hTarget));
                if ((e) && (e->service.binder) && (e->service.cookie)) {
                    binder_uintptr_t* ptr = (binder_uintptr_t *)(pbwr->read_buffer + BINDER_CMD_SIZE);
                    (*ptr++) = e->service.binder;
                    (*ptr)   = e->service.cookie;
                    pbwr->read_consumed += 2 * sizeof(binder_uintptr_t);
                } else {
                    LOG_ALWAYS_FATAL("No object %s:%d", __FILE__, __LINE__);
                    (*cmd) = BR_NOOP;
                }
            }
                break;
            case BR_FINISHED:
            case BR_OK:
            case BR_TRANSACTION_COMPLETE:
                break;
            default:
                LOG_ALWAYS_FATAL("Unknown command %s:%d", __FILE__, __LINE__);
                break;
        } // switch
    } // if
    
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
    LOG_ALWAYS_FATAL_IF((e == NULL), "Failed to create binder entry. %s:%d", __FILE__, __LINE__);
    LOG_ALWAYS_FATAL_IF((e->revicerLoop != NULL), "The handler is already opened. %s:%d", __FILE__, __LINE__);
	if ((!e) || (e->revicerLoop != NULL)) {
		return (-1);
	}

    e->id = handler;
	e->revicerLoop = new Looper(true);
    LOG_ALWAYS_FATAL_IF((e->revicerLoop == NULL), "Failed to create receiver loop. %s:%d", __FILE__, __LINE__);
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
    LOG_ALWAYS_FATAL_IF((e == NULL), "Handler is already closed. %s:%d", __FILE__, __LINE__);
	if (e) {
        if (e->revicerLoop != NULL) {
            int32_t finish = BR_FINISHED;
            binder_send_local(handler, -1, (uint8_t *)(&finish), sizeof(finish));
        }
        
#if BINDER_DEBUG
        if (e->name) {
            delete (e->name);
            e->name = NULL;
        }
#endif // BINDER_DEBUG
		result = NO_ERROR;
	}

	return result;
}

status_t binder_ioctl_local(int handler, int cmd, void* data)
{
	status_t result = NO_ERROR;

    LOG_ALWAYS_FATAL_IF((handler < 0), "Invalid handler %s:%d", __FILE__, __LINE__);
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
        LOG_ALWAYS_FATAL("Invalid operation %s:%d", __FILE__, __LINE__);
		result = INVALID_OPERATION;
		break;
	}

	return result;
}

} // namespace android
