
#include <gtest/gtest.h>
#include <binder/MemoryDealer.h>

namespace android {

TEST(libbinder, MemoryDealer_getAllocationAlignment)
{
	EXPECT_EQ(32, MemoryDealer::getAllocationAlignment());
}

TEST(libbinder, MemoryDealer_one)
{
#define TEST_MEM_SIZE  (4096)

	sp<MemoryDealer> memoryDealer = new MemoryDealer(TEST_MEM_SIZE, "MemoryDealer_one");
	EXPECT_TRUE(memoryDealer != NULL);

	sp<IMemory> mem = memoryDealer->allocate(TEST_MEM_SIZE);
	EXPECT_TRUE(mem != NULL);

	EXPECT_TRUE(mem->pointer() != NULL);
	EXPECT_EQ(TEST_MEM_SIZE, mem->size());
}

TEST(libbinder, MemoryDealer_multiple)
{
#define TEST_MEM_PER_SIZE  (4096)
#define TEST_MEM_COUNT     (6)

	sp<MemoryDealer> memoryDealer = new MemoryDealer(TEST_MEM_PER_SIZE*TEST_MEM_COUNT, "MemoryDealer_multiple");
	EXPECT_TRUE(memoryDealer != NULL);

	for (int i = 0; i < TEST_MEM_COUNT * 2; ++i) {
		sp<IMemory> mem = memoryDealer->allocate(TEST_MEM_PER_SIZE);
		EXPECT_TRUE(mem != NULL);

		EXPECT_TRUE(mem->pointer() != NULL);
		EXPECT_EQ(TEST_MEM_SIZE, mem->size());
	}
}

}; // android
