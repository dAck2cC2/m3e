
#include <gtest/gtest.h>
#include <binder/Parcel.h>
#include <utils/String8.h>

namespace android {

TEST(libbinder, Parcel_data)
{
	// write & read
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
 
	// setData & read
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
    
	// writeInplace & readInplace
	size_t pos = parcel.dataPosition();
    void* pwrite = parcel.writeInplace(6);
    EXPECT_TRUE(NULL != pwrite);
    *((char *)pwrite) = 20;

    parcel.setDataPosition(pos);
    const void* pread = parcel.readInplace(6);
    EXPECT_TRUE(NULL != pread);
    EXPECT_EQ(20, *((char *)pread));

	// appendFrom
	pos = parcel.dataPosition();
	char appenddata[8] = { 30, 31, 32, 33, 34, 35, 36, 37 };
	Parcel append;
	EXPECT_EQ(NO_ERROR, append.setData((uint8_t *)(&appenddata[0]), sizeof(appenddata)));
	EXPECT_EQ(NO_ERROR, parcel.appendFrom(&append, 1, 3));

	//parcel.setDataPosition(pos);
	//memset(readdata, 0x00, sizeof(readdata));
	//EXPECT_EQ(NO_ERROR, parcel.read((void*)(&readdata[0]), 3));
	//for (int i = 0; i < 3; ++i) {
	//	EXPECT_EQ(appenddata[1 + i], readdata[i]) << i;
	//}
}

TEST(libbinder, Parcel_value)
{
	#define TEST_INT32  (-320)
    #define TEST_UINT32 (32000)
	#define TEST_INT64  (-64000000)  
	#define TEST_UINT64 (64000000000)  
	#define TEST_FLOAT  (0.12345678f)  
	#define TEST_DOUBLE (-0.12345678012345678)  
    #define TEST_CHAR16 (0x7788)
	#define TEST_BYTE   (0x66)

	#define TEST_CNT    (8)
	int32_t  writeint[TEST_CNT]  = {10, 11, 12, 13, 14, 15, 16, 17};
	uint8_t  writebyte[TEST_CNT] = {0, 1, 2, 3, 4, 5, 6, 7};

	// write
	Parcel parcel;
	EXPECT_EQ(NO_ERROR, parcel.writeInt32(TEST_INT32));
	EXPECT_EQ(NO_ERROR, parcel.writeInt32(TEST_INT32));
    
    EXPECT_EQ(NO_ERROR, parcel.writeUint32(TEST_UINT32));
    EXPECT_EQ(NO_ERROR, parcel.writeUint32(TEST_UINT32));

	EXPECT_EQ(NO_ERROR, parcel.writeInt64(TEST_INT64));
	EXPECT_EQ(NO_ERROR, parcel.writeInt64(TEST_INT64));

	EXPECT_EQ(NO_ERROR, parcel.writeUint64(TEST_UINT64));
	EXPECT_EQ(NO_ERROR, parcel.writeUint64(TEST_UINT64));

	EXPECT_EQ(NO_ERROR, parcel.writeFloat(TEST_FLOAT));
	EXPECT_EQ(NO_ERROR, parcel.writeFloat(TEST_FLOAT));

	EXPECT_EQ(NO_ERROR, parcel.writeDouble(TEST_DOUBLE));
	EXPECT_EQ(NO_ERROR, parcel.writeDouble(TEST_DOUBLE));

	EXPECT_EQ(NO_ERROR, parcel.writeBool(true));
	EXPECT_EQ(NO_ERROR, parcel.writeBool(false));

	EXPECT_EQ(NO_ERROR, parcel.writeChar(TEST_CHAR16));
	EXPECT_EQ(NO_ERROR, parcel.writeChar(TEST_CHAR16));

	EXPECT_EQ(NO_ERROR, parcel.writeByte(TEST_BYTE));
	EXPECT_EQ(NO_ERROR, parcel.writeByte(TEST_BYTE));

	EXPECT_EQ(NO_ERROR, parcel.writeInt32Array(TEST_CNT, writeint));
	EXPECT_EQ(NO_ERROR, parcel.writeByteArray(TEST_CNT, writebyte));

	// read
	parcel.setDataPosition(0);
	EXPECT_EQ(TEST_INT32, parcel.readInt32());
	int32_t read_int32 = 0;
	EXPECT_EQ(NO_ERROR, parcel.readInt32(&read_int32));
	EXPECT_EQ(TEST_INT32, read_int32);

    EXPECT_EQ(TEST_UINT32, parcel.readUint32());
    uint32_t read_uint32 = 0;
    EXPECT_EQ(NO_ERROR, parcel.readUint32(&read_uint32));
    EXPECT_EQ(TEST_UINT32, read_uint32);

	EXPECT_EQ(TEST_INT64, parcel.readInt64());
	int64_t read_int64 = 0;
	EXPECT_EQ(NO_ERROR, parcel.readInt64(&read_int64));
	EXPECT_EQ(TEST_INT64, read_int64);

	EXPECT_EQ(TEST_UINT64, parcel.readUint64());
	uint64_t read_uint64 = 0;
	EXPECT_EQ(NO_ERROR, parcel.readUint64(&read_uint64));
	EXPECT_EQ(TEST_UINT64, read_uint64);

	EXPECT_EQ(TEST_FLOAT, parcel.readFloat());
	float read_float = 0.0f;
	EXPECT_EQ(NO_ERROR, parcel.readFloat(&read_float));
	EXPECT_EQ(TEST_FLOAT, read_float);

	EXPECT_EQ(TEST_DOUBLE, parcel.readDouble());
	double read_double = 0.0;
	EXPECT_EQ(NO_ERROR, parcel.readDouble(&read_double));
	EXPECT_EQ(TEST_DOUBLE, read_double);

	EXPECT_EQ(true, parcel.readBool());
	bool read_bool = true;
	EXPECT_EQ(NO_ERROR, parcel.readBool(&read_bool));
	EXPECT_EQ(false, read_bool);

	EXPECT_EQ(TEST_CHAR16, parcel.readChar());
	char16_t read_char = 0x0000;
	EXPECT_EQ(NO_ERROR, parcel.readChar(&read_char));
	EXPECT_EQ(TEST_CHAR16, read_char);

	EXPECT_EQ(TEST_BYTE, parcel.readByte());
	int8_t read_byte = 0x0000;
	EXPECT_EQ(NO_ERROR, parcel.readByte(&read_byte));
	EXPECT_EQ(TEST_BYTE, read_byte);

	EXPECT_EQ(TEST_CNT, parcel.readInt32());
	for (int i = 0; i < TEST_CNT; ++i) {
		EXPECT_EQ(writeint[i], parcel.readInt32()) << i;
	}

	EXPECT_EQ(TEST_CNT, parcel.readInt32());
	uint8_t readdata[TEST_CNT] = {};
	EXPECT_EQ(NO_ERROR, parcel.read((void*)(&readdata[0]), sizeof(readdata)));
	for (int i = 0; i < TEST_CNT; ++i) {
		EXPECT_EQ(writebyte[i], readdata[i]);
	}
}

TEST(libbinder, Parcel_string)
{
	#define TEST_STRING "android.parcel.test"
	String8  str8_w(TEST_STRING);
	String16 str16_w(TEST_STRING);

	// write
	Parcel parcel;
	EXPECT_EQ(NO_ERROR, parcel.writeCString(TEST_STRING));
	EXPECT_EQ(NO_ERROR, parcel.writeString8(str8_w));
	EXPECT_EQ(NO_ERROR, parcel.writeString16(str16_w));

	// read
	parcel.setDataPosition(0);
	EXPECT_STREQ(TEST_STRING, parcel.readCString());
	String8 str8_r = parcel.readString8();
	EXPECT_STREQ(TEST_STRING, str8_r.string());
	String16 str16_r = parcel.readString16();
	EXPECT_TRUE(str16_w == str16_r);
}

}; // android
