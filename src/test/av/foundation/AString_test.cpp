
#include <gtest/gtest.h>
#include <media/stagefright/foundation/AString.h>

namespace android {

TEST(libstagefight_foundation, AString)
{
    static const char* TEST_STRING = "test.libstagetfight_foundation.AString";
    
    AString str(TEST_STRING);
    EXPECT_FALSE(str.empty());
    EXPECT_STREQ(TEST_STRING, str.c_str());
    EXPECT_EQ(strlen(TEST_STRING), str.size());
    
    str.clear();
    EXPECT_TRUE(str.empty());
    EXPECT_EQ(0, str.size());

    str.setTo(TEST_STRING);
    EXPECT_STREQ(TEST_STRING, str.c_str());
    EXPECT_EQ(strlen(TEST_STRING), str.size());
}

}; // android
