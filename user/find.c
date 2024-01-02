#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int find(char *path, char *file)
{
	int fd;
	struct stat st;

	if((fd = open(path, 0)) < 0){
		fprintf(2, "find: cannot open %s\n", path);
		return -1;
	}

	if(fstat(fd, &st) < 0){
		fprintf(2, "find: cannot stat %s\n", path);
		close(fd);
		return -1;
	}


}

int main(int argc, char *argv[])
{
	int ret;

	if (argc == 1 || argc > 4)
	{
		printf("usage: find [path] [file]\n");
		exit(0);
	}

	if (find(argv[1], argv[2]) < 0)
	{
		printf("find function return error\n");
		exit(0);
	}
	exit(0);
}
