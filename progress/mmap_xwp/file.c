#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>

int main(void)
{
	int fd;
	fd = open("filemap", O_CREAT|O_RDWR, 0644);
	if (fd < 0) {
		perror("open file");
		exit(-1);
	}
	lseek(fd, 4095, SEEK_SET);
	write(fd, "1", 1);
	close(fd);

	return 0;
}
