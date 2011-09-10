#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>

int main(void)
{
	int fd;

	fd = open("aaa", O_RDWR);
	if (fd < 0)
	{
		perror("open aaa");
		exit(-1);
	}
//	lseek(fd, 10, SEEK_SET);
	write(fd, "abc", 1);
	close(fd);
	return 0;
}
