#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>

char str[4096];

int main(void)
{
    int fd;

    fd = open("pifo", O_WRONLY);
    if (fd < 0) 
    {
        perror("open failed");
        exit(-1);
    }
    while (1)
    {
        fgets(str, sizeof(str), stdin);
        write(fd, str, strlen(str));
        sleep(3);
    }
    close(fd);
    return 0;
}
