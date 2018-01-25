
#include <gtest/gtest.h>
#include <android/log.h>

TEST(liblog, __android_log_write) {
	EXPECT_LT(0, __android_log_write(ANDROID_LOG_INFO,
		"TEST__android_log_buf_print",
		"radio"));
}
