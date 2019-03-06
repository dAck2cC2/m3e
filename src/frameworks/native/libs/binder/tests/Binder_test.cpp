#include <gtest/gtest.h>
#include <binder/Parcel.h>
#include <binder/MemoryDealer.h>
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>

#include <utils/threads.h>
#include <utils/Vector.h>
#include <string.h>

#include <initrc.h>

#include <binder/local/ThreadService.h>

namespace android {

#define TEST_MEM_SIZE  (32)
    
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
    
    
#define TEST_STRING    "binder.test.memory"
#define TEST_AMOUNT    (3)
    
static String16  gRecursiveTestName("binder_nested_test_service");
static String16  gBinderTestName("binder_test_service");
static int32_t   gBinderTestCounter = 0;

class  IBinderTest : public IInterface
{
public:
    DECLARE_META_INTERFACE(BinderTest);
    
    virtual int  increase(int amount) = 0;
    virtual sp<IMemory> getMemory(int32_t isStatic) = 0;
    
    virtual sp<IBinder> createToken(int32_t id) = 0;
    virtual int32_t getTokenId(const sp<IBinder>& token) = 0;
    virtual sp<IBinder> getToken(int32_t id) = 0;

	virtual int callRecursive(int code) = 0;

	enum {
		BD_TEST_INCREASE = IBinder::FIRST_CALL_TRANSACTION,
		BD_TEST_MEMORY,
		BD_TEST_CREATE_TOKEN,
		BD_TEST_GET_TOKEN_ID,
		BD_TEST_GET_TOKEN,
		BD_TEST_CALL_RECURSIVE,
	};
};

class  IRecursiveTest : public IInterface
{
public:
	DECLARE_META_INTERFACE(RecursiveTest);

	virtual int callRecursive(int code) = 0;
	virtual int recursive(int code) = 0;

	enum {
		BD_TEST_CALL_RECURSIVE = IBinder::FIRST_CALL_TRANSACTION,
		BD_TEST_RECURSIVE,
	};
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
    
    virtual sp<IMemory> getMemory(int32_t isStatic) {
        sp<IMemory> result;
        
        Parcel data, reply;
        data.writeInterfaceToken(IBinderTest::getInterfaceDescriptor());
		data.writeInt32(isStatic);
        if (remote()->transact(BD_TEST_MEMORY, data, &reply) == NO_ERROR) {
            sp<IBinder> binder = reply.readStrongBinder();
            result = interface_cast<IMemory>(binder);
        }
        
        return result;
    };
    
    virtual sp<IBinder> createToken(int32_t id)
    {
        sp<IBinder> result;
        Parcel data, reply;
        data.writeInterfaceToken(IBinderTest::getInterfaceDescriptor());
        data.writeInt32(id);
        if (remote()->transact(BD_TEST_CREATE_TOKEN, data, &reply) == NO_ERROR) {
            result = reply.readStrongBinder();
        }
        return result;
    };
    
    virtual int32_t getTokenId(const sp<IBinder>& token)
    {
        int32_t result = 0;
        Parcel data, reply;
        data.writeInterfaceToken(IBinderTest::getInterfaceDescriptor());
        data.writeStrongBinder(token);
        if (remote()->transact(BD_TEST_GET_TOKEN_ID, data, &reply) == NO_ERROR) {
            result = reply.readInt32();
        }
        return result;
    };
    
    virtual sp<IBinder> getToken(int32_t id)
    {
        sp<IBinder> result;
        Parcel data, reply;
        data.writeInterfaceToken(IBinderTest::getInterfaceDescriptor());
        data.writeInt32(id);
        if (remote()->transact(BD_TEST_GET_TOKEN, data, &reply) == NO_ERROR) {
            result = reply.readStrongBinder();
        }
        return result;
    };

	virtual int  callRecursive(int code) {
		int result = 0;
		Parcel data, reply;
		data.writeInterfaceToken(IBinderTest::getInterfaceDescriptor());
		data.writeInt32(code);
		if (remote()->transact(BD_TEST_CALL_RECURSIVE, data, &reply) == NO_ERROR) {
			result = reply.readInt32();
		}
		return result;
	};
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
				int32_t isStatic = data.readInt32();
                sp<IMemory> mem = getMemory(isStatic);
                reply->writeStrongBinder(IInterface::asBinder(mem));
                return NO_ERROR;
            } break;
            case BD_TEST_CREATE_TOKEN: {
                CHECK_INTERFACE(IBinderTest, data, reply);
                int32_t id = data.readInt32();
                sp<IBinder> token = createToken(id);
                reply->writeStrongBinder(token);
                return NO_ERROR;
            } break;
            case BD_TEST_GET_TOKEN_ID: {
                CHECK_INTERFACE(IBinderTest, data, reply);
                sp<IBinder> token = data.readStrongBinder();
                int32_t id = getTokenId(token);
                reply->writeInt32(id);
                return NO_ERROR;
            } break;
            case BD_TEST_GET_TOKEN: {
                CHECK_INTERFACE(IBinderTest, data, reply);
                int32_t id = data.readInt32();
                sp<IBinder> token = getToken(id);
                reply->writeStrongBinder(token);
                return NO_ERROR;
            } break;
			case BD_TEST_CALL_RECURSIVE: {
				CHECK_INTERFACE(IBinderTest, data, reply);
				int32_t c = data.readInt32();
				int ret = callRecursive((int)c);
				reply->writeInt32(ret);
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
    
    virtual sp<IMemory> getMemory(int32_t isStatic) {
		if (isStatic) {
			return mMem;
		}
		else {
			return mDealer->allocate(TEST_MEM_SIZE);
		}
    };
    
    virtual sp<IBinder> createToken(int32_t id)
    {
        if ((id < 0) || (id >= TOKEN_MAX)) {
            return NULL;
        }
        
        if (mToken[id] == NULL) {
            mToken[id] = new BBinder();
        }
        
        return mToken[id];
    };
    
    virtual int32_t getTokenId(const sp<IBinder>& token)
    {
        int32_t id = -1;
        for (int32_t i = 0; i < TOKEN_MAX; ++i) {
            if (token == mToken[i]) {
                id = i;
                break;
            }
        }
        
        return id;
    };
    
    virtual sp<IBinder> getToken(int32_t id)
    {
        if ((id < 0) || (id >= TOKEN_MAX)) {
            return NULL;
        }
        
        return mToken[id];
    };

	virtual int  callRecursive(int code) {
		sp<IRecursiveTest> nested;
		status_t chk = getService(gRecursiveTestName, &nested);
		EXPECT_EQ(NO_ERROR, chk);
		EXPECT_TRUE(nested != NULL);

		return (nested->recursive(code));
	};
    
private:
    sp<MemoryDealer> mDealer;
    sp<IMemory>      mMem;
    
    static const int TOKEN_MAX = 2;
    sp<IBinder>      mToken[2];
};
    
class BinderTestService : public ThreadService
{
public:
    BinderTestService()  {};
    ~BinderTestService() {};

private:
	virtual bool startService()
	{
		mTest = new CBinderTest();
        defaultServiceManager()->addService(gBinderTestName, IInterface::asBinder(mTest));
        
        return true;
    };

	sp<IBinderTest> mTest;
};
    
static InitRC& inirc = InitRC::getInstance();
static sp<BinderTestService> service = new BinderTestService();

class ServiceTest : public testing::Test {
protected:
    virtual void SetUp() {
        // EMPTY
    };
};
    
TEST_F(ServiceTest, Binder_service)
{
    service->waitForStarted();
    
    sp<IBinder> client = defaultServiceManager()->getService(gBinderTestName);
    EXPECT_TRUE(client != NULL);

    sp<IBinderTest> test = interface_cast<IBinderTest>(client);
    EXPECT_TRUE(test != NULL);

    int ret = test->increase(TEST_AMOUNT);
    EXPECT_EQ(TEST_AMOUNT, ret);
    EXPECT_EQ(gBinderTestCounter, ret);
}

TEST_F(ServiceTest, Binder_memory)
{
    service->waitForStarted();
    
    sp<IBinderTest> test;
    status_t chk = getService(gBinderTestName, &test);
    EXPECT_EQ(NO_ERROR, chk);
    EXPECT_TRUE(test != NULL);
    
    sp<IMemory> mem = test->getMemory(1);
    EXPECT_TRUE(mem != NULL);
    
    void* pBuf = mem->pointer();
    EXPECT_TRUE(pBuf != NULL);
    EXPECT_STREQ(TEST_STRING, (char *)pBuf);
}

TEST_F(ServiceTest, DISABLED_Binder_memory_dynamic)
{
	service->waitForStarted();

	sp<IBinderTest> test;
	status_t chk = getService(gBinderTestName, &test);
	EXPECT_EQ(NO_ERROR, chk);
	EXPECT_TRUE(test != NULL);

	sp<IMemory> mem = test->getMemory(0);
	EXPECT_TRUE(mem != NULL);

	void* pBuf = mem->pointer();
	EXPECT_TRUE(pBuf != NULL);

	size_t size = mem->size();
	EXPECT_EQ(TEST_MEM_SIZE, size);
}

TEST_F(ServiceTest, Binder_token)
{
    service->waitForStarted();

    sp<IBinderTest> test;
    status_t chk = getService(gBinderTestName, &test);
    EXPECT_EQ(NO_ERROR, chk);
    EXPECT_TRUE(test != NULL);

    sp<IBinder> token[2];
    
    for (int32_t i = 0; i < 2; ++i) {
        token[i] = test->createToken(i);
        EXPECT_TRUE(token[i] != NULL) << i;
    }
    
    for (int32_t i = 0; i < 2; ++i) {
        int32_t id = test->getTokenId(token[i]);
        EXPECT_EQ(i, id) << i;
    }
    
    for (int32_t i = 0; i < 2; ++i) {
        sp<IBinder> t;
        t = test->getToken(i);
        EXPECT_TRUE(token[i] == t) << i;
    }
}

class BpRecursiveTest : public BpInterface<IRecursiveTest>
{
public:
	BpRecursiveTest(const sp<IBinder>& impl) : BpInterface<IRecursiveTest>(impl) {};

	virtual int  callRecursive(int code) {
		int result = 0;
		Parcel data, reply;
		data.writeInterfaceToken(IRecursiveTest::getInterfaceDescriptor());
		data.writeInt32(code);
		if (remote()->transact(BD_TEST_CALL_RECURSIVE, data, &reply) == NO_ERROR) {
			result = reply.readInt32();
		}
		return result;
	};

	virtual int  recursive(int code) {
		int result = 0;
		Parcel data, reply;
		data.writeInterfaceToken(IRecursiveTest::getInterfaceDescriptor());
		data.writeInt32(code);
		if (remote()->transact(BD_TEST_RECURSIVE, data, &reply) == NO_ERROR) {
			result = reply.readInt32();
		}
		return result;
	};
};
class BnRecursiveTest : public BnInterface<IRecursiveTest>
{
public:
	virtual status_t onTransact(
		uint32_t code,
		const Parcel& data,
		Parcel* reply,
		uint32_t flags = 0)
	{
		switch (code) {
		case BD_TEST_CALL_RECURSIVE: {
			CHECK_INTERFACE(IRecursiveTest, data, reply);
			int32_t c = data.readInt32();
			int ret = callRecursive((int)c);
			reply->writeInt32(ret);
			return NO_ERROR;
		} break;
		case BD_TEST_RECURSIVE: {
			CHECK_INTERFACE(IRecursiveTest, data, reply);
			int32_t c = data.readInt32();
			int ret = recursive((int)c);
			reply->writeInt32(ret);
			return NO_ERROR;
		} break;
		default:
			return BBinder::onTransact(code, data, reply, flags);
		}
	}

	BnRecursiveTest() {};
protected:
	virtual ~BnRecursiveTest() {};
};
IMPLEMENT_META_INTERFACE(RecursiveTest, "android.test.binder.nested");
class CRecursiveTest : public BnRecursiveTest
{
public:
	CRecursiveTest() {
		service->waitForStarted();
		status_t chk = getService(gBinderTestName, &mTest);
		EXPECT_EQ(NO_ERROR, chk);
		EXPECT_TRUE(mTest != NULL);
	};
	~CRecursiveTest() {};

	virtual int  callRecursive(int code) {
		EXPECT_TRUE(mTest != NULL);
		return (mTest->callRecursive(code));
	};
	virtual int  recursive(int code) {
		return (code);
	};
private:
	sp<IBinderTest> mTest;
};
class RecursiveTestService : public ThreadService
{
public:
	RecursiveTestService() {};
	~RecursiveTestService() {};

private:
	virtual bool startService()
	{
		mRecursive = new CRecursiveTest();
		defaultServiceManager()->addService(gRecursiveTestName, IInterface::asBinder(mRecursive));

		return true;
	};

	sp<IRecursiveTest> mRecursive;
};
static sp<RecursiveTestService> serviceRecursive = new RecursiveTestService();

TEST_F(ServiceTest, Binder_recursive)
{
	service->waitForStarted();
	serviceRecursive->waitForStarted();

	sp<IRecursiveTest> nested;
	status_t chk = getService(gRecursiveTestName, &nested);
	EXPECT_EQ(NO_ERROR, chk);
	EXPECT_TRUE(nested != NULL);

	int ret = nested->callRecursive(TEST_AMOUNT);
	EXPECT_EQ(TEST_AMOUNT, ret);
}

TEST_F(ServiceTest, Binder_death)
{
    service->waitForStarted();
    service->waitForStopped();
    
    sp<IBinderTest> test;
    status_t chk = getService(gBinderTestName, &test);
    EXPECT_NE(NO_ERROR, chk);
    EXPECT_TRUE(test == NULL);
}

} // namespace android
