#include <gtest/gtest.h>
#include <cutils/bitops.h>

TEST(libcutils, bitops)
{
	unsigned int  bitmask[2] = { 0xFFFFFFFF, 0xFFFFFFFF };
	bitmask_init(bitmask, 1);
	EXPECT_EQ(0, bitmask[0]);
	bitmask_init(bitmask, sizeof(unsigned int) * 8 + 1);
	EXPECT_EQ(0, bitmask[1]);
}
