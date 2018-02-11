
#include <gtest/gtest.h>
#include <utils/String8.h>
#include <media/stagefright/foundation/AString.h>

namespace android {

TEST(libstagefight_foundation, AString_String)
{
    static const char* TEST_STRING = "test.libstagetfight_foundation.AString";
    static const char* TEST_PREFIX = "test.";
    static const char* TEST_SUFFIX = ".AString";
    
    // constructor
    AString str(TEST_STRING);
    EXPECT_FALSE(str.empty());
    EXPECT_STREQ(TEST_STRING, str.c_str());
    EXPECT_EQ(strlen(TEST_STRING), str.size());
    
    // clear
    str.clear();
    EXPECT_TRUE(str.empty());
    EXPECT_EQ(0, str.size());

    // setTo
    str.setTo(TEST_STRING);
    EXPECT_STREQ(TEST_STRING, str.c_str());
    EXPECT_EQ(strlen(TEST_STRING), str.size());
    
    // append
    str.erase(strlen(TEST_PREFIX), strlen(TEST_STRING) - strlen(TEST_PREFIX) - strlen(TEST_SUFFIX));
    String8 str8(TEST_PREFIX);
    AString res(str8);
    res.append(TEST_SUFFIX);
    EXPECT_STREQ(res.c_str(), str.c_str());

    // trim
    str.clear();
    str.append("          ", 5);
    str.append(res, strlen(TEST_PREFIX), strlen(TEST_SUFFIX));
    EXPECT_STREQ("     .AString", str.c_str());
    str.trim();
    EXPECT_STREQ(TEST_SUFFIX, str.c_str());
    
    // operator=
    AString tmp(res, strlen(TEST_PREFIX), strlen(TEST_SUFFIX));
    EXPECT_STREQ(TEST_SUFFIX, tmp.c_str());
    tmp.clear();
    tmp = str;
    EXPECT_STREQ(TEST_SUFFIX, tmp.c_str());

    
}

}; // android
