
#define LOG_TAG "BinderLocal"

#include <stdint.h>

#include <utils/Errors.h>
#include <utils/KeyedVector.h>
#include <utils/Looper.h>

#include <binder/Parcel.h>
#include <private/binder/binder_module.h>

#define BINDER_DEBUG  0

namespace android {
    
// ---------------------------------------------------------------------------
// Private API
    
#define BINDER_CMD_SIZE    (sizeof(int32_t))
#define BINDER_TR_SIZE     (sizeof(binder_transaction_data))
#define BINDER_TIMEOUT_MS  (500)
    
class CBinderEntry : public RefBase
{
public:
#if BINDER_DEBUG
    String16 mName;
#endif // BINDER_DEBUG
    
    CBinderEntry(int handler)
    : mHandler(handler),
    mLooper(),
    mMsgSender(-1),
    mMsgCache(NULL)
    { };
    
    ~CBinderEntry() { mLooper = NULL; };
    void SetLooper(const sp<Looper>& looper) {mLooper = looper;};
    
    status_t WriteRead(void* data)
    {
        status_t result = BAD_VALUE;
        int bNeedRead = 0;
        int readTimeout = -1;
        
        binder_write_read* pbwr = (binder_write_read*)data;
        if (!pbwr) return result;
        
        result = Write(pbwr, bNeedRead, readTimeout);
        
        if (bNeedRead) {
            result = Read(pbwr, readTimeout);
        }
        
        return result;
    }
    
    status_t Push(Parcel* data, int sender)
    {
        status_t result = NO_ERROR;

        LOG_ALWAYS_FATAL_IF((mLooper == NULL), "No Message Looper. %s:%d", __FILE__, __LINE__);
        if (mLooper == NULL) return FAILED_TRANSACTION;
        
        Message evt(sender);
        sp<MessageHandler> msg = new BinderMessage(data, mMsgCache, mMsgSender);
        LOG_ALWAYS_FATAL_IF((msg == NULL), "No memory when creating Message. %s:%d", __FILE__, __LINE__);
        if (msg == NULL) return NO_MEMORY;

        mLooper->sendMessage(msg, evt);
        
        return result;
    }
    
private:
    status_t Write(binder_write_read* pbwr, int& bNeedRead, int readTimeout)
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
                    
                    binder_transaction_data* tr = (binder_transaction_data *)(data + BINDER_CMD_SIZE);
                    pbwr->write_consumed += sizeof(binder_transaction_data);
                    tr->target.handle = mMsgSender;
                    
                    void* copyData = malloc(tr->data_size);
                    LOG_ALWAYS_FATAL_IF((copyData == NULL), "No memory when creating data copy. %s:%d", __FILE__, __LINE__);
                    if (!copyData) return NO_MEMORY;
                    
                    memcpy(copyData, tr->data.ptr.buffer, tr->data_size);
                    tr->data.ptr.buffer = copyData;
                    
                    if (tr->data.ptr.offsets && tr->offsets_size) {
                        result = RegisterBn(*tr);
                        if (result) return result;
                    }
                    
                    result = Send(mMsgSender, (uint8_t *)data, BINDER_CMD_SIZE + BINDER_TR_SIZE);
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
                        result = RegisterBn(*tr);
                        if (result) return result;
                    }
                    
                    result = Send(tr->target.handle, (uint8_t *)data, BINDER_CMD_SIZE + BINDER_TR_SIZE);
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
                    ExitLoop();
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
                    result = Send(dstHandler, (uint8_t *)data, BINDER_CMD_SIZE + sizeof(int32_t));
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
                    result = Reply((uint8_t *)data, BINDER_CMD_SIZE);
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
                    result = Send(dstHandler, (uint8_t *)data, BINDER_CMD_SIZE + sizeof(int32_t));
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
    } // Write
    
    status_t Read(binder_write_read* pbwr, int readTimeout)
    {
        status_t result = NO_ERROR;
        
        if ((pbwr->read_buffer == 0) || (pbwr->read_size == 0)) {
            return NO_ERROR;
        }
        int32_t* cmd = (int32_t *)(pbwr->read_buffer);
        
        LOG_ALWAYS_FATAL_IF((mLooper == NULL), "No Message Looper. %s:%d", __FILE__, __LINE__);
        if (mLooper == NULL) return FAILED_TRANSACTION;
        
        int ret = mLooper->pollOnce(readTimeout);
        if (Looper::POLL_TIMEOUT == ret) {
            (*cmd) = BR_DEAD_REPLY;
            return NO_ERROR;
        }
        
        if (mMsgCache != NULL && mMsgCache->dataSize() <= pbwr->read_size) {
            memcpy((void *)(pbwr->read_buffer), mMsgCache->data(), mMsgCache->dataSize());
            pbwr->read_consumed += sizeof(int32_t);
            
            switch (*cmd) {
                case BR_REPLY:
                case BR_TRANSACTION: {
                    binder_transaction_data* tr = (binder_transaction_data *)(pbwr->read_buffer + BINDER_CMD_SIZE);
                    pbwr->read_consumed += sizeof(binder_transaction_data);

                    if (mBnList.indexOfKey(tr->target.handle) >= 0) {
                        flat_binder_object& obj = mBnList.editValueFor(tr->target.handle);
                        tr->target.ptr = (void *)(obj.binder);
                        tr->cookie = (void *)(obj.cookie);
                    }
                    
                    if (BR_TRANSACTION == (*cmd)) {
                        int32_t complete = BR_TRANSACTION_COMPLETE;
                        Send(mMsgSender, (uint8_t *)(&complete), sizeof(complete));
                    }
                }
                    break;
                case BR_ACQUIRE:
                case BR_RELEASE:
                case BR_INCREFS:
                case BR_DECREFS: {
                    int32_t* hTarget = (int32_t *)(pbwr->read_buffer + BINDER_CMD_SIZE);
                    if (mBnList.indexOfKey(*hTarget) >= 0) {
                        flat_binder_object& obj = mBnList.editValueFor(*hTarget);
                        binder_uintptr_t* ptr = (binder_uintptr_t *)(pbwr->read_buffer + BINDER_CMD_SIZE);
                        (*ptr++) = obj.binder;
                        (*ptr)   = obj.cookie;
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
        
        if (mMsgCache) {
            delete (mMsgCache);
            mMsgCache = NULL;
        }
        
        return result;
    } // Read

    status_t Reply(uint8_t* data, size_t size)
    {
        return Send(mMsgSender, data, size);
    }

    
    status_t RegisterBn(binder_transaction_data& tr);
    status_t Send(int hDst, uint8_t* data, size_t size);
    status_t ExitLoop();
    
private:
    class BinderMessage : public MessageHandler
    {
    public:
        BinderMessage(Parcel* data, Parcel*& out, int& handler) : src(data), dst(out), sender(handler) {};
        
        virtual void handleMessage(const Message& evt) {
            sender = evt.what;
            dst = src;
        };
    private:
        Parcel*   src;
        Parcel*&  dst;
        int&      sender;
    }; // BinderMessage
    
    // server
    KeyedVector<int, flat_binder_object>  mBnList;
    int         mHandler;
    sp<Looper>  mLooper;
    
    // Message
    int         mMsgSender;
    Parcel*     mMsgCache;
}; // CBinderEntry

static Mutex                                gServiceLock;
static KeyedVector<int, sp<CBinderEntry> >  gServiceList;
static int  gHandlerContextManager = 0;
static int  gHandlerCounter = 0;
    
static sp<CBinderEntry> binder_lookupEntry_local(int handler)
{
    const ssize_t N = gServiceList.indexOfKey(handler);
    if (N < 0) {
        sp<CBinderEntry> e = new CBinderEntry(handler);
        gServiceList.add(handler, e);
    }
    
    return (gServiceList.editValueFor(handler));
}
    
status_t CBinderEntry::RegisterBn(binder_transaction_data& tr)
{
    status_t result = NO_ERROR;
    
    for (int i = 0; i < ((tr.offsets_size)/sizeof(binder_size_t)); ++i) {
        binder_size_t objOffset = ((binder_size_t *)(tr.data.ptr.offsets))[i];
        flat_binder_object* obj = (flat_binder_object*)((uint8_t *)(tr.data.ptr.buffer) + objOffset);
        if (obj->type == BINDER_TYPE_BINDER) {
            reinterpret_cast<RefBase::weakref_type*>(obj->binder)->incWeak((void *)0);
            
#if  BINDER_DEBUG
            int32_t   nameLen = *reinterpret_cast<const int32_t*>(tr.data.ptr.buffer);
            char16_t* nameBuf = (char16_t *)((uint8_t *)(tr.data.ptr.buffer) + sizeof(int32_t));
#endif // ç
            int handlerBp = mHandler;
            if (mBnList.isEmpty()) {
                handlerBp = mHandler;
#if  BINDER_DEBUG
                mName = new String16(nameBuf);
#endif // BINDER_DEBUG
            } else {
                handlerBp = gHandlerCounter++;
                sp<CBinderEntry> add = binder_lookupEntry_local(handlerBp);
                if (add == NULL) return NO_MEMORY;
                add->SetLooper(mLooper);
#if  BINDER_DEBUG
                add->mName = new String16(nameBuf);
#endif  //  BINDER_DEBUG
            }
            
            mBnList.add(handlerBp, *obj);
            
            obj->type = BINDER_TYPE_HANDLE;
            obj->binder = 0;
            obj->handle = handlerBp;
            obj->cookie = 0;
        }
    }
    
    return result;
}
    
status_t CBinderEntry::Send(int hDst, uint8_t* data, size_t size)
{
    status_t result = NO_ERROR;
    
    sp<CBinderEntry> eDst = binder_lookupEntry_local(hDst);
    LOG_ALWAYS_FATAL_IF((eDst == NULL), "No object. %s:%d", __FILE__, __LINE__);
    if (eDst == NULL) return (DEAD_OBJECT);
    
    Parcel* msg = new Parcel();
    LOG_ALWAYS_FATAL_IF((msg == NULL), "No memory when creating Parcel. %s:%d", __FILE__, __LINE__);
    if (!msg) return NO_MEMORY;
    
    msg->setData((uint8_t *)data, size);
    result = eDst->Push(msg, mHandler);
    
    return result;
}

status_t CBinderEntry::ExitLoop()
{
    status_t result = NO_ERROR;
    
    mLooper = NULL;
    
    for (size_t i = 0; i < mBnList.size(); ++i) {
        // remove the service for it
        int handler = mBnList.keyAt(i);
        if (handler != mHandler) {
            AutoMutex _l(gServiceLock);

            sp<CBinderEntry> subEntry = gServiceList.editValueFor(handler);
            if (subEntry != NULL) {
                subEntry->SetLooper(NULL);
                subEntry = NULL;
            }
            gServiceList.removeItem(handler);
        }
        
        // remove the binder native for it
        flat_binder_object obj = mBnList.editValueAt(i);
        if (obj.binder) {
            reinterpret_cast<RefBase::weakref_type*>(obj.binder)->decWeak((void *)0);
            obj.binder = 0;
            obj.cookie = 0;
        }
    }
    
    mBnList.clear();

    return result;
}

// ---------------------------------------------------------------------------
// Public API

int binder_open_local()
{
    AutoMutex _l(gServiceLock);
    
    int handler = gHandlerCounter++;
    sp<CBinderEntry> e = binder_lookupEntry_local(handler);
    LOG_ALWAYS_FATAL_IF((e == NULL), "Failed to create binder entry. %s:%d", __FILE__, __LINE__);
    if (e == NULL) {
        return (-1);
    }

    e->SetLooper(new Looper(true));

    return handler;
}

status_t binder_close_local(int handler)
{
    AutoMutex _l(gServiceLock);
    
    status_t result = NO_ERROR;
    sp<CBinderEntry> e = binder_lookupEntry_local(handler);
    LOG_ALWAYS_FATAL_IF((e == NULL), "Handler is already closed. %s:%d", __FILE__, __LINE__);
    if (e != NULL) {
        Parcel finish;
        finish.writeInt32(BR_FINISHED);
        e->Push(&finish, -1);
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
    
    if (handler == gHandlerContextManager) {
        handler = 0;
    }

	switch (cmd) {
	case BINDER_VERSION:
		*((int *)data) = BINDER_CURRENT_PROTOCOL_VERSION;
		break;
	case BINDER_SET_MAX_THREADS:
		// EMPTY
		break;
	case BINDER_SET_CONTEXT_MGR: {
        gHandlerContextManager = handler;
    }
		break;
    case BINDER_WRITE_READ: {
        sp<CBinderEntry> e = binder_lookupEntry_local(handler);
        LOG_ALWAYS_FATAL_IF((e == 0), "Invalid handler %s:%d", __FILE__, __LINE__);

        if (e != NULL) {
            result = e->WriteRead(data);
        } else {
            result = DEAD_OBJECT;
        }
    }
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
