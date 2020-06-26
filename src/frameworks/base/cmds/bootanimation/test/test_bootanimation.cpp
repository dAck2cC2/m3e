
#include <initrc/initrc.h>

int main(int argc, char** argv)
{
    InitRC_set("run.start.bootanim", "true");

	InitRC_entry(argc, argv);

	InitRC_run();

	return 0;
}
