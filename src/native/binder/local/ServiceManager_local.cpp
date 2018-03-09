#define LOG_TAG "ServiceManager"

#include <binder/IServiceManager.h>
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>
#include <binder/Status.h>

#include <utils/threads.h>
#include <utils/KeyedVector.h>

namespace android {

class LocalServiceManager : public BBinder, public Thread
{
public:
    LocalServiceManager() : mDescriptor("android.os.IServiceManager") {  };
    virtual const String16& getInterfaceDescriptor() const { return mDescriptor; };
    
    virtual status_t onTransact( 
            uint32_t code,
            const Parcel& data,
            Parcel* reply,
            uint32_t flags = 0)
    {
        switch (code) {
            case IServiceManager::CHECK_SERVICE_TRANSACTION:
            {
                CHECK_INTERFACE(IServiceManager, data, reply);
                String16 name = data.readString16();
                
                sp<IBinder> binder;
                ssize_t n = mServices.indexOfKey(name);
                if (n >= 0) {
                    binder = mServices.valueFor(name);
                }
                
                reply->writeStrongBinder(binder);
            }
                break;
            case IServiceManager::ADD_SERVICE_TRANSACTION:
            {
                CHECK_INTERFACE(IServiceManager, data, reply);
                String16 name = data.readString16();
                sp<IBinder> binder = data.readStrongBinder();
                int32_t allowIsolated = data.readInt32();
                ssize_t n = mServices.indexOfKey(name);
                if (n < 0) {
                    n = mServices.add(name, binder);
                }
                if (n < 0) {
                    reply->writeInt32(n);
                } else {
                    reply->writeInt32(binder::Status::EX_NONE);
                }
            }
                break;
            case IServiceManager::LIST_SERVICES_TRANSACTION:
            {
                CHECK_INTERFACE(IServiceManager, data, reply);
                int32_t index = data.readInt32();
                
                status_t ret = BAD_INDEX;
                String16 name;
                if (index < mServices.size()) {
                    name = mServices.keyAt(index);
                    ret = NO_ERROR;
                }
                reply->writeString16(name);
                return (ret);
            }
            case IServiceManager::GET_SERVICE_TRANSACTION:
            default:
                return BBinder::onTransact(code, data, reply, flags);
        }
        
        return OK;
    };

protected:
    ~LocalServiceManager() {};
    
private:
    virtual bool threadLoop()
    {
		sp<ProcessState>  proc = ProcessState::self();
        proc->becomeContextManager(NULL, NULL);

        //sp<IBinder> thiz = IInterface::asBinder(this);
        Parcel parcel;
        parcel.writeStrongBinder(this);
        IPCThreadState::self()->transact(0, IBinder::PING_TRANSACTION, parcel, NULL, IBinder::FLAG_ONEWAY);

		IPCThreadState::self()->joinThreadPool();

        return false;
    };
    
private:
    const android::String16              mDescriptor;
    KeyedVector<String16, sp<IBinder> >  mServices;
};

    
class LocalServiceManagerInit
{
public:
	LocalServiceManagerInit() { 
		sm = new LocalServiceManager();
		sm->run();
	};
	~LocalServiceManagerInit() {};
private:
	sp<LocalServiceManager> sm;
};

    
static LocalServiceManagerInit gLocalServiceManager;

}; // namespace android
