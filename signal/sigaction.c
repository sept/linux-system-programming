#include <stdio.h>
#include <signal.h>

void sig(int num)
{
    printf("%d\n", num);
    printf("111\n");
}

int main(void)
{
    struct sigaction sig_set;

//    sigemptyset(&sig_set.sa_mask);
    sigfillset(&sig_set.sa_mask);
    sig_set.sa_handler = sig;
    sig_set.sa_flags = 0;

    sigaction(2, &sig_set, NULL);

    while (1)
    {
        printf("aaa\n");
        sleep(1);
    }
    return 0;
}
