#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

char str[4096];

int main(void)
{
    int fd[2], fp, i = 3;
    int len = 0;
    pid_t pid;

    if (pipe(fd) != 0) 
    {
        perror("pipe");
        exit(-1);
    }
    pid = fork();
    while (i--)
    {
        if (pid == 0) 
        {
            close(fd[0]);
            //        strcpy(str, "hello");
            fgets(str, sizeof(str), stdin);
            write(fd[1], str, strlen(str));
            //           sleep(3);
        }
        else if (pid > 0)
        {
            close(fd[1]);
            fp = open("hel", O_RDWR);
            if (fp < 0) 
            {
                perror("open failed");
                exit(-1);
            }
            len = read(fd[0], str, sizeof(str));
            write(fp, str, len);
            //        write(STDOUT_FILENO, "\n", 1);
            wait(NULL);
            close(fp);
        }
        else
        {
            perror("fork");
            exit(-1);
        }
    }

    return 0;
}
