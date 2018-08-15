
#include <initrc.h>

using namespace android;

int main(int argc, char** argv)
{
	InitRC::getInstance().Entry(argc, argv);

	InitRC::getInstance().Run();

	return 0;
}
