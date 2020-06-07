/******************************************************************************
handler 0 : gProcess
handler 1 : Service Manager thread STL
-------------------------------------------------------------------------------
The handler 0 and 1 are created by Service Manager thread. The handler 0 is 
also the one for Bp of ServiceManager. So, we replace the 1 to 0 in driver 
level. It means the ServiceManager thread will pass the handler 1 to driver, 
but it is actually watching the Binder Entry of handler 0 but not 1. The Binder
Entry of handler 1 is not used at all.
*/

/******************************************************************************
handler 2 ~ gDeamonCount : Deamon Service thread STL
-------------------------------------------------------------------------------
The native binder may be passed to driver through a non-IPCThread, which means 
it has no thread to watch the Binder Entry. 

e.g. 
	ACodec::UninitializedState::onAllocateComponent()
	err = omx->allocateNode(componentName.c_str(), observer, &mCodec->mNodeBinder, &node);
It passes native binder of observer from non-IPCThread.

So, we need a common thread to watch Binder Entry for such kind of native binder.
*/

#define LOG_TAG "BinderLocal"

#include <stdint.h>

#include <utils/Errors.h>
#include <utils/KeyedVector.h>
#include <utils/Looper.h>
#include <utils/Vector.h>
#include <utils/String8.h>

#include <binder/Parcel.h>
#include <private/binder/binder_module.h>

#define BINDER_DEBUG  0

namespace android {
    
// ---------------------------------------------------------------------------
// Private API

class IBinderEntry : public RefBase
{
public:
    IBinderEntry()  {};
    ~IBinderEntry() {};
    
	virtual void SetName(const char* name) = 0;
    virtual void SetLooper(const sp<Looper>& looper) = 0;
	virtual sp<Looper> GetLooper() const = 0;
	virtual int  GetHandler() const = 0;
	virtual int  AddNativeBinder(const int& hProxy, const flat_binder_object& binder) = 0;
	virtual int  FindNativeBinder(const uintptr_t& cookie) = 0;
    virtual void CacheMessage(Parcel* msg, int sender) = 0;
    virtual void SetParentHandler(int handler) = 0;
    virtual int  GetParentHandler() const = 0;
    
    virtual status_t WriteRead(void* data) = 0;
    virtual status_t Push(Parcel* data, int sender) = 0;
    
    virtual void AddDeathNotify(int handle, uintptr_t proxy) = 0;
    virtual void DelDeathNotify(int handle, uintptr_t proxy) = 0;
    
    virtual void Exit() = 0;
}; // IBinderEntry
  
static Mutex                                gServiceLock;
static KeyedVector<int, sp<IBinderEntry> >  gServiceList;
static int                                  gHandlerContextManager = 0;
static int                                  gHandlerCounter = 0;

static sp<IBinderEntry> binder_lookupEntry_local(int handler);

#define BINDER_DEAMON_START   (2)
static int gDeamonCount = 1;
static sp<IBinderEntry> binder_lookupEntry_deamon();
static int binder_lookupProxy_deamon(uintptr_t cookie);

// ---------------------------------------------------------------------------
// Implementation
    
#define BINDER_CMD_SIZE    (sizeof(int32_t))
#define BINDER_TR_SIZE     (sizeof(binder_transaction_data))
#define BINDER_TIMEOUT_MS  (500)
    
class CBinderEntry : public IBinderEntry
{
public:
#if BINDER_DEBUG
    String16 mName;
#endif // BINDER_DEBUG
    
    CBinderEntry(int handler)
    : mHandler(handler), mhParent(-1), mLooper(), mMsgSender(-1), mMsgCache(NULL)
    { /* empty */ };
    
    ~CBinderEntry() {
        mLooper = NULL;
    };

	virtual void SetName(const char* name) { mName = name; };
    virtual int  GetParentHandler() const { return mhParent; };
    virtual void SetParentHandler(int handler) { mhParent = handler; };
    virtual void SetLooper(const sp<Looper>& looper) {mLooper = looper;};
	virtual sp<Looper> GetLooper() const { return mLooper; };
	virtual int  GetHandler() const { return mHandler; };
	virtual int  AddNativeBinder(const int& hProxy, const flat_binder_object& binder) { return mBnList.add(hProxy, binder); };

	virtual int  FindNativeBinder(const uintptr_t& cookie) 
	{
		int hProxy = -1;

		for (int i = 0; i < mBnList.size(); ++i) {
			if (mBnList[i].cookie == cookie) {
				hProxy = mBnList.keyAt(i);
				break;
			}
		}

		return (hProxy);
	};

    // TODO
    // When the client has 2 or more Binder Proxy, also register death notification for each,
    // unregistering one of them will remove all the notification.
    virtual void AddDeathNotify(int handle, uintptr_t proxy)
    {
        AutoMutex _l(mBpLock);
        mBpList.add(handle, proxy);
    };
    virtual void DelDeathNotify(int handle, uintptr_t proxy)
    {
        AutoMutex _l(mBpLock);
        if (mBpList.indexOfKey(handle) > -1) {
            mBpList.removeItem(handle);
        }
    };
    
    virtual void Exit()
    {
        for (size_t i = 0; i < mBnList.size(); ++i) {
            // remove handler from service list
            int handler = mBnList.keyAt(i);
            if (handler != mHandler) {
                if (gServiceList.indexOfKey(handler) >= 0) {
                    sp<IBinderEntry> subEntry = gServiceList.editValueFor(handler);
                    LOG_ALWAYS_FATAL_IF((subEntry == NULL), "Handler[%d] is impossible disappeared. (-_-)!!! %s:%d", handler, __FILE__, __LINE__);
                    if (subEntry != NULL) {
                        subEntry->SetLooper(NULL);
                        subEntry = NULL;
                    }
                    gServiceList.removeItem(handler);
                }
            }
            
            // release the reference of native binder
            flat_binder_object obj = mBnList.editValueAt(i);
            if (obj.hdr.type == BINDER_TYPE_BINDER  && obj.binder && obj.cookie) {
				//reinterpret_cast<IBinder*>(obj.cookie)->decStrong((void *)0);
                reinterpret_cast<RefBase::weakref_type*>(obj.binder)->decWeak((void *)0);
                obj.binder = 0;
                obj.cookie = 0;
            }
        }
        mBnList.clear();
        
        // death notification
        for (size_t i = 0; i < mBpList.size(); ++i) {
            int handler = mBpList.keyAt(i);
            uintptr_t proxy = mBpList.valueAt(i);
            
            if (gServiceList.indexOfKey(handler) >= 0) {
                sp<IBinderEntry> eProxy = gServiceList.editValueFor(handler);
                ALOGE_IF((eProxy == NULL), "Handler[%d] is impossible disappeared. (-_-)!!! %s:%d", handler, __FILE__, __LINE__);

                if (eProxy != NULL) {
                    Parcel* dead = new Parcel;
                    dead->writeInt32(BR_DEAD_BINDER);
                    dead->write((void *)&proxy, sizeof(proxy));
                    status_t result = eProxy->Push(dead, mHandler);
                    if (NO_ERROR != result) delete dead;
                }
            }
        }
        mBpList.clear();
    }
    
    virtual void CacheMessage(Parcel* msg, int sender)
    {
        mMsgCache  = msg;
        mMsgSender = sender;
    };
    
    virtual status_t WriteRead(void* data)
    {
        status_t result = NO_ERROR;
        int bNeedRead = 0;
        int readTimeout = -1;
        
        binder_write_read* pbwr = (binder_write_read*)data;
        LOG_ALWAYS_FATAL_IF((pbwr == NULL), "Handler[%d] Data is empty. %s:%d", mHandler, __FILE__, __LINE__);
        if (pbwr == NULL) return BAD_VALUE;
        
        result = Write(pbwr, bNeedRead, readTimeout);
        
        if (bNeedRead) {
            result = Read(pbwr, readTimeout);
        }
        
        return result;
    }
    
    virtual status_t Push(Parcel* data, int sender)
    {
        LOG_ALWAYS_FATAL_IF((mLooper == NULL), "Handler[%d] No Message Looper. %s:%d", mHandler, __FILE__, __LINE__);
        if (mLooper == NULL) return FAILED_TRANSACTION;
        
        sp<MessageHandler> msg;
        if (mhParent == -1) {
            msg = new BinderMessage(data, this);
        } else {
            sp<IBinderEntry> parent = binder_lookupEntry_local(mhParent);
            ALOGE_IF((parent == NULL), "Handler[%d] is dead. %s:%d", mhParent, __FILE__, __LINE__);
            if (parent == NULL) return DEAD_OBJECT;
            
            msg = new BinderMessage(data, parent.get());
        }
        LOG_ALWAYS_FATAL_IF((msg == NULL), "Handler[%d] No memory when creating Message. %s:%d", mHandler, __FILE__, __LINE__);
        if (msg == NULL) return NO_MEMORY;

        Message evt(sender);
        mLooper->sendMessage(msg, evt);
        
        return NO_ERROR;
    }
    
private:
    status_t Write(binder_write_read* pbwr, int& bNeedRead, int& readTimeout)
    {
        status_t result = NO_ERROR;
        
        bNeedRead   = 0;
        readTimeout = -1;
        
        // Nothing to write, read only.
        if ((pbwr->write_buffer != 0) && (pbwr->write_size < BINDER_CMD_SIZE)) {
            bNeedRead++;
            return NO_ERROR;
        }
        
        // Something wrong with the writing data. Do we need to read ? No, currently.
        if  ((pbwr->write_buffer == 0) && (pbwr->write_size > 0)) {
            LOG_ALWAYS_FATAL_IF((pbwr->write_buffer == 0), "Handler[%d] Wrong data. %s:%d", mHandler, __FILE__, __LINE__);
            return BAD_VALUE;
        }
        
        while (pbwr->write_consumed < pbwr->write_size) {
            uintptr_t data = (uintptr_t)(pbwr->write_buffer + pbwr->write_consumed);
            size_t    size = pbwr->write_size - pbwr->write_consumed;
            
            // Do not trust the data for reading when something wrong.
            LOG_ALWAYS_FATAL_IF((size < BINDER_CMD_SIZE), "Handler[%d] Wrong data format. %s:%d", mHandler, __FILE__, __LINE__);
            if (size < BINDER_CMD_SIZE) {
                bNeedRead = 0;
                return NOT_ENOUGH_DATA;
            }
            
            int32_t* cmd = ((int32_t *)data);
            pbwr->write_consumed += sizeof(int32_t);
            
            switch (*cmd) {
                case BC_TRANSACTION:
                case BC_REPLY: {
                    LOG_ALWAYS_FATAL_IF(size < (BINDER_CMD_SIZE + BINDER_TR_SIZE), "Handler[%d] Wrong data format. %s:%d", mHandler, __FILE__, __LINE__);
                    
                    binder_transaction_data* tr = (binder_transaction_data *)(data + BINDER_CMD_SIZE);
                    pbwr->write_consumed += sizeof(binder_transaction_data);
                    
                    // reply to the previous sender
                    //tr->target.handle = mMsgSender;
                    
                    // the data will be released by caller, we have to make a copy for receiver.
					// this new copy should be released by BC_FREE_BUFFER.
                    void* copyData = malloc(tr->data_size);
                    LOG_ALWAYS_FATAL_IF((copyData == NULL), "Handler[%d] No memory when creating data copy. %s:%d", mHandler, __FILE__, __LINE__);
                    if (copyData == NULL) return NO_MEMORY;
                    memcpy(copyData, (void *)tr->data.ptr.buffer, tr->data_size);
                    tr->data.ptr.buffer = (binder_uintptr_t)copyData;
                    
                    // map the native binder to proxy
                    if (tr->data.ptr.offsets && tr->offsets_size) {
						// the offsets will be released by caller, we have to make a copy for receiver.
						// this new copy should be released by BC_FREE_BUFFER.
						void* copyOffsets = malloc(tr->offsets_size);
						LOG_ALWAYS_FATAL_IF((copyData == NULL), "Handler[%d] No memory when creating offsets copy. %s:%d", mHandler, __FILE__, __LINE__);
						if (copyOffsets == NULL) return NO_MEMORY;
						memcpy(copyOffsets, (void *)tr->data.ptr.offsets, tr->offsets_size);
						tr->data.ptr.offsets = (binder_uintptr_t)copyOffsets;
                        result = RegisterBn(*tr, *cmd);
                        if (result) return result;

					// when the offests is empty, it is no need to pass anything to receiver.
					} else if (tr->offsets_size == 0) {
						tr->data.ptr.offsets = 0;
					}
                    
                    if (BC_REPLY == (*cmd)) {
						LOG_ALWAYS_FATAL_IF((mCallStack.size() <= 0), "Handler[%d] No sender to reply. %s:%d", mHandler, __FILE__, __LINE__);
						if (mCallStack.size() <= 0) return INVALID_OPERATION;
						int hCaller = mCallStack.top();
						mCallStack.pop();
                        (*cmd) = BR_REPLY;
                        result = Send(hCaller, (uint8_t *)data, BINDER_CMD_SIZE + BINDER_TR_SIZE);
                    } else {
                        (*cmd) = BR_TRANSACTION;
                        result = Send(tr->target.handle, (uint8_t *)data, BINDER_CMD_SIZE + BINDER_TR_SIZE);
                    }
                    
                    if (NO_ERROR == result) {
                        // wait for the transaction complete
                        bNeedRead++;
                        readTimeout = BINDER_TIMEOUT_MS;
                    }
                }   break;
                case BC_ENTER_LOOPER:
                case BC_REGISTER_LOOPER:
                    // go to read
                    bNeedRead++;
                    break;
                case BC_EXIT_LOOPER: {
                    // it should never reach here.
                    // just exit no need to read
                    bNeedRead = 0;
                    return NO_ERROR;
                }   break;
                case BC_FREE_BUFFER: {
                    LOG_ALWAYS_FATAL_IF(size < (BINDER_CMD_SIZE + sizeof(uintptr_t)), "Handler[%d] Wrong data format. %s:%d", mHandler, __FILE__, __LINE__);
                    
					// copy of tr->data.ptr.buffer
                    uintptr_t buf = *((uintptr_t *)(data + BINDER_CMD_SIZE));
                    pbwr->write_consumed += sizeof(uintptr_t);
                    if (buf != 0) {
                        free((void*)buf);
                    }

					// copy of tr->data.ptr.offset
					buf = *((uintptr_t *)(data + BINDER_CMD_SIZE) + 1);
					pbwr->write_consumed += sizeof(uintptr_t);
					if (buf != 0) {
						free((void*)buf);
					}
                    
                    // local command
                    bNeedRead = 0;
                }   break;
                case BC_ACQUIRE:
                case BC_INCREFS: {
                    LOG_ALWAYS_FATAL_IF(size < (BINDER_CMD_SIZE + sizeof(int32_t)), "Handler[%d] Wrong data format. %s:%d", mHandler, __FILE__, __LINE__);
                    if (BC_INCREFS == (*cmd)) {
                        (*cmd) = BR_INCREFS;
                    } else {
                        (*cmd) = BR_ACQUIRE;
                    }
                    
                    int32_t dstHandler = *((int32_t *)(data + BINDER_CMD_SIZE));
                    pbwr->write_consumed += sizeof(int32_t);
                    
                    /*
                     * It may not be necessary to keep or release the object in this way.
                     * Besides, it will cause some objects are released unexpectedly.
                     * Investigate it later.
                     */
                    #if TODO
                    result = Send(dstHandler, (uint8_t *)data, BINDER_CMD_SIZE + sizeof(int32_t));
                    if (NO_ERROR == result) {
                        // wait for the result
                        bNeedRead++;
                        readTimeout = BINDER_TIMEOUT_MS;
                    }
                    #endif // TODO
                }   break;
                case BC_ACQUIRE_DONE:
                case BC_INCREFS_DONE: {
                    uintptr_t value = *((uintptr_t *)(pbwr->write_buffer + pbwr->write_consumed));
                    pbwr->write_consumed += sizeof(uintptr_t);
                    value = *((uintptr_t *)(pbwr->write_buffer + pbwr->write_consumed));
                    pbwr->write_consumed += sizeof(uintptr_t);
                    
                    (*cmd) = BR_OK;
                    result = Reply((uint8_t *)data, BINDER_CMD_SIZE);
                    
                    // no reply for reply
                    bNeedRead = 0;
                }   break;
                    
                case BC_RELEASE:
                case BC_DECREFS: {
                    LOG_ALWAYS_FATAL_IF(size < (BINDER_CMD_SIZE + sizeof(int32_t)), "Handler[%d] Wrong data format. %s:%d", mHandler, __FILE__, __LINE__);
                    if (BC_DECREFS == (*cmd)) {
                        (*cmd) = BR_DECREFS;
                    } else {
                        (*cmd) = BR_RELEASE;
                    }
                    
                    int32_t dstHandler = *((int32_t *)(data + BINDER_CMD_SIZE));
                    pbwr->write_consumed += sizeof(int32_t);
                    #if TODO
                    result = Send(dstHandler, (uint8_t *)data, BINDER_CMD_SIZE + sizeof(int32_t));
                    #endif // TODO
                    
                    // no reply for this command
                    bNeedRead = 0;
                }   break;
                case BC_ATTEMPT_ACQUIRE: {
                    (*cmd) = BR_ATTEMPT_ACQUIRE;
                    
                    // no use currently
                    int32_t value = *((int32_t *)(pbwr->write_buffer + pbwr->write_consumed));
                    pbwr->write_consumed += sizeof(int32_t);
                    
                    // handler
                    value = *((int32_t *)(pbwr->write_buffer + pbwr->write_consumed));
                    pbwr->write_consumed += sizeof(int32_t);
                    
                    // No HAS_BC_ATTEMPT_ACQUIRE currently
                    // IPCThreadState::attemptIncStrongHandle
                    result = Send(value, (uint8_t *)data, BINDER_CMD_SIZE);
                    if (NO_ERROR == result) {
                        // wait for the reulst
                        bNeedRead++;
                        readTimeout = BINDER_TIMEOUT_MS;
                    }
                }   break;
                case BC_ACQUIRE_RESULT: {
                    int32_t success = *((int32_t *)(data + BINDER_CMD_SIZE));
                    pbwr->write_consumed += sizeof(int32_t);
                    
                    // No HAS_BC_ATTEMPT_ACQUIRE currently
                    // IPCThreadState::attemptIncStrongHandle
                    if (success) {
                        (*cmd) = BR_OK;
                        result = Reply((uint8_t *)data, BINDER_CMD_SIZE);
                    } else {
                        (*cmd) = BR_ERROR;
                        result = Reply((uint8_t *)data, BINDER_CMD_SIZE + sizeof(int32_t));
                    }
                    
                    // no reply for reply
                    bNeedRead = 0;
                }   break;
                case BC_REQUEST_DEATH_NOTIFICATION: {
                    int32_t hDst = *((int32_t *)(data + BINDER_CMD_SIZE));
                    pbwr->write_consumed += sizeof(int32_t);
                    uintptr_t proxy = *((uintptr_t *)(data + BINDER_CMD_SIZE + sizeof(int32_t)));
                    pbwr->write_consumed += sizeof(uintptr_t);
                    
                    sp<IBinderEntry> eDst = binder_lookupEntry_local(hDst);
                    ALOGE_IF((eDst == NULL), "Handler[%d] is dead. %s:%d", hDst, __FILE__, __LINE__);
                    if (eDst == NULL) return DEAD_OBJECT;

                    eDst->AddDeathNotify(mHandler, proxy);
                    
                    // local command
                    bNeedRead = 0;
                }   break;
                case BC_CLEAR_DEATH_NOTIFICATION: {
                    int32_t hDst = *((int32_t *)(data + BINDER_CMD_SIZE));
                    pbwr->write_consumed += sizeof(int32_t);
                    uintptr_t proxy = *((uintptr_t *)(data + BINDER_CMD_SIZE + sizeof(int32_t)));
                    pbwr->write_consumed += sizeof(uintptr_t);

                    sp<IBinderEntry> eDst = binder_lookupEntry_local(hDst);
                    ALOGE_IF((eDst == NULL), "Handler[%d] is dead. %s:%d", hDst, __FILE__, __LINE__);
                    if (eDst == NULL) return DEAD_OBJECT;

                    eDst->DelDeathNotify(mHandler, proxy);
                    
                    // local command
                    bNeedRead = 0;
                }   break;
                case BC_DEAD_BINDER_DONE: {
                    //uintptr_t proxy = *((uintptr_t *)(data + BINDER_CMD_SIZE));
                    pbwr->write_consumed += sizeof(uintptr_t);
                    
                    // the death notification is managed on native binder side
                    // we do not have to do anything on proxy side.
                    
                    bNeedRead = 0;
                }   break;
                default:
                    LOG_ALWAYS_FATAL("Handler[%d] Cmd[%d] Unknown command %s:%d", mHandler, *cmd, __FILE__, __LINE__);
                    break;
            } // switch
        } // while
        
        return result;
    } // Write
    
    status_t Read(binder_write_read* pbwr, int readTimeout)
    {
        // No read buffer. It seems not possible.
        if ((pbwr->read_buffer == 0) || (pbwr->read_size == 0)) {
            return NO_ERROR;
        }
        int32_t* cmd = (int32_t *)(pbwr->read_buffer);
        
        LOG_ALWAYS_FATAL_IF((mLooper == NULL), "Handler[%d] No Message Looper. %s:%d", mHandler, __FILE__, __LINE__);
        if (mLooper == NULL) return FAILED_TRANSACTION;
        
        int ret = mLooper->pollOnce(readTimeout);
        if (Looper::POLL_TIMEOUT == ret) {
            // It means thread is dead when we cannot get reply in time.
            (*cmd) = BR_DEAD_REPLY;
            return NO_ERROR;
        }
        
        if (mMsgCache != NULL && mMsgCache->dataSize() <= pbwr->read_size) {
            // backup the data to reading buffer
            memcpy((void *)(pbwr->read_buffer), mMsgCache->data(), mMsgCache->dataSize());
            
            // it only has command at first.
            pbwr->read_consumed += sizeof(int32_t);
            switch (*cmd) {
                case BR_REPLY:
                case BR_TRANSACTION: {
                    binder_transaction_data* tr = (binder_transaction_data *)(pbwr->read_buffer + BINDER_CMD_SIZE);
                    pbwr->read_consumed += sizeof(binder_transaction_data);
					LOG_ALWAYS_FATAL_IF((pbwr->read_consumed != mMsgCache->dataSize()), "Handler[%d] wrong data format (consumed:%d, actual:%d). %s:%d", mHandler, pbwr->read_consumed, mMsgCache->dataSize(), __FILE__, __LINE__);

					// the message is not for the current native server, but for the children.
                    if (mBnList.indexOfKey(tr->target.handle) >= 0) {
                        flat_binder_object& obj = mBnList.editValueFor(tr->target.handle);
                        tr->target.ptr = (obj.binder);
                        tr->cookie = (obj.cookie);
                    }
                    
                    // map the proxy to native binder
                    if (tr->data.ptr.offsets && tr->offsets_size) {
                        SearchBp(*tr);
                    }
                    
					if ((BR_TRANSACTION == (*cmd)) && ((tr->flags & TF_ONE_WAY) == 0)) {
						mCallStack.push(mMsgSender);
					}

                    // we have to send the complete also for BR_REPLY
                    int32_t complete = BR_TRANSACTION_COMPLETE;
                    Send(mMsgSender, (uint8_t *)(&complete), sizeof(complete));
                }   break;
                case BR_ACQUIRE:
                case BR_RELEASE:
                case BR_INCREFS:
                case BR_DECREFS: {
                    int32_t* hTarget = (int32_t *)(pbwr->read_buffer + BINDER_CMD_SIZE);
                    if (mBnList.indexOfKey(*hTarget) >= 0) {
                        const flat_binder_object& obj = mBnList.valueFor(*hTarget);
                        binder_uintptr_t* ptr = (binder_uintptr_t *)(pbwr->read_buffer + BINDER_CMD_SIZE);
                        (*ptr++) = obj.binder;
                        (*ptr)   = obj.cookie;
                        pbwr->read_consumed += 2 * sizeof(binder_uintptr_t);
                    } else {
                        LOG_ALWAYS_FATAL("Handler[%d] No object %s:%d", *hTarget, __FILE__, __LINE__);
                        (*cmd) = BR_NOOP;
                    }
                }   break;
                case BR_ATTEMPT_ACQUIRE: {
                    if (mBnList.size() > 0) {
                        const flat_binder_object& obj = mBnList[0];
                        binder_uintptr_t* ptr = (binder_uintptr_t *)(pbwr->read_buffer + BINDER_CMD_SIZE);
                        (*ptr++) = obj.binder;
                        (*ptr)   = obj.cookie;
                        pbwr->read_consumed += 2 * sizeof(binder_uintptr_t);
                    } else {
                        LOG_ALWAYS_FATAL("Handler[%d] No object %s:%d", mHandler, __FILE__, __LINE__);
                        (*cmd) = BR_NOOP;
                    }
                }   break;
                case BR_DEAD_BINDER: {
                    pbwr->read_consumed += sizeof(uintptr_t);
                }   break;
                case BR_ERROR: {
                    pbwr->read_consumed += sizeof(int32_t);
                }   break;
                case BR_OK:
                case BR_FINISHED:
                case BR_TRANSACTION_COMPLETE:
                    break;
                default:
                    LOG_ALWAYS_FATAL("Handler[%d] Cmd[%d] Unknown command %s:%d", mHandler, *cmd, __FILE__, __LINE__);
                    break;
            } // switch
        } // if
        
        if (mMsgCache) {
            delete (mMsgCache);
            mMsgCache = NULL;
        }
        
        return NO_ERROR;
    } // Read

    status_t Reply(uint8_t* data, size_t size)
    {
        return Send(mMsgSender, data, size);
    }

    status_t RegisterBn(binder_transaction_data& tr, int cmd)
    {
        // decode the binder object from Parcel according to Parcel::writeObject
        for (int i = 0; i < ((tr.offsets_size)/sizeof(binder_size_t)); ++i) {
            binder_size_t objOffset = ((binder_size_t *)(tr.data.ptr.offsets))[i];
            flat_binder_object* obj = (flat_binder_object*)((uint8_t *)(tr.data.ptr.buffer) + objOffset);
            if (obj->hdr.type == BINDER_TYPE_BINDER) {
				LOG_ALWAYS_FATAL_IF(((cmd != BC_TRANSACTION) && (mBnList.isEmpty())), "Something strange. %s:%d", __FILE__, __LINE__);

                // the first should be the one which is registered to Service Manager (handler of 0)
                int hProxy = -1;
                if (mBnList.isEmpty() && (tr.target.handle == 0)) {
					hProxy = mHandler;

					// Add reference to avoid it may be released
					reinterpret_cast<RefBase::weakref_type*>(obj->binder)->incWeak((void *)0);
					//reinterpret_cast<IBinder*>(obj->cookie)->incStrong((void *)0);

					// map the handler to native binder
					mBnList.add(hProxy, *obj);
                    
                // the following is anonymous binder
                } else {
                    // do not map the same native binder twice
					hProxy = FindNativeBinder(obj->cookie);
					if (hProxy == -1) {
						// the native binder may have registered to deamon
						hProxy = binder_lookupProxy_deamon(obj->cookie);
					}

                    // create handler for new native binder
                    if (hProxy == -1) {
                        sp<IBinderEntry> eProxy;
                        {
                            AutoMutex _l(gServiceLock);

                            hProxy = gHandlerCounter++;
                            eProxy = new CBinderEntry(hProxy);
                            LOG_ALWAYS_FATAL_IF((eProxy == NULL), "Handler[%d] Failed to create binder entry. %s:%d", hProxy, __FILE__, __LINE__);
                            
                            ssize_t N = gServiceList.add(hProxy, eProxy);
                            LOG_ALWAYS_FATAL_IF((N < 0), "Handler[%d] Failed to add binder entry. %s:%d", hProxy, __FILE__, __LINE__);
                            if (N < 0) {
                                return (NO_MEMORY);
                            }
                        }
                        
						// the anonymous binder which has no IPCThread
						if (mBnList.isEmpty()) {
							// get the common deamon thread
							sp<IBinderEntry> eDeamon = binder_lookupEntry_deamon();
							ALOGE_IF((eDeamon == NULL), "Deamon service is dead. %s:%d", __FILE__, __LINE__);
							if (eDeamon == NULL) return (DEAD_OBJECT);

							// it sends the message to deamon threads
							eProxy->SetLooper(eDeamon->GetLooper());
							eProxy->SetParentHandler(eDeamon->GetHandler());

							// Add reference to avoid it may be released
							reinterpret_cast<RefBase::weakref_type*>(obj->binder)->incWeak((void *)0);
							//reinterpret_cast<IBinder*>(obj->cookie)->incStrong((void *)0);

							// map the handler to native binder
							eDeamon->AddNativeBinder(hProxy, *obj);

						// the one which is registered to Service Manager
						} else {
							// it sends the message to current threads
							eProxy->SetLooper(mLooper);
							eProxy->SetParentHandler(mHandler);

							// Add reference to avoid it may be released
							reinterpret_cast<RefBase::weakref_type*>(obj->binder)->incWeak((void *)0);
							//reinterpret_cast<IBinder*>(obj->cookie)->incStrong((void *)0);

							// map the handler to native binder
							mBnList.add(hProxy, *obj);
						} // if (mBnList.isEmpty())
                    } // if (hProxy == -1)
                } // if (mBnList.isEmpty() && (tr.target.handle == 0))
                
                // return the proxy for this native binder
                obj->hdr.type = BINDER_TYPE_HANDLE;
                //obj->binder = 0;
                obj->handle = hProxy;
                obj->cookie = 0;
            } // if (obj->type == BINDER_TYPE_BINDER)
        } // for
        
        return NO_ERROR;
    } // RegisterBn

    status_t SearchBp(binder_transaction_data& tr)
    {
        // decode the binder object from Parcel according to Parcel::writeObject
        for (int i = 0; i < ((tr.offsets_size)/sizeof(binder_size_t)); ++i) {
            binder_size_t objOffset = ((binder_size_t *)(tr.data.ptr.offsets))[i];
            flat_binder_object* obj = (flat_binder_object*)((uint8_t *)(tr.data.ptr.buffer) + objOffset);
            
            // binder proxy
            if (obj->hdr.type == BINDER_TYPE_HANDLE) {
                for (int i = 0; i < mBnList.size(); ++i) {
                    if (obj->handle == mBnList.keyAt(i)) {
                        (*obj) = mBnList[i];
						break;
                    }
                }
            }
        } // for

        return NO_ERROR;
    }
    
    status_t Send(int hDst, uint8_t* data, size_t size)
    {
        status_t result = NO_ERROR;
        
        sp<IBinderEntry> eDst = binder_lookupEntry_local(hDst);
        ALOGE_IF((eDst == NULL), "Handler[%d] is dead. %s:%d", hDst, __FILE__, __LINE__);
        if (eDst == NULL) return (DEAD_OBJECT);
        
        Parcel* msg = new Parcel();
        LOG_ALWAYS_FATAL_IF((msg == NULL), "No memory when creating Parcel. %s:%d", __FILE__, __LINE__);
        if (msg == NULL) return NO_MEMORY;
        
        msg->setData((uint8_t *)data, size);
        result = eDst->Push(msg, mHandler);
        if (NO_ERROR != result) delete msg;
        
        return result;
    }
    
private:
    class BinderMessage : public MessageHandler
    {
    public:
        BinderMessage(Parcel* data, IBinderEntry* out) : mMsg(data), mDst(out) {};
        ~BinderMessage() { if (mMsg != NULL) delete mMsg; };
        
        virtual void handleMessage(const Message& evt) {
            if (mDst != NULL) {
                mDst->CacheMessage(mMsg, evt.what);
                mMsg = NULL;
            }
        };
    private:
        Parcel*          mMsg;
        sp<IBinderEntry> mDst;
    }; // BinderMessage
    
    // server
    KeyedVector<int, flat_binder_object>  mBnList;   // pointer of native binder
    KeyedVector<int, uintptr_t>           mBpList;   // proxy for death notification
    Mutex                                 mBpLock;

	String8     mName;

    int         mHandler;
    int         mhParent;
    sp<Looper>  mLooper;
    
    // Message
	Parcel*     mMsgCache;
    int         mMsgSender;
	Vector<int> mCallStack;
}; // CBinderEntry
 


static sp<IBinderEntry> binder_lookupEntry_local(int handler)
{
    AutoMutex _l(gServiceLock);

    const ssize_t N = gServiceList.indexOfKey(handler);
    if (N < 0) {
        return (NULL);
    }
    
    return (gServiceList.editValueFor(handler));
}
    
static sp<IBinderEntry> binder_lookupEntry_deamon()
{
	static int s_hCurrentDeamon = BINDER_DEAMON_START;

	if (s_hCurrentDeamon >= BINDER_DEAMON_START + gDeamonCount) {
		s_hCurrentDeamon = BINDER_DEAMON_START;
	}
	
	return (binder_lookupEntry_local(s_hCurrentDeamon++));
}

static int binder_lookupProxy_deamon(uintptr_t cookie)
{
	// if the native binder has already registered to deamon thread before,
	// do not register it again to another deamon thread.
	for (int handler = BINDER_DEAMON_START; handler < BINDER_DEAMON_START + gDeamonCount; ++handler) {
		sp<IBinderEntry> e = binder_lookupEntry_local(handler);
		int hProxy = e->FindNativeBinder(cookie);
		if (hProxy > 0) {
			return (hProxy);
		}
	}

	return (-1);
}

// ---------------------------------------------------------------------------
// Public API

int binder_open_local(const char* name)
{
    AutoMutex _l(gServiceLock);
    
    int handler = gHandlerCounter++;

    sp<IBinderEntry> e = new CBinderEntry(handler);
    LOG_ALWAYS_FATAL_IF((e == NULL), "Failed to create binder entry. %s:%d", __FILE__, __LINE__);

    ssize_t N = gServiceList.add(handler, e);
    LOG_ALWAYS_FATAL_IF((N < 0), "Failed to add binder entry. %s:%d", __FILE__, __LINE__);
    if (N < 0) {
        return (-1);
    }
    
    e->SetLooper(new Looper(true));

	if (name) {
		e->SetName(name);
	}

    return handler;
}

status_t binder_close_local(int handler)
{
    AutoMutex _l(gServiceLock);
    
    const ssize_t N = gServiceList.indexOfKey(handler);
    LOG_ALWAYS_FATAL_IF((N < 0), "Handler[%d] does not exist. %s:%d", handler, __FILE__, __LINE__);
    if (N < 0) {
        return (BAD_VALUE);
    }
    
    sp<IBinderEntry> e = gServiceList.editValueFor(handler);
    LOG_ALWAYS_FATAL_IF((e == NULL), "Handler[%d] is impossible disappeared. (-_-)!!! %s:%d", handler, __FILE__, __LINE__);
    if (e != NULL) {
        // send the message to exit the thread
        Parcel* finish = new Parcel;
        finish->writeInt32(BR_ERROR);
        finish->writeInt32(-ECONNREFUSED);
        status_t result = e->Push(finish, -1);
        if (NO_ERROR != result) delete finish;
        
        // exit service
        e->Exit();
        e = NULL;
    }
    gServiceList.removeItem(handler);

	return NO_ERROR;
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
	case BINDER_SET_MAX_THREADS: {
		size_t maxThreads = *((size_t *)data);
		if (maxThreads > gDeamonCount) {
			gDeamonCount = maxThreads;
		}
	}   break;
	case BINDER_SET_CONTEXT_MGR: {
        gHandlerContextManager = handler;
    }   break;
    case BINDER_WRITE_READ: {
        // service manager is not ready
        if ((handler == 0) && (gHandlerContextManager == 0)) {
            return INVALID_OPERATION;
        }
        
        sp<IBinderEntry> e = binder_lookupEntry_local(handler);
        ALOGE_IF((e == 0), "Handler[%d] is dead. %s:%d", handler, __FILE__, __LINE__);

        if (e != NULL) {
            result = e->WriteRead(data);
        } else {
            result = DEAD_OBJECT;
        }
    }   break;
	case BINDER_THREAD_EXIT:
		break;
	default:
        LOG_ALWAYS_FATAL("Invalid operation %s:%d", __FILE__, __LINE__);
		result = INVALID_OPERATION;
		break;
	}

    if (NO_ERROR != result) {
        result = EBADF;
    }
    
	return result;
}

} // namespace android
