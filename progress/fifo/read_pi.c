#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main(void)
{
    int fp, n;
    char array[4096];    

    fp = open("pifo", O_RDONLY);
    if (fp < 0) 
    {
        perror("open failed");
        exit(-1);
    }
    while (1) 
    {
        n = read(fp, array, 4096);
        write(STDOUT_FILENO, array, n);
    }
    close(fp);

    return 0;
}
