#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>

int main(void)
{
    int fd;

    fd = open("m_file", O_RDWR);
    if (fd < 0) 
    {
        perror("open failed");
        exit(-1);
    }
    lseek(fd, 4095, SEEK_SET);
    write(fd, "1", 1);
    close(fd);
    return 0;
}
