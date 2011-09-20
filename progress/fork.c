#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    pid_t pid;

    pid = fork();
    if (pid == 0) 
    {
        printf("I am child\n");
        sleep(4);
    }
    else if(pid > 0)
    {
        printf("I am father\n");
        sleep(2);
    }
    else
    {
        perror("fork failed");
        exit(-1);
    }

    return 0;
}
