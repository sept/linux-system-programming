#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sighandler(int num)
{
    wait(NULL);
}
int main(void)
{
    struct sigaction sig_set;
    pid_t pid1, pid2, pid3;
    int i = 4, m = 4;

    pid1 = fork();

    sigfillset(&sig_set.sa_mask);
    sig_set.sa_handler = sighandler;
    sig_set.sa_flags = 0;
    if (pid1 == 0) 
    {
        while (i--)
        {
            printf("I am child\n");
            sleep(3);
        }
        sigaction(17, &sig_set, NULL);
    }
    else if (pid1 > 0)
    {
        /*        pid2 = fork();
                  if (pid2 == 0)
                  {
                  while (m--)
                  {
                  printf("I am child two\n");
                  sleep(2);
                  }
                  sigaction(17, &sig_set, NULL);
                  }
                  else if (pid2 < 0) 
                  {
                  perror("fork pid2");
                  exit(-2);
                  }
         */
        while (1)
        {
            printf("I am father one \n");
            sleep(2);
        }
    }
    else
    {
        perror("fork .");
        exit(-1);
    }

    return 0;
}
