
// Implementation
// https://stackoverflow.com/questions/2494356/how-to-use-gettimeofday-or-something-equivalent-with-visual-studio-c-2008
//

#include <sys/time.h>

const unsigned __int64 DELTA_EPOCH_IN_MICROSECS = 116444736000000000ui64;

int gettimeofday(struct timeval *tv/*in*/, struct timezone *tz/*in*/)
{
	FILETIME ft;
	int rez = 0;

	ZeroMemory(&ft, sizeof(ft));
	GetSystemTimeAsFileTime(&ft);

#if 1
	unsigned __int64 tmpres = 0;
	tmpres = ft.dwHighDateTime;
	tmpres <<= 32;
	tmpres |= ft.dwLowDateTime;

	/*converting file time to unix epoch*/
	tmpres -= DELTA_EPOCH_IN_MICROSECS;
	tv->tv_sec  = (long)(tmpres / 10000000);
	tv->tv_usec = (long)(tmpres % 10000000) / 10;  /* microseconds */
	if (tv->tv_usec < 0) {
		return 0;
	}
#else
	SYSTEMTIME st;
	FileTimeToSystemTime(&ft, &st);

	tv->tv_sec = st.wHour*60*60 + st.wMinute*60 + st.wSecond;
	tv->tv_usec = st.wMilliseconds * 1000;
#endif
	/*
	TIME_ZONE_INFORMATION tz_winapi;
	ZeroMemory(&tz_winapi, sizeof(tz_winapi));
	//_tzset(),don't work properly, so we use GetTimeZoneInformation
	rez = GetTimeZoneInformation(&tz_winapi);
	tz->tz_dsttime = (rez == 2) ? true : false;
	tz->tz_minuteswest = tz_winapi.Bias + ((rez == 2) ? tz_winapi.DaylightBias : 0);
	*/

	return 0;
}

void usleep(DWORD waitTime)
{
	HANDLE timer;
	LARGE_INTEGER ft;

	ft.QuadPart = -(10 * waitTime); // Convert to 100 nanosecond interval, negative value indicates relative time

	timer = CreateWaitableTimer(NULL, TRUE, NULL);
	SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
	WaitForSingleObject(timer, INFINITE);
	CloseHandle(timer);
}

int clock_nanosleep(int clock_id, int flags,
	const struct timespec *request,
	struct timespec *remain)
{

	return 0;
}

int nanosleep(const struct timespec *req, struct timespec *rem)
{
	if (req) {
		DWORD usec = req->tv_sec * 1000 + req->tv_nsec / 1000;
		usleep(usec);
	}

	if (rem) {
		rem->tv_sec = 0;
		rem->tv_nsec = 0;
	}

	return 0;
}

#if 0
int clock_gettime(clockid_t clk_id, struct timespec *ts)
{
	if (!ts) {
		return -1;
	}

	struct timeval tv;
	gettimeofday(&tv, NULL);
	ts->tv_sec = tv.tv_sec;
	ts->tv_nsec = tv.tv_usec * 1000;

	return 0;
}
#endif
