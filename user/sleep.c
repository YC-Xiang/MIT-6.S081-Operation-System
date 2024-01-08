#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
	int sum = 0;
	int ret = 0;

	if (argc == 1)
	{
		printf("Usage: sleep + <time>\n");
		exit(1);
	}

	for (int i = 1; i < argc; i++)
	{
		sum += atoi(argv[i]);
	}

	ret = sleep(sum);

	if (ret < 0)
	{
		printf("sleep system call return wrong!\n");
	}

	exit(0);
}
