#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

char str[1024];
void sighandler(int num)
{
    waitpid(-1, NULL, WNOHANG);
    printf("#####################\n");
}
int main(int argc, char *argv[])
{
    int fd1, fd2;
    int len;
    pid_t pid;
    struct stat buf;
    struct sigaction sig_set;

    sigfillset(&sig_set.sa_mask);
    sig_set.sa_handler = sighandler;
    sig_set.sa_flags = 0;

    if (argc != 3) 
    {
        printf("please input ./a.out src dest ");
        exit(1);
    }

    fd1 = open(argv[1], O_RDONLY);
    if (fd1 < 0) 
    {
        perror("open argv[1] failed");
        exit(-1);
    }
    fstat(fd1, &buf);
    fd2 = open(argv[2], O_RDWR | O_CREAT, 0777);
    if (fd2 < 0) 
    {
        perror("open argv[2] failed");
        exit(-1);
    }

    pid = fork();
    if (pid > 0) 
    {
        pid = fork();
        if (pid > 0) 
        {
            pid = fork();
            if (pid > 0) 
            {
                while (1)
                {
                    sigaction(17, &sig_set, NULL);
                    printf("I am father\n");
                    sleep(2);
                }
            }
            else if (pid == 0)
            {
                lseek(fd1, buf.st_size/3, SEEK_SET);
                lseek(fd2, buf.st_size/3, SEEK_SET);
                len = read(fd1, str, buf.st_size/3);
                write(fd2, str, len);
            }
            else
            {
                perror("fork 333");
                exit(-1);
            }
        }
        else if (pid == 0)
        {
            lseek(fd1, buf.st_size*2/3, SEEK_SET);
            lseek(fd2, buf.st_size*2/3, SEEK_SET);
            len = read(fd1, str, buf.st_size/3);
            write(fd2, str, len);
        }
        else
        {
            perror("fork 22");
            exit(-1);
        }
    }
    else if (pid == 0)
    {
        lseek(fd1, 0, SEEK_SET);
        lseek(fd2, 0, SEEK_SET);
        len = read(fd1, str, buf.st_size/3);
        write(fd2, str, len);
    }
    else
    {
        perror("fork 111");
        exit(-2);
    }
    close(fd1);
    close(fd2);
    return 0;
}
