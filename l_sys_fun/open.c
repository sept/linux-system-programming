#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

void sys_err(char *ptr)
{
	write(1, ptr, strlen(ptr));
	exit(-1);
}

int main(int argc, char *argv[])
{
	int fd = 0;
	if (argc != 2)
	{
		sys_err("./a.out file's name\n");
	}
	fd = open(argv[1], O_RDWR);
	if (fd < 0)
	{
		sys_err("open file failed~!\n");
	}
	close(fd);
	return 0;
}
