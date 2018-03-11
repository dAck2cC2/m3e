#include <gtest/gtest.h>
#include <binder/Parcel.h>
#include <binder/MemoryDealer.h>
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>

#include <utils/threads.h>
#include <string.h>


namespace android {

#define TEST_MEM_SIZE  (32)
#define TEST_STRING    "binder.test.memory"
    
static String16  gBinderTestName("binder_test_service");
static int32_t   gBinderTestCounter = 0;

class  IBinderTest : public IInterface
{
public:
    DECLARE_META_INTERFACE(BinderTest);
    
    virtual int  increase(int amount) = 0;
    virtual sp<IMemory> getMemory() = 0;
};
    
enum {
    BD_TEST_INCREASE = IBinder::FIRST_CALL_TRANSACTION,
    BD_TEST_MEMORY,
};

class BpBinderTest : public BpInterface<IBinderTest>
{
public:
    BpBinderTest(const sp<IBinder>& impl) : BpInterface<IBinderTest>(impl) {};
    virtual ~BpBinderTest() {};
    
    virtual int  increase(int amount) {
        int result = 0;
        Parcel data, reply;
        data.writeInterfaceToken(IBinderTest::getInterfaceDescriptor());
        data.writeInt32(amount);
        if (remote()->transact(BD_TEST_INCREASE, data, &reply) == NO_ERROR) {
            result = reply.readInt32();
        }
        return result;
    };
    
    virtual sp<IMemory> getMemory() {
        sp<IMemory> result;
        
        Parcel data, reply;
        data.writeInterfaceToken(IBinderTest::getInterfaceDescriptor());
        if (remote()->transact(BD_TEST_MEMORY, data, &reply) == NO_ERROR) {
            sp<IBinder> binder = reply.readStrongBinder();
            result = interface_cast<IMemory>(binder);
        }
        
        return result;
    }
};

class BnBinderTest : public BnInterface<IBinderTest>
{
public:
    virtual status_t onTransact(
                                uint32_t code,
                                const Parcel& data,
                                Parcel* reply,
                                uint32_t flags = 0)
    {
        switch(code) {
            case BD_TEST_INCREASE: {
                CHECK_INTERFACE(IBinderTest, data, reply);
                int32_t amount = data.readInt32();
                int ret = increase((int)amount);
                reply->writeInt32(ret);
                return NO_ERROR;
            } break;
            case BD_TEST_MEMORY: {
                CHECK_INTERFACE(IBinderTest, data, reply);
                sp<IMemory> mem = getMemory();
                reply->writeStrongBinder(IInterface::asBinder(mem));
                return NO_ERROR;
            } break;
            default:
                return BBinder::onTransact(code, data, reply, flags);
        }
    }
    
    BnBinderTest() {};
protected:
    virtual ~BnBinderTest() {};
};
    
IMPLEMENT_META_INTERFACE(BinderTest, "android.test.binder");

class CBinderTest : public BnBinderTest
{
public:
    CBinderTest() {
        mDealer = new MemoryDealer(TEST_MEM_SIZE, "CBinderTest");
        EXPECT_TRUE(mDealer != NULL);
        
        mMem = mDealer->allocate(TEST_MEM_SIZE);
        EXPECT_TRUE(mMem != NULL);
        
        void* pBuf = mMem->pointer();
        EXPECT_TRUE(pBuf != NULL);

        strcpy((char *)pBuf, TEST_STRING);
    };
    ~CBinderTest() {};
    
    virtual int  increase(int amount) {
        gBinderTestCounter += amount;
        return (gBinderTestCounter);
    };
    
    virtual sp<IMemory> getMemory() {
        return mMem;
    };
private:
    sp<MemoryDealer> mDealer;
    sp<IMemory>      mMem;
};
    
class BinderTestService : public Thread
{
public:
    BinderTestService()  {};
    ~BinderTestService() {};
    void waitForStarted(void) {
        mThreadStartedMutex.lock();
        
        Thread::run();
        
        mThreadStartedCondition.wait(mThreadStartedMutex);
        mThreadStartedMutex.unlock();
    }
    void waitForStopped(void) {
        mThreadStartedMutex.lock();
        
        mIPCThread->stopProcess();
        Thread::requestExitAndWait();
        //mIPCThread->shutdown();

        mThreadStartedMutex.unlock();
    }
private:
    virtual bool threadLoop()
    {
        mThreadStartedMutex.lock();
        
        sp<ProcessState>  proc = ProcessState::self();
        sp<IBinderTest> test = new CBinderTest();
        
        defaultServiceManager()->addService(gBinderTestName, IInterface::asBinder(test));

        mIPCThread = IPCThreadState::self();
        
        mThreadStartedCondition.broadcast();
        mThreadStartedMutex.unlock();
        
        IPCThreadState::self()->joinThreadPool();
        
        return false;
    };
private:
    Mutex     mThreadStartedMutex;
    Condition mThreadStartedCondition;
    IPCThreadState* mIPCThread;;
};

TEST(libbinder, Binder_native)
{
	sp<MemoryDealer> memoryDealer = new MemoryDealer(TEST_MEM_SIZE, "Binder_bn");
    EXPECT_TRUE(memoryDealer != NULL);
    
    sp<IMemory> bnMem = memoryDealer->allocate(TEST_MEM_SIZE);
    EXPECT_TRUE(bnMem != NULL);

    sp<IBinder> binder = IInterface::asBinder(bnMem);
    EXPECT_TRUE(bnMem != NULL);

    sp<IMemory> mem = interface_cast<IMemory>(binder);
    EXPECT_TRUE(mem != NULL);
    EXPECT_TRUE(mem == bnMem);
}
    
TEST(libbinder, Binder_parcel)
{
    sp<MemoryDealer> memoryDealer = new MemoryDealer(TEST_MEM_SIZE, "Binder_parcel");
    EXPECT_TRUE(memoryDealer != NULL);
    
    sp<IMemory> bnMem = memoryDealer->allocate(TEST_MEM_SIZE);
    EXPECT_TRUE(bnMem != NULL);
    
    Parcel parcel;
    EXPECT_EQ(NO_ERROR, parcel.writeStrongBinder(IInterface::asBinder(bnMem)));
    
    parcel.setDataPosition(0);
    sp<IBinder> binder = parcel.readStrongBinder();
    
    sp<IMemory> mem = interface_cast<IMemory>(binder);
    EXPECT_TRUE(mem != NULL);
    EXPECT_TRUE(mem == bnMem);
}

TEST(libbinder, Binder_service)
{
#define TEST_AMOUNT (3)
    
    sp<BinderTestService> service = new BinderTestService();
    service->waitForStarted();
    
    sp<IBinder> client = defaultServiceManager()->getService(gBinderTestName);
    EXPECT_TRUE(client != NULL);

    sp<IBinderTest> test = interface_cast<IBinderTest>(client);
    EXPECT_TRUE(test != NULL);

    int ret = test->increase(TEST_AMOUNT);
    EXPECT_EQ(TEST_AMOUNT, ret);
    EXPECT_EQ(gBinderTestCounter, ret);
    
    //service->waitForStopped();
}

TEST(libbinder, Binder_memory)
{
    //sp<BinderTestService> service = new BinderTestService();
    //service->waitForStarted();
    
    sp<IBinderTest> test;
    status_t chk = getService(gBinderTestName, &test);
    EXPECT_EQ(NO_ERROR, chk);
    EXPECT_TRUE(test != NULL);
    
    sp<IMemory> mem = test->getMemory();
    EXPECT_TRUE(mem != NULL);
    
    void* pBuf = mem->pointer();
    EXPECT_TRUE(mem != NULL);
    EXPECT_STREQ(TEST_STRING, (char *)pBuf);
    
    //service->waitForStopped();
}
    
} // namespace android
