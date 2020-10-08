
#include <initrc/initrc.h>

int main(int argc, char** argv)
{
    InitRC_set(M_PROPERTY_BOOT_ANIMATION_TIME_SEC, "3");

	InitRC_entry(argc, argv);

	InitRC_run();

	return 0;
}
