
#if defined(_MSC_VER)
#include <windows.h>
#endif

#include <string>

std::string backtrace_string(const uintptr_t* frames, size_t frame_count)
{
	std::string result;
	return result;
}
