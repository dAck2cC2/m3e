
#include <gtest/gtest.h>
#include <utils/String8.h>
#include <binder/Parcel.h>
#include <media/stagefright/foundation/AString.h>
#include <media/stagefright/foundation/AStringUtils.h>

namespace android {

static const char* TEST_STRING    = "test.libstagetfight_foundation.AString";
static const char* TEST_STRING_UP = "TEST.LIBSTAGETFIGHT_FOUNDATION.AString";
static const char* TEST_PREFIX    = "test.";
static const char* TEST_PREFIX_UP = "TEST.";
static const char* TEST_SUFFIX    = ".AString";
static const char* TEST_SUFFIX_UP = ".ASTRING";
static const char* TEST_MIDDLE    = "libstagetfight_foundation";

TEST(libstagefight_foundation, AString_constructor)
{   
    // char* 
    AString str(TEST_STRING);
    EXPECT_FALSE(str.empty());
    EXPECT_STREQ(TEST_STRING, str.c_str());
    EXPECT_EQ(strlen(TEST_STRING), str.size());
    
	// char*, size
	AString str_prefix(TEST_STRING, strlen(TEST_PREFIX));
	EXPECT_STREQ(TEST_PREFIX, str_prefix.c_str());
	EXPECT_EQ(strlen(TEST_PREFIX), str_prefix.size());

	// String8
	String8 str8(TEST_STRING);
	AString str_str8(str8);
	EXPECT_STREQ(TEST_STRING, str_str8.c_str());
	EXPECT_EQ(strlen(TEST_STRING), str_str8.size());

	// AString
	AString str_str(str);
	EXPECT_STREQ(TEST_STRING, str_str.c_str());
	EXPECT_EQ(strlen(TEST_STRING), str_str.size());

	// AString, offset, size
	AString str_suf(str, strlen(TEST_STRING) - strlen(TEST_SUFFIX), strlen(TEST_SUFFIX));
	EXPECT_STREQ(TEST_SUFFIX, str_suf.c_str());
	EXPECT_EQ(strlen(TEST_SUFFIX), str_suf.size());

	// operator=
	AString str_equ;
	EXPECT_TRUE(str_equ.empty());
	EXPECT_EQ(0, str_equ.size());
	str_equ = str;
	EXPECT_STREQ(TEST_STRING, str_equ.c_str());
	EXPECT_EQ(strlen(TEST_STRING), str_equ.size());

    // erase
	str_str8.erase(strlen(TEST_PREFIX), strlen(TEST_STRING) - strlen(TEST_PREFIX) - strlen(TEST_SUFFIX));
    AString res(TEST_PREFIX);
    res.append(TEST_SUFFIX);
    EXPECT_STREQ(res.c_str(), str_str8.c_str());

	// clear
	str.clear();
	EXPECT_TRUE(str.empty());
	EXPECT_EQ(0, str.size());

    // trim
    str.append("          ", 5);
    str.append(res, strlen(TEST_PREFIX), strlen(TEST_SUFFIX));
    EXPECT_STREQ("     .AString", str.c_str());
    str.trim();
    EXPECT_STREQ(TEST_SUFFIX, str.c_str());
}

TEST(libstagefight_foundation, AString_setTo)
{
	AString str;

	// char*
	str.setTo(TEST_STRING);
	EXPECT_STREQ(TEST_STRING, str.c_str());
	EXPECT_EQ(strlen(TEST_STRING), str.size());

	// AString, offset, size
	AString str_suf;
	str_suf.setTo(str, strlen(TEST_STRING) - strlen(TEST_SUFFIX), strlen(TEST_SUFFIX));
	EXPECT_STREQ(TEST_SUFFIX, str_suf.c_str());
	EXPECT_EQ(strlen(TEST_SUFFIX), str_suf.size());

	// char*, size
	str.clear();
	str.setTo(TEST_STRING, strlen(TEST_PREFIX));
	EXPECT_STREQ(TEST_PREFIX, str.c_str());
	EXPECT_EQ(strlen(TEST_PREFIX), str.size());
}

TEST(libstagefight_foundation, AString_append)
{
	AString str("ABC");

	// char
	str.append('D');
	EXPECT_STREQ("ABCD", str.c_str());

	// char*
	str.append("EFG");
	EXPECT_STREQ("ABCDEFG", str.c_str());

	// char*, size
	str.append("HIJK", 3);
	EXPECT_STREQ("ABCDEFGHIJ", str.c_str());

	// AString
	AString str_app("abcdef");
	str.append(str_app);
	EXPECT_STREQ("ABCDEFGHIJabcdef", str.c_str());

	// AString, offset, size
	str.append(str_app, 3, 3);
	EXPECT_STREQ("ABCDEFGHIJabcdefdef", str.c_str());

	// int
	int intval = -1;
	str.append(intval);
	EXPECT_STREQ("ABCDEFGHIJabcdefdef-1", str.c_str());

	// unsigned
	unsigned unsignedval = 234;
	str.append(unsignedval);
	EXPECT_STREQ("ABCDEFGHIJabcdefdef-1234", str.c_str());

	// long
	long longval = -5678;
	str.append(longval);
	EXPECT_STREQ("ABCDEFGHIJabcdefdef-1234-5678", str.c_str());

	// unsigned long
	unsigned long ulval = 9012;
	str.append(ulval);
	EXPECT_STREQ("ABCDEFGHIJabcdefdef-1234-56789012", str.c_str());

	// long long
	long long llval = -98765432;
	str.append(llval);
	EXPECT_STREQ("ABCDEFGHIJabcdefdef-1234-56789012-98765432", str.c_str());

	// unsigned long long
	unsigned long long ullval = 9876543210987654321;
	str.append(ullval);
	EXPECT_STREQ("ABCDEFGHIJabcdefdef-1234-56789012-987654329876543210987654321", str.c_str());

	// float
	float fval = -0.123456f;
	str.append(fval);
	EXPECT_STREQ("ABCDEFGHIJabcdefdef-1234-56789012-987654329876543210987654321-0.123456", str.c_str());

	// double
	double dval = -0.123456;
	str.append(dval);
	EXPECT_STREQ("ABCDEFGHIJabcdefdef-1234-56789012-987654329876543210987654321-0.123456-0.123456", str.c_str());

	// void*
}

TEST(libstagefight_foundation, AString_insert)
{
	AString str(TEST_PREFIX);
	str.append(TEST_SUFFIX);

	// AString, pos
	AString mid(TEST_MIDDLE);
	str.insert(mid, strlen(TEST_PREFIX));
	EXPECT_STREQ(TEST_STRING, str.c_str());
	EXPECT_EQ(strlen(TEST_STRING), str.size());

	// char*, size, pos
	str.clear();
	str.append(TEST_PREFIX);
	str.append(TEST_SUFFIX);
	str.insert(TEST_MIDDLE, strlen(TEST_MIDDLE), strlen(TEST_PREFIX));
	EXPECT_STREQ(TEST_STRING, str.c_str());
	EXPECT_EQ(strlen(TEST_STRING), str.size());

	// find
	EXPECT_EQ(0, str.find(TEST_PREFIX));
	EXPECT_EQ(strlen(TEST_PREFIX), str.find(TEST_MIDDLE));
	EXPECT_EQ(strlen(TEST_PREFIX) + strlen(TEST_MIDDLE), str.find(TEST_SUFFIX, strlen(TEST_PREFIX)));

	// hash
	EXPECT_NE(mid.hash(), str.hash());
	str.clear();
	str.setTo(TEST_MIDDLE);
	EXPECT_EQ(mid.hash(), str.hash());
}

TEST(libstagefight_foundation, AString_compare)
{
	AString str(TEST_STRING);

	// operator
	EXPECT_TRUE(str == AString(TEST_STRING));
	EXPECT_FALSE(str == AString(TEST_MIDDLE));
	EXPECT_TRUE(str != AString(TEST_MIDDLE));
	EXPECT_FALSE(str != AString(TEST_STRING));
	EXPECT_TRUE(str > AString(TEST_MIDDLE));
	EXPECT_FALSE(AString(TEST_MIDDLE) > str);
	EXPECT_TRUE(AString(TEST_MIDDLE) < str);
	EXPECT_FALSE(str < AString(TEST_MIDDLE));

	// compare
	EXPECT_EQ(0, str.compare(AString(TEST_STRING)));
	EXPECT_NE(0, str.compare(AString(TEST_MIDDLE)));
	EXPECT_EQ(0, str.compareIgnoreCase(AString(TEST_STRING_UP)));
	EXPECT_NE(0, str.compareIgnoreCase(AString(TEST_PREFIX_UP)));

	EXPECT_TRUE( str.equalsIgnoreCase(AString(TEST_STRING_UP)));
	EXPECT_FALSE(str.equalsIgnoreCase(AString(TEST_PREFIX_UP)));
	EXPECT_TRUE( str.startsWith(TEST_PREFIX));
	EXPECT_FALSE(str.startsWith(TEST_SUFFIX));
	EXPECT_TRUE( str.endsWith(TEST_SUFFIX));
	EXPECT_FALSE(str.endsWith(TEST_PREFIX));
	EXPECT_TRUE( str.startsWithIgnoreCase(TEST_PREFIX_UP));
	EXPECT_FALSE(str.startsWithIgnoreCase(TEST_SUFFIX_UP));
	EXPECT_TRUE( str.endsWithIgnoreCase(TEST_SUFFIX_UP));
	EXPECT_FALSE(str.endsWithIgnoreCase(TEST_PREFIX_UP));

	// tolower
	AString str_up(TEST_PREFIX_UP);
	EXPECT_STREQ(TEST_PREFIX_UP, str_up.c_str());
	str_up.tolower();
	EXPECT_STREQ(TEST_PREFIX, str_up.c_str());
}

TEST(libstagefight_foundation, AString_Parcel)
{
	Parcel p;
	AString src(TEST_STRING);
	EXPECT_STREQ(TEST_STRING, src.c_str());
	EXPECT_EQ(strlen(TEST_STRING), src.size());
	EXPECT_EQ(0, src.writeToParcel(&p));

	p.setDataPosition(0);
	AString dst = AString::FromParcel(p);
	EXPECT_TRUE(src == dst);
	EXPECT_STREQ(TEST_STRING, dst.c_str());
	EXPECT_EQ(strlen(TEST_STRING), dst.size());
}

TEST(libstagefight_foundation, AStringUtils)
{
	// Compare
	EXPECT_EQ(0, AStringUtils::Compare(TEST_STRING, TEST_STRING, strlen(TEST_STRING), false));
	EXPECT_EQ(0, AStringUtils::Compare(TEST_STRING, TEST_PREFIX, strlen(TEST_PREFIX), false));
	EXPECT_NE(0, AStringUtils::Compare(TEST_STRING, TEST_SUFFIX, strlen(TEST_SUFFIX), false));

	EXPECT_EQ(0, AStringUtils::Compare(TEST_STRING, TEST_STRING_UP, strlen(TEST_STRING_UP), true));
	EXPECT_EQ(0, AStringUtils::Compare(TEST_STRING, TEST_PREFIX_UP, strlen(TEST_PREFIX_UP), true));
	EXPECT_NE(0, AStringUtils::Compare(TEST_STRING, TEST_SUFFIX_UP, strlen(TEST_SUFFIX_UP), true));

	// MatchesGlob
	EXPECT_TRUE( AStringUtils::MatchesGlob("t*t.", 4, TEST_PREFIX, strlen(TEST_PREFIX), false));
	EXPECT_TRUE( AStringUtils::MatchesGlob("*t.",  3, TEST_PREFIX, strlen(TEST_PREFIX), false));
	EXPECT_FALSE(AStringUtils::MatchesGlob("t*t",  3, TEST_SUFFIX, strlen(TEST_SUFFIX), false));

	EXPECT_TRUE( AStringUtils::MatchesGlob("T*T.", 4, TEST_PREFIX, strlen(TEST_PREFIX), true));
	EXPECT_TRUE( AStringUtils::MatchesGlob("*T.",  3, TEST_PREFIX, strlen(TEST_PREFIX), true));
	EXPECT_FALSE(AStringUtils::MatchesGlob("T*T",  3, TEST_SUFFIX, strlen(TEST_SUFFIX), true));
}

}; // android
