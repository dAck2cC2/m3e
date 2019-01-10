
#include <gtest/gtest.h>
#include <android/log.h>
#include <log/log.h>

// sleep 1 ms.
#ifdef _MSC_VER
#include <windows.h>
#define _sys_sleep  Sleep
#define SLEEP_TIME   (1)
#else
#define _sys_sleep  usleep
#define SLEEP_TIME   (1000)
#endif

TEST(liblog, __android_log_write) {
	EXPECT_LT(0, __android_log_write(ANDROID_LOG_UNKNOWN,
		"TEST__android_log_write",
		"unknown"));
	_sys_sleep(SLEEP_TIME);
	EXPECT_LT(0, __android_log_write(ANDROID_LOG_DEFAULT,
		"TEST__android_log_write",
		"default"));
	_sys_sleep(SLEEP_TIME);
	EXPECT_LT(0, __android_log_write(ANDROID_LOG_VERBOSE,
		"TEST__android_log_write",
		"verbose"));
	_sys_sleep(SLEEP_TIME);
	EXPECT_LT(0, __android_log_write(ANDROID_LOG_DEBUG,
		"TEST__android_log_write",
		"debug"));
	_sys_sleep(SLEEP_TIME);
	EXPECT_LT(0, __android_log_write(ANDROID_LOG_INFO,
		"TEST__android_log_write",
		"info"));
	_sys_sleep(SLEEP_TIME);
	EXPECT_LT(0, __android_log_write(ANDROID_LOG_WARN,
		"TEST__android_log_write",
		"warn"));
	_sys_sleep(SLEEP_TIME);
	EXPECT_LT(0, __android_log_write(ANDROID_LOG_ERROR,
		"TEST__android_log_write",
		"error"));
	_sys_sleep(SLEEP_TIME);
	EXPECT_LT(0, __android_log_write(ANDROID_LOG_FATAL,
		"TEST__android_log_write",
		"fatal"));
	_sys_sleep(SLEEP_TIME);
	EXPECT_LT(0, __android_log_write(ANDROID_LOG_SILENT,
		"TEST__android_log_write",
		"silent"));
	_sys_sleep(SLEEP_TIME);
}

TEST(liblog, __android_log_print) {
	EXPECT_LT(0, __android_log_print(ANDROID_LOG_UNKNOWN,
		"TEST__android_log_print",
		"unknown"));
	_sys_sleep(SLEEP_TIME);
	EXPECT_LT(0, __android_log_print(ANDROID_LOG_DEFAULT,
		"TEST__android_log_print",
		"default"));
	_sys_sleep(SLEEP_TIME);
	EXPECT_LT(0, __android_log_print(ANDROID_LOG_VERBOSE,
		"TEST__android_log_print",
		"verbose"));
	_sys_sleep(SLEEP_TIME);
	EXPECT_LT(0, __android_log_print(ANDROID_LOG_DEBUG,
		"TEST__android_log_print",
		"debug"));
	_sys_sleep(SLEEP_TIME);
	EXPECT_LT(0, __android_log_print(ANDROID_LOG_INFO,
		"TEST__android_log_print",
		"info"));
	_sys_sleep(SLEEP_TIME);
	EXPECT_LT(0, __android_log_print(ANDROID_LOG_WARN,
		"TEST__android_log_print",
		"warn"));
	_sys_sleep(SLEEP_TIME);
	EXPECT_LT(0, __android_log_print(ANDROID_LOG_ERROR,
		"TEST__android_log_print",
		"error"));
	_sys_sleep(SLEEP_TIME);
	EXPECT_LT(0, __android_log_print(ANDROID_LOG_FATAL,
		"TEST__android_log_print",
		"fatal"));
	_sys_sleep(SLEEP_TIME);
	EXPECT_LT(0, __android_log_print(ANDROID_LOG_SILENT,
		"TEST__android_log_print",
		"silent"));
	_sys_sleep(SLEEP_TIME);
}

TEST(liblog, __android_log_is_loggable) {
	//IF_ALOGV() 
	{
	}
}