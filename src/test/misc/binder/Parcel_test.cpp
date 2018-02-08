
#include <gtest/gtest.h>
#include <binder/Parcel.h>

namespace android {

TEST(libbinder, Parcel_data)
{
	char writedata[8] = {0, 1, 2, 3, 4, 5, 6, 7};
	Parcel parcel;
	EXPECT_EQ(NO_ERROR, parcel.write((void*)(&writedata[0]), sizeof(writedata)));

    EXPECT_EQ(0, parcel.dataAvail());
    EXPECT_TRUE(NULL != parcel.data());
    EXPECT_EQ(sizeof(writedata), parcel.dataSize());
    EXPECT_EQ(sizeof(writedata), parcel.dataPosition());

    EXPECT_EQ(NO_ERROR, parcel.write((void*)(&writedata[0]), sizeof(writedata)));
    
	parcel.setDataPosition(0);
    EXPECT_EQ(sizeof(writedata) * 2, parcel.dataAvail());

	char readdata[8] = {};
	EXPECT_EQ(NO_ERROR, parcel.read((void*)(&readdata[0]), sizeof(readdata)));
	for (int i = 0; i < sizeof(readdata); ++i) {
		EXPECT_EQ(writedata[i], readdata[i]);
	}
    memset(readdata, 0x00, sizeof(readdata));
    EXPECT_EQ(NO_ERROR, parcel.read((void*)(&readdata[0]), sizeof(readdata)));
    for (int i = 0; i < sizeof(readdata); ++i) {
        EXPECT_EQ(writedata[i], readdata[i]);
    }
    
    char rewritedata[8] = {10, 11, 12, 13, 14, 15, 16, 17};
    EXPECT_EQ(NO_ERROR, parcel.setData((uint8_t *)(&rewritedata[0]), sizeof(rewritedata)));
    
    EXPECT_EQ(sizeof(rewritedata), parcel.dataAvail());
    EXPECT_TRUE(NULL != parcel.data());
    EXPECT_EQ(sizeof(writedata), parcel.dataSize());
    EXPECT_EQ(0, parcel.dataPosition());
    
    memset(readdata, 0x00, sizeof(readdata));
    EXPECT_EQ(NO_ERROR, parcel.read((void*)(&readdata[0]), sizeof(readdata)));
    for (int i = 0; i < sizeof(readdata); ++i) {
        EXPECT_EQ(rewritedata[i], readdata[i]) << i;
    }
    
    void* pwrite = parcel.writeInplace(6);
    EXPECT_TRUE(NULL != pwrite);
    *((char *)pwrite) = 20;
    
    //parcel.setDataPosition(parcel.dataPosition() - 6);
    //const void* pread = parcel.readInplace(6);
    //EXPECT_TRUE(NULL != pread);
    //EXPECT_EQ(20, *((char *)pwrite));
}

TEST(libbinder, Parcel_value)
{
	#define TEST_INT32  (-320)
    #define TEST_UINT32 (32000)

	Parcel parcel;
	EXPECT_EQ(NO_ERROR, parcel.writeInt32(TEST_INT32));
	EXPECT_EQ(NO_ERROR, parcel.writeInt32(TEST_INT32));
    
    EXPECT_EQ(NO_ERROR, parcel.writeUint32(TEST_UINT32));
    EXPECT_EQ(NO_ERROR, parcel.writeUint32(TEST_UINT32));

	parcel.setDataPosition(0);
	EXPECT_EQ(TEST_INT32, parcel.readInt32());
	int32_t read_int32 = 0;
	EXPECT_EQ(NO_ERROR, parcel.readInt32(&read_int32));
	EXPECT_EQ(TEST_INT32, read_int32);

    EXPECT_EQ(TEST_UINT32, parcel.readUint32());
    uint32_t read_uint32 = 0;
    EXPECT_EQ(NO_ERROR, parcel.readUint32(&read_uint32));
    EXPECT_EQ(TEST_UINT32, read_uint32);

}

TEST(libbinder, Parcel_string)
{
	#define TEST_STRING "android.parcel.test"

	Parcel parcel;
	EXPECT_EQ(NO_ERROR, parcel.writeCString(TEST_STRING));

	parcel.setDataPosition(0);
	EXPECT_STREQ(TEST_STRING, parcel.readCString());
}

}; // android
