
#include <gtest/gtest.h>
#include <binder/Parcel.h>

namespace android {

TEST(libmisc, Parcel_data)
{
	char writedata[8] = {0, 1, 2, 3, 4, 5, 6, 7};
	Parcel parcel;
	EXPECT_EQ(NO_ERROR, parcel.write((void*)(&writedata[0]), sizeof(writedata)));

	parcel.setDataPosition(0);
	char readdata[8] = {};
	EXPECT_EQ(NO_ERROR, parcel.read((void*)(&readdata[0]), sizeof(readdata)));
	for (int i = 0; i < sizeof(writedata); ++i) {
		EXPECT_EQ(writedata[i], readdata[i]);
	}
}

TEST(libmisc, Parcel_value)
{
	#define TEST_INT32  (-320)

	Parcel parcel;
	EXPECT_EQ(NO_ERROR, parcel.writeInt32(TEST_INT32));
	EXPECT_EQ(NO_ERROR, parcel.writeInt32(TEST_INT32));

	parcel.setDataPosition(0);
	EXPECT_EQ(TEST_INT32, parcel.readInt32());
	int32_t read = 0;
	EXPECT_EQ(NO_ERROR, parcel.readInt32(&read));
	EXPECT_EQ(TEST_INT32, read);
}

TEST(libmisc, Parcel_string)
{
	#define TEST_STRING "android.parcel.test"

	Parcel parcel;
	EXPECT_EQ(NO_ERROR, parcel.writeCString(TEST_STRING));

	parcel.setDataPosition(0);
	EXPECT_STREQ(TEST_STRING, parcel.readCString());
}

}; // android
