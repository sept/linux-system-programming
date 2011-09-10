#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>

int main (int argc, char *argv[])
{
	int srcfd, destfd;
	int len;
	char buf[4096];

	srcfd = open(argv[1], O_RDONLY);
	if (srcfd < 0)
	{
		perror("open src");
		exit(-1);
	}
	destfd = open(argv[2], O_RDWR | O_CREAT | O_EXCL, 0777);
	if (destfd < 0)
	{
		perror("open dest");
		exit(-1);
	}
	while (len = read(srcfd, buf, sizeof(buf)))
	{
		write(destfd, buf, len);
	}
	close(srcfd);
	close(destfd);

	return 0;
}

