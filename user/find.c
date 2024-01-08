#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int find(char *path, char *file)
{
	int fd;
	char buf[512], *p;
	struct stat st;
	struct dirent de;

	if ((fd = open(path, 0)) < 0){
		fprintf(2, "find: cannot open %s\n", path);
		return -1;
	}

	strcpy(buf, path);
	p = buf+strlen(buf);
	*p++ = '/';

	while (read(fd, &de, sizeof(de)) == sizeof(de)) { /// read all file in fd
		if(de.inum == 0) /// what does inum represents???
			continue;
		memmove(p, de.name, DIRSIZ);
		if (!strcmp(de.name, ".") || !strcmp(de.name, "..")) /// skip . and ..
			continue;
		p[DIRSIZ] = 0;

		if(stat(buf, &st) < 0) {
			printf("find: cannot stat %s\n", buf);
			continue;
		}

		switch (st.type)
		{
		case T_DIR:
			find(buf, file);
			break;
		case T_FILE:
		case T_DEVICE:
			if (!strcmp(file, de.name))
			{
				printf("%s\n", buf);
			}
			break;
		}
	}

	return 0;

}

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("usage: find [path] [file]\n");
		exit(1);
	}

	if (find(argv[1], argv[2]) < 0)
	{
		exit(1);
	}
	exit(0);
}
