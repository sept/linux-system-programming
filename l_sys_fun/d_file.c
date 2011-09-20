#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

#define MAX_PATH 1024

void dirwalk(char *dir, void (*fcn)(char *))
{
	char name[MAX_PATH];
	struct dirent *dp;
	DIR *dfd;

	if ((dfd = opendir(dir)) == NULL)
	{
		fprintf(stderr, "dirwalk: can't open %s\n", dir);
		return;
	}
	while ((dp = readdir(dfd)) != NULL)
	{
		if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
			continue;
		if (strlen(dir)+strlen(dp->d_name)+2 > sizeof(name))
		{
			fprintf(stderr, "dirwalk: name %s %s too long\n", dir, dp->d_name);
		}
		else
		{
			sprintf(name, "%s/%s", dir, dp->d_name);
			(*fcn)(name);
		}
	}
	closedir(dfd);
}

void fsize(char *name)
{
	struct stat stbuf;
/*注意此处使用的lstat与stat区别*/
/*若为软链接 则使用stat 会使程序成为死循环*/
/*而lstat 不跟踪软链接 故不会造成死循环*/
//	if (stat(name, &stbuf) == -1)
	if (lstat(name, &stbuf) == -1)
	{
		fprintf(stderr, "fsize: can't access %s\n", name);
		return;
	}
	if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
		dirwalk(name, fsize);
	printf("%8ld %s\n", stbuf.st_size, name);
}

int main(int argc, char *argv[])
{
	if (argc == 1)
		fsize(".");
	else
		while (--argc > 0)
			fsize(*++argv);
	return 0;
}
