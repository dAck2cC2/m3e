#include <gtest/gtest.h>
#include <binder/Parcel.h>
#include <binder/MemoryDealer.h>

namespace android {
    
TEST(libbinder, Binder_bn)
{
    #define TEST_MEM_SIZE  (32)

	sp<MemoryDealer> memoryDealer = new MemoryDealer(TEST_MEM_SIZE, "BpBinder");
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
    sp<MemoryDealer> memoryDealer = new MemoryDealer(TEST_MEM_SIZE, "BpBinder");
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

} // namespace android
