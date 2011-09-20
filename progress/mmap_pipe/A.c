#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>

int main(void)
{
    char *src;
    int fd;
    struct stat filedp;

    fd = open("m_file", O_RDWR);
    if (fd < 0) 
    {
        perror("open failed");
        exit(-1);
    }
    fstat(fd, &filedp);
    src = mmap(NULL, filedp.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (src == MAP_FAILED) 
    {
        perror("mmap src");
        exit(-1);
    }
    while (*src != '\0')
    {
        printf("%d\n", *src);
        sleep(3);
        src++;
    }
    munmap(src, filedp.st_size);
    close(fd);

    return 0;
}
