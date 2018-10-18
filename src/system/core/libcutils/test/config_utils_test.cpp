
#include <gtest/gtest.h>
#include <cutils/config_utils.h>

// sleep 1 ms.
#ifdef _MSC_VER
#include <windows.h>
#define _sys_sleep  Sleep
#define SLEEP_TIME   (1)
#else
#define _sys_sleep  usleep
#define SLEEP_TIME   (1000)
#endif

TEST(libcutils, config_load)
{
    #define ITEM_NAME_A  "item_A"
	#define ITEM_VALUE_A "Yes"
	#define ITEM_NAME_B  "item_B"
	#define ITEM_VALUE_B "No"

	char TEST_DATA[128] = {
		ITEM_NAME_A " " ITEM_VALUE_A "\n"
		ITEM_NAME_B " " ITEM_VALUE_B "\n"
	};

	cnode root;
	memset(&root, 0x00, sizeof(root));
	config_load(&root, TEST_DATA);

	cnode* result = config_find(&root, ITEM_NAME_A);
	EXPECT_TRUE(NULL != result);
	EXPECT_STREQ(ITEM_NAME_A, result->name);
	EXPECT_STREQ(ITEM_VALUE_A, result->value);
	EXPECT_EQ(1, config_bool(&root, ITEM_NAME_A, 0));
	EXPECT_STREQ(ITEM_VALUE_A, config_str(&root, ITEM_NAME_A, "unknown"));

	result = config_find(&root, ITEM_NAME_B);
	EXPECT_TRUE(NULL != result);
	EXPECT_STREQ(ITEM_NAME_B, result->name);
	EXPECT_STREQ(ITEM_VALUE_B, result->value);
	EXPECT_EQ(0, config_bool(&root, ITEM_NAME_B, 1));
	EXPECT_STREQ(ITEM_VALUE_B, config_str(&root, ITEM_NAME_B, "unknown"));

	config_free(&root);
}

TEST(libcutils, config_set_one) 
{
	const char* TEST_NAME  = "gtest.libcutils.config_set";
	const char* TEST_VALUE = "Yes";
	cnode root;
	memset(&root, 0x00, sizeof(root));
	config_set(&root, TEST_NAME, TEST_VALUE);

	cnode* result = config_find(&root, TEST_NAME);
	EXPECT_TRUE(NULL != result);
	EXPECT_STREQ(TEST_NAME,  result->name);
	EXPECT_STREQ(TEST_VALUE, result->value);

	EXPECT_EQ(1, config_bool(&root, TEST_NAME, 0));

	EXPECT_STREQ(TEST_VALUE, config_str(&root, TEST_NAME, "unknown"));

	config_free(&root);
}

TEST(libcutils, config_set_multiple) 
{
	const char* TEST_NAME_A  = "gtest.libcutils.config_set_A";
	const char* TEST_VALUE_A = "1";

	const char* TEST_NAME_B  = "gtest.libcutils.config_set_B";
	const char* TEST_VALUE_B = "No";

	cnode root;
	memset(&root, 0x00, sizeof(root));
	config_set(&root, TEST_NAME_A, TEST_VALUE_A);
	config_set(&root, TEST_NAME_B, TEST_VALUE_B);

	cnode* result = config_find(&root, TEST_NAME_A);
	EXPECT_TRUE(NULL != result);
	EXPECT_STREQ(TEST_NAME_A,  result->name);
	EXPECT_STREQ(TEST_VALUE_A, result->value);
	EXPECT_EQ(1, config_bool(&root, TEST_NAME_A, 0));
	EXPECT_STREQ(TEST_VALUE_A, config_str(&root, TEST_NAME_A, "unknown"));

	result = config_find(&root, TEST_NAME_B);
	EXPECT_TRUE(NULL != result);
	EXPECT_STREQ(TEST_NAME_B, result->name);
	EXPECT_STREQ(TEST_VALUE_B, result->value);
	EXPECT_EQ(0, config_bool(&root, TEST_NAME_B, 1));
	EXPECT_STREQ(TEST_VALUE_B, config_str(&root, TEST_NAME_B, "unknown"));

	config_free(&root);
}
