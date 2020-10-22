#include <gtest/gtest.h>
#include <cutils/bitops.h>

TEST(libcutils, bitops)
{
	unsigned int  bitmask[2] = { 0x01, 0xFFFFFFFF };
	int bitcnt = 0;
	bitcnt = popcount(bitmask[0]);
	EXPECT_EQ(1, bitcnt);
	bitcnt = popcount(bitmask[1]);
	EXPECT_EQ(32, bitcnt);
}
