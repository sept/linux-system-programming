#if 1 
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main(int argc, char *argv[])
{
	int srcfd, destfd;
	int *src, *dest;
	struct stat filedp;

	if (argc != 3)
	{
		printf("./a.out src dest\n");
		exit(-1);
	}
	srcfd = open(argv[1], O_RDONLY);
	if (srcfd < 0)
	{
		perror("open src");
		exit(1);
	}
	fstat(srcfd, &filedp);
	destfd = open(argv[2], O_RDWR | O_CREAT | O_EXCL, 0644);
	if (destfd < 0)
	{
		perror("open dest");
		exit(-1);
	}
	lseek(destfd, filedp.st_size-1, SEEK_SET);
	write(destfd, "1", 1);
	src = mmap(NULL, filedp.st_size, PROT_READ, MAP_SHARED, srcfd, 0);
	if (src == MAP_FAILED)
	{
		perror("mmap src\n");
		exit(-1);
	}
	dest = mmap(NULL, filedp.st_size, PROT_WRITE | PROT_READ, MAP_SHARED, destfd, 0);
	if (dest == MAP_FAILED)
	{
		perror("mmap dest\n");
		exit(-1);
	}
	memcpy(dest, src, filedp.st_size);
	munmap(src, filedp.st_size);
	munmap(dest, filedp.st_size);
	close(srcfd);
	close(destfd);

	return 0;
}
#endif

#if 0 
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>

int main(void)
{
	int *p;
	int fd = open("hello", O_RDWR);
	if (fd < 0) {
		perror("open hello");
		exit(1);
	}
	p = mmap(NULL, 6, PROT_WRITE, MAP_SHARED, fd, 0);
	if (p == MAP_FAILED) {
		perror("mmap");
		exit(1);
	}
	close(fd);
	p[0] = 0x30313233;
	munmap(p, 6);
	return 0;
}

#endif
